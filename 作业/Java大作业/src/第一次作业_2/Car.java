package 第一次作业_2;

import java.awt.*;
import java.util.Objects;

public class Car {
    private String plateNo;                 /* 汽车号牌 */
    private String vehicleType;             /* 车辆类型 */
    private String owner;                   /* 所有人 */
    private String address;                 /* 住址 */
    private String engineNo;                /* 发动机号码 */
    private String identificationNo;        /* 车辆识别号VIN */
    private String registerDate;            /* 注册日期 */
    private String issueDate;               /* 发证日期 */
    private double fuelTankCapacity;        /* 油箱容量 */
    private double currentFuelQuantity;     /* 当前容量 */
    private double weight;                  /* 重量 */
    private double loadCapacity;            /* 载重量 */
    private Image licenseImage;             /* 行驶证照片 */
    private Image appearanceImage;          /* 外观图片(400*300) */
    private double totalMileage;            /* 总行驶公里数 */
    private Driver motorist;                /* 驾驶汽车的人 */

    private double a = 0;                   /* 当前加速度 */
    private double v = 0;                   /* 当前速度 */
    private double k = 0;                   /* 比例系数 */
    private double μ = 0;                   /* 阻力系数 */
    private double g = 9.8;                 /* 重力加速度 */

    public Car(String engineNo, Driver motorist) {
        this.plateNo = "";
        this.vehicleType = "";
        this.owner = "";
        this.address = "";
        this.engineNo = engineNo;
        this.identificationNo = "";
        this.registerDate = "1800-01-01";
        this.issueDate = "1800-01-01";
        this.fuelTankCapacity = 0;
        this.currentFuelQuantity = 0;
        this.weight = 0;
        this.loadCapacity = 0;
        this.totalMileage = totalMileage;
        this.motorist = motorist;
    }
    public Car(String plateNo, String vehicleType, String owner, String address, String engineNo, String identificationNo, String registerDate, String issueDate, double fuelTankCapacity, double currentFuelQuantity, double weight, double loadCapacity, Image licenseImage, Image appearanceImage, double totalMileage, Driver motorist) {
        this.plateNo = plateNo;
        this.vehicleType = vehicleType;
        this.owner = owner;
        this.address = address;
        this.engineNo = engineNo;
        this.identificationNo = identificationNo;
        this.registerDate = registerDate;
        this.issueDate = issueDate;
        this.fuelTankCapacity = fuelTankCapacity;
        this.currentFuelQuantity = currentFuelQuantity;
        this.weight = weight;
        this.loadCapacity = loadCapacity;
        this.licenseImage = licenseImage;
        this.appearanceImage = appearanceImage;
        this.totalMileage = totalMileage;
        this.motorist = motorist;
    }

    public String getPlateNo() { return plateNo; }
    public void setPlateNo(String plateNo) { this.plateNo = plateNo; }
    public String getVehicleType() { return vehicleType; }
    public void setVehicleType(String vehicleType) { this.vehicleType = vehicleType; }
    public String getOwner() { return owner; }
    public void setOwner(String owner) { this.owner = owner; }
    public String getAddress() { return address; }
    public void setAddress(String address) { this.address = address; }
    public String getEngineNo() { return engineNo; }
    public String getIdentificationNo() { return identificationNo; }
    /**
     * 设置车辆识别代号
     * @param identificationNo 仅接受数字和除I、O、Q外的字母，小写字母将被自动转换为大写字母
     */
    public void setIdentificationNo(String identificationNo) {
        String pattern = "^[A-H0-9J-NPR-Z]{17}$";
        if(identificationNo.toUpperCase().matches(pattern))
            this.identificationNo = identificationNo.toUpperCase();
    }
    public String getRegisterDate() { return registerDate; }
    /**
     * 设置有效起始日期
     */
    public void setRegisterDate(int year, int month, int day) {
        String date = General.checkDate(year, month, day);
        if(date != null)
            this.registerDate = date;
    }
    /**
     * 以字符串形式设置有效起始日期
     */
    public void setRegisterDate(String registerDate) {
        String date = General.checkDate(registerDate);
        if (date != null)
            this.registerDate = date;
    }

    public String getIssueDate() {
        return issueDate;
    }
    /**
     * 设置有效起始日期
     */
    public void setIssueDate(int year, int month, int day) {
        String date = General.checkDate(year, month, day);
        if(date != null)
            this.issueDate = date;
    }
    /**
     * 以字符串形式设置有效起始日期
     */
    public void setIssueDate(String issueDate) {
        String date = General.checkDate(issueDate);
        if (date != null)
            this.issueDate = date;
    }
    public double getFuelTankCapacity() { return fuelTankCapacity; }
    /**
     * @param fuelTankCapacity 必须为非负
     */
    public void setFuelTankCapacity(double fuelTankCapacity) {
        if(fuelTankCapacity < 0) return;
        this.fuelTankCapacity = fuelTankCapacity;
    }
    public double getCurrentFuelQuantity() { return currentFuelQuantity; }
    /**
     * @param currentFuelQuantity 必须为非负
     */
    public void setCurrentFuelQuantity(double currentFuelQuantity) {
        if(currentFuelQuantity < 0) return;
        this.currentFuelQuantity = currentFuelQuantity;
    }
    public double getWeight() { return weight; }
    /**
     * @param weight 必须为非负
     */
    public void setWeight(double weight) {
        if(weight < 0) return;
        this.weight = weight;
    }
    public double getLoadCapacity() { return loadCapacity; }
    /**
     * @param loadCapacity 必须为非负
     */
    public void setLoadCapacity(double loadCapacity) {
        if(loadCapacity < 0) return;
        this.loadCapacity = loadCapacity;
    }
    public Image getLicenseImage() { return licenseImage; }
    public void setLicenseImage(Image licenseImage) { this.licenseImage = licenseImage; }
    public Image getAppearanceImage() { return appearanceImage; }
    public void setAppearanceImage(Image appearanceImage) { this.appearanceImage = appearanceImage; }
    public double getTotalMileage() { return totalMileage; }
    public Driver getMotorist() { return motorist; }
    public void setMotorist(Driver motorist) { this.motorist = motorist; }

    /**
     * @param totalMileage 必须为非负
     */
    public void setTotalMileage(double totalMileage) { this.totalMileage = totalMileage; }
    public double getμ() { return μ; }
    /**
     * @param μ 必须为非负
     */
    public void setμ(double μ) {
        if(μ < 0) return;
        this.μ = μ;
    }
    public double getG() { return g; }
    /**
     * @param g 必须为非负
     */
    public void setG(double g) {
        if(g < 0) return;
        this.g = g;
    }
    public double getK() { return k; }
    /**
     * 取得当前的加速度
     */
    public double getAcceleration() { return a; }
    /**
     * 取得当前的速度
     */
    public double getV() { return v; }

    /**
     * 根据已有k、μ、g值计算当前平均油耗
     * @return 若k、μ、g值有为0项，则返回null
     */
    public Double getAverage() {
        if(k == 0)
            return null;
        return Math.abs(k * (a + μ * g) * weight * v);
    }

    /**
     * 提供k、μ获取当前平均油耗，计算公式：油耗=k·(a+μ·g)·m·v，【油耗∝功率P=(ma+f)v，f=μmg】，需要提供两个系数，可通过CalcCoefficient获得
     * @param k 比例系数
     * @param μ 阻力系数
     * @return 返回当前平均油耗
     */
    public Double getAverage(double k, double μ) {
        this.k = k;
        this.μ = μ;
        return getAverage();
    }

    /**
     * 通过匀速运动状态下两个速度分别对应的油耗计算k和μ的值并存储
     *
     * @param average1 当前对象加速度为0时，速度v1下的油耗
     * @param average2 当前对象加速度为0时，速度v2下的油耗
     * @return 返回是否计算成功，若加速度a1与a2相等、v1或v2为0、提供数据重复或g的数据有误，返回false
     */
    public boolean calcCoefficient(double v1, double a1, double average1, double v2, double a2, double average2) {
        if (a1 == a2 || v1 == 0 || v2 == 0) return false;
        k = (v1 * average2 - v2 * average1) / ((a2 - a1) * weight * v1 * v2);
        μ = (a2 * v2 * average1 - a1 * v1 * average2) / (g * v1 * average2 - g * v2 * average1);
        return true;
    }

    /**
     * 加速方法，仅设定一个加速度，请通过travel方法进行行驶
     * @param a 加速度
     */
    public void speedUp(double a) {
        this.a = a;
    }

    /**
     * 减速方法
     * @param a 减速的加速度，正值为减速
     */
    public void speedDown(double a) { speedUp(-a); }

    public void stop() {
        v = 0;
        a = 0;
    }

    /**
     * 行驶方法
     * @param path 汽车要行驶的路径
     * @param time 汽车要行驶的时间，必须是非负数
     * @return 成功行驶（含油量不足行驶到中途的情况）返回true，当时间为负、路径不连通或长度不足以行驶时返回false
     */
    public boolean travel(Node path, long time) {
        if (time < 0) return false;
        if(!path.checkAccessable()) return false;       /* 路径不连通 */
        path = path.getNodeBeforePoint();
        if (path == null) return false;                 /* 未找到汽车在路径上的位置 */
        long t = 0, dertaT = 1;
        double v0 = v;
        while(t < time) {
            if(currentFuelQuantity <= 0) break;
            t += dertaT;
            v += a * dertaT;
            Double average = getAverage();
            if (average != null)
                currentFuelQuantity -= average;
            if(currentFuelQuantity < 0) return false;
        }
        double x = v0 * t + 0.5 * a * t * t;             /* 理论行驶距离 */
        return path.setDistance(path.getDistance() + x);
    }

    /**
     * 加油方法，加满油
     */
    public void fillUp() { currentFuelQuantity = fuelTankCapacity; }

    /**
     * 计算预计可行驶距离
     * @return 返回预计可行驶距离，若参数k = 0或μ = 0，则返回null
     */
    public Double getExpectDistance() {
        Double average = getAverage();
        if (average == null) return null;
        return (fuelTankCapacity - currentFuelQuantity) / average;
    }

    @Override
    public String toString() {
        return "汽车号牌：" + plateNo + '\n' +
               "车辆类型：" + vehicleType + '\n' +
               "所有人：" + owner + '\n' +
               "住址：" + address + '\n' +
               "发动机号码：" + engineNo + '\n' +
               "车辆识别号：" + identificationNo + '\n' +
               "注册日期：" + registerDate + '\n' +
               "发证日期：" + issueDate + '\n' +
               "油箱容量：" + fuelTankCapacity + '\n' +
               "当前容量：" + currentFuelQuantity + '\n' +
               "重量：" + weight + '\n' +
               "载重量：" + loadCapacity + '\n' +
               "总行驶公里数：" + totalMileage + '\n' +
               "当前加速度：" + a + '\n' +
               "当前速度：" + v + '\n' +
               "油耗功率比例系数：" + k + '\n' +
               "动摩擦因数：" + μ + '\n';
    }

    /**
     * 发动机号码相同的对象被认为是同一汽车
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Car car = (Car) o;
        return Objects.equals(engineNo, car.engineNo);
    }

    @Override
    public int hashCode() {

        return Objects.hash(engineNo);
    }

    /**
     * 静态方法，不必创建对象
     * @return 返回字符串：“设计者：[姓名]  学号：[学号] 班级：[班级]”。
     */
    public static String getDesigner() { return "设计者：杨添宝  学号：320170941671 班级：计算机基地班"; }
}