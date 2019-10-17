class Test {
    companion object {
        var a = 1
        val b = "abc"
        fun c() = b + a
    }
}

fun main(args: Array<String>) {
    //通过伴生对象名类访问，这种情况和普通的类内部的object对象相同
    println(Test.Companion.a)
    //访问伴生对象的成员可以省略伴生对象名
    println(Test.b)
    println(Test.c())
}