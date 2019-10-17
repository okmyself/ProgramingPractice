class JavaLambdaTest {
    public static void main(String[] args) {
        new JavaLambdaTest().repeatPrint("abc", 10000);
    }
    
    public void repeatPrint(String s, int times) {
        Runnable r = () -> {
            System.out.println(this);
            for (int i = 0; i < times; i++) {
                System.out.println(s + i);
            }
        };
        new Thread(r).start();
    }
}