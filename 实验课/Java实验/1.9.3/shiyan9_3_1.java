import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class shiyan9_3_1 extends JFrame implements ActionListener {
    private JLabel label;
    private JPanel panel1, panel2;
    private JTextField textField;
    private JButton button1, button2;

    shiyan9_3_1() {
        super("文本框Action事件测试");
        setLayout(new BorderLayout());
        label = new JLabel("姓名:");
        panel1 = new JPanel();
        panel2 = new JPanel();
        panel1.setLayout(new FlowLayout());
        panel2.setLayout(new FlowLayout());
        textField = new JTextField(50);
        button1 = new JButton("确定");
        button2 = new JButton("清除");
        panel1.add(label); panel1.add(textField);
        panel2.add(button1); panel2.add(button2);
        add(panel1, BorderLayout.NORTH); add(panel2, BorderLayout.CENTER);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();
        setVisible(true);
        button1.addActionListener(this);
        button2.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
        Object obj = e.getSource();
        if(obj == button1)
            textField.setText("你好," + textField.getText() + ",欢迎你使用Java编程!");
        if(obj == button2)
            textField.setText("");
    }

    public static void main(String[] args) {
        new shiyan9_3_1();
    }
}