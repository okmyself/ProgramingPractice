fun main(args: Array<String>) {
    // 执行test闭包的内容

    "abcde".start {
        println(length)
    }
}

fun <T, R> T.start(param: T.() -> R): T {
    param()
    return this
}