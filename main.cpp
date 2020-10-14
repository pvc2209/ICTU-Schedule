#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("PCC");
    a.setOrganizationDomain("PCDomain");
    a.setApplicationName("ICTU Schedule");

    Widget w;
    w.setWindowTitle("ICTU Schedule");
    w.show();
    return a.exec();
}
