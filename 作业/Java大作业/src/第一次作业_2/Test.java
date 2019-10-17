//package 第一次作业_2;
//
//import 第一次作业_1.REvent;
//
//import java.awt.*;
//import java.awt.event.*;
//import java.util.ArrayList;
//import java.util.List;
//import javax.swing.*;
//
//class PanelInformation {
//    private Driver driver;
//    private Car car;
//
//    public PanelInformation(Driver driver, Car car){
//        this.driver = driver;
//        this.car = car;
//    }
//
//    public Driver getDriver() { return driver; }
//    public Car getCar() { return car; }
//}
//
//class Test implements ActionListener {
//    private List<PanelInformation> information = new ArrayList<PanelInformation>();
//    private JComboBox CarList;
//    private JFrame frame;
//    private int currentIndex = 0;
//
//    public static void main(String[] args) {
//        Toolkit imgtool = Toolkit.getDefaultToolkit();
//        String name = "姚观槐",
//               sex = "男",
//               nationality = "中国",
//               driverAddress = "广东省阳西县上洋镇居民委员会建设中路65号",
//               birthDate = "1992-01-10",
//               driverIssueDate = "2012-12-20",
//               validFrom = "2012-12-20",
//               fileNo = "440710418572";
//        Driver.ClassPermitted classPermitted = Driver.ClassPermitted.C1;
//        int validFor = 6;
//        Image photo = imgtool.getImage("./res/2.png");
//        Driver driver = new Driver(name, nationality, driverAddress, birthDate, driverIssueDate, classPermitted, validFrom, validFor, photo, fileNo);
//        String plateNo = "冀E48920",
//               vehicleType = "小型轿车",
//               owner = "武绍波",
//               carAddress = "河北省邢台市平乡县平乡镇东闫庄村113号",
//               engineNo = "C375857",
//               identificationNo = "LMGFE1351F1866000",
//               registerDate = "2015-09-29",
//               carIssueDate = "2015-09-29";
//        double fuelTankCapacity = 50,
//               currentFuelQuantity = 0,
//               weight = 1500,
//               loadCapacity = 375,
//               totalMileage = 0;
//        Image licenseImage = imgtool.getImage("./res/3.png");
//        Image appearanceImage = imgtool.getImage("./res/1.png");
//
//        Car car = new Car(plateNo, vehicleType, owner, carAddress, engineNo, identificationNo, registerDate, carIssueDate, fuelTankCapacity, currentFuelQuantity, weight, loadCapacity, licenseImage, appearanceImage, totalMileage, driver);
//        car.calcCoefficient(70, 0, 7.5, 70, 1, 7.8);
//        /* 创建一条路径：(0,0)→(500,500)→(200,700) */
//        Node path = new Node(0, 0);
//        path.addNext(500, 500)
//            .addNext(200, 700);
//        path.setDistance(0);           /* 设置开始时位于原点 */
//
//
//        /* 对类进行测试 */
//        System.out.println("演示Car类：");
//        car.fillUp();                  /* 加油 */
//        System.out.print("加满后的邮箱油量为：");
//        System.out.println(car.getFuelTankCapacity() + "L");
//        System.out.println("从原点出发，以1m/s²的加速度加速15s");
//        car.speedUp(1);             /* 加速 */
//        car.travel(path, 10);     /* 以该加速度行驶 */
//        System.out.print("加速后到达点：");
//        REvent point = path.getPoint();
//        System.out.println("(" + Math.round(point.getX()) + "m, " + Math.round(point.getY()) + "m)");
//        System.out.print("邮箱剩余的油量为：");
//        System.out.println(Math.round(car.getCurrentFuelQuantity()) + "L");
//        System.out.println("以2m/s²的加速度减速5s");
//        car.speedDown(2);
//        car.travel(path, 5);
//        System.out.print("减速后到达点：");
//        point = path.getPoint();
//        System.out.println("(" + Math.round(point.getX()) + "m, " + Math.round(point.getY()) + "m)");
//        System.out.print("邮箱剩余的油量为：");
//        System.out.println(Math.round(car.getCurrentFuelQuantity()) + "L");
//        System.out.println("停车");
//        car.stop();
//
//        System.out.println("\n演示Driver类：");
////        displayImage(driver.getPhoto());
//        new Test().displayCar(car);
//    }
//
////    public static void displayImage(Image img) {
////        JFrame frame = new JFrame("图片显示");
////        ImageIcon imgicon = new ImageIcon(img);
////        frame.setSize(imgicon.getIconWidth(), imgicon.getIconHeight());
////        JLabel label = new JLabel();
////        label.setIcon(imgicon);
////        frame.add(label);
////
////        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
////        frame.setVisible(true);
////    }
//
//    public void displayCar(Car car) {
//        frame = new JFrame("驾驶员汽车信息");
//
//        JPanel comboBox = new JPanel(new FlowLayout());
//        CarList = new JComboBox();
//        JButton addButton = new JButton("添加");
//        JButton deleteButton = new JButton("删除");
//        CarList.addItem(car.getMotorist().getFileNo());
//
//        comboBox.add(CarList);
//        comboBox.add(addButton);
//        comboBox.add(deleteButton);
//        frame.add(comboBox);
//
//        information.add(new PanelInformation(car.getMotorist(), car));
//
//        JTabbedPane tabbedPane = new JTabbedPane();
//        tabbedPane.addTab("司机", new DriverPanel(information.get(0).getDriver()));
//        tabbedPane.addTab("汽车", new CarPanel(information.get(0).getCar()));
//
//        frame.add(tabbedPane, BorderLayout.SOUTH);
//
//        frame.pack();
//        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        frame.setVisible(true);
//
//        CarList.addActionListener(this);
//        /* 添加按钮 */
//        addButton.addMouseListener(new MouseAdapter() {
//            @Override
//            public void mouseClicked(MouseEvent e) {
//                String fileNo = null;
//                while (fileNo == null || fileNo.equals(""))
//                    fileNo = JOptionPane.showInputDialog("请输入您要创建的汽车的发动机号码(不能关闭或留空)：");
//                String engineNo = null;
//                while (engineNo == null || engineNo.equals(""))
//                    engineNo = JOptionPane.showInputDialog("请输入驾驶该汽车司机的档案编号(不能关闭或留空)：");
//
//                tabbedPane.setVisible(false);
//                JTabbedPane tabbedPane = new JTabbedPane();
//                Driver driver = new Driver(fileNo);
//                tabbedPane.addTab("司机", new DriverPanel(driver));
//                tabbedPane.addTab("汽车", new CarPanel(new Car(engineNo, driver)));
//
//                CarList.addItem(fileNo);
//                tabbedPanes.add(tabbedPane);
//                frame.add(tabbedPane, BorderLayout.SOUTH);
//                currentIndex = CarList.getItemCount() - 1;
//                CarList.setSelectedIndex(CarList.getItemCount() - 1);
////                actionPerformed(new ActionEvent(CarList, 0, ""));
//
//            }
//        });
//    }
//    /* 下拉框（组合框）事件 */
//    @Override
//    public void actionPerformed(ActionEvent e) {
//        if (e.getSource() == CarList) {
//            int selectedIndex = CarList.getSelectedIndex();
//            if (selectedIndex != currentIndex) {
//                tabbedPanes.get(currentIndex).setVisible(false);
//                JTabbedPane tabbedPane = tabbedPanes.get(selectedIndex);
//                tabbedPane.setVisible(true);
//                frame.add(tabbedPane, BorderLayout.SOUTH);
//            }
//        }
//    }
//}
