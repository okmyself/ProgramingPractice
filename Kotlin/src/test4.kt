class Person(var name: String = "", var age: Int = 0) {
    infix fun test(str: String) {
        println(str)
    }
}

fun task(block: Person.() -> Unit) {
    var p = Person()
    block(p)
}

fun main(args: Array<String>) {
     task {
         this test "ok"
         test("ok")
         this.test("ok")
     }
}