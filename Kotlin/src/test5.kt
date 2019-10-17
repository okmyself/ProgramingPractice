class Person(val name: String){
    infix fun 说(word: String){
        println("\"$name 说 $word\"")
    }
}

fun main(args: Array<String>) {
    val 老张 = Person("老张")
    老张 说 "小伙砸,你咋又调皮捏!"
}
