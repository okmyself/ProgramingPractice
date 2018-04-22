fun main(args: Array<String>) {

    val map = mapOf<Int, String>(1 to "a", 2 to "b", 3 to "c", 4 to "d")
    for ((key, value) in map) {
        println(value)
    }
}