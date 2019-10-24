package 第二次作业;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.Socket;

public class Client {
    private Socket client = new Socket("114.116.73.229", 4331);

    private ObjectInputStream in;
    private ObjectOutputStream out;

    public Client() throws IOException {
        if (client == null) throw new IOException("Connecting failed!");
        out = new ObjectOutputStream(client.getOutputStream());
        in = new ObjectInputStream(client.getInputStream());
    }

    //返回整数1代表红方，2代表黑方，0表示失败
    public int connect(int number) {
        try {
            System.out.println(out);
            out.writeObject(number);      //向服务器写出配对序号
            int n = (Integer) in.readObject();
            if (n != 0) {
                System.out.println("正在进行配对...");
                if ((Boolean) in.readObject()) {
                    return n;
                }
            }
            return 0;
        } catch (IOException | ClassNotFoundException e) {
            return 0;
        }
    }

    public void send(int x1, int y1, int x2, int y2) {
        try {
            System.out.println("发出：from: (" + x1 + ", " + y1 + "), to: (" + x2 + ", " + y2 + ")");
            out.writeObject(new PlayChess(x1, y1, x2, y2));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public PlayChess receive() {
        try {
            PlayChess playChess = (PlayChess) in.readObject();
            System.out.println("收到：" + playChess);
            return playChess;
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] args) {
        JFrame myApp = new JFrame("联机");
        myApp.setLayout(new BorderLayout());
        JTextField jtf = new JTextField(20);
        JButton btn = new JButton("确定");
        myApp.add(new JLabel("请和伙伴输入同一个数字，点击确定匹配进入"), BorderLayout.NORTH);
        myApp.add(jtf, BorderLayout.CENTER);
        myApp.add(btn, BorderLayout.SOUTH);
        myApp.pack();
        myApp.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        myApp.setVisible(true);
        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    myApp.dispose();
                    new ChineseChess(new Client(), Integer.parseInt(jtf.getText()));
                } catch (IOException e1) {
                    JOptionPane.showMessageDialog(myApp, "连接服务器失败！", "错误：", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
    }

    public ObjectInputStream getIn() { return in; }

    public ObjectOutputStream getOut() { return out; }

    //关闭流
    public void close() {
        try {
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
