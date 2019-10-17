//Java代码
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ButtonClick {
    public static void main(String[] args) {
        Frame frame = new Frame("按钮单击事件");
        Button btn = new Button("按钮");
        frame.add(btn);
        frame.pack();
        frame.setVisible(true);
        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("按钮被单击");
            }
        });
    }
}
