//Kotlin代码
import java.awt.*
import java.awt.event.ActionEvent
import java.awt.event.ActionListener

fun main(args: Array<String>) {
    val frame = Frame("按钮单击事件")
    val btn = Button("按钮")
    frame.add(btn)
    frame.pack()
    frame.isVisible = true
    btn.addActionListener(object : ActionListener {
        override fun actionPerformed(e: ActionEvent?) {
            println("按钮被单击")
        }
    })
}
