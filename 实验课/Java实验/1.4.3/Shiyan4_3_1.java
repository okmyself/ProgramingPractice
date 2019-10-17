import java.awt.Color;

import javax.lang.model.util.ElementScanner6;
class Point {
    int x, y;
    Color mycolor;
    public Point() {
        this(0, 0);
    }
    public Point(int x, int y) {
        this(x, y, Color.black);
    }
    public Point(int x, int y, Color c) {
        this.x = x;
        this.y = y;
        mycolor = c;
    }
    public int getX() { return x; }
    public void setX(int x) { this.x = x; }
    public int getY() { return y; }
    public void setY(int y) { this.y = y; }
    public Color getColor() { return mycolor; }
    public void setColor(Color c) { mycolor = c; }
    public double distance(Point another) {
        return Math.sqrt((another.getX() - x) * (another.getX() - x) + (another.getY() - y) * (another.getY() - y));    
    }
    public boolean equals(Point another) {
        if(x == another.getX() && y == another.getY() && mycolor.equals(another.mycolor))
            return true;
        else return false;
    }
    public String toString() {
        return x + ", " + y + ", " + mycolor;
    }
}
public class Shiyan4_3_1 {
    public static void main(String[] agrs) {
        Point A = new Point();
        Point B = new Point(50, 60);
        Point C = new Point(100, 200, Color.red);
        System.out.println("B:(" + B.getX() + "," + B.getY() + ") color: " + B.getColor());
        A.setX(100);
        A.setY(200);
        A.setColor(Color.red);
        System.out.println("A == B? " + A.equals(B));
        System.out.println("A → B " + A.distance(B));
    }
}