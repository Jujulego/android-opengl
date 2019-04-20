package net.capellari.julien.threed

import net.capellari.julien.threed.jni.JNIClass
import net.capellari.julien.threed.math.D2
import net.capellari.julien.threed.math.Point
import net.capellari.julien.threed.math.coordX
import net.capellari.julien.threed.math.coordY

class Point2i: JNIClass, Point<Int,D2> {
    // Companion
    companion object {
        // Méthodes
        @JvmStatic
        private external fun create(x: Int = 0, y: Int = 0): Long
    }

    // Propriétés
    var x by coordX()
    var y by coordY()

    // Constructeurs
    private constructor(handle: Long): super(handle)

    constructor(): this(create())
    constructor(x: Int, y: Int): this(create(x, y))

    // Opérateurs
    override operator fun get(i: Int)         = getCoord(i)
    override operator fun set(i: Int, v: Int) = setCoord(i, v)

    override fun unaryPlus()  = Point2i(plus())
    override fun unaryMinus() = Point2i(minus())

    // Méthodes
    override fun equals(other: Any?): Boolean {
        if (other is Point2i) {
            return equal(other)
        }

        return false
    }
    override fun hashCode(): Int {
        return (x shl 32) + y
    }

    private external fun getCoord(i: Int): Int
    private external fun setCoord(i: Int, v: Int)

    private external fun equal(other: Point2i): Boolean

    private external fun plus(): Long
    private external fun minus(): Long
}