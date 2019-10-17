import kotlin.properties.Delegates

fun main(args: Array<String>) {
    var a: Int by Delegates.notNull()
    println(a)      //运行时抛出IllegalStateException异常
    a = 1
    println(a)
}
