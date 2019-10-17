package test

import java.io.BufferedInputStream
import java.io.FileInputStream
import javax.swing.JFrame

fun main(args: Array<String>) {
    BufferedInputStream(FileInputStream("")).use {

    }
}

class MyFrame(title: String) : JFrame(title) {
    init {
        println(title)
        setSize(100, 100)
        isVisible = true
    }
}