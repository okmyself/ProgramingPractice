//WindowCloser.java用来关闭GUI窗口
import java.awt.event.*;
public class WindowCloser extends WindowAdapter {
    public void windowClosing(WindowEvent e) {
        System.exit(0);
    }
}