#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Student.h"

using namespace std;

const string DATA_FILE = "students.txt";
const double PASSING_GRADE = 50.0;

// Helper: Checks if a student ID already exists in the list
int findStudentIndexById(const vector<Student>& students, int id) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].getId() == id) {
            return static_cast<int>(i);
        }
    }
    return -1; // Not found
}

// Loads student records from text file into the vector
void loadStudentsFromFile(vector<Student>& students, const string& filename) {
    students.clear();
    ifstream inFile(filename.c_str());

    if (!inFile.is_open()) {
        cout << "[Note] No existing database found. Starting with a fresh list." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, name, ageStr, department, gradeStr;

        if (getline(ss, idStr, ',') &&
            getline(ss, name, ',') &&
            getline(ss, ageStr, ',') &&
            getline(ss, department, ',') &&
            getline(ss, gradeStr, ',')) {

            stringstream idStream(idStr);
            stringstream ageStream(ageStr);
            stringstream gradeStream(gradeStr);

            int id = 0, age = 0;
            double grade = 0.0;

            idStream >> id;
            ageStream >> age;
            gradeStream >> grade;

            students.push_back(Student(id, name, age, department, grade));
        }
    }

    inFile.close();
}

// Saves all student records from the vector to the text file
void saveStudentsToFile(const vector<Student>& students, const string& filename) {
    ofstream outFile(filename.c_str());

    if (!outFile.is_open()) {
        cout << "[Error] Unable to open " << filename << " for saving data!" << endl;
        return;
    }

    for (size_t i = 0; i < students.size(); ++i) {
        outFile << students[i].getId() << ","
                << students[i].getName() << ","
                << students[i].getAge() << ","
                << students[i].getDepartment() << ","
                << students[i].getGrade() << "\n";
    }

    outFile.close();
}

// Prints the table header for displaying students
void printTableHeader() {
    cout << string(84, '-') << endl;
    cout << left
         << setw(8)  << "ID"
         << setw(24) << "Name"
         << setw(6)  << "Age"
         << setw(22) << "Department"
         << setw(8)  << "Grade"
         << setw(12) << "Status"
         << endl;
    cout << string(84, '-') << endl;
}

// 1. Add a new student
void addStudent(vector<Student>& students) {
    cout << "\n--- Add New Student ---" << endl;

    int id = 0;
    cout << "Enter Student ID: ";
    if (!(cin >> id)) {
        cout << "[!] Invalid ID entered. Please enter a valid number." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    // Creative touch: Prevent duplicate student IDs
    if (findStudentIndexById(students, id) != -1) {
        cout << "[!] Error: A student with ID " << id << " already exists! Duplicates are not allowed." << endl;
        cin.ignore(1000, '\n');
        return;
    }

    cin.ignore(1000, '\n'); // Clear remaining newline from buffer

    string name;
    cout << "Enter Full Name: ";
    getline(cin, name);

    int age = 0;
    cout << "Enter Age: ";
    if (!(cin >> age) || age <= 0) {
        cout << "[!] Invalid age entered." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cin.ignore(1000, '\n');

    string department;
    cout << "Enter Department: ";
    getline(cin, department);

    double grade = 0.0;
    cout << "Enter Grade (0 - 100): ";
    if (!(cin >> grade) || grade < 0.0 || grade > 100.0) {
        cout << "[!] Invalid grade entered. Must be between 0 and 100." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    // Creative touch: Warning if grade is below passing threshold
    if (grade < PASSING_GRADE) {
        cout << "\n>> [WARNING] Grade " << grade << " is below the passing score (" << PASSING_GRADE << ")! Academic Status: Failed." << endl;
    }

    // Add to list and save
    students.push_back(Student(id, name, age, department, grade));
    saveStudentsToFile(students, DATA_FILE);

    // Creative touch: Friendly confirmation message
    cout << "\n>> Great news! Student \"" << name << "\" (ID: " << id << ") was added successfully!" << endl;
}

// 2. View all students
void viewStudents(const vector<Student>& students) {
    cout << "\n--- Student Directory ---" << endl;
    if (students.empty()) {
        cout << "No student records found. Add some students first!" << endl;
        return;
    }

    printTableHeader();
    for (size_t i = 0; i < students.size(); ++i) {
        students[i].display();
    }
    cout << string(84, '-') << endl;
    cout << "Total Students: " << students.size() << endl;
}

// 3. Search for a student by ID
void searchStudent(const vector<Student>& students) {
    cout << "\n--- Search Student ---" << endl;
    if (students.empty()) {
        cout << "Directory is empty." << endl;
        return;
    }

    int id = 0;
    cout << "Enter Student ID to search: ";
    if (!(cin >> id)) {
        cout << "[!] Invalid ID entered." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    int index = findStudentIndexById(students, id);
    if (index == -1) {
        cout << "[!] Student with ID " << id << " was not found." << endl;
    } else {
        cout << "\nStudent Record Found:" << endl;
        printTableHeader();
        students[static_cast<size_t>(index)].display();
        cout << string(84, '-') << endl;
    }
}

// 4. Update student information
void updateStudent(vector<Student>& students) {
    cout << "\n--- Update Student ---" << endl;
    if (students.empty()) {
        cout << "Directory is empty." << endl;
        return;
    }

    int id = 0;
    cout << "Enter Student ID to update: ";
    if (!(cin >> id)) {
        cout << "[!] Invalid ID entered." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    int index = findStudentIndexById(students, id);
    if (index == -1) {
        cout << "[!] Student with ID " << id << " was not found." << endl;
        return;
    }

    size_t idx = static_cast<size_t>(index);
    cout << "\nCurrent details for Student ID " << id << ":" << endl;
    printTableHeader();
    students[idx].display();
    cout << string(84, '-') << endl;

    cin.ignore(1000, '\n');

    string name;
    cout << "Enter New Full Name (leave blank to keep current): ";
    getline(cin, name);
    if (!name.empty()) {
        students[idx].setName(name);
    }

    string ageInput;
    cout << "Enter New Age (leave blank to keep current): ";
    getline(cin, ageInput);
    if (!ageInput.empty()) {
        stringstream ss(ageInput);
        int age = 0;
        if (ss >> age && age > 0) {
            students[idx].setAge(age);
        }
    }

    string department;
    cout << "Enter New Department (leave blank to keep current): ";
    getline(cin, department);
    if (!department.empty()) {
        students[idx].setDepartment(department);
    }

    string gradeInput;
    cout << "Enter New Grade (leave blank to keep current): ";
    getline(cin, gradeInput);
    if (!gradeInput.empty()) {
        stringstream ss(gradeInput);
        double grade = 0.0;
        if (ss >> grade && grade >= 0.0 && grade <= 100.0) {
            students[idx].setGrade(grade);
            if (grade < PASSING_GRADE) {
                cout << "\n>> [WARNING] Updated grade (" << grade << ") is below the passing score (" << PASSING_GRADE << ")!" << endl;
            }
        }
    }

    saveStudentsToFile(students, DATA_FILE);
    cout << "\n>> Student ID " << id << " updated successfully!" << endl;
}

// 5. Delete a student
void deleteStudent(vector<Student>& students) {
    cout << "\n--- Delete Student ---" << endl;
    if (students.empty()) {
        cout << "Directory is empty." << endl;
        return;
    }

    int id = 0;
    cout << "Enter Student ID to delete: ";
    if (!(cin >> id)) {
        cout << "[!] Invalid ID entered." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    int index = findStudentIndexById(students, id);
    if (index == -1) {
        cout << "[!] Student with ID " << id << " was not found." << endl;
        return;
    }

    size_t idx = static_cast<size_t>(index);
    string studentName = students[idx].getName();

    char confirm = 'n';
    cout << "Are you sure you want to delete \"" << studentName << "\" (ID: " << id << ")? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        students.erase(students.begin() + index);
        saveStudentsToFile(students, DATA_FILE);
        cout << "\n>> Student \"" << studentName << "\" has been deleted successfully." << endl;
    } else {
        cout << "Deletion canceled." << endl;
    }
}

// 6. View statistics
void viewStatistics(const vector<Student>& students) {
    cout << "\n--- Academic Statistics ---" << endl;
    if (students.empty()) {
        cout << "No student records available to calculate statistics." << endl;
        return;
    }

    double totalGrade = 0.0;
    double highestGrade = students[0].getGrade();
    double lowestGrade = students[0].getGrade();
    string topStudent = students[0].getName();
    string lowStudent = students[0].getName();

    for (size_t i = 0; i < students.size(); ++i) {
        double g = students[i].getGrade();
        totalGrade += g;

        if (g > highestGrade) {
            highestGrade = g;
            topStudent = students[i].getName();
        }
        if (g < lowestGrade) {
            lowestGrade = g;
            lowStudent = students[i].getName();
        }
    }

    double averageGrade = totalGrade / static_cast<double>(students.size());

    cout << left << setw(26) << "Total Students:" << students.size() << endl;
    cout << left << setw(26) << "Highest Grade:"  << fixed << setprecision(1) << highestGrade
         << " (" << topStudent << ")" << endl;
    cout << left << setw(26) << "Lowest Grade:"   << fixed << setprecision(1) << lowestGrade
         << " (" << lowStudent << ")" << endl;
    cout << left << setw(26) << "Overall Class Average:" << fixed << setprecision(2) << averageGrade << endl;
}

// Comparison functions for sorting
bool compareByGradeDescending(const Student& a, const Student& b) {
    return a.getGrade() > b.getGrade();
}

bool compareByGradeAscending(const Student& a, const Student& b) {
    return a.getGrade() < b.getGrade();
}

// 7. Sort students by grade
void sortStudents(vector<Student>& students) {
    cout << "\n--- Sort Students by Grade ---" << endl;
    if (students.size() <= 1) {
        cout << "Need at least 2 students to sort." << endl;
        return;
    }

    cout << "1. Highest to Lowest (Descending)\n";
    cout << "2. Lowest to Highest (Ascending)\n";
    cout << "Choose order (1-2): ";

    int choice = 0;
    if (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "[!] Invalid choice. Sorting canceled." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    if (choice == 1) {
        sort(students.begin(), students.end(), compareByGradeDescending);
        cout << "\n>> Students sorted from highest to lowest grade!" << endl;
    } else {
        sort(students.begin(), students.end(), compareByGradeAscending);
        cout << "\n>> Students sorted from lowest to highest grade!" << endl;
    }

    // Auto-save new order to file and display
    saveStudentsToFile(students, DATA_FILE);
    viewStudents(students);
}

// Main console menu loop
int main() {
    vector<Student> students;
    loadStudentsFromFile(students, DATA_FILE);

    int choice = 0;
    bool running = true;

    cout << "==========================================\n";
    cout << "    Welcome to Student Manager (C++)\n";
    cout << "==========================================\n";
    cout << "Loaded " << students.size() << " student record(s).\n";

    while (running) {
        cout << "\n==========================================\n";
        cout << "              MAIN MENU\n";
        cout << "==========================================\n";
        cout << " 1. Add Student\n";
        cout << " 2. View Students\n";
        cout << " 3. Search Student\n";
        cout << " 4. Update Student\n";
        cout << " 5. Delete Student\n";
        cout << " 6. View Statistics\n";
        cout << " 7. Sort Students\n";
        cout << " 8. Exit\n";
        cout << "==========================================\n";
        cout << "Enter your choice (1-8): ";

        if (!(cin >> choice)) {
            cout << "\n[!] Please enter a valid number between 1 and 8.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                viewStudents(students);
                break;
            case 3:
                searchStudent(students);
                break;
            case 4:
                updateStudent(students);
                break;
            case 5:
                deleteStudent(students);
                break;
            case 6:
                viewStatistics(students);
                break;
            case 7:
                sortStudents(students);
                break;
            case 8:
                cout << "\nThank you for using Student Manager. Goodbye!\n";
                running = false;
                break;
            default:
                cout << "\n[!] Invalid option. Please select a number from 1 to 8.\n";
                break;
        }
    }

    return 0;
}
