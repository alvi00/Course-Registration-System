# Course Registration System (C++ with Linked Lists)

This is a simple course registration system written in C++. It uses **Singly Linked Lists** to store and manage data about students and courses.

---

## Features

- Student can:

  - Register and log in
  - View all courses
  - Register for a course
  - Drop a course

- Admin can:
  - Add, update, or delete courses
  - View all students and courses
  - Delete a student

---

## Data Structures Used

- Singly Linked List for:
  - Students
  - Courses
  - Registered courses for each student

---

## Compilation Instructions

Make sure you have **g++** installed on your system.

### If all files are in one folder:

Open terminal or command prompt in that folder, then run:

```bash
g++ -std=c++11 -Iinclude src/\*.cpp -o course_registration

```

```bash
course_registration
```

---

## Sample Test Scenarios

- Register a new student
- Log in as student or admin
- Add courses as admin
- Register/drop courses as student
- Delete courses or students as admin

---

## File Overview

| File                    | Purpose                                    |
| ----------------------- | ------------------------------------------ |
| `main.cpp`              | Starts the program and shows the menu      |
| `admin.h/.cpp`          | Admin actions (add/update/delete courses)  |
| `student_portal.h/.cpp` | Student registration and login             |
| `utils.h/.cpp`          | Helper functions (searching, validation)   |
| `student.h`             | Defines Student struct                     |
| `course.h`              | Defines Course struct                      |
| `student_course_node.h` | Defines struct for student's courses       |
| `global.h/.cpp`         | Global variables for student & course list |

---
