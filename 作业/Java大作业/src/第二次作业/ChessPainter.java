package 第二次作业;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;

//事件源类，用于棋盘和棋子作图以及处理事件的类
class ChessPainter extends JComponent implements MouseListener, MouseMotionListener {
    protected static int sideLength = 80;          //边长以及侧边长
    protected static int distanceToSide = 3;
    protected static double lengthRate = 0.10;
    protected Font borderFont = Util.loadFont(this, "WeibeiSC-Bold.otf", Font.PLAIN, 50);
    protected Font coordinateFont1 = Util.loadFont(this, "times.ttf", Font.PLAIN, 25);
    protected Font coordinateFont2 = Util.loadFont(this, "Libian.ttc", Font.PLAIN, 25);
    protected static Image background = Util.loadImage("res/background.jpeg");
    protected Chessman[][] chessmanData = new Chessman[9][10];
    public final Color playerColor;         //玩家使用的棋子颜色

//    private final List<ActionListener> actionListenerRepo = Collections.synchronizedList(new ArrayList<>());
//    private final List<MouseListener> mouseListenerRepo = Collections.synchronizedList(new ArrayList<>());
//    private final List<MouseMotionListener> mouseMotionListenerRepo = Collections.synchronizedList(new ArrayList<>());
    private final List<ChessPainterListener> listeners = Collections.synchronizedList(new ArrayList<>());   //Vector是线程安全的，ArrayList不是

    public ChessPainter(Color playerColor) {
        this.playerColor = playerColor;
        if (playerColor != Color.RED && playerColor != Color.BLACK) System.exit(-1);
        super.addMouseListener(this);
        super.addMouseMotionListener(this);
        setPreferredSize(new Dimension(sideLength * 10, sideLength * 11));
    }

    public void addListener(ChessPainterListener l) {
        if (l == null) return;
        synchronized (listeners) {
            listeners.add(l);
        }
    }
    public void removeListener(ChessPainterListener l) {
        if (l == null) return;
        synchronized (listeners) {
            listeners.remove(l);
        }
    }
    public void notifyListener(ChessPainterEvent e) {
        synchronized (listeners) {
            Iterator<ChessPainterListener> i = listeners.iterator();
            label:
            while (i.hasNext()) {
                ChessPainterListener listener = i.next();
                //执行所有的监听器
                switch (e.getEventType()) {
                    case MOUSE_EXITED: listener.mouseExited(e); break;
                    case MOUSE_ENTERED: listener.mouseEntered(e); break;
                    case MOUSE_PRESSED: listener.mousePressed(e); break;
                    case MOUSE_RELEASED: listener.mouseReleased(e); break;
                    case MOUSE_MOVED: listener.mouseMoved(e); break;
                    case MOUSE_DRAGGED: listener.mouseDragged(e); break;
                    case ACTION_PERFORMED: listener.actionPerformed(e); break;
                    default: break label;
                }
            }
        }
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        //处理鼠标单击棋子事件
        Point p = getPointFromPosition(getMousePosition(), playerColor);
        if (p == null) return;
        if (chessmanData[p.x][p.y] == null) chessmanData[p.x][p.y] = new Chessman();
        Chessman c = chessmanData[p.x][p.y];
        //src是棋子对象，可能为null；(x, y)是棋子的位置
        ChessPainterEvent cpe = new ChessPainterEvent(c, p.x , p.y , EVENT_TYPE.ACTION_PERFORMED);
        notifyListener(cpe);
    }

    @Override
    public void mouseMoved(MouseEvent e) {
        Point p = getPointFromPosition(getMousePosition(), playerColor);
        if (p == null) return;
        if (chessmanData[p.x][p.y] == null) chessmanData[p.x][p.y] = new Chessman();
        Chessman c = chessmanData[p.x][p.y];
        ChessPainterEvent cpe = new ChessPainterEvent(c, p.x, p.y, EVENT_TYPE.MOUSE_MOVED);
        notifyListener(cpe);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        Point p = getPointFromPosition(getMousePosition(), playerColor);
        if (p == null) return;
        if (chessmanData[p.x][p.y] == null) chessmanData[p.x][p.y] = new Chessman();
        Chessman c = chessmanData[p.x][p.y];
        ChessPainterEvent cpe = new ChessPainterEvent(c, p.x, p.y, EVENT_TYPE.MOUSE_PRESSED);
        notifyListener(cpe);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        Point p = getPointFromPosition(getMousePosition(), playerColor);
        if (p == null) return;
        if (chessmanData[p.x][p.y] == null) chessmanData[p.x][p.y] = new Chessman();
        Chessman c = chessmanData[p.x][p.y];
        ChessPainterEvent cpe = new ChessPainterEvent(c, p.x, p.y, EVENT_TYPE.MOUSE_RELEASED);
        notifyListener(cpe);
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        Point p = getPointFromPosition(getMousePosition(), playerColor);
        if (p == null) return;
        if (chessmanData[p.x][p.y] == null) chessmanData[p.x][p.y] = new Chessman();
        Chessman c = chessmanData[p.x][p.y];
        ChessPainterEvent cpe = new ChessPainterEvent(c, p.x, p.y, EVENT_TYPE.MOUSE_ENTERED);
        notifyListener(cpe);
    }

    @Override
    public void mouseExited(MouseEvent e) {
        notifyListener(new ChessPainterEvent(this, EVENT_TYPE.MOUSE_EXITED));
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        notifyListener(new ChessPainterEvent(this, EVENT_TYPE.MOUSE_DRAGGED));
    }

    //双缓冲绘图
    @Override
    protected void paintComponent(Graphics g) {
        int x1, y1, x2, y2;     //A(x1, y1), B(x2, y2)
        Graphics2D g2 = (Graphics2D) g;


        //画棋盘
        g2.setColor(new Color(220, 190, 160));
        g2.fillRect(0, 0, getWidth(), getHeight());
//        g2.drawImage(background, 0, 0, getWidth(), getHeight(), null);    //TODO:不知道为什么使用背景图片第一次加载时无效
        //外边框
//        g2.translate(0, 0);
        g2.setColor(Color.BLACK);
        g2.setStroke(new BasicStroke(4.0f));
        g2.drawLine((int) (sideLength - sideLength * lengthRate),
                (int) (sideLength - sideLength * lengthRate),
                (int) (sideLength - sideLength * lengthRate),
                (int) (10 * sideLength + sideLength * lengthRate));
        g2.drawLine((int) (sideLength - sideLength * lengthRate),
                (int) (sideLength - sideLength * lengthRate),
                (int) (9 * sideLength + sideLength * lengthRate),
                (int) (sideLength - sideLength * lengthRate));
        g2.drawLine((int) (sideLength - sideLength * lengthRate),
                (int) (10 * sideLength + sideLength * lengthRate),
                (int) (9 * sideLength + sideLength * lengthRate),
                (int) (10 * sideLength + sideLength * lengthRate));
        g2.drawLine((int) (9 * sideLength + sideLength * lengthRate),
                (int) (sideLength - sideLength * lengthRate),
                (int) (9 * sideLength + sideLength * lengthRate),
                (int) (10 * sideLength + sideLength * lengthRate));
        g2.setStroke(new BasicStroke(2.0f));
        //绘制棋盘横竖的线条
        for (int i = 1; i <= 10; i++) {
            x1 = sideLength;
            y1 = i * sideLength;
            x2 = 9 * sideLength;
            y2 = y1;
            g2.drawLine(x1, y1, x2, y2);
        }
        for (int i = 1; i <= 9; i++) {
            x1 = i * sideLength;
            y1 = sideLength;
            x2 = x1;
            y2 = 5 * sideLength;
            g2.drawLine(x1, y1, x2, y2);
            y1 = 6 * sideLength;
            y2 = 10 * sideLength;
            g2.drawLine(x1, y1, x2, y2);
        }
        x1 = sideLength;
        y1 = 5 * sideLength;
        x2 = x1;
        y2 = 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        x1 = 9 * sideLength;
        x2 = x1;
        g2.drawLine(x1, y1, x2, y2);
        //绘制将、帅位置交叉的线条
        x1 = 4 * sideLength;
        y1 = sideLength;
        x2 = 6 * sideLength;
        y2 = 3 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        x1 = x2;
        x2 = 4 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        y1 = 8 * sideLength;
        y2 = 10 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        x1 = 4 * sideLength;
        x2 = 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        //绘制炮、兵等初始位置的线条
        final int length = (int) (sideLength * lengthRate);
        //卒、兵
        for (int i = 0; i < 4; i++) {
            //右上-竖（A在B上）
            x1 = (2 * i + 1) * sideLength + distanceToSide;
            y2 = 4 * sideLength - distanceToSide;
            x2 = x1;
            y1 = y2 - length;
            g2.drawLine(x1, y1, x2, y2);
            y1 += 3 * sideLength;
            y2 += 3 * sideLength;
            g2.drawLine(x1, y1, x2, y2);
            //右上-横（A在B右）
            x1 = x2 + length;
            y1 = y2;
            g2.drawLine(x1, y1, x2, y2);
            y1 -= 3 * sideLength;
            y2 -= 3 * sideLength;
            g2.drawLine(x1, y1, x2, y2);
            //右下-横（A在B右）
            y1 += 2 * distanceToSide;
            y2 += 2 * distanceToSide;
            g2.drawLine(x1, y1, x2, y2);
            y1 += 3 * sideLength;
            y2 += 3 * sideLength;
            g2.drawLine(x1, y1, x2, y2);
            //右下-竖（A在B下）
            x1 = x2;
            y1 = y2 + length;
            g2.drawLine(x1, y1, x2, y2);
            y1 -= 3 * sideLength;
            y2 -= 3 * sideLength;
            g2.drawLine(x1, y1, x2, y2);

            //左上-竖（A在B上）
            x1 = (2 * i + 3) * sideLength - distanceToSide;
            y2 = 4 * sideLength - distanceToSide;
            x2 = x1;
            y1 = y2 - length;
            g2.drawLine(x1, y1, x2, y2);
            y1 += 3 * sideLength;
            y2 += 3 * sideLength;
            g2.drawLine(x1, y1, x2, y2);
            //左上-横（A在B左）
            x1 = x2 - length;
            y1 = y2;
            g2.drawLine(x1, y1, x2, y2);
            y1 -= 3 * sideLength;
            y2 -= 3 * sideLength;
            g2.drawLine(x1, y1, x2, y2);
            //左下-横（A在B左）
            y1 += 2 * distanceToSide;
            y2 += 2 * distanceToSide;
            g2.drawLine(x1, y1, x2, y2);
            y1 += 3 * sideLength;
            y2 += 3 * sideLength;
            g2.drawLine(x1, y1, x2, y2);
            //左下-竖（A在B下）
            x1 = x2;
            y1 = y2 + length;
            g2.drawLine(x1, y1, x2, y2);
            y1 -= 3 * sideLength;
            y2 -= 3 * sideLength;
            g2.drawLine(x1, y1, x2, y2);
        }
        //炮、砲
        //右上-竖
        x1 = 2 * sideLength + distanceToSide;
        x2 = x1;
        y2 = 3 * sideLength - distanceToSide;
        y1 = y2 - length;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        x1 += 6 * sideLength;
        x2 += 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        //右上-横
        x1 = x2 + length;
        y1 = y2;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        x1 -= 6 * sideLength;
        x2 -= 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        //右下-横
        y1 += 2 * distanceToSide;
        y2 += 2 * distanceToSide;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        x1 += 6 * sideLength;
        x2 += 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        //右下-竖
        x1 = x2;
        y1 = y2 + length;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        x1 -= 6 * sideLength;
        x2 -= 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        //左上-竖
        x1 = 2 * sideLength - distanceToSide;
        x2 = x1;
        y2 = 3 * sideLength - distanceToSide;
        y1 = y2 - length;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        x1 += 6 * sideLength;
        x2 += 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        //左上-横
        x1 = x2 - length;
        y1 = y2;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        x1 -= 6 * sideLength;
        x2 -= 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        //左下-横
        y1 += 2 * distanceToSide;
        y2 += 2 * distanceToSide;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        x1 += 6 * sideLength;
        x2 += 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        //左下-竖
        x1 = x2;
        y1 = y2 + length;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        x1 -= 6 * sideLength;
        x2 -= 6 * sideLength;
        g2.drawLine(x1, y1, x2, y2);
        g2.drawLine(x1, y1 + 5 * sideLength, x2, y2 + 5 * sideLength);
        //楚河·汉界
        int y = (int) (5.5 * sideLength);
        int x = 3 * sideLength;
        g2.rotate(-Math.PI / 2, x, y);
        Util.drawString("楚", g2, borderFont, x, y);
        g2.rotate(Math.PI / 2, x, y);
        x = 4 * sideLength;
        g2.rotate(-Math.PI / 2, x, y);
        Util.drawString("河", g2, borderFont, x, y);
        g2.rotate(Math.PI / 2, x, y);
        x = 7 * sideLength;
        g2.rotate(Math.PI / 2, x, y);
        Util.drawString("漢", g2, borderFont, x, y);
        g2.rotate(-Math.PI / 2, x, y);
        x = 6 * sideLength;
        g2.rotate(Math.PI / 2, x, y);
        Util.drawString("界", g2, borderFont, x, y);
        g2.rotate(-Math.PI / 2, x, y);
        //坐标
        if (playerColor == Color.RED)
            y = (int) (10.6 * sideLength);
        else
            y = (int) (0.4 * sideLength);
        x = sideLength;
        Util.drawString("九", g2, coordinateFont2, x, y);
        x += sideLength;
        Util.drawString("八", g2, coordinateFont2, x, y);
        x += sideLength;
        Util.drawString("七", g2, coordinateFont2, x, y);
        x += sideLength;
        Util.drawString("六", g2, coordinateFont2, x, y);
        x += sideLength;
        Util.drawString("五", g2, coordinateFont2, x, y);
        x += sideLength;
        Util.drawString("四", g2, coordinateFont2, x, y);
        x += sideLength;
        Util.drawString("三", g2, coordinateFont2, x, y);
        x += sideLength;
        Util.drawString("二", g2, coordinateFont2, x, y);
        x += sideLength;
        Util.drawString("一", g2, coordinateFont2, x, y);
        if (playerColor == Color.RED)
            y = (int) (0.4 * sideLength);
        else
            y = (int) (10.6 * sideLength);
        x = sideLength;
        Util.drawString("1", g2, coordinateFont1, x, y);
        x += sideLength;
        Util.drawString("2", g2, coordinateFont1, x, y);
        x += sideLength;
        Util.drawString("3", g2, coordinateFont1, x, y);
        x += sideLength;
        Util.drawString("4", g2, coordinateFont1, x, y);
        x += sideLength;
        Util.drawString("5", g2, coordinateFont1, x, y);
        x += sideLength;
        Util.drawString("6", g2, coordinateFont1, x, y);
        x += sideLength;
        Util.drawString("7", g2, coordinateFont1, x, y);
        x += sideLength;
        Util.drawString("8", g2, coordinateFont1, x, y);
        x += sideLength;
        Util.drawString("9", g2, coordinateFont1, x, y);
    }

    //设置焦点，x、y均从0开始，(0, 0)表示棋盘左上角車所在位置
    public void setFocus(int x, int y, Color c) {
        if (x < 0 || x > 8 || y < 0 || y > 9) return;
        if (chessmanData[x][y] == null)
            chessmanData[x][y] = new Chessman().setFocusColor(c);
        else
            chessmanData[x][y].setFocusColor(c);
    }
    //移除焦点
    public void removeFocus(int x, int y) {
        if (x < 0 || x > 8 || y < 0 || y > 9) return;
        if(chessmanData[x][y] == null) return;
        chessmanData[x][y].setFocusColor(null);
    }
    //移除全部焦点
    public void removeAllFocus() {
        for (int x = 0; x <= 8; x++) {
            for (int y = 0; y <= 9; y++) {
                removeFocus(x, y);
            }
        }
    }
    //移除棋子
    public void removeChess(int x, int y) {
        if (x < 0 || x > 8 || y < 0 || y > 9) return;
        chessmanData[x][y] = null;
    }
    //画棋子，x、y均从0开始，(0, 0)表示棋盘左上角車所在位置
    public void drawChess(Graphics2D g, int x, int y, Chessman c) {
        if (g == null || c == null) return;
        c.draw(g, (x + 1) * sideLength, (y + 1) * sideLength, playerColor == Color.BLACK);
    }
    //画全部棋子
    public void drawAllChess(Graphics2D g) {
        if (playerColor == Color.BLACK) g.rotate(Math.PI, 5 * sideLength, 5.5 * sideLength);
        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 10; y++) {
                Chessman c = chessmanData[x][y];
                if (c != null) drawChess(g, x, y, c);
            }
        }
        if (playerColor == Color.BLACK) g.rotate(-Math.PI, 5 * sideLength, 5.5 * sideLength);
    }

    public static Point getPointFromPosition(Point Position, Color playerColor) {
        if (Position == null) return null;
        //位于棋盘外
        if (    Position.getX() < sideLength - Chessman.diameter / 2 ||
                Position.getY() < sideLength - Chessman.diameter / 2 ||
                Position.getX() > 9 * sideLength + Chessman.diameter / 2 ||
                Position.getY() > 10 * sideLength + Chessman.diameter / 2)
            return null;
        int rx = Position.x % sideLength, ry = Position.y % sideLength;
        //位于棋子之间的空隙
        if (    (rx > Chessman.diameter / 2 && sideLength - rx > Chessman.diameter / 2) ||
                (ry > Chessman.diameter / 2 && sideLength - ry > Chessman.diameter / 2))
            return null;

        int x = (int) (Position.getX() / sideLength), y = (int) (Position.getY() / sideLength);
        if (rx < sideLength / 2) x--;
        if (ry < sideLength / 2) y--;
        if (playerColor == Color.BLACK) {
            x = 8 - x;
            y = 9 - y;
        }
        return new Point(x, y);
    }
}
