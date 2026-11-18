# Student Manager (C++)

A beginner-friendly console-based **Student Management System** developed in C++. This project demonstrates fundamental C++ programming practices, basic Object-Oriented Programming (OOP), modular architecture, dynamic vectors, and file handling.

---

## 📂 Project Organization

```text
StudentManager/
│
├── main.cpp        # Console menu loop, CRUD operations, statistics, sorting, and file I/O
├── Student.h       # Student class declaration (header)
├── Student.cpp     # Student class methods implementation
├── students.txt    # Persistent plain-text data store
├── README.md       # Project documentation and learning guide
└── .gitignore      # Ignores build binaries (.exe, .o, .obj)
```

---

## 🎯 C++ Concepts Demonstrated

1. **Variables and Data Types**:
   - `int` for ID and age, `double` for grades, `string` for names and departments.
2. **Object-Oriented Programming (Encapsulation)**:
   - Private member variables protected from unintended external manipulation.
   - Public getters (accessors) and setters (mutators).
   - Dedicated constructors for clean object instantiation.
3. **Dynamic Arrays (`std::vector`)**:
   - Storing a dynamically resizable collection of `Student` objects in memory without hardcoded limits.
4. **Conditions and Loops**:
   - `while` loop keeping the interactive console menu running until exit.
   - `switch` statement for routing menu options.
   - `for` loops for calculating statistics, searching, and displaying tables.
5. **Basic File Handling (`<fstream>`)**:
   - `ifstream` loads existing records into the vector on program startup.
   - `ofstream` synchronizes changes to `students.txt` whenever students are added, edited, deleted, or sorted.
6. **Input Buffer Safety**:
   - Managing `cin.ignore()` and `cin.clear()` to prevent common newline-skipping bugs when mixing `cin >>` with `getline()`.

---

## ✨ Features & Creative Touches

- **Add Student**: Adds a student with ID, Name, Age, Department, and Grade.
  - *Duplicate Prevention*: Automatically verifies ID uniqueness before creating records.
  - *Academic Warning*: Prompts a warning alert if a student's grade is below the passing mark ($< 50$).
  - *Friendly Message*: Confirms successful record addition.
- **View Students**: Displays all records in a formatted table with calculated academic statuses.
- **Search Student**: Locates and displays a specific student by their unique ID.
- **Update Student**: Modifies student details, allowing fields to remain unchanged if left blank.
- **Delete Student**: Safely deletes a record with a confirmation prompt.
- **View Statistics**: Calculates total student count, highest grade (and student), lowest grade (and student), and class average.
- **Sort Students**: Allows ordering records by grade in either descending (highest first) or ascending order.

---

## 📊 Academic Grading Scale

| Grade Range | Academic Status |
| :--- | :--- |
| $90.0 - 100.0$ | Excellent |
| $80.0 - 89.9$ | Very Good |
| $70.0 - 79.9$ | Good |
| $50.0 - 69.9$ | Pass |
| $0.0 - 49.9$ | Failed *(Triggers Warning)* |

---

## 🛠️ How to Compile and Run

### Using GCC / MinGW (Command Line)

Navigate to the `StudentManager` folder in your terminal:

```bash
g++ main.cpp Student.cpp -o StudentManager.exe
```

Run the application:

```bash
./StudentManager.exe
```

### Using IDEs (Visual Studio, Code::Blocks, C-Free, CLion)

1. Create a new C++ Console project.
2. Add `Student.h`, `Student.cpp`, and `main.cpp` to the project's source files.
3. Make sure `students.txt` is located in the working directory next to the executable.
4. Click **Build and Run**.
