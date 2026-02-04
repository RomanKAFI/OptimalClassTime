#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Schedule.h"

using namespace std;

// buffer sizes for reading and copying
static const int MAX_NAME_LEN = 512;
static const int MAX_LINE_LEN = 1024;

static const char* getStudentNameFromPath(const char* filePath)
{
    //TODO: stripe folders and optional .tct extension
    if (filePath == nullptr) return filePath;
    // find where the filename starts (after last slash)
    const char* filenameStart = filePath;
    for (int i = 0; filePath[i] != '\0'; i++) {
        if (filePath[i] == '/') filenameStart = filePath + i + 1;
    }
    // copy into our buffer so we can change it
    static char nameBuf[MAX_NAME_LEN];
    int len = 0;
    while (filenameStart[len] != '\0' && len < MAX_NAME_LEN - 1) {
        nameBuf[len] = filenameStart[len];
        len++;
    }
    nameBuf[len] = '\0';
    // take off .tct if it's there
    if (len >= 4 && nameBuf[len-4] == '.' && nameBuf[len-3] == 't' && nameBuf[len-2] == 'c' && nameBuf[len-1] == 't') {
        nameBuf[len - 4] = '\0';
    }
    return nameBuf;
}

static void trimWhitespace(char* text)
{
    //TODO: trim leading/trailing spaces in-place
    if (text == nullptr) return;
    // skip leading spaces
    int readPos = 0;
    while (text[readPos] == ' ' || text[readPos] == '\t') readPos++;
    // shift everything left
    int writePos = 0;
    while (text[readPos] != '\0') {
        text[writePos] = text[readPos];
        writePos++;
        readPos++;
    }
    text[writePos] = '\0';
    // remove trailing spaces (find last non-space and cut there)
    int lastGood = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] != ' ' && text[i] != '\t') lastGood = i;
    }
    text[lastGood + 1] = '\0';
}

static bool parseScheduleLine(char* lineBuffer, char* dayTokenOut, int dayTokenOutSize, char** timePartOut)
{
    // TODO: split at ':' and return day + timePart
    if (lineBuffer == nullptr || dayTokenOut == nullptr || timePartOut == nullptr || dayTokenOutSize <= 0) return false;
    // find the colon
    int colonIdx = 0;
    while (lineBuffer[colonIdx] != '\0' && lineBuffer[colonIdx] != ':') colonIdx++;
    if (lineBuffer[colonIdx] != ':') return false;
    lineBuffer[colonIdx] = '\0';
    // copy day part into dayTokenOut
    int dayLen = 0;
    while (lineBuffer[dayLen] != '\0' && dayLen < dayTokenOutSize - 1) {
        dayTokenOut[dayLen] = lineBuffer[dayLen];
        dayLen++;
    }
    dayTokenOut[dayLen] = '\0';
    // time part is after the colon
    *timePartOut = lineBuffer + colonIdx + 1;
    return true;
}

static void processTimesPart(const char* timePart, int dayIndex, const char* studentName, Schedule& schedule)
{
    //TODO: split by ',' -> parse double -> validate -> schedule.addChoice(...)
    if (timePart == nullptr || studentName == nullptr) return;
    // copy so we can split it up
    char copy[MAX_LINE_LEN];
    int i = 0;
    while (timePart[i] != '\0' && i < MAX_LINE_LEN - 1) {
        copy[i] = timePart[i];
        i++;
    }
    copy[i] = '\0';
    // go through each time separated by comma
    int pos = 0;
    while (copy[pos] != '\0') {
        while (copy[pos] == ' ' || copy[pos] == ',') pos++;
        if (copy[pos] == '\0') break;
        int startPos = pos;
        while (copy[pos] != '\0' && copy[pos] != ',') pos++;
        if (copy[pos] == ',') {
            copy[pos] = '\0';
            pos++;
        }
        trimWhitespace(copy + startPos);
        if (copy[startPos] != '\0') {
            double timeVal = atof(copy + startPos);
            if (Schedule::isValidStartTime(timeVal)) {
                schedule.addChoice(dayIndex, timeVal, studentName);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    //TODO:
    // validate argc (need at laast 1 file)
    // for each file -> open, warn if fail
    // read lines -> parse day/times -> addchoice
    // ask minMatches -> displayMatches

    if (argc < 2) {
        cerr << "Need at least one schedule file." << endl;
        return 1;
    }
    Schedule schedule;
    for (int fileNum = 1; fileNum < argc; fileNum++) {
        ifstream inFile(argv[fileNum]);
        if (!inFile.is_open()) {
            cerr << "Cannot open file: " << argv[fileNum] << endl;
            continue;
        }
        const char* studentName = getStudentNameFromPath(argv[fileNum]);
        char line[MAX_LINE_LEN];
        while (inFile.getline(line, MAX_LINE_LEN)) {
            trimWhitespace(line);
            if (line[0] == '\0') continue;
            char dayToken[32];
            char* timePart = nullptr;
            if (!parseScheduleLine(line, dayToken, 32, &timePart)) continue;
            trimWhitespace(dayToken);
            int dayIdx = Schedule::dayToIndex(dayToken);
            if (dayIdx < 0) continue;
            trimWhitespace(timePart);
            processTimesPart(timePart, dayIdx, studentName, schedule);
        }
        inFile.close();
    }
    int minMatches = 0;
    cout << "Minimum number of matches? ";
    cin >> minMatches;
    schedule.displayMatches(minMatches);
    return 0;
}
