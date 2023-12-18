// Project 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Course structure
struct Course {
    string courseNum;
    string courseName;
    string prerequisites;
};

// HashTable class
class HashTable {
private:
    static const int DEFAULT_SIZE = 10;
    vector<vector<Course>> table;

public:
    HashTable() : table(DEFAULT_SIZE) {}

    void insert(const Course& course) {
        int key = hash(course.courseNum);
        table[key].push_back(course);
    }

    Course search(const string& courseNum) {
        int key = hash(courseNum);
        for (const auto& course : table[key]) {
            if (course.courseNum == courseNum) {
                return course;
            }
        }
        return { "", "", "" };
    }

    void printSortedCourses() {
        vector<Course> allCourses;
        for (const auto& bucket : table) {
            allCourses.insert(allCourses.end(), bucket.begin(), bucket.end());
        }

        sort(allCourses.begin(), allCourses.end(),
            [](const Course& a, const Course& b) {
                return a.courseNum < b.courseNum;
            });

        cout << "Here is a sample schedule: " << endl << endl;
        for (const auto& course : allCourses) {
            cout << course.courseNum << ", " << course.courseName << endl;
        }
    }

private:
    int hash(const string& courseNum) {
        int sum = 0;
        for (char c : courseNum) {
            sum += static_cast<int>(c);
        }
        return sum % DEFAULT_SIZE;
    }
};

// Function to read data from file and populate the hash table
void loadDataFromFile(HashTable& hashTable, const string& Project2Courses){
    ifstream infile(Project2Courses);
    if (!infile.is_open()) {
        cout << "Sorry, the file was not found." << endl;
        return;
    }

    cout << "File has opened." << endl;

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        vector<string> courseInfo;
        string substr;
        while (getline(ss, substr, ',')) {
            courseInfo.push_back(substr);
        }

        Course course;
        course.courseNum = courseInfo[0];
        course.courseName = courseInfo[1];

        if (courseInfo.size() > 2) {
            course.prerequisites = courseInfo[2];
        }

        hashTable.insert(course);
    }

    cout << "Data structure is loaded." << endl << endl;
}

int main() {
    HashTable courseTable;
    int choice;

    while (true) {
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  4. Exit" << endl;
        cout << "What would you like to do?" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            loadDataFromFile(courseTable, "Project2Courses.txt");
            break;

        case 2:
            courseTable.printSortedCourses();
            break;

        case 3:
            string courseNum;
            cout << endl << "What course do you want to know about?" << endl;
            cin >> courseNum;
            Course result = courseTable.search(courseNum);
            if (result.courseNum.empty()) {
                cout << "Course Number: " << courseNum << " not found." << endl;
            }
            else {
                cout << result.courseNum << ", " << result.courseName << endl
                    << " Prerequisites: " << result.prerequisites << endl;
            }
            break;

        case 4:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        }
        
    }

    return 0;
}


