class test {
    public static void main(String[] args) {
        Student me = new Student("杨添宝", "320170941671", 20, 'M', 100);
        me.display();
    }
}

class Student extends Person {

    private String id = "noid";
    private int score = 0;
    public Student() {}
    public Student(String name, String id, int age, char sex, int score) {
        super(name, age, sex);
        this.id = id;
        if(score >= 0 && score <= 100) this.score = score;
        else this.score = 0;
    }
    public void display() {
        System.out.println("学号：" + id);
        System.out.println("姓名：" + super.getName());
        System.out.println("性别：" + (super.getSex() == 'M' ? "男" : "女"));
        System.out.println("年龄：" + super.getAge());
        System.out.println("成绩：" + score);
    }
    @Override
    public String toString() {
        return id + "," + super.getName() + "," + super.getSex() + "," + super.getAge() + "," + score;
    }
}