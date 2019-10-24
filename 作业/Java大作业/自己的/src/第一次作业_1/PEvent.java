package 第一次作业_1;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Objects;

/**
 * Title:极坐标系类<br>
 * Descripte:极坐标系中事件的抽象<br>
 * @author 杨添宝
 * @version 1.0.0
 */
public class PEvent {
    private double r = 0, theta = 0;
    private Date time;

    /**
     * PEvent的空构造方法，默认为当前时间下的极点
     */
    public PEvent() {
        this(0, 0);
    }
    /**
     * 给定坐标，创建当前时间下的坐标对象的构造方法
     * @param r 极径
     * @param θ 极角（单位：弧度）
     */
    public PEvent(double r, double θ) {
        this(r, θ, new Date());
    }
    /**
     * 通过坐标和时间创建对象的构造方法
     * @param r 极径
     * @param θ 极角（单位：弧度）
     * @param t 时间
     */
    public PEvent(double r, double θ, Date t) {
        this.r = r;
        theta = θ;
        time = t;
    }
    /**
     * 通过REvent创建对象的构造方法
     * @param r 需要用来创建PEvent的REvent
     */
    public PEvent(REvent r) {
        PEvent p = r.toPEvent();
        this.r = p.r;
        theta = p.theta;
        time = p.time;
    }

    public double getR() {
        return r;
    }
    public void setR(double r) {
        this.r = r;
    }
    public double getTheta() {
        return theta;
    }
    public void setTheta(double θ) {
        theta = θ;
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
    public double distance() { return distance(0, 0); }
    /**
     * @param r 另一点极径
     * @param θ 另一点极角（单位：弧度）
     * @return 返回当前点到另一点的距离
     */
    public double distance(double r, double θ) {
        return distance(r, θ, time);
    }
    /**
     * @param r 另一点极径
     * @param θ 另一点极角（单位：弧度）
     * @param t 另一点所处时间
     * @return 不同时间下返回-1，相同时间下返回当前点到另一点的距离
     */
    public double distance(double r, double θ, Date t) {
        return distance(new PEvent(r, θ, t));
    }
    /**
     * @param p 另一点的极坐标对象
     * @return 不同时间下返回-1，相同时间下返回当前点到另一点的距离
     */
    public double distance(PEvent p) {
        if(!p.time.equals(time))
            return -1;
        else {          /* 极坐标中(r1, θ1)到(r2, θ2)的距离为√(r1²+r2²-2r1r2cos(θ1-θ2)) */
            double r1 = p.r, r2 = r;
            double deltaTheta = p.theta - theta;
            return Math.sqrt(r1 * r1 + r2 * r2 - 2 * r1 * r2 * Math.cos(deltaTheta));
        }
    }
    /**
     * 求极坐标点和直角坐标点间的距离
     * @param r 另一点的直角坐标对象
     * @return 不同时间下返回-1，相同时间下返回当前点到另一点的距离
     */
    public double distance(REvent r) {
        return distance(r.toPEvent());
    }

    /**
     * @return 返回与当前极坐标系对应的直角坐标系下的点，时间与极坐标系中相同
     */
    public REvent toREvent() {
        return new REvent(r * Math.cos(theta), r * Math.sin(theta), time);
    }

    /**
     * @return 返回格式为(r, θ)  time:yyyy年MM月dd日 HH:mm:ss
     */
    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy年MM月dd日 HH:mm:ss");
        return "(" + r + ", " + theta + ")  time:" + dateFormat.format(time);
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
     * @param o 进行比较的对象若类型不为PEvent或REvent直接返回false，若为REvent则先转化为PEvent再进行比较
     * @return 是同一个坐标并且时间相同返回true，否则返回false
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null) return false;
        if(!(o instanceof REvent || o instanceof PEvent)) return false;
        // PEvent p;
        // if(o instanceof REvent)
        //     p = ((REvent) o).toPEvent();
        // else
        //     p = (PEvent) o;
        return o.hashCode() == hashCode();  /* 比较两个对象的hashCode值是否相等 */
    }
    
    /**
     * 相同时间下平面内同一点的极坐标和直角坐标对应的hashCode值相等
     */
    @Override
    public int hashCode() {
        /* 进行乘以1e14并取整的运算是为了去除最后几位的精度对于坐标是否相同比较的影响 */
        return Objects.hash(Math.round(r * Math.cos(theta) * 1e14), Math.round(r * Math.sin(theta) * 1e14), time.getTime());
    }
}
