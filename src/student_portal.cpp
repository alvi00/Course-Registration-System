#include <iostream>
#include <limits>
#include "admin.h"
#include "course.h"
#include "global.h"
#include "student_course_node.h" 
#include "student_portal.h" 
#include "utils.h"

using namespace std;

void registerStudent() {
    string id, name, email, password;

    cout << "Enter Student ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;

    Student* newStudent = new Student{id, name, email, password, nullptr, nullptr};

    newStudent->next = studentHead;
    studentHead = newStudent;

    cout << "Student registered successfully.\n";
}



void dropStudentFromCourse() {
    string sid, cid;
    cout << "Enter Student ID: ";
    cin >> sid;
    cout << "Enter Course ID: ";
    cin >> cid;

    Student* student = findStudentByID(sid);
    Course* course = findCourseByID(cid);
    if (!student || !course) {
        cout << "Invalid student or course ID.\n";
        return;
    }
    StudentCourseNode* prev = nullptr;
    StudentCourseNode* curr = student->registeredCourses;
    while (curr && curr->course != course) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        cout << "Student is not registered in this course.\n";
        return;
    }
    if (prev) prev->next = curr->next;
    else student->registeredCourses = curr->next;
    course->enrolledCount--;
    delete curr;
    cout << "Course dropped successfully.\n";
}

void studentLogin() {
    string id;
    cout << "Enter your Student ID: ";
    cin >> id;
    Student* student = findStudentByID(id);
    if (!student) {
        cout << "Student not found.\n";
        return;
    }
    string pass;
    cout << "Enter Password: ";
    cin >> pass;
    if (student->password != pass) {
        cout << "Incorrect password.\n";
        return;
    }

    int choice;
    do {
        cout << "\nWelcome, " << student->name << "!\n";
        cout << "1. View Registered Courses\n2. Register for a Course\n3. Drop a Course\n0. Logout\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                StudentCourseNode* n = student->registeredCourses;
                if (!n) cout << "No registered courses.\n";
                while (n) {
                    cout << n->course->courseID << " - " << n->course->title << endl;
                    n = n->next;
                }
                break;
            }
            case 2: {
                string cid;
                cout << "Enter Course ID to register: ";
                cin >> cid;
                Course* course = findCourseByID(cid);
                if (!course) {
                    cout << "Course not found.\n";
                } else if (course->enrolledCount >= course->maxCapacity) {
                    cout << "Course is full.\n";
                } else if (isStudentRegisteredInCourse(student, course)) {
                    cout << "Already registered in this course.\n";
                } else {
                    StudentCourseNode* node = new StudentCourseNode();
                    node->course = course;
                    node->next = student->registeredCourses;
                    student->registeredCourses = node;
                    course->enrolledCount++;
                    cout << "Course registered successfully.\n";
                }
                break;
            }
            case 3: {
                string cid;
                cout << "Enter Course ID to drop: ";
                cin >> cid;
                Course* course = findCourseByID(cid);
                if (!course) {
                    cout << "Course not found.\n";
                    break;
                }
            
                StudentCourseNode* prev = nullptr;
                StudentCourseNode* curr = student->registeredCourses;
                while (curr && curr->course != course) {
                    prev = curr;
                    curr = curr->next;
                }
                if (!curr) {
                    cout << "You are not registered in this course.\n";
                } else {
                    if (prev) prev->next = curr->next;
                    else student->registeredCourses = curr->next;
                    course->enrolledCount--;
                    delete curr;
                    cout << "Course dropped successfully.\n";
                }
                break;
            }            
        }
    } while (choice != 0);
}
