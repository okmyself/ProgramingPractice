public class Fibonacci {
    public static void main(String[] args) {
        int[] Fibo = new int[20];
        Fibo[0] = 1;
        Fibo[1] = 1;
        for(int i = 2; i < 20; i++)
            Fibo[i] = Fibo[i - 2] + Fibo[i - 1];
        for(int x: Fibo)
            System.out.print(" " + x);
    }
}
