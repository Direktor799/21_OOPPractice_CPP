#include "mainwindow.h"

MainWindow::MainWindow(User *user, QWidget *parent) : QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(600, 600);

    now_user = user;
    account_manager_bar = new AccountManagerBar(now_user, this);
    connect(account_manager_bar, &AccountManagerBar::toLogin, this, &MainWindow::recvToLogin);
}

void MainWindow::recvToLogin()
{
    emit toLogin();
    close();
}

MainWindow::~MainWindow()
{

}

