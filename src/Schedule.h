#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "TimeNode.h"

/** schedule stores 7 linked lists 1 per day of week
 *  index mapping:
 *   0=sun, 1=mon, 2=tue, 3=wed, 4=thu, 5=fri, 6=sat
*/

class Schedule {
    private:
        TimeNode* dayHeads[7];

    public:
        Schedule();
        ~Schedule();

        // add a time choce for a student (creates or updates a node)
        void addChoice(int dayIndex, double startTimeValue, const char* studentName);

        // display nodes with matchcount >= miniMatches
        void displayMatches(int minMatches) const;

        //helpers
        static int dayToIndex(const char* dayToken);
        static bool isValidStartTime(double startTimeValue);

};
#endif

