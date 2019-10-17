public class Person {
    private int age = 0;
    private String name = "noname";
    private char sex = 'M';
    public Person() {}
    public Person(String n, int a, char s) {
        name = n;
        if(a >= 0 && a < 140) age = a;
        else age = 0;
        if(s == 'M') sex = s;
        else sex = 'F';
    }
    public void introduceme() {
        System.out.println("my name is:" + name + "\tmy age is:" + age);
        if(sex == 'M') System.out.println("I am a man!");
        else System.out.println("I am a woman!");
    }
    public String getName() { return name; }
    public void setName(String n) { name = n; }
    public int getAge() { return age; }
    public void setAge(int a) {
        if(a >= 0 && a < 140) age = a;
        else age = 0;
    }
    public char getSex() { return sex; }
    public void setSex(char s) {
        if(s == 'M') sex = 'M';
        else sex = 'F';
    }
    public boolean equals(Person a) {
        if(this.name.equals(a.name) && this.age == a.age)
            return true;
        else return false;
    }
    public String toString() {
        return name + "," + sex + "," + age;
    }
}
class PersonTest {
    public static void main(String args[]) {
        Person p1, p2;
        p1 = new Person("张三", 28, 'M');
        p2 = new Person();
        p2.setName("陈红"); p2.setAge(38); p2.setSex('F');
        p1.introduceme();
        p2.introduceme();
    }
}
