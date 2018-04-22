fun main(args: Array<String>) {

//    val ss = "我1231是2131中国故12国国故123"
//    val r1 = Regex("""[\u4e00-\u9fa5]+[0-9]+""")
//    val result = r1.findAll(ss)
//    val b = result.mapTo(mutableListOf()) { it.value }
////    b.forEach { println(it) }
//    result.groupBy {  }.forEach {
//        print(it.key)
//        print(":")
//        it.value.forEach { print(it.value + " ") }
//        println()
//    }

//    val words = listOf("a", "abc", "ab", "def", "abcd")
////    val byLength = words.groupBy(keySelector = { it.length }, valueTransform = { it.toUpperCase() })
//    val a = words.mapIndexed { key, value -> key to value }
//    val byLength = a.groupBy { (key, value) -> key }
//            .map { (key, value) -> key to value.map { it.second } }

    val words = listOf("a", "abc", "ab", "def", "abcd")
    val byLength = words.groupIndexedBy({ index, _ -> index }, { index, value ->
        if (index % 2 == 0) {
            value.toUpperCase()
        } else {
            value.toLowerCase()
        }
    })

    byLength.forEach { (key, value) ->
        print("$key:")
        value.forEach { print("$it ") }
        println()
    }
}

inline fun <T, K> Iterable<T>.groupIndexedBy(keySelector: (index: Int, value: T) -> K): Map<K, List<T>> {

    var i = 0
    return this.groupBy { keySelector(i++, it) }
}

inline fun <T, K, V> Iterable<T>.groupIndexedBy(keySelector: (index: Int, value: T) -> K, valueTransform: (index: Int, value: T) -> V): Map<K, List<V>> {

    var i = 0
    return this.groupBy({ keySelector(i, it) }, { valueTransform(i++, it) })
} 