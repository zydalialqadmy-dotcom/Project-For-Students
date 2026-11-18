#include "Student.h"
#include <iostream>
#include <iomanip>

// Default constructor
Student::Student()
    : id(0), name(""), age(0), department(""), grade(0.0) {}

// Parameterized constructor
Student::Student(int id, const std::string& name, int age, const std::string& department, double grade)
    : id(id), name(name), age(age), department(department), grade(grade) {}

// Getters
int Student::getId() const {
    return id;
}

std::string Student::getName() const {
    return name;
}

int Student::getAge() const {
    return age;
}

std::string Student::getDepartment() const {
    return department;
}

double Student::getGrade() const {
    return grade;
}

// Setters
void Student::setName(const std::string& newName) {
    name = newName;
}

void Student::setAge(int newAge) {
    age = newAge;
}

void Student::setDepartment(const std::string& newDepartment) {
    department = newDepartment;
}

void Student::setGrade(double newGrade) {
    grade = newGrade;
}

// Determines the academic status based on grade
std::string Student::getAcademicStatus() const {
    if (grade >= 90.0) {
        return "Excellent";
    } else if (grade >= 80.0) {
        return "Very Good";
    } else if (grade >= 70.0) {
        return "Good";
    } else if (grade >= 50.0) {
        return "Pass";
    } else {
        return "Failed";
    }
}

// Displays a formatted table row of the student's details
void Student::display() const {
    std::cout << std::left
              << std::setw(8)  << id
              << std::setw(24) << name
              << std::setw(6)  << age
              << std::setw(22) << department
              << std::setw(8)  << std::fixed << std::setprecision(1) << grade
              << std::setw(12) << getAcademicStatus()
              << std::endl;
}
