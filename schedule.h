#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "subject.h"
#include <BasicExcel.hpp>
using namespace YExcel;

enum CurrentDay {
    TODAY,
    YESTERDAY,
    NEXTDAY,
};

class Schedule
{
private:
    std::vector<Subject> subjects;
    QDate day;

    static bool compareTime(Subject subject1, Subject subject2);
    QString readCellWString(BasicExcelWorksheet* sheet, size_t row, size_t col);
    QDate readStartDate(BasicExcelWorksheet* sheet, size_t row, size_t col);
    QDate readEndDate(BasicExcelWorksheet* sheet, size_t row, size_t col);
    Subject readSubject(BasicExcelWorksheet* sheet, size_t row);
public:
    Schedule();
    ~Schedule();
    bool loadData(QString fileName);
    void print();
    void printTodaySubjects();

    QString getCurrentSubjects(CurrentDay currenday);
    QString getVNDate();
};

#endif // SCHEDULE_H
