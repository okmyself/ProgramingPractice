/*
<html>
    <head></head>
    <body>
        <applet code="Clock_good.class" width=500 height=500>
        </applet>
    </body>
</html>
 */
import java.awt.*;  
import java.util.*;  
import java.applet.*;  
public class  Clock_good extends Applet implements Runnable  
{    
    Thread 时针 = null, 分针 = null,秒针 = null; //用来表示时针、分针和秒针的线程。  
    //表示时针、分针、秒针端点的整型变量：  
    int hour_a,hour_b,munite_a,munite_b,second_a,second_b;  
    //用来获取当前时间的整型变量：  
    int hour = 0,munite = 0,second = 0;  
    //用来绘制时针、分针和秒针的Grapghics对象：  
    Graphics g_second = null,g_munite = null,g_hour = null;  
    //用来存放表盘刻度的数组，供指针走动时使用：  
    double point_x[] = new double[61],point_y[] = new double[61];  
    //用来存放表盘刻度的数组，供绘制表盘使用：  
    double scaled_x[] = new double[61],scaled_y[] = new double[61];  
    //用来判断小程序是否重新开始的变量：  
    int start_count = 0;  
    public void init()  
    {  
        setSize(400,400);      //控制Applet初始界面的大小  
        g_hour = this.getGraphics();  
        g_hour.setColor(Color.cyan);  
        g_second = this.getGraphics();   
        g_second.setColor(Color.red);  
        g_munite = this.getGraphics();   
        g_munite.setColor(Color.blue);  
        g_second.translate(200,200);//进行坐标系变换，将新坐标系原点设在（200，200）处。  
        g_munite.translate(200,200);  
        g_hour.translate(200,200);  
        point_x[0] = 0;  
        point_y[0] = -120;//各个时针12点处的位置坐标（按新坐标系的坐标）。  
        scaled_x[0] = 0;  
        scaled_y[0] = -140;//12点处的刻度位置坐标（按新坐标系的坐标）。  
        double jiaodu = 6*Math.PI/180;  
        //表盘分割成60份，将分割点处的坐标存放在数组中：  
        for(int i = 0;i < 60;i++)  
        {   
            point_x[i+1] = point_x[i]*Math.cos(jiaodu)-  
                Math.sin(jiaodu)*point_y[i];  
            point_y[i+1] = point_y[i]*Math.cos(jiaodu)+  
                point_x[i]*Math.sin(jiaodu);  
        }  
        point_x[60] = 0;  
        point_y[60] = -120; //12点各个时针的位置坐标（按新坐标系的坐标）。  
        //表盘分割成60份，将分割点处的坐标存放在数组中：  
        for(int i = 0;i < 60;i++)  
        {  
            scaled_x[i+1] = scaled_x[i]*Math.cos(jiaodu)-  
                Math.sin(jiaodu)*scaled_y[i];  
            scaled_y[i+1] = scaled_y[i]*Math.cos(jiaodu)+  
                scaled_x[i]*Math.sin(jiaodu);  
        }  
        scaled_x[60] = 0;  
        scaled_y[60] = -140;  
    }  
    public void start()  
    {   
        //每当小程序重新开始时，首先消灭线程，然后重新开始创建线程。  
        if(start_count >= 1)  
        {  
            秒针.interrupt();  
            分针.interrupt();  
            时针.interrupt();  
        }  
        秒针=new Thread(this);  
        分针=new Thread(this);  
        时针=new Thread(this);  
        秒针.start();  
        分针.start();  
        时针.start();  
        start_count++;  
        if(start_count >= 2)   
            start_count=1;  
    }  
    public void stop()  
    {  
        秒针.interrupt();  
        分针.interrupt();  
        时针.interrupt();  
    }  
    public void paint (Graphics g)  
    {    
        //每当小程序重新绘制自己时，重新开始创建线程：  
        this.start();  
        //绘制表盘的外观：  
        g.drawOval(50,50,300,300); //表盘的外圈。  
        g.translate(200,200);  
        //绘制表盘上的小刻度和大刻度：  
        for(int i = 0;i < 60;i++)  
        {   
            if(i%5 == 0)  
            {  
                g.setColor(Color.red);  
                g.fillOval((int) scaled_x[i],(int) scaled_y[i],8,8);  
            }  
            else  
                g.fillOval((int) scaled_x[i],(int) scaled_y[i],3,3);  
        }  
    }  
    public void run()  
    {   
        //获取本地时间:  
        Date date = new Date();  
        String s = date.toString();  
        hour = Integer.parseInt(s.substring(11,13));  
        munite=Integer.parseInt(s.substring(14,16));  
        second=Integer.parseInt(s.substring(17,19));  
        if(Thread.currentThread() == 秒针)  
        {  
            second_a = (int)point_x[second];  
            second_b=(int)point_y[second];  
            g_second.drawLine(0,0,second_a,second_b);  //秒针的初始位置。  
            g_second.drawString("秒",second_a,second_b);  
            int i=second;  
            while(true)  //秒针开始行走，每一秒走6度。  
            {  
                try  
                {  
                    秒针.sleep(1000);  
                    Color c=getBackground();  
                    g_second.setColor(c);  
                    g_second.drawLine(0,0,second_a,second_b);//用背景色清除前一秒时的秒针。  
                    g_second.drawString("秒",second_a,second_b);  
                    //如果这时秒针与分针重合，则恢复分针的显示：  
                    if((second_a==munite_a)&&(second_b==munite_b))  
                    {  
                        g_munite.drawLine(0,0,munite_a,munite_b);  
                        g_munite.drawString("分",munite_a,munite_b);  
                    }  
                    //如果这时秒针与时针重合，则恢复时针的显示：  
                    if((second_a==hour_a)&&(second_b==hour_b))  
                    {  
                        g_hour.drawLine(0,0,hour_a,hour_b);  
                        g_hour.drawString("时",hour_a,hour_b);  
                    }  
                }  
                catch(InterruptedException e)  
                {   
                    Color c=getBackground();  
                    g_second.setColor(c);  
                    g_second.drawLine(0,0,second_a,second_b);//用背景色清除秒针。  
                    g_second.drawString("秒",second_a,second_b);  
                    return;  
                }  
                //秒针向前走一个单位：  
                second_a=(int)point_x[(i+1)%60];  
                second_b=(int)point_y[(i+1)%60];//每一秒走6度（一个单位格）。  
                g_second.setColor(Color.red);  
                g_second.drawLine(0,0,second_a,second_b);//绘制新的秒针。  
                g_second.drawString("秒",second_a,second_b);  
                i++;  
            }  
        }  
        if(Thread.currentThread() == 分针)  
        {  
            munite_a=(int)point_x[munite];munite_b=(int)point_y[munite];  
            g_munite.drawLine(0,0,munite_a,munite_b);//分针的初始位置。  
            g_munite.drawString("分",munite_a,munite_b);  
            int i=munite;  
            while(true)  
            {  
                //第一次，过60-second秒就前进一分钟，以后每过60秒前进一分钟。  
                try  
                {  
                    分针.sleep(1000*60-second*1000);  
                    second=0;  
                    Color c=getBackground();  
                    g_munite.setColor(c);  
                    //用背景色清除前一分钟的分针：  
                    g_munite.drawLine(0,0,munite_a,munite_b);  
                    g_munite.drawString("分",munite_a,munite_b);  
                    //如果这时分针与时针重合，则恢复时针的显示：  
                    if((hour_a==munite_a) && (hour_b==munite_b))  
                    {   
                        g_hour.drawLine(0,0,hour_a,hour_b);  
                        g_hour.drawString("时",hour_a,hour_b);  
                    }  
                }  
                catch(InterruptedException e)  
                {  
                    return;  
                }  
                //分针向前走一个单位：  
                munite_a=(int)point_x[(i+1)%60];  
                munite_b=(int)point_y[(i+1)%60];//分针每分钟走6度（一个单位格）。  
                g_munite.setColor(Color.blue);  
                g_munite.drawLine(0,0,munite_a,munite_b);//绘制新的分针。  
                g_munite.drawString("分",munite_a,munite_b);  
                i++;  second=0;  
            }  
        }  
        if(Thread.currentThread()==时针)  
        {  
            int h=hour%12;  
            hour_a=(int)point_x[h*5+munite/12];  
            hour_b=(int)point_y[h*5+munite/12];  
            int i= h*5+munite/12;  
            g_hour.drawLine(0,0,hour_a,hour_b);  
            g_hour.drawString("时",hour_a,hour_b);  
            while(true)  
            {  
                //第一次，过12-munite%12分钟就前进一个刻度，以后每过12分钟前进一个刻度。  
                try  
                {  
                    时针.sleep(1000*60*12-1000*60*(munite%12)-second*1000);  
                    munite=0;  
                    Color c=getBackground();  
                    g_hour.setColor(c);  
                    g_hour.drawLine(0,0,hour_a,hour_b);//用背景色清除前12分钟时的时针。  
                    g_hour.drawString("时",hour_a,hour_b);  
                }  
                catch(InterruptedException e)  
                {  
                    return;  
                }  
                hour_a=(int)point_x[(i+1)%60];  
                hour_b=(int)point_y[(i+1)%60];//时针每12分走6度（一个单位格）。  
                g_hour.setColor(Color.cyan);  
                g_hour.drawLine(0,0,hour_a,hour_b);//绘制新的时针。  
                g_hour.drawString("时",hour_a,hour_b);  
                i++;  
                munite=0;  
            }  
        }  
  }  
 }  