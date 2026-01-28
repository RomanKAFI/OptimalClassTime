#include "TimeNode.h"

TimeNode::TimeNode(double startTimeValue)
    : startTime(startTimeValue),
      matchCount(0),
      studentNames(nullptr),
      next(nullptr)
{
} // constructor body must exist

TimeNode::~TimeNode()
{
    // TODO:
    // 1) Delete the NameNode linked list starting at studentNames
    // 2) Set studentNames = nullptr (optional safety)
    //
    // NOTE:
    // Do NOT delete 'next' here; Schedule deletes the TimeNode chain.
}

void TimeNode::addStudentName(const char* studentName)
{
    // TODO:
    // 1) Create a new NameNode that stores a copy of studentName
    // 2) Insert into the studentNames list
    // 3) Increment matchCount
    //
    // NOTE:
    // Implement this after NameNode exists.

    (void)studentName; // temporary: avoids unused parameter warning
}
