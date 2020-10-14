#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include <QDate>

class Subject
{
private:
    QString day;
    QString name;
    QString time;
    QString type;
    QString location;
    QString teacher;

    QDate startDate;
    QDate endDate;

public:
    Subject();
    void setDay(QString day) { this->day = day; }
    void setName(QString name) { this->name = name; }
    void setTime(QString time) { this->time = time; }
    void setType(QString type) { this->type = type; }
    void setLocation(QString location) { this->location = location; }
    void setTeacher(QString teacher) { this->teacher = teacher; }
    void setStartDate(QDate startDay) { this->startDate = startDay; }
    void setEndDate(QDate endDay) { this->endDate = endDay; }

    QDate getStartDate() const { return startDate; }
    QDate getEndDate() const { return endDate; }
    QString getDay() const { return day; }
    QString getTime() const { return time; }
    void print();
    QString getSubject() const;
};

#endif // SUBJECT_H
