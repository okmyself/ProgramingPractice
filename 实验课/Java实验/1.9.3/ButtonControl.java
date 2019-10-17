import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.io.Reader;
class ButtonControl extends Frame implements ActionListener {
    Button btnDisplay;
    Label lblMsg;
    public ButtonControl() {
        super("按钮控件演示程序");
        btnDisplay = new Button("显示消息");
        lblMsg = new Label("");
        add(btnDisplay, BorderLayout.NORTH);
        add(lblMsg);
        btnDisplay.addActionListener(this);
        setSize(200, 200);
        setVisible(true);
    }
    public void actionPerformed(ActionEvent ae) {
        if(ae.getActionCommand().equals("显示消息")) {
            btnDisplay.setLabel("隐藏消息");
            lblMsg.setText("你好,世界!");
        } else if (ae.getActionCommand().equals("隐藏消息")) {
            btnDisplay.setLabel("显示消息");
            lblMsg.setText("");
        }
    }
    public static void main(String[] args) {
        new ButtonControl();
    }
}