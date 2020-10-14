#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QSettings>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSettings settings;
    fileDir = settings.value("filedir").toString();
    schedule.loadData(fileDir);

    ui->label->setText(schedule.getCurrentSubjects(TODAY));
    ui->groupBox->setTitle(schedule.getVNDate());

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    ui->label->setText(schedule.getCurrentSubjects(TODAY));
    ui->groupBox->setTitle(schedule.getVNDate());
}

void Widget::on_pushButton_clicked()
{
    ui->label->setText(schedule.getCurrentSubjects(YESTERDAY));
    ui->groupBox->setTitle(schedule.getVNDate());
}

void Widget::on_pushButton_3_clicked()
{
    ui->label->setText(schedule.getCurrentSubjects(NEXTDAY));
    ui->groupBox->setTitle(schedule.getVNDate());
}


void Widget::on_pushButton_4_clicked()
{
    fileDir = QFileDialog::getOpenFileName(this, "Open the file");

    QDir dir(fileDir);
    ui->label_2->setText(dir.dirName());
}

void Widget::on_loadButton_clicked()
{
    bool success = schedule.loadData(fileDir);

    QString message;
    if (success) {
        message = "Đọc dữ liệu thành công";
    } else {
        message = "Đọc dữ liệu thất bại";
    }

    QMessageBox::about(this, "Thông báo", message);

    if (!success) {
        return;
    }

    QSettings settings;
    settings.setValue("filedir", fileDir);
}
