package 第二次作业;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

//棋盘Panel所在的Frame
public class ChineseChess extends JFrame {
    ChessPainter chessPanel;
    ChineseChess(Client client, int number) {
        int result = client.connect(number);
        if (result == 1) chessPanel = new ChessBoard(Color.RED, client);        //等待对方
        else if (result == 2) chessPanel = new ChessBoard(Color.BLACK, client); //开始
        else {
            client.close();
            JOptionPane.showMessageDialog(this, "该序号已经存在对局！", "错误：", JOptionPane.ERROR_MESSAGE);
            dispose();
        }
        chessPanel.repaint();

        add(chessPanel);
        pack();
        setResizable(false);
        setVisible(true);
        chessPanel.repaint();
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                if (JOptionPane.showConfirmDialog(null, "确认要退出吗？", "信息：", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
                    System.exit(0);
                }
            }
        });
    }
}
