#include "admin.h"
#include "course.h"
#include "global.h"
#include "student_course_node.h" 
#include "student_portal.h" 
#include "utils.h"
#include <cstdlib>

Student* findStudentByID(const std::string& id) {
    Student* temp = studentHead;
    while (temp) {
        if (temp->studentID == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}

Course* findCourseByID(const std::string& id) {
    Course* temp = courseHead;
    while (temp) {
        if (temp->courseID == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}

bool isStudentRegisteredInCourse(Student* student, Course* course) {
    StudentCourseNode* temp = student->registeredCourses;
    while (temp) {
        if (temp->course == course) return true;
        temp = temp->next;
    }
    return false;
}



void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
