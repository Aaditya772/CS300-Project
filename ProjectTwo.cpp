// ProjectTwo.cpp
// Aaditya Fadnavis
// Aug 17, 2025

// This program uses a binary search tree to create a course planner that 
// can store course information, including course numbers, names, and prerequisites.
// The user can then choose between four options of loading all the data, printing 
// the list of courses, printing the title of prerequisites of a course, or exiting the program.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Struct function to hold the course information.
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Node for Binary Search Tree.
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Inserts course into Binary Search Tree.
void insert(Node*& root, Course course) {
    if (root == nullptr) {
        root = new Node(course);
    } else if (course.courseNumber < root->course.courseNumber) {
        insert(root->left, course);
    } else {
        insert(root->right, course);
    }
}

// In-order print.
void printInOrder(Node* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    cout << root->course.courseNumber << ", " << root->course.courseName << endl;
    printInOrder(root->right);
}

// Search for course.
Node* search(Node* root, string courseNumber) {
    if (root == nullptr || root->course.courseNumber == courseNumber) {
        return root;
    }
    if (courseNumber < root->course.courseNumber) {
        return search(root->left, courseNumber);
    }
    return search(root->right, courseNumber);
}

// Helper: split string by commas.
vector<string> split(const string& line) {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, ',')) {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}

// Load hardcoded data into Binary Search Tree to avoid dependency on external file.
Node* loadCourses() {
    vector<string> rawData = {
        "MATH201,Discrete Mathematics",
        "CSCI300,Introduction to Algorithms,CSCI200,MATH201",
        "CSCI350,Operating Systems,CSCI300",
        "CSCI101,Introduction to Programming in C++,CSCI100",
        "CSCI100,Introduction to Computer Science",
        "CSCI301,Advanced Programming in C++,CSCI101",
        "CSCI400,Large Software Development,CSCI301,CSCI350",
        "CSCI200,Data Structures,CSCI101"
    };

    Node* root = nullptr;

    for (string line : rawData) {
        vector<string> tokens = split(line);
        if (tokens.size() < 2) continue;

        Course course;
        course.courseNumber = tokens[0];
        course.courseName = tokens[1];
        for (size_t i = 2; i < tokens.size(); i++) {
            course.prerequisites.push_back(tokens[i]);
        }

        insert(root, course);
    }
    return root;
}

int main() {
    Node* root = nullptr;
    bool loaded = false;
    int choice;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        cin >> choice;

        if (choice == 1) {
            root = loadCourses();
            loaded = true;
            cout << "Data loaded successfully." << endl;
        } 
        else if (choice == 2) {
            if (!loaded) {
                cout << "Please load the data first." << endl;
            } else {
                cout << "\nHere is a sample schedule:" << endl;
                printInOrder(root);
            }
        } 
        else if (choice == 3) {
            if (!loaded) {
                cout << "Please load the data first." << endl;
            } else {
                cout << "What course do you want to know about? ";
                string courseNumber;
                cin >> courseNumber;
                transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

                Node* result = search(root, courseNumber);
                if (result == nullptr) {
                    cout << "Course not found." << endl;
                } else {
                    cout << result->course.courseNumber << ", " << result->course.courseName << endl;
                    if (result->course.prerequisites.empty()) {
                        cout << "Prerequisites: None" << endl;
                    } else {
                        cout << "Prerequisites: ";
                        for (size_t i = 0; i < result->course.prerequisites.size(); i++) {
                            cout << result->course.prerequisites[i];
                            if (i < result->course.prerequisites.size() - 1) cout << ", ";
                        }
                        cout << endl;
                    }
                }
            }
        } 
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            break;
        } 
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}