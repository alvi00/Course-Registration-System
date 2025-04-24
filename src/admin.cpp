#include <iostream>
#include <limits>
#include "admin.h"
#include "course.h"
#include "global.h"
#include "student_course_node.h" 
#include "student_portal.h" 
#include "utils.h"

using namespace std;

void addCourse() {
    string courseID;
    cout << "Enter Course ID: ";
    cin >> courseID;

    // Check for duplicate
    if (findCourseByID(courseID)) {
        cout << "Course with this ID already exists.\n";
        return;
    }

    Course* newCourse = new Course();
    newCourse->courseID = courseID;
    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, newCourse->title);
    cout << "Enter Credit Hour: ";
    cin >> newCourse->creditHour;
    cout << "Enter Max Capacity: ";
    cin >> newCourse->maxCapacity;
    newCourse->enrolledCount = 0;
    newCourse->next = courseHead;
    courseHead = newCourse;
    cout << "Course added successfully!\n";
}


void updateCourse() {
    string id;
    cout << "Enter Course ID to update: ";
    cin >> id;
    Course* course = findCourseByID(id);
    if (course) {
        cout << "Enter new Title: ";
        cin.ignore();
        getline(cin, course->title);
        cout << "Enter new Credit Hour: ";
        cin >> course->creditHour;
        cout << "Enter new Max Capacity: ";
        cin >> course->maxCapacity;
        cout << "Course updated successfully!\n";
    } else {
        cout << "Course not found.\n";
    }
}

void dropCourseAdmin() {
    string id;
    cout << "Enter Course ID to delete: ";
    cin >> id;
    Course* prev = nullptr;
    Course* curr = courseHead;
    while (curr && curr->courseID != id) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        cout << "Course not found.\n";
        return;
    }
    if (prev) prev->next = curr->next;
    else courseHead = curr->next;

    // Remove from all student registered lists
    Student* s = studentHead;
    while (s) {
        StudentCourseNode* prevNode = nullptr;
        StudentCourseNode* node = s->registeredCourses;
        while (node) {
            if (node->course == curr) {
                if (prevNode) prevNode->next = node->next;
                else s->registeredCourses = node->next;
                delete node;
                break;
            }
            prevNode = node;
            node = node->next;
        }
        s = s->next;
    }

    delete curr;
    cout << "Course deleted successfully.\n";
}

void adminView() {
    int choice;
    do {
        cout << "\nAdmin View Options:\n";
        cout << "1. List all students with their registered courses\n";
        cout << "2. List all courses with enrolled count\n";
        cout << "3. List students of a particular course\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Student* s = studentHead;
                while (s) {
                    cout << "Student ID: " << s->studentID << ", Name: " << s->name << "\nRegistered Courses:\n";
                    StudentCourseNode* c = s->registeredCourses;
                    if (!c) cout << "  None\n";
                    while (c) {
                        cout << "  " << c->course->courseID << " - " << c->course->title << "\n";
                        c = c->next;
                    }
                    s = s->next;
                }
                break;
            }
            case 2: {
                Course* c = courseHead;
                while (c) {
                    cout << "Course ID: " << c->courseID << ", Title: " << c->title
                         << ", Enrolled: " << c->enrolledCount << "/" << c->maxCapacity << "\n";
                    c = c->next;
                }
                break;
            }
            case 3: {
                string cid;
                cout << "Enter Course ID: ";
                cin >> cid;
                Course* course = findCourseByID(cid);
                if (!course) {
                    cout << "Course not found.\n";
                    break;
                }
                cout << "Students registered in " << course->courseID << ":\n";
                Student* s = studentHead;
                bool found = false;
                while (s) {
                    StudentCourseNode* c = s->registeredCourses;
                    while (c) {
                        if (c->course == course) {
                            cout << "  " << s->studentID << " - " << s->name << "\n";
                            found = true;
                            break;
                        }
                        c = c->next;
                    }
                    s = s->next;
                }
                if (!found) cout << "  No students registered.\n";
                break;
            }
        }
    } while (choice != 0);
}


void deleteStudent() {
    string id;
    cout << "Enter Student ID to delete: ";
    cin >> id;
    Student* prev = nullptr;
    Student* curr = studentHead;
    while (curr && curr->studentID != id) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        cout << "Student not found.\n";
        return;
    }
    if (prev) prev->next = curr->next;
    else studentHead = curr->next;

    // Decrement enrolled count in courses
    StudentCourseNode* n = curr->registeredCourses;
    while (n) {
        n->course->enrolledCount--;
        StudentCourseNode* temp = n;
        n = n->next;
        delete temp;
    }
    delete curr;
    cout << "Student deleted successfully.\n";
}