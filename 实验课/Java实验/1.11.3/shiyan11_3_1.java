/*
<html>
    <head></head>
    <body>
        <applet code="shiyan11_3_1.class" width=500 height=500>
        </applet>
    </body>
</html>
 */
import java.awt.*;
import java.awt.image.*;
import java.applet.*;

public class shiyan11_3_1 extends Applet implements Runnable {
    Image im[] = new Image[4];
    Graphics g = null;
    Thread pictureThread = null;        //用来画图片的线程 
    Thread lineThread = null;           //用来画线的线程
    int startCount = 0;                 //用来判断小程序是否重新开始的变量
    @Override
    public void paint(Graphics g) {
        this.start();                   //每次重画，调用start方法
        Point mp = getMousePosition();
        if(mp == null) return;
        int i = (int)(Math.random() * 4);
        if(im[i] == null) return;
        int x = mp.x - im[i].getWidth(this) / 2;
        int y = mp.y - im[i].getHeight(this) / 2;
        //ImageObserver: 当转换了更多图像时要通知的对象
        g.drawImage(im[i], x, y, this);
    }
    //test
    @Override
    public boolean imageUpdate(Image img, int infoflags, int x, int y, int w, int h) {
        System.out.println("Image has been updated! ("+x+","+y+")");
        return super.imageUpdate(img, infoflags, x, y, w, h);
    }
    @Override
    public void run() {
        Point mp = null, temp = null;
        int x;
        int y;
        if (Thread.currentThread() == pictureThread) {
            mp = getMousePosition();
            if(mp != null) {
                Image image = im[(int)(Math.random() * 4)];
                x = mp.x - image.getWidth(this) / 2;
                y = mp.y - image.getHeight(this) / 2;
                g.drawImage(image, x, y, this); 
                try {
                    Thread.currentThread().sleep(1000);
                } catch(InterruptedException e) { }
            }
            while(true) {
                try {
                    Thread.sleep(100);
                } catch(InterruptedException e) { }
                temp = getMousePosition();
                if(temp == null) continue;
                if(!temp.equals(mp)) {
                    repaint();
                    break;
                }
            }
        } else if (Thread.currentThread() == lineThread) {
            mp = getMousePosition();
            if(mp != null) {
                x = mp.x;
                y = mp.y;
                g.drawLine(x, 0, x, y);
                g.drawLine(0, y, x, y);
            }
            while(true) {
                try {
                    Thread.sleep(100);
                } catch(InterruptedException e) { }
                temp = getMousePosition();
                if(temp == null) continue;
                if(!temp.equals(mp)) {
                    repaint();
                    break;
                }
            }
        }
    }
    @Override
    public void init() {
        setSize(500, 500);
        //加载图片
        for(int i = 0; i < 4; i++)
            im[i] = getImage(getCodeBase(), "b" + i + ".gif");
        g = this.getGraphics();
    }
    @Override
    public void start() {
        if(startCount >= 1)
            this.stop();
        pictureThread = new Thread(this);
        lineThread = new Thread(this);
        pictureThread.start();
        lineThread.start();
        startCount++;
        if(startCount >= 2) startCount = 1;
    }
    @Override
    public void stop() {
        pictureThread.interrupt();
        lineThread.interrupt();
    }
}