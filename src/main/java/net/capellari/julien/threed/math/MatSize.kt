package net.capellari.julien.threed.math

// Classes
class MatSize<D1: Dimension, D2: Dimension>(d1: D1, d2: D2) {
    // Attributs
    val col = d1.size
    val lig = d2.size

    val size = d1.size * d2.size

    // Méthodes
    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (other is MatSize<*, *>) {
            return other.col == col && other.lig == lig
        }

        return false
    }

    override fun hashCode(): Int {
        var result = col
        result = 31 * result + lig
        return result
    }
}