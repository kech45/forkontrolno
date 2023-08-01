#include <vector>
#include <string>
#include <iostream>

class Grade {
private:
    double grade;
    std::string subject;
    void copy(const Grade& other)
    {
        grade = other.getGrade();
        subject = other.getSubject();
    }
public:
    Grade() = default;
    Grade(double gr, std::string sub) : grade(gr), subject(sub) {}
    bool operator !=(const Grade& other)
    {
        if (this->grade != other.getGrade() || this->getSubject() != other.getSubject())
        {
            return true;
        }
        return false;
    }
    Grade& operator=(const Grade& other)
    {
        if (this != &other)
        {
            copy(other);
        }
    }
    const double getGrade()const {
        return grade;
    }
    const std::string getSubject()const {
        return subject;
    }
};

class Student 
{
private:
    std::string name;
    std::string facultyNum;
    std::vector<Grade>grades;
public:
    Student() = default;
    Student(std::string n, std::string fn, std::vector<Grade>gr): name(n), facultyNum(fn), grades(gr){}
    Student(std::string n, std::string fn) : name(n), facultyNum(fn) {}
    virtual std::string whichUni()const = 0;
    virtual void printUni()const = 0;
    virtual Student* clone()const = 0;
    void addGrade(Grade grade) {
        this->grades.push_back(grade);
    }
    void removeGrade(std::string subjectName)
    {
        for (size_t i = 0; i < grades.size(); i++)
        {
            if (grades[i].getSubject() == subjectName)
            {
                grades.erase(grades.begin() + i);
            }
        }
    }
    void print() {
        this->printUni();
        std::cout << "Student name: " << name << std::endl;
        std::cout << "Faculty number: " << facultyNum << std::endl;
        std::cout << "Grades: " << std::endl;
        for (size_t i=0; i<this->grades.size(); i++)
        {
            std::cout << "Subject: " << this->grades[i].getSubject() << " grade: " << this->grades[i].getGrade() << std::endl;
        }
        std::cout << std::endl;
    }
    double calcAvgGrade()
    {
        double sum = 0;
        int count = 0;
        for (Grade curr: grades)
        {
            sum += curr.getGrade();
            count++;
        }
        return sum/count;
    }

    const std::string getName()const {
        return name;
    }
    const std::string getFacultyNum()const {
        return facultyNum;
    }
    const std::vector<Grade>getGrades()const {
        return grades;
    }
};

class UNSSstudent : public Student {
private:
public:
    UNSSstudent():Student(){}
    UNSSstudent(std::string n, std::string fn) :Student(n, fn) {}
    UNSSstudent(std::string n, std::string fn, std::vector<Grade>gr) :Student(n, fn, gr) {}
    virtual ~UNSSstudent() = default;
    void printUni()const override
    {
        std::cout << "UNSS" << std::endl;
    }
    std::string whichUni()const override {
        return "I AM FROM UNSS, THEREFORE I SUCK CAWK!";
    }
    UNSSstudent* clone()const override {
        return new UNSSstudent(*this);
    }
};

class FMIstudent : public Student {
private:
public:
    FMIstudent():Student(){}
    FMIstudent(std::string n, std::string fn) :Student(n, fn) {}
    FMIstudent(std::string n, std::string fn, std::vector<Grade>gr) :Student(n, fn, gr) {}
    virtual ~FMIstudent() = default;
    void printUni()const override
    {
        std::cout << "FMI" << std::endl;
    }
    std::string whichUni()const override {
        return "I AM FROM FMI, I AM SUPERIOR";
    }
    FMIstudent* clone()const override {
        return new FMIstudent(*this);
    }
};

class StudentComparer {
private:
    std::string name;
    std::vector<Student*> students;
    void destroy() {
        for (Student* curr : students) 
        {
            delete curr;
        }
        students.clear();
    }
    void copy(const StudentComparer& obj)
    {
        name = obj.getName();
        for (Student* curr:obj.getStudents())
        {
            this->students.push_back(curr);
        }
    }
public:
    StudentComparer() = default;
    StudentComparer(std::string n) : name(n){}
    StudentComparer(std::string n, std::vector<Student*>stu) : name(n), students(stu) {}
    StudentComparer(const StudentComparer& obj)
    {
        copy(obj);
    }
    ~StudentComparer()
    {
        this->destroy();
    }
    StudentComparer& operator =(const StudentComparer& obj)
    {
        if (this != &obj)
        {
            this->destroy();
            copy(obj);
        }
        return *this;
    }
    StudentComparer* clone()const
    {
        return new StudentComparer(*this);
    }
    
    void addStudent(const Student* student) {
        this->students.push_back(student->clone());
    }
    void removeStudent(std::string fn)
    {
        for (size_t i = 0; i < this->students.size(); i++)
        {
            if (students[i]->getFacultyNum() == fn)
            {
                this->students.erase(this->students.begin() + i);
            }
        }
    }
    double calculateFMIAverage() {
        double sum = 0;
        int count = 0;
        for (size_t i = 0; i < this->students.size(); i++)
        {
            if (students[i]->whichUni() == "I AM FROM FMI, I AM SUPERIOR")
            {
                sum += students[i]->calcAvgGrade();
                count++;
            }
        }
        return sum/count;
    }
    double calcucalteUNSSAverage() {
        double sum = 0;
        int count = 0;
        for (size_t i = 0; i < this->students.size(); i++)
        {
            if (students[i]->whichUni() == "I AM FROM UNSS, THEREFORE I SUCK CAWK!")
            {
                sum += students[i]->calcAvgGrade();
                count++;
            }
        }
        return sum / count;
    }
    void CompareAvg()
    {
        if (this->calcucalteUNSSAverage() >= this->calculateFMIAverage())
        {
            std::cout << "PROBABLY NOT TRUE FMI BETTER!!!! CAP" << std::endl;
        }
        else
        {
            std::cout << "FMI OBV DAFAK" << std::endl;
        }
    }

    const std::string getName()const
    {
        return name;
    }
    const std::vector<Student*> getStudents()const
    {
        return students;
    }

};



int main()
{
    Grade grade0(5.50, "ANALITICHNA GEOMETRIQ");
    Grade grade1(4.00, "Algebra");
    Grade grade2(3.00, "Programirane");
    Grade grade3(2.00, "DIS");
    Grade grade4(6.00, "OOP");
    Grade grade5(3.00, "UNSS1");
    Grade grade6(2.00, "UNSS2");
    Grade grade7(2.00, "UNSSWORST");
    Grade grade8(5.00, "UNSSKEKW");
    Grade grade9(2.00, "SPORTUNSS?");

    FMIstudent Goata("GOATQ", "0MI0320303");
    UNSSstudent Ladjiqta("Ladjiq", "59993299");

    Goata.addGrade(grade0);
    Goata.addGrade(grade1);
    Goata.addGrade(grade2);
    Goata.addGrade(grade3);
    Goata.addGrade(grade4);

    Ladjiqta.addGrade(grade5);
    Ladjiqta.addGrade(grade6);
    Ladjiqta.addGrade(grade7);
    Ladjiqta.addGrade(grade8);
    Ladjiqta.addGrade(grade9);

    std::cout << Goata.calcAvgGrade() << std::endl;
    std::cout << Ladjiqta.calcAvgGrade() << std::endl;
    std::cout << std::endl;

    Goata.print();
    Ladjiqta.print();

    StudentComparer Comparer1("comaprerat");
    Comparer1.addStudent(&Goata);
    Comparer1.addStudent(&Ladjiqta);
    Comparer1.CompareAvg();
       

}
