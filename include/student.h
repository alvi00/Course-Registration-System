#ifndef STUDENT_H
#define STUDENT_H
#include <string>
struct Course;
struct StudentCourseNode;

struct Student {
    std::string studentID;
    std::string name;
    std::string email;
    std::string password; // Add this line
    StudentCourseNode* registeredCourses;
    Student* next;
};


#endif // STUDENT_H