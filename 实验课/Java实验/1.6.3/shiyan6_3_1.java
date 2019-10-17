import java.util.*;

public class shiyan6_3_1 {
    public static void main(String[] args) {
        int n1 = 0, n2 = 0, result = 0;
        char infix;
        try {
            n1 = Integer.parseInt(args[0]);
            n2 = Integer.parseInt(args[2]);
            infix = args[1].charAt(0);
            switch(infix) {
                case '+': result = n1 + n2; break;
                case '-': result = n1 - n2; break;
                case '*': result = n1 * n2; break;
                case '/': result = n1 / n2; break;
            }
            System.out.println("result=" + result);
        } catch(ArrayIndexOutOfBoundsException e1) {
            System.out.println("此程序要输入三个参数!");
        } catch(NumberFormatException e2) {
            System.out.println("必须输入数字!");
        } catch(ArithmeticException e3) {
            System.out.println("除数不能为0!");
            System.out.print("请重新输入除数:");
            Scanner in = new Scanner(System.in);
            n2 = in.nextInt();
            result = n1 / n2;
            System.out.println("result=" + result);
            in.close();
        }
    }
}