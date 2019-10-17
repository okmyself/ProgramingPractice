import java.awt.*;
import java.awt.event.*;

class shiyan9_3_2 extends Frame {
    Button sinButton, cosButton, exitButton;
    mycanvas canvas;
    shiyan9_3_2() {
        sinButton = new Button("SIN");
        cosButton = new Button("COS");
        exitButton = new Button("EXIT");
        canvas = new mycanvas();
        Panel panel = new Panel();
        setLayout(new BorderLayout());
        panel.setLayout(new FlowLayout());
        panel.add(sinButton);
        panel.add(cosButton);
        panel.add(exitButton);
        add(panel, BorderLayout.NORTH);
        add(canvas, BorderLayout.CENTER);
        ActionListener myActionListener = new MyActionAdapter();
        sinButton.addActionListener(myActionListener);
        cosButton.addActionListener(myActionListener);
        exitButton.addActionListener(myActionListener);
    }

    class MyActionAdapter implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            Object obj = e.getSource();
            if (obj == sinButton) {
                canvas.setFlag(1);
                canvas.repaint();
            } else if (obj == cosButton) {
                canvas.setFlag(2);
                canvas.repaint();
            } else if (obj == exitButton) {
                canvas.setFlag(3);
                canvas.repaint();
            }
        }
    }

    class mycanvas extends Canvas {
        private int flag;
        mycanvas() { flag = 0; }
        public int getFlag() { return flag; }
        public void setFlag(int i) { flag = i; }
        @Override
        public void paint(Graphics g) {
            super.paint(g);
            g.drawLine(1, 1, getWidth(), 1);
            g.drawLine(1, 1, 1, getHeight());
            int y0 = getHeight() / 2;   //原点位置
            g.drawLine(1, y0, getWidth(), y0);
            int A = 110;    //图象高度的一半
            switch(flag) {
                case 1:
                    //画sin
                    for(int i = 1; i <= 360; i++) {
                        int x = i;
                        int y = y0 - (int)(A * Math.sin(i * Math.PI / 180));
                        g.drawLine(x, y, x, y);
                    }
                    break;
                case 2:
                    //画cos
                    for(int i = 1; i <= 360; i++) {
                        int x = i;
                        int y = y0 - (int)(A * Math.cos(i * Math.PI / 180));
                        g.drawLine(x, y, x, y);
                    }
                    break;
                case 3:
                    System.exit(0);
                default: break;
            }
        }
    }

    public static void main(String[] args) {
        shiyan9_3_2 myFrame = new shiyan9_3_2();
        myFrame.setSize(400, 300);
        myFrame.setVisible(true);
        myFrame.addWindowListener(new WindowCloser());
    }
}