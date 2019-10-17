//fun main(args: Array<String>) {
//    val clz1 = Int::class
//    val fn2 = ::add
//    val fn1: ((Double, Double) -> Double)? = null
//    println(fn2.call(1,2))
//}
//
//public fun add(a: Double, b:  ble) = a + b

import java.util.*

interface Subject {
    fun hello()
}

class RealSubject(val name: String) : Subject {
    override fun hello() {
        val now = Date()
        println("Hello, REAL $name! Now is $now")
    }
}

class ProxySubject(val sb: Subject):Subject by sb {
    override fun hello() {
        println("Before ! Now is ${Date()}")
        sb.hello()
        println("After ! Now is ${Date()}")
    }
}

fun main(args: Array<String>) {
    val subject = RealSubject("World")
    subject.hello()
    println("-------------------------")
    val proxySubject = ProxySubject(subject)
    proxySubject.hello()
}