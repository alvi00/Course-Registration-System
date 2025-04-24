#ifndef UTILS_H
#define UTILS_H
#include "student.h"
#include "course.h"

Student* findStudentByID(const std::string& id);
Course* findCourseByID(const std::string& id);
bool isStudentRegisteredInCourse(Student* student, Course* course);
void clearScreen();

#endif // UTILS_H