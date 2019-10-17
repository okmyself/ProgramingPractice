package 第二次作业;

import java.awt.*;
import java.io.Serializable;

//用于流传递的类，记录一次移动中棋的运动路径
public class PlayChess implements Serializable {
    private int x1, y1,x2,y2;

    public PlayChess(int x1, int y1, int x2, int y2) {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
    }

    public Point getFrom() { return new Point(x1, y1); }
    public Point getTo() { return new Point(x2, y2); }

    @Override
    public String toString() {
        return "from: (" + x1 + ", " + y1 + "), to: (" + x2 + ", " + y2 + ")";
    }
}
