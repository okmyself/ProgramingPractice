public class SinTable {
    public static void main(String[] agrs) {
        for(int i = 0; i <= 90; i++) {
            System.out.println("sin(" + i + "°)=" + Math.sin((i * 3.14) / 180));
        }
    }
}
