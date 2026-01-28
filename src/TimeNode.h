#ifndef TIMENODE_H
#define TIMENODE_H


class NameNode;

/**
 * node representing a specific start time on a specific day
 * stored in a sorted linked list 
*/
class TimeNode {
    public: 
        double startTime;      // example: 14.5 means 14:30 pm
        int matchcount;        // number of students who selected this time
        NameNode* studentName; // linked list of student names (TODO)
        TimeNode* next;        // next lite node in this day list

        TimeNode(double startTimeValue);
        ~TimeNode();

        void addStudentName(const char* studentName); // TODO: will use NameNode
};

#endif