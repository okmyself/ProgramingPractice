package 第二次作业;

import javax.swing.*;
import java.awt.*;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.HashSet;

//基于作图类的扩展类
public class ChessBoard extends ChessPainter implements Runnable {
    public static final Color srcColor = Color.BLUE;        //棋子来源位置颜色
    public static final Color selectColor = Color.YELLOW;   //选择项的颜色
    public static final Color destColor = Color.GREEN;      //提示的目标点的颜色
    private boolean isOurTurn = playerColor != Color.BLACK; //判断当前谁执子
//    public Point currentFocus = new Point(-1, -1);          //当前焦点位置，-1表示没有
    public Point currentSelected = new Point(-1, -1);       //当前选中位置
    private Client client;

    public ChessBoard(Color playerColor, Client client) {
        super(playerColor);
        //棋盘加载完成前的加载界面
        Thread temp = new Thread() {
            JFrame progress;
            @Override
            public void run() {
                progress = new JFrame("棋盘加载中，请稍候！");
//                Image img = Util.loadImage("loading.gif");    //加载时的动图
                JLabel progressLabel = new JLabel("棋盘加载中，请稍候！");
                progressLabel.setFont(new Font("宋体", Font.BOLD, 30));
                progress.add(progressLabel);
                progress.pack();
                progress.setVisible(true);
            }

            @Override
            public void interrupt() {
                super.interrupt();
                progress.dispose();
            }
        };
        temp.start();

        this.client = client;

        if (playerColor == Color.BLACK) new Thread(this).start();

        ChessPainterListener l = new EventManager();
        addListener(l);
        init();
        temp.interrupt();
    }

    //网络线程
    @Override
    public void run() {
        ObjectInputStream in = client.getIn();
        ObjectOutputStream out = client.getOut();
        while (true) {
            if (!isOurTurn) {
                System.out.println("等待对方下子");
                PlayChess playChess = client.receive();
                System.out.println(playerColor + "  " + playChess);
                System.out.println("对方下子完毕");
//                new Thread(new Runnable() {
//                    @Override
//                    public void run() {
                        removeAllFocus();
                        Point from = playChess.getFrom(), to = playChess.getTo();
                        if (hasChess(to.x, to.y)) {
                            if (chessmanData[to.x][to.y].getChessType() == CHESS_TYPE.Kings &&
                                    chessmanData[from.x][from.y].getChessColor() != playerColor) {
                                JOptionPane.showConfirmDialog(ChessBoard.this, "你输了！", "信息：", JOptionPane.YES_OPTION);
                                System.exit(0);
                            }
                        }
                        setFocus(from.x, from.y, srcColor);
                        setFocus(to.x, to.y, selectColor);
                        chessmanData[to.x][to.y] = chessmanData[from.x][from.y];
                        removeChess(from.x, from.y);
                        isOurTurn = true;
                        repaint();
//                    }
//                }).start();     //重画效率较低，在新的线程中执行
                break;
            }
        }
    }

    //初始化棋盘
    public void init() {
        chessmanData[0][9] = new Chessman().setChessType(CHESS_TYPE.Rooks).setChessColor(Color.RED);
        chessmanData[8][9] = new Chessman().setChessType(CHESS_TYPE.Rooks).setChessColor(Color.RED);
        chessmanData[1][9] = new Chessman().setChessType(CHESS_TYPE.Knights).setChessColor(Color.RED);
        chessmanData[7][9] = new Chessman().setChessType(CHESS_TYPE.Knights).setChessColor(Color.RED);
        chessmanData[2][9] = new Chessman().setChessType(CHESS_TYPE.Ministers).setChessColor(Color.RED);
        chessmanData[6][9] = new Chessman().setChessType(CHESS_TYPE.Ministers).setChessColor(Color.RED);
        chessmanData[3][9] = new Chessman().setChessType(CHESS_TYPE.Guards).setChessColor(Color.RED);
        chessmanData[5][9] = new Chessman().setChessType(CHESS_TYPE.Guards).setChessColor(Color.RED);
        chessmanData[4][9] = new Chessman().setChessType(CHESS_TYPE.Kings).setChessColor(Color.RED);
        chessmanData[1][7] = new Chessman().setChessType(CHESS_TYPE.Cannons).setChessColor(Color.RED);
        chessmanData[7][7] = new Chessman().setChessType(CHESS_TYPE.Cannons).setChessColor(Color.RED);
        chessmanData[0][6] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.RED);
        chessmanData[2][6] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.RED);
        chessmanData[4][6] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.RED);
        chessmanData[6][6] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.RED);
        chessmanData[8][6] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.RED);

        chessmanData[0][0] = new Chessman().setChessType(CHESS_TYPE.Rooks).setChessColor(Color.BLACK);
        chessmanData[8][0] = new Chessman().setChessType(CHESS_TYPE.Rooks).setChessColor(Color.BLACK);
        chessmanData[1][0] = new Chessman().setChessType(CHESS_TYPE.Knights).setChessColor(Color.BLACK);
        chessmanData[7][0] = new Chessman().setChessType(CHESS_TYPE.Knights).setChessColor(Color.BLACK);
        chessmanData[2][0] = new Chessman().setChessType(CHESS_TYPE.Ministers).setChessColor(Color.BLACK);
        chessmanData[6][0] = new Chessman().setChessType(CHESS_TYPE.Ministers).setChessColor(Color.BLACK);
        chessmanData[3][0] = new Chessman().setChessType(CHESS_TYPE.Guards).setChessColor(Color.BLACK);
        chessmanData[5][0] = new Chessman().setChessType(CHESS_TYPE.Guards).setChessColor(Color.BLACK);
        chessmanData[4][0] = new Chessman().setChessType(CHESS_TYPE.Kings).setChessColor(Color.BLACK);
        chessmanData[1][2] = new Chessman().setChessType(CHESS_TYPE.Cannons).setChessColor(Color.BLACK);
        chessmanData[7][2] = new Chessman().setChessType(CHESS_TYPE.Cannons).setChessColor(Color.BLACK);
        chessmanData[0][3] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.BLACK);
        chessmanData[2][3] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.BLACK);
        chessmanData[4][3] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.BLACK);
        chessmanData[6][3] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.BLACK);
        chessmanData[8][3] = new Chessman().setChessType(CHESS_TYPE.Pawns).setChessColor(Color.BLACK);
    }

    class EventManager extends ChessPainterAdapter {

//        @Override
//        public void mouseMoved(ChessPainterEvent e) {
//            if (currentFocus.x == e.getX() && currentFocus.y == e.getY()) {
//                return;     //如果鼠标所在棋子没变，则直接返回
//            }
//            HashSet<Point> dest = getDestinations(e.getX(), e.getY());
//            removeAllFocus();
//            if (dest == null) return;
//            for (Point i : dest) {
//                setFocus(i.x, i.y, destColor);
//            }
//            setFocus(e.getX(), e.getY(), selectColor);
//            repaint();
//        }
//
//        @Override
//        public void mouseExited(ChessPainterEvent e) {
//            removeFocus(currentFocus.x, currentFocus.y);
//            currentFocus = new Point(-1, -1);
//            repaint();
//        }

        @Override
        public void actionPerformed(ChessPainterEvent e) {
            if(!isOurTurn) return;
            if (currentSelected.x == e.getX() && currentSelected.y == e.getY()) {
                return;         //棋子位置没变，不作处理
            }
            removeAllFocus();
            Boolean isEnemy = isEnemy(e.getX(), e.getY());
            if (isEnemy != null && !isEnemy) {      //点了自己的棋子
                currentSelected.x = e.getX();
                currentSelected.y = e.getY();
                //标记目标点
                HashSet<Point> dest = getDestinations(e.getX(), e.getY());
                if (dest == null) return;
                for (Point i : dest) {
                    setFocus(i.x, i.y, destColor);
                }
                setFocus(e.getX(), e.getY(), selectColor);
            } else {                                //点了空白处或对方的棋子
                if (currentSelected.x == -1 && currentSelected.y == -1) return; //没有当前选中项
                HashSet<Point> dest = getDestinations(currentSelected.x, currentSelected.y);
                try {
                    if (dest.contains(new Point(e.getX(), e.getY()))) { //判断是否可以这样走
                        chessmanData[e.getX()][e.getY()] = chessmanData[currentSelected.x][currentSelected.y];
                        Color destColor = chessmanData[e.getX()][e.getY()].getChessColor();
                        removeChess(currentSelected.x, currentSelected.y);
                        setFocus(currentSelected.x, currentSelected.y, selectColor);
                        setFocus(e.getX(), e.getY(), srcColor);
                        if (hasChess(e.getX(), e.getY())) {
                            if (chessmanData[e.getX()][e.getY()].getChessType() == CHESS_TYPE.Kings &&
                                    destColor != playerColor) {
                                JOptionPane.showConfirmDialog(ChessBoard.this, "你赢了！", "信息：", JOptionPane.YES_OPTION);
                                System.exit(0);
                            }
                        }
                        //TODO: Client Send
                        client.send(currentSelected.x, currentSelected.y, e.getX(), e.getY());
                        isOurTurn = false;
                        repaint();
                        new Thread(ChessBoard.this).start();
                    } else {    //无效点击
                        currentSelected.x = -1;
                        currentSelected.y = -1;
                    }
                } catch (NullPointerException n) {
                    System.out.println("点击了对方棋子");
                }
            }
            repaint();
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        drawAllChess((Graphics2D) g);
    }

    //获得指定坐标处的棋子可以落子的全部位置
    public HashSet<Point> getDestinations(int x0, int y0) {
        if (!hasChess(x0, y0)) return null;       //给定位置无棋子
        if (isEnemy(x0, y0)) return null;         //给定位置不是我方棋子
        HashSet<Point> set = new HashSet<>();
        Chessman chess = chessmanData[x0][y0];
        CHESS_TYPE type = chess.getChessType();
        Color color = chess.getChessColor();
        if (type == CHESS_TYPE.Rooks) {            //車
            //前
            Point from = getPointAround(color, x0, y0, Direction.forward);
            Point to = getNearestChessInDirection(color, x0, y0, Direction.forward);
            if (to == null) {
                to = getEdge(color, x0, y0, Direction.forward);
            } else if (!isEnemy(to.x, to.y)) {
                to = getPointAround(color, to.x, to.y, Direction.backward);
            }
            HashSet<Point> result = getContinuePoints(color, from, to, Direction.forward);
            if (result != null) set.addAll(result);
            //后
            from = getPointAround(color, x0, y0, Direction.backward);
            to = getNearestChessInDirection(color, x0, y0, Direction.backward);
            if (to == null) {
                to = getEdge(color, x0, y0, Direction.backward);
            } else if (!isEnemy(to.x, to.y)) {
                to = getPointAround(color, to.x, to.y, Direction.forward);
            }
            result = getContinuePoints(color, from, to, Direction.backward);
            if (result != null) set.addAll(result);
            //左
            from = getPointAround(color, x0, y0, Direction.left);
            to = getNearestChessInDirection(color, x0, y0, Direction.left);
            if (to == null) {
                to = getEdge(color, x0, y0, Direction.left);
            } else if (!isEnemy(to.x, to.y)) {
                to = getPointAround(color, to.x, to.y, Direction.right);
            }
            result = getContinuePoints(color, from, to, Direction.left);
            if (result != null) set.addAll(result);
            //右
            from = getPointAround(color, x0, y0, Direction.right);
            to = getNearestChessInDirection(color, x0, y0, Direction.right);
            if (to == null) {
                to = getEdge(color, x0, y0, Direction.right);
            } else if (!isEnemy(to.x, to.y)) {
                to = getPointAround(color, to.x, to.y, Direction.left);
            }
            result = getContinuePoints(color, from, to, Direction.right);
            if (result != null) set.addAll(result);
        } else if (type == CHESS_TYPE.Knights) {    //马
            //前
            Point leg = getPointAround(color, x0, y0, Direction.forward), temp, dest;
            if (leg != null && !hasChess(leg.x, leg.y)) {   //如果没有蹩马腿
                temp = getPointAround(color, leg.x, leg.y, Direction.forward);
                if (temp != null) {
                    dest = getPointAround(color, temp.x, temp.y, Direction.left);
                    //符合"日"规则的前方位置不是我方棋子
                    if (dest != null) {   //存在dest
                        Boolean isEnemy = isEnemy(dest.x, dest.y);
                        if (isEnemy == null || isEnemy) {   //位置不是我方棋子
                            set.add(dest);
                        }
                    }
                    dest = getPointAround(color, temp.x, temp.y, Direction.right);
                    if (dest != null) {   //存在dest
                        Boolean isEnemy = isEnemy(dest.x, dest.y);
                        if (isEnemy == null || isEnemy) {   //位置不是我方棋子
                            set.add(dest);
                        }
                    }
                }
            }
            //后
            leg = getPointAround(color, x0, y0, Direction.backward);
            if (leg != null && !hasChess(leg.x, leg.y)) {   //如果没有蹩马腿
                temp = getPointAround(color, leg.x, leg.y, Direction.backward);
                if (temp != null) {
                    dest = getPointAround(color, temp.x, temp.y, Direction.left);
                    //符合"日"规则的前方位置不是我方棋子
                    if (dest != null) {   //存在dest
                        Boolean isEnemy = isEnemy(dest.x, dest.y);
                        if (isEnemy == null || isEnemy) {   //位置不是我方棋子
                            set.add(dest);
                        }
                    }
                    dest = getPointAround(color, temp.x, temp.y, Direction.right);
                    if (dest != null) {   //存在dest
                        Boolean isEnemy = isEnemy(dest.x, dest.y);
                        if (isEnemy == null || isEnemy) {   //位置不是我方棋子
                            set.add(dest);
                        }
                    }
                }
            }
            //左
            leg = getPointAround(color, x0, y0, Direction.left);
            if (leg != null && !hasChess(leg.x, leg.y)) {   //如果没有蹩马腿
                temp = getPointAround(color, leg.x, leg.y, Direction.left);
                if (temp != null) {
                    dest = getPointAround(color, temp.x, temp.y, Direction.backward);
                    //符合"日"规则的前方位置不是我方棋子
                    if (dest != null) {   //存在dest
                        Boolean isEnemy = isEnemy(dest.x, dest.y);
                        if (isEnemy == null || isEnemy) {   //位置不是我方棋子
                            set.add(dest);
                        }
                    }
                    dest = getPointAround(color, temp.x, temp.y, Direction.forward);
                    if (dest != null) {   //存在dest
                        Boolean isEnemy = isEnemy(dest.x, dest.y);
                        if (isEnemy == null || isEnemy) {   //位置不是我方棋子
                            set.add(dest);
                        }
                    }
                }
            }
            //右
            leg = getPointAround(color, x0, y0, Direction.right);
            if (leg != null && !hasChess(leg.x, leg.y)) {   //如果没有蹩马腿
                temp = getPointAround(color, leg.x, leg.y, Direction.right);
                if (temp != null) {
                    dest = getPointAround(color, temp.x, temp.y, Direction.backward);
                    //符合"日"规则的前方位置不是我方棋子
                    if (dest != null) {   //存在dest
                        Boolean isEnemy = isEnemy(dest.x, dest.y);
                        if (isEnemy == null || isEnemy) {   //位置不是我方棋子
                            set.add(dest);
                        }
                    }
                    dest = getPointAround(color, temp.x, temp.y, Direction.forward);
                    if (dest != null) {   //存在dest
                        Boolean isEnemy = isEnemy(dest.x, dest.y);
                        if (isEnemy == null || isEnemy) {   //位置不是我方棋子
                            set.add(dest);
                        }
                    }
                }
            }
        } else if (type == CHESS_TYPE.Ministers) {  //象
            if (x0 == 2 && y0 == 0) {
                if (!hasChess(1, 1)) {
                    Boolean isEnemy = isEnemy(0, 2);
                    if (isEnemy == null || isEnemy) set.add(new Point(0, 2));
                }
                if (!hasChess(3, 1)) {
                    Boolean isEnemy = isEnemy(4, 2);
                    if(isEnemy == null || isEnemy) set.add(new Point(4, 2));
                }
            } else if (x0 == 6 && y0 == 0) {
                if (!hasChess(5, 1)) {
                    Boolean isEnemy = isEnemy(4, 2);
                    if (isEnemy == null || isEnemy) set.add(new Point(4, 2));
                }
                if (!hasChess(7, 1)) {
                    Boolean isEnemy = isEnemy(8, 2);
                    if(isEnemy == null || isEnemy) set.add(new Point(8, 2));
                }
            } else if (x0 == 0 && y0 == 2) {
                if (!hasChess(1, 1)) {
                    Boolean isEnemy = isEnemy(2, 0);
                    if (isEnemy == null || isEnemy) set.add(new Point(2, 0));
                }
                if (!hasChess(1, 3)) {
                    Boolean isEnemy = isEnemy(2, 4);
                    if(isEnemy == null || isEnemy) set.add(new Point(2, 4));
                }
            } else if (x0 == 8 && y0 == 2) {
                if (!hasChess(7, 1)) {
                    Boolean isEnemy = isEnemy(6, 0);
                    if (isEnemy == null || isEnemy) set.add(new Point(6, 0));
                }
                if (!hasChess(7, 3)) {
                    Boolean isEnemy = isEnemy(6, 4);
                    if(isEnemy == null || isEnemy) set.add(new Point(6, 4));
                }
            } else if (x0 == 4 && y0 == 2) {
                if (!hasChess(3, 1)) {
                    Boolean isEnemy = isEnemy(2, 0);
                    if (isEnemy == null || isEnemy) set.add(new Point(2, 0));
                }
                if (!hasChess(5, 1)) {
                    Boolean isEnemy = isEnemy(6, 0);
                    if(isEnemy == null || isEnemy) set.add(new Point(6, 0));
                }
                if (!hasChess(3, 3)) {
                    Boolean isEnemy = isEnemy(2, 4);
                    if(isEnemy == null || isEnemy) set.add(new Point(2, 4));
                }
                if (!hasChess(5, 3)) {
                    Boolean isEnemy = isEnemy(6, 4);
                    if(isEnemy == null || isEnemy) set.add(new Point(6, 4));
                }
            } else if (x0 == 2 && y0 == 4) {
                if (!hasChess(1, 3)) {
                    Boolean isEnemy = isEnemy(0, 2);
                    if (isEnemy == null || isEnemy) set.add(new Point(0, 2));
                }
                if (!hasChess(3, 3)) {
                    Boolean isEnemy = isEnemy(4, 2);
                    if (isEnemy == null || isEnemy) set.add(new Point(4, 2));
                }
            } else if (x0 == 6 && y0 == 4) {
                if (!hasChess(5, 3)) {
                    Boolean isEnemy = isEnemy(4, 2);
                    if (isEnemy == null || isEnemy) set.add(new Point(4, 2));
                }
                if (!hasChess(7, 3)) {
                    Boolean isEnemy = isEnemy(8, 2);
                    if (isEnemy == null || isEnemy) set.add(new Point(8, 2));
                }
                //上面是黑方，下面是红方
            } else if (x0 == 2 && y0 == 9) {
                if (!hasChess(1, 8)) {
                    Boolean isEnemy = isEnemy(0, 7);
                    if (isEnemy == null || isEnemy) set.add(new Point(0, 7));
                }
                if (!hasChess(3, 8)) {
                    Boolean isEnemy = isEnemy(4, 7);
                    if(isEnemy == null || isEnemy) set.add(new Point(4, 7));
                }
            } else if (x0 == 6 && y0 == 9) {
                if (!hasChess(5, 8)) {
                    Boolean isEnemy = isEnemy(4, 7);
                    if (isEnemy == null || isEnemy) set.add(new Point(4, 7));
                }
                if (!hasChess(7, 8)) {
                    Boolean isEnemy = isEnemy(8, 7);
                    if(isEnemy == null || isEnemy) set.add(new Point(8, 7));
                }
            } else if (x0 == 0 && y0 == 7) {
                if (!hasChess(1, 8)) {
                    Boolean isEnemy = isEnemy(2, 9);
                    if (isEnemy == null || isEnemy) set.add(new Point(2, 9));
                }
                if (!hasChess(1, 6)) {
                    Boolean isEnemy = isEnemy(2, 5);
                    if(isEnemy == null || isEnemy) set.add(new Point(2, 5));
                }
            } else if (x0 == 8 && y0 == 7) {
                if (!hasChess(7, 8)) {
                    Boolean isEnemy = isEnemy(6, 9);
                    if (isEnemy == null || isEnemy) set.add(new Point(6, 9));
                }
                if (!hasChess(7, 6)) {
                    Boolean isEnemy = isEnemy(6, 5);
                    if(isEnemy == null || isEnemy) set.add(new Point(6, 5));
                }
            } else if (x0 == 4 && y0 == 7) {
                if (!hasChess(3, 8)) {
                    Boolean isEnemy = isEnemy(2, 9);
                    if (isEnemy == null || isEnemy) set.add(new Point(2, 9));
                }
                if (!hasChess(5, 8)) {
                    Boolean isEnemy = isEnemy(6, 9);
                    if(isEnemy == null || isEnemy) set.add(new Point(6, 9));
                }
                if (!hasChess(3, 6)) {
                    Boolean isEnemy = isEnemy(2, 5);
                    if(isEnemy == null || isEnemy) set.add(new Point(2, 5));
                }
                if (!hasChess(5, 6)) {
                    Boolean isEnemy = isEnemy(6, 5);
                    if(isEnemy == null || isEnemy) set.add(new Point(6, 5));
                }
            } else if (x0 == 2 && y0 == 5) {
                if (!hasChess(1, 6)) {
                    Boolean isEnemy = isEnemy(0, 7);
                    if (isEnemy == null || isEnemy) set.add(new Point(0, 7));
                }
                if (!hasChess(3, 6)) {
                    Boolean isEnemy = isEnemy(4, 7);
                    if (isEnemy == null || isEnemy) set.add(new Point(4, 7));
                }
            } else if (x0 == 6 && y0 == 5) {
                if (!hasChess(5, 6)) {
                    Boolean isEnemy = isEnemy(4, 7);
                    if (isEnemy == null || isEnemy) set.add(new Point(4, 7));
                }
                if (!hasChess(7, 6)) {
                    Boolean isEnemy = isEnemy(8, 7);
                    if (isEnemy == null || isEnemy) set.add(new Point(8, 7));
                }
            }
        } else if (type == CHESS_TYPE.Guards) {   //士
            Boolean isEnemy;
            if (x0 == 3 && y0 == 0) {
                isEnemy = isEnemy(4, 1);
                if (isEnemy == null || isEnemy) set.add(new Point(4, 1));
            } else if (x0 == 5 && y0 == 0) {
                isEnemy = isEnemy(4, 1);
                if (isEnemy == null || isEnemy) set.add(new Point(4, 1));
            } else if (x0 == 4 && y0 == 1) {
                isEnemy = isEnemy(3, 0);
                if (isEnemy == null || isEnemy) set.add(new Point(3, 0));
                isEnemy = isEnemy(5, 0);
                if (isEnemy == null || isEnemy) set.add(new Point(5, 0));
                isEnemy = isEnemy(3, 2);
                if (isEnemy == null || isEnemy) set.add(new Point(3, 2));
                isEnemy = isEnemy(5, 2);
                if (isEnemy == null || isEnemy) set.add(new Point(5, 2));
            } else if (x0 == 3 && y0 == 2) {
                isEnemy = isEnemy(4, 1);
                if (isEnemy == null || isEnemy) set.add(new Point(4, 1));
            } else if (x0 == 5 && y0 == 2) {
                isEnemy = isEnemy(4, 1);
                if (isEnemy == null || isEnemy) set.add(new Point(4, 1));
            } else if (x0 == 3 && y0 == 9) {
                isEnemy = isEnemy(4, 8);
                if (isEnemy == null || isEnemy) set.add(new Point(4, 8));
            } else if (x0 == 5 && y0 == 9) {
                isEnemy = isEnemy(4, 8);
                if (isEnemy == null || isEnemy) set.add(new Point(4, 8));
            } else if (x0 == 4 && y0 == 8) {
                isEnemy = isEnemy(3, 9);
                if (isEnemy == null || isEnemy) set.add(new Point(3, 9));
                isEnemy = isEnemy(5, 9);
                if (isEnemy == null || isEnemy) set.add(new Point(5, 9));
                isEnemy = isEnemy(3, 7);
                if (isEnemy == null || isEnemy) set.add(new Point(3, 7));
                isEnemy = isEnemy(5, 7);
                if (isEnemy == null || isEnemy) set.add(new Point(5, 7));
            } else if (x0 == 3 && y0 == 7) {
                isEnemy = isEnemy(4, 8);
                if (isEnemy == null || isEnemy) set.add(new Point(4, 8));
            } else if (x0 == 5 && y0 == 7) {
                isEnemy = isEnemy(4, 8);
                if (isEnemy == null || isEnemy) set.add(new Point(4, 8));
            }
        } else if (type == CHESS_TYPE.Kings) {  //将
            //前
            Point to = getPointAround(color, x0, y0, Direction.forward);
            Boolean isEnemy;
            if (to != null) {
                isEnemy = isEnemy(to.x, to.y);
                if (isEnemy == null || isEnemy) {
                    set.add(to);
                }
            }
            //后
            to = getPointAround(color, x0, y0, Direction.backward);
            if (to != null) {
                isEnemy = isEnemy(to.x, to.y);
                if (isEnemy == null || isEnemy) {
                    set.add(to);
                }
            }
            //左
            to = getPointAround(color, x0, y0, Direction.left);
            if (to != null) {
                isEnemy = isEnemy(to.x, to.y);
                if (isEnemy == null || isEnemy) {
                    set.add(to);
                }
            }
            //右
            to = getPointAround(color, x0, y0, Direction.right);
            if (to != null) {
                isEnemy = isEnemy(to.x, to.y);
                if (isEnemy == null || isEnemy) {
                    set.add(to);
                }
            }
            //是否明将
            to = getNearestChessInDirection(color, x0, y0, Direction.forward);
            if (to != null) {
                Chessman c = chessmanData[to.x][to.y];
                if (c != null && c.getChessType() == CHESS_TYPE.Kings) {
                    set.add(to);
                }
            }
        } else if (type == CHESS_TYPE.Cannons) {    //炮
            //前
            Point from = getPointAround(color, x0, y0, Direction.forward);
            Point to = getNearestChessInDirection(color, x0, y0, Direction.forward);
            if (to == null) {
                to = getEdge(color, x0, y0, Direction.forward);
            } else {
                Point another = getNearestChessInDirection(color, to.x, to.y, Direction.forward);
                //存在炮可以打到的棋子
                if (another != null && chessmanData[another.x][another.y].getChessColor() != color) {
                    set.add(another);
                }
                to = getPointAround(color, to.x, to.y, Direction.backward);
            }
            HashSet<Point> result = getContinuePoints(color, from, to, Direction.forward);
            if (result != null) set.addAll(result);
            //后
            from = getPointAround(color, x0, y0, Direction.backward);
            to = getNearestChessInDirection(color, x0, y0, Direction.backward);
            if (to == null) {
                to = getEdge(color, x0, y0, Direction.backward);
            } else {
                Point another = getNearestChessInDirection(color, to.x, to.y, Direction.backward);
                //存在炮可以打到的棋子
                if (another != null && chessmanData[another.x][another.y].getChessColor() != color) {
                    set.add(another);
                }
                to = getPointAround(color, to.x, to.y, Direction.forward);
            }
            result = getContinuePoints(color, from, to, Direction.backward);
            if (result != null) set.addAll(result);
            //左
            from = getPointAround(color, x0, y0, Direction.left);
            to = getNearestChessInDirection(color, x0, y0, Direction.left);
            if (to == null) {
                to = getEdge(color, x0, y0, Direction.left);
            } else {
                Point another = getNearestChessInDirection(color, to.x, to.y, Direction.left);
                //存在炮可以打到的棋子
                if (another != null && chessmanData[another.x][another.y].getChessColor() != color) {
                    set.add(another);
                }
                to = getPointAround(color, to.x, to.y, Direction.right);
            }
            result = getContinuePoints(color, from, to, Direction.left);
            if (result != null) set.addAll(result);
            //右
            from = getPointAround(color, x0, y0, Direction.right);
            to = getNearestChessInDirection(color, x0, y0, Direction.right);
            if (to == null) {
                to = getEdge(color, x0, y0, Direction.right);
            } else {
                Point another = getNearestChessInDirection(color, to.x, to.y, Direction.right);
                //存在炮可以打到的棋子
                if (another != null && chessmanData[another.x][another.y].getChessColor() != color) {
                    set.add(another);
                }
                to = getPointAround(color, to.x, to.y, Direction.left);
            }
            result = getContinuePoints(color, from, to, Direction.right);
            if (result != null) set.addAll(result);
        } else if (type == CHESS_TYPE.Pawns) {  //卒
            //前
            Point to = getPointAround(color, x0, y0, Direction.forward);
            Boolean isEnemy;
            if (to != null) {
                isEnemy = isEnemy(to.x, to.y);
                if (isEnemy == null || isEnemy) {
                    set.add(to);
                }
            }
            if (isCrossRiver(color, x0, y0)) {
                //左
                to = getPointAround(color, x0, y0, Direction.left);
                if (to != null) {
                    isEnemy = isEnemy(to.x, to.y);
                    if (isEnemy == null || isEnemy) {
                        set.add(to);
                    }
                }
                //右
                to = getPointAround(color, x0, y0, Direction.right);
                if (to != null) {
                    isEnemy = isEnemy(to.x, to.y);
                    if (isEnemy == null || isEnemy) {
                        set.add(to);
                    }
                }
            }
        }
        return set;
    }
    //判断某棋子是否过河
    public boolean isCrossRiver(Color c, int x, int y) {
        if (c == Color.RED) {
            if (y < 5) return true;
        } else if (c == Color.BLACK) {
            if (y > 4) return true;
        }
        return false;
    }
    //判断某个位置是否有棋子
    public boolean hasChess(int x, int y) {
        if (x < 0 || x > 8 || y < 0 || y > 9) return false;
        if (chessmanData[x][y] == null || chessmanData[x][y].getChessType() == null) {
            return false;
        }
        return true;
    }
    //判断某个位置是否是对方的棋子，true代表对方棋子，false代表我方棋子，null代表无棋子
    public Boolean isEnemy(int x, int y) {
        if(hasChess(x, y))
            if (chessmanData[x][y].getChessColor() == playerColor) return false;
            else return true;
        return null;
    }
    //所有方向均以使用start位置棋子的人为视角
    enum Direction {
        forward,    //向前
        backward,   //向后
        left,       //向左
        right       //向右
    }
    //在某个方向前进一个单位得到的坐标，baseColor为代表视角的颜色
    public Point getPointAround(Color baseColor, int start_x, int start_y, Direction d) {
        return getPointAround(baseColor, start_x, start_y, d, 1);
    }
    //在某个方向前进n个单位得到的坐标，baseColor为代表视角的颜色
    public Point getPointAround(Color baseColor, int start_x, int start_y, Direction d, int n) {
        if (baseColor == Color.RED) {
            if (d == Direction.forward) {
                if (start_y - n >= 0) return new Point(start_x, start_y - n);
            } else if (d == Direction.backward) {
                if (start_y + n <= 9) return new Point(start_x, start_y + n);
            } else if (d == Direction.left) {
                if(start_x - n >= 0) return new Point(start_x - n, start_y);
            } else if (d == Direction.right) {
                if(start_x + n <= 8) return new Point(start_x + n, start_y);
            }
        } else if (baseColor == Color.BLACK) {
            if (d == Direction.forward) {
                if (start_y + n <= 9) return new Point(start_x, start_y + n);
            } else if (d == Direction.backward) {
                if (start_y - n >= 0) return new Point(start_x, start_y - n);
            } else if (d == Direction.left) {
                if(start_x + n <= 8) return new Point(start_x + n, start_y);
            } else if (d == Direction.right) {
                if(start_x - n >= 0) return new Point(start_x - n, start_y);
            }
        }
        return null;
    }
    //在某个方向上寻找最近棋子的坐标，baseColor为代表视角的颜色
    public Point getNearestChessInDirection(Color baseColor, int start_x, int start_y, Direction d) {
        int x, y;
        if (baseColor == Color.RED) {                //红棋
            if (d == Direction.forward) {            //前进
                x = start_x;
                for (y = start_y - 1; y >= 0; y--) {
                    if (hasChess(x, y)) return new Point(x, y);
                }
            } else if (d == Direction.backward) {   //后退
                x = start_x;
                for (y = start_y + 1; y <= 9; y++) {
                    if (hasChess(x, y)) return new Point(x, y);
                }
            } else if (d == Direction.left) {       //向左
                y = start_y;
                for (x = start_x - 1; x >= 0; x--) {
                    if (hasChess(x, y)) return new Point(x, y);
                }
            } else if (d == Direction.right) {      //向右
                y = start_y;
                for (x = start_x + 1; x <= 8; x++) {
                    if (hasChess(x, y)) return new Point(x, y);
                }
            }
        } else if (baseColor == Color.BLACK) {      //黑棋
            if (d == Direction.forward) {           //前进
                x = start_x;
                for (y = start_y + 1; y <= 9; y++) {
                    if (hasChess(x, y)) return new Point(x, y);
                }
            } else if (d == Direction.backward) {   //后退
                x = start_x;
                for (y = start_y - 1; y >= 0; y--) {
                    if (hasChess(x, y)) return new Point(x, y);
                }
            } else if (d == Direction.left) {       //向左
                y = start_y;
                for (x = start_x + 1; x <= 8; x++) {
                    if (hasChess(x, y)) return new Point(x, y);
                }
            } else if (d == Direction.right) {      //向右
                y = start_y;
                for (x = start_x - 1; x >= 0; x--) {
                    if (hasChess(x, y)) return new Point(x, y);
                }
            }
        }
        return null;
    }
    //得到在某个方向边界上的点，baseColor为代表视角的颜色
    public Point getEdge(Color baseColor, int start_x, int start_y, Direction d) {
        if (baseColor == Color.red) {
            if (d == Direction.forward) return new Point(start_x, 0);
            if (d == Direction.backward) return new Point(start_x, 9);
            if (d == Direction.left) return new Point(0, start_y);
            if (d == Direction.right) return new Point(8, start_y);
        } else if (baseColor == Color.black) {
            if (d == Direction.forward) return new Point(start_x, 9);
            if (d == Direction.backward) return new Point(start_x, 0);
            if (d == Direction.left) return new Point(8, start_y);
            if (d == Direction.right) return new Point(0, start_y);
        }
        return null;
    }
    //判断在某个方向上是否已经抵达边界，baseColor为代表视角的颜色
    public boolean isEdge(Color baseColor, int x, int y, Direction d) {
        if (baseColor == Color.RED) {
            if (d == Direction.forward && y == 0) return true;
            if (d == Direction.backward && y == 9) return true;
            if (d == Direction.left && x == 0) return true;
            if (d == Direction.right && x == 8) return true;
        } else if (baseColor == Color.BLACK) {
            if (d == Direction.forward && y == 9) return true;
            if (d == Direction.backward && y == 0) return true;
            if (d == Direction.left && x == 8) return true;
            if (d == Direction.right && x == 0) return true;
        }
        return false;
    }
    //一次性添加连续多个位置到set集合，baseColor为代表视角的颜色，如果与方向不一致返回null
    public HashSet<Point> getContinuePoints(Color baseColor, Point from, Point to, Direction d) {
        if (from == null || to == null) return null;
        HashSet<Point> set = new HashSet<>();
        if (baseColor == Color.RED) {
            if (d == Direction.forward) {
                if (from.x != to.x || from.y < to.y) return null;
                for (int i = to.y; i <= from.y; i++) {
                    set.add(new Point(from.x, i));
                }
                return set;
            } else if (d == Direction.backward) {
                if (from.x != to.x || from.y > to.y) return null;
                for (int i = from.y; i <= to.y; i++) {
                    set.add(new Point(from.x, i));
                }
                return set;
            } else if (d == Direction.left) {
                if (from.y != to.y || from.x < to.x) return null;
                for (int i = to.x; i <= from.x; i++) {
                    set.add(new Point(i, from.y));
                }
                return set;
            } else if (d == Direction.right) {
                if (from.y != to.y || from.x > to.x) return null;
                for (int i = from.x; i <= to.x; i++) {
                    set.add(new Point(i, from.y));
                }
                return set;
            }
        } else if (baseColor == Color.BLACK) {
            if (d == Direction.forward) {
                if (from.x != to.x || from.y > to.y) return null;
                for (int i = from.y; i <= to.y; i++) {
                    set.add(new Point(from.x, i));
                }
                return set;
            } else if (d == Direction.backward) {
                if (from.x != to.x || from.y < to.y) return null;
                for (int i = to.y; i <= from.y; i++) {
                    set.add(new Point(from.x, i));
                }
                return set;
            } else if (d == Direction.left) {
                if (from.y != to.y || from.x > to.x) return null;
                for (int i = from.x; i <= to.x; i++) {
                    set.add(new Point(i, from.y));
                }
                return set;
            } else if (d == Direction.right) {
                if (from.y != to.y || from.x < to.x) return null;
                for (int i = to.x; i <= from.x; i++) {
                    set.add(new Point(i, from.y));
                }
                return set;
            }
        }
        return null;
    }
}
