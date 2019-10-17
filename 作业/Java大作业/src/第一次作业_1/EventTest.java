package 第一次作业_1;

import java.text.SimpleDateFormat;
import java.util.Date;
/**
 * 测试类：用于尽可能多的测试PEvent和REvent中实现的方法<br><br>
 *
 * PEvent和REvent类主要实现了以下方法：<br>
 * 一、构造方法<br>
 * 1. 提供了空参数的默认构造方法，默认在相应坐标系下创建当前时间下的坐标原点/极点<br>
 * 2. 提供了两个参数的构造方法，分别对应极坐标系下的极径r、极角θ和平面直角坐标系下的横坐标x、纵坐标y，用于创建当前时间下的相应坐标<br>
 * 3. 提供了三个参数的构造方法，前两个参数同2，第三个参数为Date类型的时间<br>
 * 4. 提供了两个坐标系对象互转的构造方法，参数为另一坐标系类型的对象<br>
 * 二、Getter、Setter访问器<br>
 * 　　主要涉及三个封装数据域的设置和获取，没有也没有必要进行数据过滤<br>
 * 三、重载方法<br>
 * 　　distance()方法有5个重载方法，分别如下：<br>
 * 1. 空参数的方法：用于计算该点对象与原点（极点）间的距离<br>
 * 2. 参数为2个坐标参数的方法：计算该对象对应的坐标点与参数给出的坐标点之间的距离<br>
 * 3. 前2个参数同2第3个参数为时间的方法：若时间不同，直接返回-1，否则同2<br>
 * 4. 参数为相同类型的坐标对象的方法：利用坐标对象参数的3个成员变量值，进行3的操作<br>
 * 5. 参数为另一坐标类型的坐标对象的方法：先将另一坐标类型转换为当前坐标类型，再进行4的操作<br>
 * 四、覆盖方法<br>
 * 　　hashCode()方法：<br>
 * 1. 利用两个坐标参数和当前时间距1970年1月1日8时的毫秒数生成哈希值<br>
 * 2. 为避免因数学运算导致的精度问题，取哈希值时不考虑坐标参数的最后一位<br>
 * 3. 为使相同时间下的相同点在极坐标和直角坐标中生成的hashCode值相同，极坐标中的hashCode值是先将r、θ分别转换为x、y再进行相同处理<br>
 * 　　equals()方法：<br>
 * 1. 若参数对象与当前对象指向地址相同，则为同一对象，直接返回true<br>
 * 2. 若参数对象为null，直接返回false，避免抛出NullPointerException异常<br>
 * 3. 若参数对象既不是PEvent的实例，也不是REvent的实例，返回false<br>
 * 4. 对于不符合1、2、3条的参数对象，比较当前对象和参数对象的hashCode值，若相同返回true，否则返回false<br>
 * 　　toString()方法：<br>
 * 该方法返回的对象格式是：(坐标参数1, 坐标参数2)  time:yyyy年MM月dd日 HH:mm:ss<br>
 * 五、其他方法<br>
 * 　　toPEvent()方法、toREvent()方法：返回相同时间下对应的坐标系下的对象<br>
 * 　　getDesigner()方法：静态方法，返回作者信息，格式为：设计者：[姓名]  学号：[学号] 班级：[班级]<br>
 */
public class EventTest {
    public static void main(String[] args) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy年MM月dd日 HH:mm:ss");
        REvent r = new REvent();
        r.setX(3);
        r.setY(4);
        r.setTime(new Date(0));
        System.out.println("r所处的时间：" + dateFormat.format(r.getTime()));
        System.out.println("r(" + r.getX() + ", " + r.getY() + ")到原点的距离为：" + r.distance());
        System.out.println("r.hashCode() = " + r.hashCode());
        PEvent p = new PEvent();
        p.setR(5);
        p.setTheta(Math.atan(4.0 / 3));
        p.setTime(new Date(0));
        System.out.println("p所处的时间：" + dateFormat.format(p.getTime()));
        System.out.println("p(" + p.getR() + ", " + p.getTheta() + ")到原点的距离为：" + p.distance());
        System.out.println("p.hashCode() = " + p.hashCode());
        System.out.println("p到r的距离为：" + p.distance(r));
        PEvent p2 = r.toPEvent();
        System.out.println("r(" + r.getX() + ", " + r.getY() + ")的极坐标p2是：" + p2.toString());
        REvent r2 = p.toREvent();
        System.out.println("p(" + p.getR() + ", " + p.getTheta() + ")的直角坐标r2是：" + r2.toString());
        System.out.println("r.equals(r2)? : " + r.equals(r2));
        System.out.println("p.equals(p2)? : " + p.equals(p2));
        System.out.println("r.equals(p)? : " + r.equals(p));
        System.out.println("p.equals(r)? : " + p.equals(r));
        REvent r3 = new REvent(3, 4, new Date());
        System.out.println("r3=" + r3.toString());
        System.out.println("r3.equals(r)? : " + r3.equals(r));
        PEvent p3 = new PEvent(5, Math.atan(4 / 3), new Date());
        System.out.println("p3=" + p3.toString());
        System.out.println("p3.equals(p)? : " + p3.equals(p));
        System.out.println(r.getDesigner());
    }
}
