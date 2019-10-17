fun main(args: Array<String>) {
    val pageList = mutableListOf<Int>(1, 1, 2, 3, 4, 5, 6)
    println((1..10).filterNot { it in pageList })
    println(pageList.groupBy { it }.filterNot { it.key in 1..10 })
}