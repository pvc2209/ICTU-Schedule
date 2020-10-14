#include "schedule.h"
#include <QString>
#include <QDebug>

Schedule::Schedule()
{
    day = QDate::currentDate();
}

Schedule::~Schedule()
{

}

bool Schedule::compareTime(Subject subject1, Subject subject2)
{
    return subject1.getTime()[0] < subject2.getTime()[0];
}

QString Schedule::readCellWString(BasicExcelWorksheet* sheet, size_t row, size_t col)
{
    return QString::fromWCharArray(sheet->Cell(row, col)->GetWString());
}

QDate Schedule::readStartDate(BasicExcelWorksheet* sheet, size_t row, size_t col)
{
    QString subjectDate = (readCellWString(sheet, row, col));
    int startDay = subjectDate.left(2).toInt();
    int startMonth = subjectDate.mid(3, 2).toInt();
    int startYear = subjectDate.mid(6, 4).toInt();

    return QDate(startYear, startMonth, startDay);
}

QDate Schedule::readEndDate(BasicExcelWorksheet* sheet, size_t row, size_t col)
{
    QString subjectDate = (readCellWString(sheet, row, col));
    int endDay = subjectDate.mid(12, 2).toInt();
    int endMonth = subjectDate.mid(15, 2).toInt();
    int endYear = subjectDate.mid(18, 4).toInt();

    return QDate(endYear, endMonth, endDay);
}

Subject Schedule::readSubject(BasicExcelWorksheet* sheet, size_t row)
{
    Subject subject;
    subject.setDay(readCellWString(sheet, row, 0));
    subject.setName(readCellWString(sheet, row, 8));
    subject.setTime(readCellWString(sheet, row, 1));
    subject.setType(readCellWString(sheet, row, 17));
    subject.setLocation(readCellWString(sheet, row, 18));
    subject.setTeacher(readCellWString(sheet, row, 24));

    subject.setStartDate(readStartDate(sheet, row, 3));
    subject.setEndDate(readEndDate(sheet, row, 3));

    return subject;
}

bool Schedule::loadData(QString fileName)
{
    BasicExcel basicExcel;
    bool loaded = basicExcel.Load(fileName.toLocal8Bit().data());
    if (!loaded) {
        qDebug() << "Can't load file " << fileName;
        return false;
    }

    BasicExcelWorksheet* sheet1 = basicExcel.GetWorksheet((size_t)0);

    if (sheet1) {
        // Bug when load file multiple times
        // vector will add a lot of subjects
        // so We need delete all data in vector first,
        subjects.clear();

        size_t maxRow = sheet1->GetTotalRows();

        QString currentDay;
        for (size_t i = 6; i < maxRow; ++i) {
            Subject subject = readSubject(sheet1, i);

            if (subject.getDay() != "") {
                currentDay = subject.getDay();
            } else {
                subject.setDay(currentDay);
            }

            subjects.push_back(subject);
        }

        // Sort subjects by start time
        sort(subjects.begin(), subjects.end(), compareTime);
    } else {
        qDebug() << "Can't get worksheet";
    }

    // Close Excel file after reading
    basicExcel.close();

    return true;
}

void Schedule::print()
{
    for (auto &subject : subjects) {
        subject.print();
    }
}

void Schedule::printTodaySubjects()
{

    QString vnDay;
    switch (day.dayOfWeek()) {
        case 1:
            vnDay = "T2";
            break;
        case 2:
            vnDay = "T3";
            break;
        case 3:
            vnDay = "T4";
            break;
        case 4:
            vnDay = "T5";
            break;
        case 5:
            vnDay = "T6";
            break;
        case 6:
            vnDay = "T7";
            break;
        case 7:
            vnDay = "CN";
            break;
    }

    bool isFree = true;
    for (auto &subject : subjects) {
        if (subject.getDay() == vnDay && day >= subject.getStartDate() && day <= subject.getEndDate()) {
           subject.print();
           isFree = false;
        }
    }

    if (isFree) {
        qDebug() << "Hom nay ban ranh!";
    }
}

QString Schedule::getCurrentSubjects(CurrentDay currenday)
{
    if (currenday == TODAY) {
        day = QDate::currentDate();
    } else if (currenday == YESTERDAY) {
        day = day.addDays(-1);
    } else if (currenday == NEXTDAY) {
        day = day.addDays(1);
    }

    QString weekDay = getVNDate().left(2);

    QString currentSubjects;
    bool isFree = true;
    for (auto &subject : subjects) {
        if (subject.getDay() == weekDay && day >= subject.getStartDate() && day <= subject.getEndDate()) {
           currentSubjects += subject.getSubject();
           isFree = false;
        }
    }

    if (isFree) {
        currentSubjects = "Hôm nay bạn rảnh!";
    }

    return currentSubjects;
}

QString Schedule::getVNDate()
{
    QString vnDay;
    switch (day.dayOfWeek()) {
        case 1:
            vnDay = "T2";
            break;
        case 2:
            vnDay = "T3";
            break;
        case 3:
            vnDay = "T4";
            break;
        case 4:
            vnDay = "T5";
            break;
        case 5:
            vnDay = "T6";
            break;
        case 6:
            vnDay = "T7";
            break;
        case 7:
            vnDay = "CN";
            break;
    }

    return vnDay + " " + day.toString("dd/MM/yyyy");
}
