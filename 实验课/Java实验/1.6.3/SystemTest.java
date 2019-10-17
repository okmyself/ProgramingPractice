import java.util.*;

public class SystemTest {
    public static void main(String[] args) {
        long starttime = System.currentTimeMillis();
        String path = System.getenv("Path");        //获得系统环境变量
        Properties myprop = System.getProperties(); //获取Java System的属性

        System.out.println("version:" + myprop.getProperty("java.version"));
        System.out.println("java home:" + myprop.getProperty("java.home"));
        System.out.println("path = " + path);
        long endtime = System.currentTimeMillis();
        System.out.println("spent time:" + (endtime - starttime));
    }
}