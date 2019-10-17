class MyComplex {
    private double realPart = 0;
    private double imaginaryPart = 0;

    public MyComplex(double r, double i) {
        realPart = r;
        imaginaryPart = i;
    }
    public MyComplex() {}

    public double getRealPart() {
        return realPart;
    }
    public void setRealPart(double r) {
        this.realPart = r;
    }
    public double getImaginaryPart() {
        return imaginaryPart;
    }
    public void setImaginaryPart(double i) {
        this.imaginaryPart = i;
    }

    public static MyComplex add(MyComplex c1, MyComplex c2) {
        return new MyComplex(c1.realPart + c2.realPart, c1.imaginaryPart + c2.imaginaryPart);
    }
    public static MyComplex sub(MyComplex c1, MyComplex c2) {
        return new MyComplex(c1.realPart - c2.realPart, c1.imaginaryPart - c2.imaginaryPart);
    }
    public static MyComplex mul(MyComplex c1, MyComplex c2) {
        double a = c1.realPart;
        double b = c1.imaginaryPart;
        double c = c2.realPart;
        double d = c2.imaginaryPart;
        MyComplex result = new MyComplex();
        result.setRealPart(a * c - b * d);
        result.setImaginaryPart(a * d + b * c);
        return result;
    }
    public static MyComplex div(MyComplex c1, MyComplex c2) {
        double a = c1.realPart;
        double b = c1.imaginaryPart;
        double c = c2.realPart;
        double d = c2.imaginaryPart;
        MyComplex result = new MyComplex();
        result.setRealPart((a * c + b * d) / (c * c + d * d));
        result.setImaginaryPart((b * c - a * d) / (c * c + d * d));
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof MyComplex))   return false;
        MyComplex c = (MyComplex)obj;
        return realPart == c.realPart && imaginaryPart == c.imaginaryPart;
    }
    @Override
    public String toString() {
        String complex = "";
        if(realPart != 0) {
            complex += realPart;
            if(imaginaryPart > 0)
                complex += "+";
        }
        if(imaginaryPart != 0)
            complex += imaginaryPart + "i";
        return complex;
    }
    
    public static void main(String[] args) {
        MyComplex m1 = new MyComplex(3.4, 8.0);
        MyComplex m2 = new MyComplex(3.4, 8.0);
        System.out.println("m1 = " + m1);
        System.out.println("m2 = " + m2);
        System.out.println("m1 == m2 = " + (m1 == m2));
        System.out.println("m1.equals(m2) = " + m1.equals(m2));
        MyComplex m3 = new MyComplex(4.4, -8.9);
        System.out.println("m3 = " + m3);
        MyComplex m4 = MyComplex.add(m1, m2);
        MyComplex m5 = MyComplex.sub(m2, m3);
        MyComplex m6 = MyComplex.mul(m1, m2);
        MyComplex m7 = MyComplex.div(m1, m2);
        System.out.println("m1 + m3 = " + m4);
        System.out.println("m2 - m3 = " + m5);
        System.out.println("m1 * m2 = " + m6);
        System.out.println("m1 / m2 = " + m7);
    }
}
