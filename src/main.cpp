#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Schedule.h"

static const char* getStudentNameFromPath(const char* filePath)
{
    //TODO: stripe folders and optional .tct extension

    return filePath;
}

static void trimWhitespace(char* text)
{
    //TODO: trim leading/trailing spaces in-place

    (void)text;
}

static bool parseScheduleLine(char* lineBuffer, char* dayTokenOut, int dayTokenOutSize, char** timePartOut)
{
    // TODO: split at ':' and return day + timePart

    (void)lineBuffer;
    (void)dayTokenOut;
    (void)dayTokenOutSize;
    (void)timePartOut;
    return false;
}

static void processTimesPart(const char* timePart, int dayIndex, const char* studentName, Schedule& schedule)
{
    //TODO: split by ',' -> parse double -> validate -> schedule.addChoice(...)

    (void)timePart;
    (void)dayIndex;
    (void)studentName;
    (void)schedule;
}

int main(int argc, char* argv[])
{
    //TODO:
    // validate argc (need at laast 1 file)
    // for each file -> open, warn if fail
    // read lines -> parse day/times -> addchoice
    // ask minMatches -> displayMatches

    (void)argc;
    (void)argv;
    return 0;
}
