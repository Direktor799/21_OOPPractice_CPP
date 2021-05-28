#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800, 600);
    hide();
    login_window = new Login();
    connect(login_window, &Login::loggedIn, this, &MainWindow::setUser);
    account_btn = new QPushButton("我的账户", this);
    my_account = new AccountManager();
    connect(account_btn, &QPushButton::clicked,my_account, &AccountManager::display);
    logout_btn = new QPushButton("注销", this);
    logout_btn->move(200, 0);
    connect(logout_btn, &QPushButton::clicked, this, &MainWindow::toLogin);
}

void MainWindow::setUser(User *user)
{
    now_user = user;
    my_account->setUser(user);
    login_window->hide();
    show();
}

void MainWindow::toLogin()
{
    hide();
    login_window->setDefault();
    login_window->show();
}

MainWindow::~MainWindow()
{
    login_window->~Login();
}

