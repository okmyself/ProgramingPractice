package 第一次作业_2;

import java.awt.*;
import java.util.Objects;

public class Driver {
    private String name = "noname";                                 /* 姓名 */
    private String sex = "男";                                      /* 性别 */
    private String nationality = "中国";                             /* 国籍 */
    private String address;                                         /* 住址 */
    private String birthDate = "1800-01-01";                        /* 出生日期 */
    private String issueDate = "1800-01-01";                        /* 初次领证日期 */
    private ClassPermitted classPermitted = ClassPermitted.C1;      /* 准驾车型 */
    private String validFrom = "1800-01-01";                        /* 有效起始日期 */
    private String validFor;                                        /* 有效期限 */
    private Image photo;                                            /* 照片 */
    private String fileNo;                                          /* 档案编号 */

    public Driver(String fileNo) {
        setFileNo(fileNo);
        setAddress("");
        setValidFor(6);
    }
    public Driver(String name, String nationality, String address, String birthDate,
                  String issueDate, ClassPermitted classPermitted, String validFrom,
                  int validFor, Image photo, String fileNo) {
        setName(name);
        setNationality(nationality);
        setAddress(address);
        setBirthDate(birthDate);
        setIssueDate(issueDate);
        setClassPermitted(classPermitted);
        setValidFrom(validFrom);
        setValidFor(validFor);
        setPhoto(photo);
        setFileNo(fileNo);
    }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getSex() {
        return sex;
    }

    /**
     * 设置性别，
     * @param sex 如果参数不为男，则设置性别为女
     */
    public void setSex(String sex) {
        if(sex.equals("男"))
            this.sex = sex;
        else this.sex = "女";
    }
    public String getNationality() { return nationality; }
    public void setNationality(String nationality) { this.nationality = nationality; }
    public String getAddress() { return address; }
    public void setAddress(String address) { this.address = address; }
    public String getBrithDate() { return birthDate; }

    /**
     * 设置出生日期，以下参数任意一条不满足则设置失败，不改变原有生日
     * @param month 要求1 ≤ month ≤ 12
     * @param day 要求1 ≤ day ≤ 28/29/30/31，最大值根据每月最大天数有所不同
     */
    public void setBirthDate(int year, int month, int day) {
        String date = General.checkDate(year, month, day);
        if(date != null)
            this.birthDate = date;
    }
    /**
     * 以字符串形式设置出生日期
     * @param date 欲设定的出生日期
     */
    public void setBirthDate(String date) {
        date = General.checkDate(date);
        if(date != null)
            this.birthDate = date;
    }
    /**
     * 设置初次领证日期，以下参数任意一条不满足则设置失败，不改变原有初次领证日期
     * @param month 要求1 ≤ month ≤ 12
     * @param day 要求1 ≤ day ≤ 28/29/30/31，最大值根据每月最大天数有所不同
     */
    public void setIssueDate(int year, int month, int day) {
        String date = General.checkDate(year, month, day);
        if(date != null)
            this.issueDate = date;
    }
    /**
     * 以字符串形式设置初次领证日期
     * @param date 欲设定的初次领证日期
     */
    public void setIssueDate(String date) {
        date = General.checkDate(date);
        if(date != null)
            this.issueDate = date;
    }
    public String getIssueDate() { return issueDate; }
    public ClassPermitted getClassPermitted() { return classPermitted; }

    public enum ClassPermitted {
        A1("A1"), A2("A2"), A3("A3"), B1("B1"), B2("B2"),
        C1("C1"), C2("C2"), C3("C3"), C4("C4"), C5("C5"),
        D("D"), E("E"), F("F"), M("M"), N("N"), P("P");

        private String classPermitted;

        ClassPermitted(String cp) {
            classPermitted = cp;
        }

        @Override
        public String toString() {
            return classPermitted;
        }
    }

    /**
     * 设置准驾车型
     * @param classPermitted 准驾车型必须满足下列之一：A1、A2、A3、B1、B2、C1、C2、C3、C4、C5、D、E、F、M、N、P
     */
    public void setClassPermitted(ClassPermitted classPermitted) {
//        switch(classPermitted.toUpperCase()) {
//            case "A1":
//            case "A2":
//            case "A3":
//            case "B1":
//            case "B2":
//            case "C1":
//            case "C2":
//            case "C3":
//            case "C4":
//            case "C5":
//            case "D":
//            case "E":
//            case "F":
//            case "M":
//            case "N":
//            case "P":
//                this.classPermitted = classPermitted.toUpperCase();
//        }
        /* 改用枚举类 */
        this.classPermitted = classPermitted;
    }
    public String getValidFrom() {
        return validFrom;
    }
    /**
     * 设置有效起始日期，以下参数任意一条不满足则设置失败，不改变原有有效起始日期
     * @param month 要求1 ≤ month ≤ 12
     * @param day 要求1 ≤ day ≤ 28/29/30/31，最大值根据每月最大天数有所不同
     */
    public void setValidFrom(int year, int month, int day) {
        String date = General.checkDate(year, month, day);
        if(date != null)
            this.validFrom = date;
    }
    /**
     * 以字符串形式设置有效起始日期
     * @param date 欲设定的有效起始日期
     */
    public void setValidFrom(String date) {
        date = General.checkDate(date);
        if(date != null)
            this.issueDate = date;
    }
    public String getValidFor() {
        return validFor;
    }
    /**
     * 设置有效期限
     * @param validFor 只能为六年、十年、长期之一
     */
    public void setValidFor(String validFor) {
        if(validFor.equals("六年") || validFor.equals("十年") || validFor.equals("长期"))
            this.validFor = validFor;
    }
    /**
     * 设置有效期限
     * @param validFor 不大于6则为六年，大于6不大于10则为十年，否则为长期
     */
    public void setValidFor(int validFor) {
        if(validFor <= 6)
            setValidFor("六年");
        else if(validFor <= 10)
            setValidFor("十年");
        else
            setValidFor("长期");
    }
    public Image getPhoto() {
        return photo;
    }
    public void setPhoto(Image photo) {
        this.photo = photo;
    }
    public String getFileNo() {
        return fileNo;
    }
    public void setFileNo(String fileNo) {
        this.fileNo = fileNo;
    }

    /**
     * 静态方法，不必创建对象
     * @return 返回字符串：“设计者：[姓名]  学号：[学号] 班级：[班级]”。
     */
    public static String getDesigner() { return "设计者：杨添宝  学号：320170941671 班级：计算机基地班"; }

    @Override
    public String toString() {
        String str = "姓名：" + name + '\n' +
                     "性别：" + sex + '\n' +
                     "国籍：" + nationality + '\n' +
                     "住址：" + nationality + '\n' +
                     "出生日期：" + birthDate + '\n' +
                     "初次领证日期：" + issueDate + '\n' +
                     "准驾车型：" + classPermitted + '\n' +
                     "有效起始日期：" + validFrom + '\n' +
                     "有效期限：" + validFor + '\n' +
                     "档案编号：" + fileNo + '\n';
        return str;
    }
    @Override
    public int hashCode() {
        return Objects.hash(fileNo);
    }
    /**
     * 具有相同档案编号的对象被认为是同一驾驶员
     */
    @Override
    public boolean equals(Object obj) {
        if(obj == this) return true;
        if(obj == null) return false;
        if (!(obj instanceof Driver)) return false;
        return ((Driver) obj).fileNo.equals(fileNo);
    }
}
