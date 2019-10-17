package 第一次作业_1;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Objects;

/**
 * Title:直角坐标系类<br>
 * Descripte:平面直角坐标系中事件的抽象<br>
 * @author 杨添宝
 * @version 1.0.0
 */
public class REvent {
    private double x = 0, y = 0;
    private Date time;

    /**
     * REvent的空构造方法，默认为当前时间下的坐标原点
     */
    public REvent() {
        this(0, 0);
    }
    /**
     * 给定坐标，创建当前时间下的坐标对象的构造方法
     * @param x 横坐标
     * @param y 纵坐标
     */
    public REvent(double x, double y) {
        this(x, y, new Date());
    }
    /**
     * 通过坐标和时间创建对象的构造方法
     * @param x 横坐标
     * @param y 纵坐标
     * @param t 时间
     */
    public REvent(double x, double y, Date t) {
        this.x = x;
        this.y = y;
        time = t;
    }
    /**
     * 通过PEvent创建对象的构造方法
     * @param p 需要用来创建REvent的PEvent
     */
    public REvent(PEvent p) {
        REvent r = p.toREvent();
        x = r.x;
        y = r.y;
        time = r.time;
    }

    public double getX() {
        return x;
    }
    public void setX(double x) {
        this.x = x;
    }
    public double getY() {
        return y;
    }
    public void setY(double y) {
        this.y = y;
    }
    public Date getTime() {
        return time;
    }
    public void setTime(Date t) {
        time = t;
    }

    /**
     * @return 返回当前点到原点的距离
     */
    public double distance() {
        return distance(0, 0);
    }
    /**
     * @param x 另一点横坐标
     * @param y 另一点纵坐标
     * @return 返回当前点到另一点的距离
     */
    public double distance(double x, double y) {
        return distance(x, y, time);
    }
    /**
     * @param x 另一点横坐标
     * @param y 另一点纵坐标
     * @param t 另一点所处时间
     * @return 不同时间下返回-1，相同时间下返回当前点到另一点的距离
     */
    public double distance(double x, double y, Date t) {
        return distance(new REvent(x, y, t));
    }

    /**
     * @param r 另一点的直角坐标对象
     * @return 不同时间下返回-1，相同时间下返回当前点到另一点的距离
     */
    public double distance(REvent r) {
        if(!r.time.equals(time))
            return -1;
        else {
            double deltaX = r.x - x;
            double deltaY = r.y - y;
            return Math.sqrt(deltaX * deltaX + deltaY * deltaY);
        }
    }
    /**
     * 求直角坐标点和极坐标点间的距离
     * @param p 另一点的极坐标对象
     * @return 不同时间下返回-1，相同时间下返回当前点到另一点的距离
     */
    public double distance(PEvent p) {
        return distance(p.toREvent());
    }

    /**
     * @return 返回与当前直角坐标系对应的极坐标系下的点，时间与直角坐标系中相同
     */
    public PEvent toPEvent() {
        return new PEvent(Math.sqrt(x * x + y * y), Math.atan(y / x), time);
    }

    /**
     * @return 返回格式为(x, y)  time:yyyy年MM月dd日 HH:mm:ss
     */
    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy年MM月dd日 HH:mm:ss");
        return "(" + x + ", " + y + ")  time:" + dateFormat.format(time);
    }
    /**
     * 静态方法，不必创建对象
     * @return 返回字符串：“设计者：[姓名]  学号：[学号] 班级：[班级]”。
     */
    public static String getDesigner() {
        return "设计者：杨添宝  学号：320170941671 班级：计算机基地班";
    }

    /**
     * 比较两个对象是否为同一个坐标，当两个坐标参数的误差小于10^(-14)时，判定为同一坐标
     * @param o 进行比较的对象若类型不为PEvent或REvent直接返回false，若为PEvent则先转化为REvent再进行比较
     * @return 是同一个坐标并且时间相同返回true，否则返回false
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null) return false;
        if(!(o instanceof REvent || o instanceof PEvent)) return false;
        // REvent r;
        // if(o instanceof PEvent)
        //     r = ((PEvent) o).toREvent();
        // else
        //     r = (REvent) o;
        return o.hashCode() == hashCode();  /* 比较两个对象的hashCode值是否相等 */
    }

    /**
     * 相同时间下平面内同一点的极坐标和直角坐标对应的hashCode值相等
     */
    @Override
    public int hashCode() {
        /* 进行乘以1e14并取整的运算是为了去除最后几位的精度对于坐标是否相同比较的影响 */
        return Objects.hash(Math.round(x * 1e14), Math.round(y * 1e14), time.getTime());
    }
}
