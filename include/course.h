#ifndef COURSE_H
#define COURSE_H
#include <string>

struct Course {
    std::string courseID;
    std::string title;
    int creditHour;
    int maxCapacity;
    int enrolledCount;
    Course* next;
};

#endif // COURSE_H