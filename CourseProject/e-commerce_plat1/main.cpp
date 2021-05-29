#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login *l = new Login();
    int ret_value = a.exec();
    delete l;
    return ret_value;
}
