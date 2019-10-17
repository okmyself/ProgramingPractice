public class Shiyan3_1_1 {
    public static void main(String[] args) {
        System.out.println("我们已经知道地球的平均半径为6370.856km");
        System.out.println("也知道公认的地球质量为5.98×10^24kg");
        System.out.println("我们就可以使用数学公式计算地球的平均密度为：");
        double radius = 6.370856E6;
        double mass = 5.98E24;
        double volume = 4 * Math.PI * Math.pow(radius, 3) / 3;
        double density = mass / volume;
        System.out.print(density + "(千克/立方米)");
    }
}
