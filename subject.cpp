#include "subject.h"
#include <QDebug>

Subject::Subject()
{

}

void Subject::print()
{
    qDebug() << "Thu: " << day;
    qDebug() << "Tiet: " << time;
    qDebug() << "Ngay bat dau: " << startDate.toString("dd/MM/yyyy");
    qDebug() << "Ngay ket thuc: " << endDate.toString("dd/MM/yyyy");
    qDebug() << "Lop hoc phan: " << name;
    qDebug() << "Kieu: " << type;
    qDebug() << "Dia diem hoc: " << location;
    qDebug() << "Giang vien: " << teacher;
    qDebug() << "================================================\n";
}

QString Subject::getSubject() const
{
    return "Tiết: " + time + "\n" +
           "Lớp học phần: " + name + "\n" +
           "Kiểu: " + type + "\n" +
           "Địa điểm học: " + location + "\n" +
           "Giảng viên: " + teacher + "\n" +
           "================================================\n\n";
}
