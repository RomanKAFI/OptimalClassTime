#include "Schedule.h"
#include <iostream>
#include <cctype> 

Schedule::Schedule()
{
    // TODO: init dayHeads[] to nullptr
}

Schedule::~Schedule()
{
    //TODO: delete all TimeNode chains for each dayHead
}

void Schedule::addChoice(int dayIndex, double startTimeValues, const char* studentName)
{
    //TODO:
    // validate dayIndex (0..6)
    // validate startTimeValue (.0/.5, 0..23.5)
    // find/insert TimeNode in stored order
    // addStrudentName(studentName) and update matchCount

    (void)dayIndex;
    (void)startTimeValues;
    (void)studentName;
}

void Schedule::displayMatches(int minMatches) const
{
    // TODO: traverse all days and print nodes with matchCount >= minMatches

    (void)minMatches;
}

int Schedule::dayToIndex(const char* dayToken)
{
    //TODO: map 'sun'..'sat' to 0..6 

    (void)dayToken;
    return -1;
}

bool Schedule::isValidStartTime(double startTimeValue)
{
    // TODO: check 0..23.5 and fractional part is .0 or .5

    (void)startTimeValue;
    return false;
}