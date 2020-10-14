#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "schedule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

    void on_loadButton_clicked();

private:
    Ui::Widget *ui;

    Schedule schedule;

    QString fileDir;

    void load();
};
#endif // WIDGET_H
