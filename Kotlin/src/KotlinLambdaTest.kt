fun main(args: Array<String>) {
    // Thread {
    //     repeat(10000) {
    //         println("Hello" + it)
    //     }
    // }.start()

    var strs = listOf("bb", "a", "cc")
    strs = strs.sortedBy { it.length }
    strs.forEach { println(it) }
}