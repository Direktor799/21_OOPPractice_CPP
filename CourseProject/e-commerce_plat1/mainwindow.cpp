#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800, 600);
    hide();
    login_window = new Login();
}

MainWindow::~MainWindow()
{
}

