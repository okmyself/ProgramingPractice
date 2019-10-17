#ifndef _STAFF_H_
#define _STAFF_H_

class Staff {
protected:
    float basicSalary;
public:
    Staff(float);
    float getBasicSalary() const;
    void setBasicSalary(float);
    virtual float salary() const = 0;
};

enum title {
    PROFESSOR = 50, // 教授
    ASSOCIATE_PROFESSOR = 30,   // 副教授
    LECTURER = 20   // 讲师
};
class Teacher: Staff {
private:
    enum title title;   // 职位
    int classHour;  // 课时
public:
    Teacher(float, enum title, int);
    enum title getTitle() const;
    void setTitle(enum title);
    int getClassHour() const;
    void setClassHour(int);
    float salary() const;
};

class Manager: Staff {
private:
    float postSalary;   // 职位工资
public:
    Manager(float, float);
    float getPostSalary() const;
    void setPostSalary(float);
    float salary() const;
};

class Lab: Staff {
private:
    float dailySubsidy; // 日补贴
    int workDayPerMonth;    // 月工作日数
public:
    Lab(float, float, int);
    float getDailySubsidy() const;
    void setDailySubsidy(float);
    int getWorkDayPerMonth() const;
    void setWorkDayPerMonth(int);
    float salary() const;
};

#endif // Staff.h