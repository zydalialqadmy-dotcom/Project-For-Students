#ifndef STUDENT_H
#define STUDENT_H

#include <string>

// Student Class
// Represents a single student and encapsulates student data and grade status logic.
class Student {
private:
    int id;
    std::string name;
    int age;
    std::string department;
    double grade;

public:
    // Default constructor
    Student();

    // Parameterized constructor
    Student(int id, const std::string& name, int age, const std::string& department, double grade);

    // Getters (Accessors)
    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getDepartment() const;
    double getGrade() const;

    // Setters (Mutators)
    void setName(const std::string& name);
    void setAge(int age);
    void setDepartment(const std::string& department);
    void setGrade(double grade);

    // Helper functions
    std::string getAcademicStatus() const;
    void display() const;
};

#endif // STUDENT_H
