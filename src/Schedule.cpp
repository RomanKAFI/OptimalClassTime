#include "Schedule.h"
#include <iostream>
#include <cctype>
#include <cmath>

Schedule::Schedule()
{
    // TODO: init dayHeads[] to nullptr
    for (int daySlot = 0; daySlot < 7; daySlot++) {
        dayHeads[daySlot] = nullptr;
    }
}

Schedule::~Schedule()
{
    //TODO: delete all TimeNode chains for each dayHead
    for (int daySlot = 0; daySlot < 7; daySlot++) {
        TimeNode* currentTimeNode = dayHeads[daySlot];
        while (currentTimeNode != nullptr) {
            TimeNode* nodeToDelete = currentTimeNode;
            currentTimeNode = currentTimeNode->next;
            delete nodeToDelete;
        }
        dayHeads[daySlot] = nullptr;
    }
}

void Schedule::addChoice(int dayIndex, double startTimeValue, const char* studentName)
{
    //TODO:
    // validate dayIndex (0..6)
    // validate startTimeValue (.0/.5, 0..23.5)
    // find/insert TimeNode in stored order
    // addStrudentName(studentName) and update matchCount
    if (dayIndex < 0 || dayIndex > 6) return;
    if (!isValidStartTime(startTimeValue)) return;
    if (studentName == nullptr) return;

    const double EPS = 1e-9;

    TimeNode* currentTimeNode = dayHeads[dayIndex];
    TimeNode* previousTimeNode = nullptr;
    // find node with same startTime or place to insert
    while (currentTimeNode != nullptr && currentTimeNode->startTime < startTimeValue - EPS) {
        previousTimeNode = currentTimeNode;
        currentTimeNode = currentTimeNode->next;
    }

    if (currentTimeNode != nullptr && std::fabs(currentTimeNode->startTime - startTimeValue) < EPS) {
        currentTimeNode->addStudentName(studentName);
        return;
    }

    TimeNode* newTimeNode = new TimeNode(startTimeValue);
    newTimeNode->addStudentName(studentName);
    newTimeNode->next = currentTimeNode;

    if (previousTimeNode == nullptr) {
        dayHeads[dayIndex] = newTimeNode;
    } else {
        previousTimeNode->next = newTimeNode;
    }
}

void Schedule::displayMatches(int minMatches) const
{
    // TODO: traverse all days and print nodes with matchCount >= minMatches
    static const char* dayNames[] = { "sun", "mon", "tue", "wed", "thu", "fri", "sat" };
    for (int daySlot = 0; daySlot < 7; daySlot++) {
        TimeNode* currentTimeNode = dayHeads[daySlot];
        while (currentTimeNode != nullptr) {
            if (currentTimeNode->matchcount >= minMatches) {
                std::cout << dayNames[daySlot] << " " << currentTimeNode->startTime
                          << ": " << currentTimeNode->matchcount << " matches" << std::endl;
            }
            currentTimeNode = currentTimeNode->next;
        }
    }
}

int Schedule::dayToIndex(const char* dayToken)
{
    //TODO: map 'sun'..'sat' to 0..6
    if (dayToken == nullptr) return -1;

    char c0 = static_cast<char>(std::tolower(static_cast<unsigned char>(dayToken[0])));
    char c1 = static_cast<char>(std::tolower(static_cast<unsigned char>(dayToken[1])));
    char c2 = static_cast<char>(std::tolower(static_cast<unsigned char>(dayToken[2])));

    // compare first 3 chars (sun, mon, tue, etc.)
    if (c0 == 's' && c1 == 'u' && c2 == 'n') return 0;
    if (c0 == 'm' && c1 == 'o' && c2 == 'n') return 1;
    if (c0 == 't' && c1 == 'u' && c2 == 'e') return 2;
    if (c0 == 'w' && c1 == 'e' && c2 == 'd') return 3;
    if (c0 == 't' && c1 == 'h' && c2 == 'u') return 4;
    if (c0 == 'f' && c1 == 'r' && c2 == 'i') return 5;
    if (c0 == 's' && c1 == 'a' && c2 == 't') return 6;

    return -1;
}

bool Schedule::isValidStartTime(double startTimeValue)
{
    // TODO: check 0..23.5 and fractional part is .0 or .5
    if (startTimeValue < 0.0 || startTimeValue > 23.5) return false;

    const double EPS = 1e-9;
    double fractionalPart = startTimeValue - static_cast<int>(startTimeValue);

    // accept fractional part close to 0.0 or 0.5
    if (std::fabs(fractionalPart - 0.0) < EPS) return true;
    if (std::fabs(fractionalPart - 0.5) < EPS) return true;

    return false;
}
