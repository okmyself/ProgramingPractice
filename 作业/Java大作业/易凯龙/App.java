import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Rectangle2D;

enum Colors {
    RED(Color.RED), GREEN(Color.GREEN), BLUE(Color.BLUE), BLACK(Color.BLACK), MAGENTA(Color.MAGENTA),
    CYAN(Color.CYAN), YELLOW(Color.YELLOW), PINK(Color.PINK), GRAY(Color.GRAY), ORANGE(Color.ORANGE),DARK_DRAY(Color.DARK_GRAY);

    private Color color;

    private Colors(Color c) {
        this.color = c;
    }

    public Color getColor() {
        return color;
    }

//随机取枚举中的颜色
    public static Color getRandomColor() {
        Colors[] colors = values();
        int n = (int) (Math.random() * colors.length);
        return colors[n].color;
    }
}

class Block extends JPanel implements KeyListener {
    private int row, range, rectLength, numberToClear;
    Color[][] array;
    Color currentColor = null;

    Block() {
        this(10, 7, 70, 3);
    }

    Block(int row, int range, int rectLength, int numberToClear) {
        init(row, range, rectLength, numberToClear);
    }

    public void init(int row, int range, int rectLength, int numberToClear) {
        this.row = row;
        this.range = range;
        this.rectLength = rectLength;
        this.numberToClear = numberToClear;
        setSize(range * rectLength, (row + 1) * rectLength);
        array = new Color[row + 1][range];
        currentColor = Colors.getRandomColor();
        array[0][(range - 1) / 2] = currentColor;
        repaint();
    }

    public int getRow() { return row; }

    public int getRange() { return range; }

    public int getRectLength() { return rectLength; }

    public int getNumberToClear() { return numberToClear; }

    //画边框
    @Override
    protected void paintBorder(Graphics g) {
        g.setColor(Color.PINK);
        Graphics2D g2 = (Graphics2D) g;
        g2.setStroke(new BasicStroke(3.0f));
        g2.drawLine(0, 0, getWidth() - 1, 0);
        g2.drawLine(0, 0, 0, getHeight() - 1);
        g2.drawLine(0, rectLength, getWidth() - 1, rectLength);
        g2.drawLine(getWidth() - 1, 0, getWidth() - 1, getHeight() - 1);
        g2.drawLine(0, getHeight() - 1, getWidth() - 1, getHeight() - 1);
    }
    //按数组画方块
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        for (int i = 0; i < row + 1; i++) {
            for (int j = 0; j < range; j++) {
                Color c = array[i][j];
                if (c == null) continue;
                g.setColor(c);
                g.fillRect(j * rectLength + 1, i * rectLength + 1, rectLength - 2, rectLength - 2);
            }
        }
    }

    @Override
    public void keyTyped(KeyEvent e) { }

    @Override
    public void keyReleased(KeyEvent e) { }

    @Override
    public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode();
        //实现键盘←方向键
        if (keyCode == KeyEvent.VK_LEFT) {
            int i;
            for (i = 0; i < range; i++) {
                if (array[0][i] != null) {
                    break;
                }
            }
            if (i <= 0 || i > range - 1) {
                return;
            }
            array[0][i - 1] = array[0][i];
            array[0][i] = null;
            repaint();
        }
        //实现键盘→方向键
        else if (keyCode == KeyEvent.VK_RIGHT) {
            int i;
            for (i = 0; i < range; i++) {
                if (array[0][i] != null) {
                    break;
                }
            }
            if (i >= range - 1) {
                return;
            }
            array[0][i + 1] = array[0][i];
            array[0][i] = null;
            repaint();
        }
        //实现键盘↓方向键
        else if (keyCode == KeyEvent.VK_DOWN) {
            int i, j = 0;
            //找到第一行中的方块
            for (i = 0; i < range; i++) {
                if (array[0][i] != null) {
                    break;
                }
            }
            //未能在第一行找到方块
            if (i > range - 1) return;
            repaint();
            //最上面一格不能下去
            if(array[1][i] != null) return;
            //找到当前列应下降到的位置
            while (j < row && array[j + 1][i] == null) {
                j++;
            }
            //下降过程动画渲染
            Graphics g = getGraphics();
            if (g != null) {
                Graphics2D g2 = (Graphics2D) g;
                long t = System.currentTimeMillis();
                while (System.currentTimeMillis() - t < 90) {
                    Color currentColor = new Color(this.currentColor.getRed(),
                            this.currentColor.getGreen(),
                            this.currentColor.getBlue(), 10);
                    g2.setPaint(new GradientPaint(0, 0, Color.WHITE, rectLength, j * rectLength, currentColor));
                    g2.fill(new Rectangle2D.Double(i * rectLength, rectLength, rectLength, j * rectLength));
                }
            }
            //drop
            array[j][i] = array[0][i];
            array[0][i] = null;
            clear(j, i);
            //判断所有空格是否填满，若填满则游戏结束
            int k;
            for(k = 0; k < this.range; k++) {
                if (this.array[1][k] == null) {
                    break;
                }
            }
            //游戏结束是否重新开始
            if (k == this.range) {
                int a = JOptionPane.showConfirmDialog(this,
                        "游戏结束！是否重新开始？", "Game Over!", JOptionPane.YES_NO_OPTION);
                if (a == JOptionPane.YES_OPTION) {
                    restart();
                } else {
                    System.exit(0);
                }
            }
            currentColor = Colors.getRandomColor();
            array[0][(range - 1) / 2] = currentColor;
            repaint();
        }
    }
    //重新开始
    public void restart() {
        this.array = new Color[row + 1][range];
        currentColor = Colors.getRandomColor();
        array[0][(range - 1) / 2] = currentColor;
        repaint();
    }
    //提供一个空白位置的坐标，上面连续的东西掉到最下面，如果提供的位置不为null则不进行处理
    //row从1开始，range从0开始
    public void drop(int row, int range) {

        if (!(row > 0 && row <= this.row && range >= 0 && range < this.range)) return;
        if (array[row][range] != null) return;
        int y = row - 1;
        while (y > 0 && array[y][range] == null) y--;
        if (y == 0) return;
        //y是上面第一个东西，从1开始
        while (row <= this.row && array[row][range] == null) row++;
        row--;  //得到的row是要下降到的位置
        int n = 1;  //判断有几个方块连着
        while (y - n > 0 && array[y - n][range] != null) n++;
        //降落到要下降的位置
        for (int i = row, j = y, k = 0; k < n; i--, j--, k++) {
            array[i][range] = array[j][range];
            array[j][range] = null;
            clear(i, range);
        }
    }
    //消去满足条件的方块
    //row从1开始，range从0开始
    public void clear(int row, int range) {
        boolean[][] isContinuous = new boolean[this.row][this.range];
        mark(row, range, isContinuous);
        //判断是否达到消去的条件（至少要有三个方块连着）
        if (numberOfTrue(isContinuous) >= numberToClear) {
            for (int i = 1; i <= this.row; i++)
                for (int j = 0; j < this.range; j++) {
                    if (isContinuous[i - 1][j]) {
                        this.array[i][j] = null;

                        //消去动画渲染
                        Graphics g = getGraphics();
                        if (g != null) {
                            Graphics2D g2 = (Graphics2D) g;
                            long t = System.currentTimeMillis();
                            while (System.currentTimeMillis() - t < 100) {
                                int bright = (int) (2.55 * (100 + (t - System.currentTimeMillis())));
                                System.out.println(bright);
                                g2.setColor(new Color(currentColor.getRed(), currentColor.getGreen(), currentColor.getBlue(), bright));
                                g2.fill(new Rectangle2D.Double(j * rectLength, i * rectLength, rectLength, rectLength));
                            }
                        }
                        //消去后的方块中上面的方块也要下降
                        drop(i, j);
                    }
                }
        }
    }
    //相同颜色连在一起的块标记为true储存在传进来的参数数组中
    //row从1开始，range从0开始
    public void mark(int row, int range, boolean[][] array) {
        array[row - 1][range] = true;
        Color currentColor = this.array[row][range];
        if (row > 1 && this.array[row - 1][range] == currentColor && !array[row - 2][range]) {
            mark(row - 1, range, array);
        }
        if (row < this.row && this.array[row + 1][range] == currentColor && !array[row][range]) {
            mark(row + 1, range, array);
        }
        if (range > 0 && this.array[row][range - 1] == currentColor && !array[row - 1][range - 1]) {
            mark(row, range - 1, array);
        }
        if (range < this.range - 1 && this.array[row][range + 1] == currentColor && !array[row - 1][range + 1]) {
            mark(row, range + 1, array);
        }
    }
    //统计true的个数
    public int numberOfTrue(boolean[][] array) {
        int n = 0;
        for (int i = 0; i < array.length; i++)
            for (int j = 0; j < array[0].length; j++)
                if(array[i][j]) n++;
        return n;
    }
}

class App implements ActionListener {
    JFrame myApp;
    Block myBlock;
    TextField rowTextField, rangeTextField, rectLengthTextField, numberToClearTextField;

    App() {
        myApp = new JFrame("方块爆破");
        myBlock = new Block();
        myApp.setSize(750, 1000);
        myApp.add(myBlock);
        //加入菜单功能（目前仅包含设置）
        JMenuBar mb = new JMenuBar();
        JMenu m1 = new JMenu("设置");
        JMenuItem mi1 = new JMenuItem("调整规格");
        mi1.addActionListener(new ActionListener() {
            @Override
            //点击调整规格弹出调整规格窗口
            public void actionPerformed(ActionEvent e) {
                JFrame setFrame = new JFrame("调整规格");
                setFrame.setLayout(new BorderLayout());
                Box baseBox, labelBox, textBox;
                int align = 8;//行间距
                baseBox = Box.createHorizontalBox();
                labelBox = Box.createVerticalBox();
                textBox = Box.createVerticalBox();
                //调整规格窗口中放入调整行、列、方块边长、满足的消去条件（块）
                labelBox.add(new Label("row:"));
                labelBox.add(Box.createVerticalStrut(align));
                labelBox.add(new Label("range:"));
                labelBox.add(Box.createVerticalStrut(align));
                labelBox.add(new Label("rectLength:"));
                labelBox.add(Box.createVerticalStrut(align));
                labelBox.add(new Label("numberToClear:"));

                rowTextField = new TextField(String.valueOf(myBlock.getRow()));
                textBox.add(rowTextField);
                textBox.add(Box.createVerticalStrut(align));
                rangeTextField = new TextField(String.valueOf(myBlock.getRange()));
                textBox.add(rangeTextField);
                textBox.add(Box.createVerticalStrut(align));
                rectLengthTextField = new TextField(String.valueOf(myBlock.getRectLength()));
                textBox.add(rectLengthTextField);
                textBox.add(Box.createVerticalStrut(align));
                numberToClearTextField = new TextField(String.valueOf(myBlock.getNumberToClear()));
                textBox.add(numberToClearTextField);
                textBox.add(Box.createVerticalStrut(align));

                baseBox.add(labelBox);
                baseBox.add(textBox);
                setFrame.add(baseBox, BorderLayout.NORTH);

                JButton saveButton = new JButton("保存");
                saveButton.addActionListener(App.this);
                setFrame.add(saveButton, BorderLayout.SOUTH);

                setFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                setFrame.pack();
                setFrame.setVisible(true);
            }
        });
        JMenuItem mi2 = new JMenuItem("重新开始");
        mi2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                myBlock.restart();
            }
        });
        JMenuItem mi3 = new JMenuItem("退出");
        mi3.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        m1.add(mi1);
        m1.add(mi2);
        m1.add(mi3);
        mb.add(m1);
        myApp.setJMenuBar(mb);

        myApp.setLayout(null);
        myApp.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        myApp.addKeyListener(myBlock);
        myApp.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        int row = Integer.parseInt(rowTextField.getText());
        int range = Integer.parseInt(rangeTextField.getText());
        int rectLength = Integer.parseInt(rectLengthTextField.getText());
        int numberToClear = Integer.parseInt(numberToClearTextField.getText());
        myBlock.removeKeyListener(myBlock);
        myBlock.init(row, range, rectLength, numberToClear);
    }

    public static void main(String[] args) {
        new App();
    }
}