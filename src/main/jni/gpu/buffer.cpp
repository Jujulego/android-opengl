//
// Created by julien on 29/08/2019.
//
#include <memory>

#include <android/log.h>
#include <GLES3/gl32.h>

#include "buffer.h"
#include "jnitools.h"
#include "macros.h"

#define LOG_DEBUG(...) __android_log_print(ANDROID_LOG_DEBUG, "gpu::Buffer", __VA_ARGS__)

using namespace gpu;

// Constructor
Buffer::Buffer() {
    generate();
}

// Destructor
Buffer::~Buffer() {
    destroy();
}

// Methods
void Buffer::generate() {
    glGenBuffers(1, &m_buffer);
}

void Buffer::destroy() {
    unbind();
    glDeleteBuffers(1, &m_buffer);
}

void Buffer::regenerate() {
    destroy();
    generate();
}

void Buffer::bind(GLenum const& target) {
    glBindBuffer(target, m_buffer);
    m_target = target;
}

void Buffer::setData(Bufferable const& data, GLenum const& usage) {
    if (m_target != GL_INVALID_ENUM) {
        glBufferData(m_target, data.getBufferSize(), data.getData(), usage);
    }
}

void Buffer::setData(void const* data, GLsizeiptr size, GLenum const& usage) {
    if (m_target != GL_INVALID_ENUM) {
        glBufferData(m_target, size, data, usage);
    }
}

void Buffer::setDataArray(BufferableArray const& data, GLenum const& usage) {
    if (m_target != GL_INVALID_ENUM) {
        glBufferData(m_target, data.getBufferSize(), nullptr, usage);

        GLintptr offset = 0;
        for (size_t i = 0; i < data.getBufferElementCount(); ++i) {
            Bufferable const& el = data.getBufferElement(i);

            glBufferSubData(m_target, offset, el.getBufferSize(), el.getData());
            offset += el.getBufferSize();
        }
    }
}

void Buffer::unbind() {
    if (m_target != GL_INVALID_ENUM) {
        glBindBuffer(m_target, 0);
        m_target = GL_INVALID_ENUM;
    }
}

// JNI
extern "C" JNIEXPORT
jlong JNICALL METH_NAME(Buffer, create)(JNIEnv*, jclass) {
    auto pt = std::make_shared<Buffer>();
    pt->register_jni(true);

    return pt->get_jhandle();
}

extern "C" JNIEXPORT
void JNICALL METH_NAME(Buffer, regenerate)(JNIEnv* env, jobject jthis) {
    auto pt = jni::fromJava<Buffer>(env, jthis);
    pt->regenerate();
}

extern "C" JNIEXPORT
void JNICALL METH_NAME(Buffer, nbind)(JNIEnv* env, jobject jthis, jint target) {
    auto pt = jni::fromJava<Buffer>(env, jthis);
    pt->bind(target);
}

extern "C" JNIEXPORT
void JNICALL METH_NAME(Buffer, setNData)(JNIEnv* env, jobject jthis, jobject jdata, jint usage) {
    auto pt = jni::fromJava<Buffer>(env, jthis);
    auto data = jni::fromJava<Bufferable>(env, jdata);

    pt->setData(*data, usage);
}

extern "C" JNIEXPORT
void JNICALL METH_NAME(Buffer, setJData___3II)(JNIEnv* env, jobject jthis, jintArray jdata, jint usage) {
    auto pt = jni::fromJava<Buffer>(env, jthis);
    auto data = jni::array<jintArray>(env, jdata);

    pt->setData(data.data(), data.size() * sizeof(jint), usage);
}

extern "C" JNIEXPORT
void JNICALL METH_NAME(Buffer, setNDataArray)(JNIEnv* env, jobject jthis, jobject jdata, jint usage) {
    auto pt = jni::fromJava<Buffer>(env, jthis);
    auto data = jni::fromJava<BufferableArray>(env, jdata);

    pt->setDataArray(*data, usage);
}

extern "C" JNIEXPORT
void JNICALL METH_NAME(Buffer, unbind)(JNIEnv* env, jobject jthis) {
    auto pt = jni::fromJava<Buffer>(env, jthis);
    pt->unbind();
}