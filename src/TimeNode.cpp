#include "TimeNode.h"
#include <iostream>

using namespace std;

// Simple node to store one student name (no STL allowed)
static const int MAX_NAME_LEN = 256;

struct NameNode {
    char name[MAX_NAME_LEN];
    NameNode* next;

    NameNode(const char* sourceName)
        : next(nullptr)
    {
        int index = 0;
        while (sourceName != nullptr &&
               sourceName[index] != '\0' &&
               index < MAX_NAME_LEN - 1)
        {
            name[index] = sourceName[index];
            index++;
        }
        name[index] = '\0';
    }
};

TimeNode::TimeNode(double startTimeValue)
    : startTime(startTimeValue),
      matchcount(0),
      studentName(nullptr),
      next(nullptr)
{
    // constructor body required
}

TimeNode::~TimeNode()
{
    // TODO:
    // 1) Delete the NameNode linked list starting at studentNames
    // 2) Set studentNames = nullptr (optional safety)
    //
    // NOTE:
    // Do NOT delete 'next' here; Schedule deletes the TimeNode chain.

    NameNode* currentNameNode = studentName;

    while (currentNameNode != nullptr) {
        NameNode* nodeToDelete = currentNameNode;
        currentNameNode = currentNameNode -> next;
        delete nodeToDelete;
    }
    studentName = nullptr; 
}

void TimeNode::addStudentName(const char* studentNameParam)
{
    // TODO:
    // 1) Create a new NameNode that stores a copy of studentName
    // 2) Insert into the studentNames list
    // 3) Increment matchCount

    if (studentNameParam == nullptr) {
        return;
    }

    NameNode* newNameNode = new NameNode(studentNameParam);

    newNameNode -> next = studentName;
    studentName = newNameNode;

    matchcount++;
}

void TimeNode::printStudentNames() const
{
    NameNode* currentNameNode = studentName;
    while (currentNameNode != nullptr) {
        cout << "  " << currentNameNode->name << endl;
        currentNameNode = currentNameNode->next;
    }
}
