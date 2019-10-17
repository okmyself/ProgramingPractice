fun main(args: Array<String>) {
    println(plus(1,5,1,0))
}

tailrec fun plus(start: Int, end: Int, increment: Int, result: Int): Int =
if(start >= end)
    result
else
    plus(start + increment, end, increment, start + result)