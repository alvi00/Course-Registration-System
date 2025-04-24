#include <iostream>
#include "admin.h"
#include "course.h"
#include "global.h"
#include "student_course_node.h" 
#include "student_portal.h" 
#include "utils.h"

using namespace std;

bool adminLogin() {
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;
    return (username == "admin" && password == "admin123"); // Change as needed
}


int main() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Course\n2. Update Course\n3. Drop Course\n";
        cout << "4. Register Student\n5. Drop Student from Course\n";
        cout << "6. Student Login\n7. Admin View\n0. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: case 2: case 3: case 7:
                if (adminLogin()) {
                    switch (choice) {
                        case 1: addCourse(); break;
                        case 2: updateCourse(); break;
                        case 3: dropCourseAdmin(); break;
                        case 7: adminView(); break;
                    }
                } else {
                    cout << "Invalid admin credentials.\n";
                }
                break;
            case 4: registerStudent(); break;
            case 5: dropStudentFromCourse(); break;
            case 6: studentLogin(); break;
        }
    } while (choice != 0);
    return 0;
}
