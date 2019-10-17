class Tortoise extends Thread {
    int sleepTime = 0, targetLength = 100;
    Tortoise(int sleepTime, int targetLength) {
        this.sleepTime = sleepTime;
        this.targetLength = targetLength;
        setName("Tortoise");
    }
    public void run() {
        while(true) {
            targetLength--;         //每次前进1
            System.out.print("T");
            try {
                sleep(sleepTime);   //让线程调用sleep方法进入休息状态
                    //经sleepTime毫秒后进入线程重新排队,等待CPU资源
            } catch(InterruptedException e) { }
            if(targetLength <= 0) {
                System.out.printf(getName() + "到达目的地!\n");
                stop();
            }
        }
    }
}
class Hare extends Thread {
    int sleepTime = 0, targetLength = 100;
    Hare(int sleepTime, int targetLength) {
        this.sleepTime = sleepTime;
        this.targetLength = targetLength;
        setName("Hare");
    }
    public void run() {
        while(true) {
            targetLength -= 3;         //每次前进3
            System.out.print(" * ");
            try {
                sleep(sleepTime);   //让线程调用sleep方法进入中断状态
                    //经sleepTime毫秒后进入线程重新排队,等待CPU资源
            } catch(InterruptedException e) { }
            if(targetLength <= 0) {
                System.out.printf(getName() + "到达目的地!\n");
                stop();
            }
        }
    }
}
public class HareTortoiseRace {
    public static void main(String[] args) {
        Hare hare;
        hare = new Hare(500, 100);
        Tortoise tortoise;
        tortoise = new Tortoise(100, 100);
        hare.start();
        tortoise.start();
    }
}