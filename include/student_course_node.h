#ifndef STUDENT_COURSE_NODE_H
#define STUDENT_COURSE_NODE_H
#include "course.h"

struct StudentCourseNode {
    Course* course;
    StudentCourseNode* next;
};

#endif // STUDENT_COURSE_NODE_H