import java.awt.*
import java.awt.event.KeyEvent
import java.io.File
import java.io.FileReader
import java.util.*
import javax.imageio.IIOException
import javax.imageio.ImageIO
import javax.swing.JFrame
import javax.swing.JPanel


fun main(args: Array<String>) {
    val properties = Properties()
    var timeDelay = 1000L
    var softwareName = "�齱���"
    var bgImagePath = "background.png"
    var logoImagePath = "logo.png"
    var bgColor = "FFFFFF"
    var logoWidth = 200
    var logoHeight = 200
    var message = "���˵��ǣ�"
    var messageColor = "000000"
    var messageFont = "����"
    var messageFontSize = 50
    var messageFontBold = 1
    var messageLeft = 250
    var messageTop = 150
    var idInitText = "���ո����ʼ�齱"
    var idColor = "000000"
    var idFont = "����"
    var idFontSize = 50
    var idFontBold = 1
    val data = mutableListOf<String>()

    FileReader("Config.txt").use {
        val buffer = it.buffered()
        properties.load(buffer)
        timeDelay = properties.getProperty("time_delay", timeDelay.toString()).toLong()
        softwareName = properties.getProperty("software_name", softwareName)
        bgImagePath = properties.getProperty("background_image", bgImagePath)
        logoImagePath = properties.getProperty("logo_image", logoImagePath)
        bgColor = properties.getProperty("background_color", bgColor)
        logoWidth = properties.getProperty("logo_width", logoWidth.toString()).toInt()
        logoHeight = properties.getProperty("logo_height", logoHeight.toString()).toInt()
        message = properties.getProperty("message", message)
        messageColor = properties.getProperty("message_color", messageColor)
        messageFont = properties.getProperty("message_font", messageFont)
        messageFontSize = properties.getProperty("message_font_size", messageFontSize.toString()).toInt()
        messageFontBold = properties.getProperty("message_font_bold", messageFontBold.toString()).toInt()
        messageLeft = properties.getProperty("message_left", messageLeft.toString()).toInt()
        messageTop = properties.getProperty("message_top", messageTop.toString()).toInt()
        idInitText = properties.getProperty("id_init_text", idInitText)
        idColor = properties.getProperty("id_color", idColor)
        idFont = properties.getProperty("id_font", idFont)
        idFontSize = properties.getProperty("id_font_size", idFontSize.toString()).toInt()
        idFontBold = properties.getProperty("id_font_bold", idFontBold.toString()).toInt()
    }

    FileReader("Data.txt").use {
        val buffer = it.buffered()
        buffer.forEachLine { line ->
            val pattern = "[1-9][0-9]{8}"
            val result = Regex(pattern).find(line)
            if(result?.groupValues != null)
                data.addAll(result.groupValues)
        }
    }

    val toolkit = Toolkit.getDefaultToolkit()
    val app = JFrame(softwareName)
    app.size = toolkit.screenSize
    app.location = Point(0, 0)
    app.isUndecorated = true

    var idText = idInitText
    var bgPanel: JPanel? = null
    try {
        val bgBufferedImage = ImageIO.read(File(bgImagePath))
        val logoBufferedImage = ImageIO.read(File(logoImagePath))
        val logoImage = logoBufferedImage.getScaledInstance(logoWidth, logoHeight, Image.SCALE_DEFAULT)     //����
        val bgHeight = bgBufferedImage.height * app.size.width / bgBufferedImage.width
        val bgImage = bgBufferedImage.getScaledInstance(app.size.width, bgHeight, Image.SCALE_DEFAULT)
        bgPanel = object : JPanel() {
            override fun paintComponent(g: Graphics?) {
                super.paintComponent(g)
                if (g != null) {
                    g.drawImage(logoImage, 0, 0, logoWidth, logoHeight, this)
                    g.drawImage(bgImage, 0, this.height - bgHeight, this.width, bgHeight, this)

                    g.font = Font(messageFont, if (messageFontBold == 0) Font.PLAIN else Font.BOLD, messageFontSize)
                    g.color = Color(Integer.parseInt(messageColor, 16))
                    g.drawString(message, messageLeft, messageTop)

                    g.font = Font(idFont, if (idFontBold == 0) Font.PLAIN else Font.BOLD, idFontSize)
                    g.color = Color(Integer.parseInt(idColor, 16))
                    g.drawString(idText, (app.width - g.font.width(idText)) / 2,
                            (app.height - g.font.height()) / 2)
                }
            }
        }
        bgPanel.background = Color(Integer.parseInt(bgColor, 16))
        app.add(bgPanel)
    } catch (e: IIOException) { }

    var flag: Boolean

    toolkit.addAWTEventListener({
        if (it is KeyEvent) {
            if (it.keyCode == KeyEvent.VK_ESCAPE) System.exit(0)
            else if (it.keyCode == KeyEvent.VK_SPACE) {
                if (it.id == KeyEvent.KEY_PRESSED) {
                    flag = true
                    Thread {
                        synchronized(toolkit) {
                            while (flag) {
                                idText = data[(Math.random() * data.size).toInt()]
                                bgPanel?.repaint()
                                Thread.sleep(timeDelay)
                            }
                        }
                    }.start()
                } else if(it.id == KeyEvent.KEY_RELEASED)
                    flag = false
            }
        }
    }, AWTEvent.KEY_EVENT_MASK)

    app.defaultCloseOperation = JFrame.EXIT_ON_CLOSE
    app.isVisible = true
}

fun Font.width(str: String): Int {
    val fm = sun.font.FontDesignMetrics.getMetrics(this)
    return (fm.stringWidth(str))
}

fun Font.height(): Int {
    val fm = sun.font.FontDesignMetrics.getMetrics(this)
    return fm.height
}