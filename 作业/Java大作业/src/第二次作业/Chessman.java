package 第二次作业;

import java.awt.*;

//棋子种类的枚举类
enum CHESS_TYPE {
    Rooks,      //车
    Knights,    //马
    Ministers,  //象
    Guards,     //士、仕
    Kings,      //将、帅
    Cannons,    //炮、砲
    Pawns;      //卒、兵

    //获取棋子名称，失败(未正确设置棋子颜色)返回null
    public String getName(Color chessColor) {
        String name = null;
        if (chessColor == Color.RED) {
            switch (this) {
                case Rooks: name = "俥"; break;
                case Knights: name = "傌"; break;
                case Ministers: name = "相"; break;
                case Guards: name = "仕"; break;
                case Kings: name = "帥"; break;
                case Cannons: name = "砲"; break;
                case Pawns: name = "兵"; break;
            }
        } else if (chessColor == Color.BLACK) {
            switch (this) {
                case Rooks: name = "車"; break;
                case Knights: name = "馬"; break;
                case Ministers: name = "象"; break;
                case Guards: name = "士"; break;
                case Kings: name = "將"; break;
                case Cannons: name = "炮"; break;
                case Pawns: name = "卒"; break;
            }
        }
        return name;
    }
}

public class Chessman {
    private CHESS_TYPE chessType;      //棋子的类型，null表示没有棋子
    private Color chessColor;       //只能为红色或黑色
    private Color focusColor;       //为null表示当前位置没有焦点

    public Font chessFont = Util.loadFont(this, "Kaiti.ttc", Font.BOLD, 50);
    public static Color chessBgColor = new Color(0xffd78c);   //棋子背景色
    public static int diameter = 70;       //棋子直径
    public static int circleDistance = 4;  //两个同心圆的间距

    public CHESS_TYPE getChessType() { return chessType; }
    public Chessman setChessType(CHESS_TYPE chessType) {
        this.chessType = chessType;
        return this;
    }

    //仅在颜色不为Color.RED和Color.BLACK时返回null，表示设置失败
    public Chessman setChessColor(Color c) {
        if (c != Color.RED && c != Color.BLACK) return null;
        if (chessType == null) return this;
        chessColor = c;
        return this;
    }
    public Color getChessColor() { return chessColor; }

    public Chessman setFocusColor(Color focusColor) {
        this.focusColor = focusColor;
        return this;
    }
    public Color getFocusColor() { return focusColor; }

    public void draw(Graphics2D g, int center_x, int center_y, boolean isReversed) {
        if (chessColor == null && focusColor == null) return;
        g.setStroke(new BasicStroke(3.0f));
        //画象棋
        if (chessColor != null) {
            if (chessFont == null) return;      //没有提供正确的字体
            int x = center_x - diameter / 2;
            int y = center_y - diameter / 2;
            g.setColor(chessBgColor);
            g.fillOval(x, y, diameter, diameter);
            g.setColor(Color.BLACK);
            g.drawOval(x, y, diameter, diameter);
            g.setColor(chessColor);
            x += circleDistance;
            y += circleDistance;
            g.drawOval(x, y, diameter - 2 * circleDistance, diameter - 2 * circleDistance);
            if (isReversed) g.rotate(Math.PI, center_x, center_y);
            Util.drawString(toString(), g, chessFont, center_x, center_y);
            if (isReversed) g.rotate(-Math.PI, center_x, center_y);
        }
        //画焦点
        if (focusColor != null) {
            g.setColor(focusColor);
            g.drawLine(center_x - diameter / 2, center_y - diameter / 2, center_x - diameter / 2, center_y - diameter / 3);
            g.drawLine(center_x - diameter / 2, center_y - diameter / 2, center_x - diameter / 3, center_y - diameter / 2);
            g.drawLine(center_x - diameter / 2, center_y + diameter / 2, center_x - diameter / 2, center_y + diameter / 3);
            g.drawLine(center_x - diameter / 2, center_y + diameter / 2, center_x - diameter / 3, center_y + diameter / 2);
            g.drawLine(center_x + diameter / 2, center_y - diameter / 2, center_x + diameter / 2, center_y - diameter / 3);
            g.drawLine(center_x + diameter / 2, center_y - diameter / 2, center_x + diameter / 3, center_y - diameter / 2);
            g.drawLine(center_x + diameter / 2, center_y + diameter / 2, center_x + diameter / 2, center_y + diameter / 3);
            g.drawLine(center_x + diameter / 2, center_y + diameter / 2, center_x + diameter / 3, center_y + diameter / 2);
        }
        g.setStroke(new BasicStroke(1.0f));
    }

    @Override
    public String toString() {
        if (chessType == null) return "";
        return chessType.getName(chessColor);
    }
}
