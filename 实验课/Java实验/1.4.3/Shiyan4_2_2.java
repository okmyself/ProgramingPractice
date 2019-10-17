class Shiyan4_2_2 {
    public static void main(String[] args) {
        int n = 100;
        Sieve s = new Sieve();
        s.executeFilter(n);
        System.out.println("小于" + n + "的素数有:");
        s.outFilter();
    }
}
class Counter {
    private int value;
    Counter(int val) { value = val; }
    public int getValue() { return value; }
    public void next() { value++; }
}
class Sieve {
    final int Max = 100;
    private int filterCount = 0;
    private int[] f;
    public Sieve() { f = new int[Max]; filterCount = 0; }
    public void executeFilter(int n) {              //产生2到n之间的素数
        Counter c = new Counter(2);
        for(; c.getValue() < n; c.next()) {
            passFilter(c);                          //实施过滤
        }
    }
    public void passFilter(Counter c) {
        for(int i = 0; i < filterCount / 2; i++)
//        for(int i = 0; f[i] <= c.getValue() / 2 && i < filterCount; i++)
            if(c.getValue() % f[i] == 0) return;    //若为合数则返回
        addElementIntoFilter(c.getValue());         //若为素数则加入过滤器
    }
    private void addElementIntoFilter(int x) {
        f[filterCount] = x;
        filterCount++;
    }
    public void outFilter() {
        for(int i = 0; i < filterCount; i++) {
            System.out.printf("%4d", f[i]);
            if((i + 1) % 10 == 0) System.out.println();
        }
    }
}
