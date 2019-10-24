package 第二次作业;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;

public class Server {
    static HashMap<Integer, ServerThread> sockets = new HashMap<>();

    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = null;
        ObjectInputStream in = null;
        ObjectOutputStream out = null;

        do {
            try {
                serverSocket = new ServerSocket(4331);
            } catch (IOException e) { }     //保证运行一个ServerSocket对象
            try {
                Socket socket = serverSocket.accept();
                InputStream in0 = socket.getInputStream();
                OutputStream out0 = socket.getOutputStream();
                in = new ObjectInputStream(in0);
                out = new ObjectOutputStream(out0);
                int n = (Integer) in.readObject();     //读入配对序号
                System.out.println("配对序号：" + n);
                if (sockets.containsKey(n)) {   //序号已经存在
                    ServerThread t = sockets.get(n);
                    if (t.isRunning()) {        //线程存在
                        if (!t.connect(socket, in, out)) {
                            out.writeObject(0);        //发送：序号冲突
                        }
                    } else {         //线程停止了
                        sockets.remove(n);
                        sockets.put(n, new ServerThread(socket, in, out));
                        out.writeObject(1);                //发送：序号合适，红方
                    }
                } else {                               //序号不存在
                    sockets.put(n, new ServerThread(socket, in, out));
                    out.writeObject(1);                //发送：序号合适，红方
                }
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        } while (true);

//        serverSocket.close();
    }
}

class ServerThread extends Thread {
    private Socket socket1 = null, socket2 = null;
    private ObjectInputStream in1, in2;
    private ObjectOutputStream out1, out2;
    private boolean isRunning = true;

    public ServerThread(Socket s, ObjectInputStream in, ObjectOutputStream out) {
        socket1 = s;
        in1 = in;
        out1 = out;
    }

    //连接另一个客户端，如果已经存在返回false
    public boolean connect(Socket s, ObjectInputStream in, ObjectOutputStream out) {
        if (socket2 != null) return false;
        socket2 = s;
        in2 = in;
        out2 = out;

        try {
            out.writeObject(2);        //发送：序号合适，黑方
            out1.writeObject(true);
            out2.writeObject(true);
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
        this.start();
        return true;
    }

    @Override
    public void interrupt() {
        isRunning = false;
        super.interrupt();
        try {
            in1.close();
            in2.close();
            out1.close();
            out2.close();
            socket1.close();
            socket2.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public boolean isRunning() { return isRunning; }

    @Override
    public void run() {
        Object obj = null;
        while (true) {
            try {
                obj = in1.readObject();
                System.out.println(obj);
                out2.writeObject(obj);
                obj = in2.readObject();
                System.out.println(obj);
                out1.writeObject(obj);
                if (obj == null) break;
            } catch (IOException e) {
                e.printStackTrace();
                break;
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
        this.interrupt();
    }
}