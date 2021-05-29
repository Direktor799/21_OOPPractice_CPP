#include "mainwindow.h"

MainWindow::MainWindow(User *user, QWidget *parent) : QMainWindow(parent)
{
    now_user = user;
    password_changer = nullptr;
    wallet_top_uper = nullptr;
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(800, 600);

    password_change_btn = new QPushButton("修改密码", this);
    connect(password_change_btn, &QPushButton::clicked, this, &MainWindow::changePassword);

    top_up_btn = new QPushButton("余额充值", this);
    top_up_btn->move(200, 0);
    connect(top_up_btn, &QPushButton::clicked, this, &MainWindow::topUpWallet);

    logout_btn = new QPushButton("切换用户", this);
    logout_btn->move(400, 0);
    connect(logout_btn, &QPushButton::clicked, this, &MainWindow::changeUser);
}

void MainWindow::changePassword()
{
    if (password_changer == nullptr)
    {
        password_changer = new PasswordChanger(now_user);
        connect(password_changer, &PasswordChanger::destroyed, this, &MainWindow::changePasswordDone);
    }
}

void MainWindow::changePasswordDone()
{
    password_changer = nullptr;
}

void MainWindow::topUpWallet()
{
    if (wallet_top_uper == nullptr)
    {
        wallet_top_uper = new WalletTopUper(now_user);
        connect(wallet_top_uper, &WalletTopUper::destroyed, this, &MainWindow::topUpWalletDone);
    }
}

void MainWindow::topUpWalletDone()
{
    wallet_top_uper = nullptr;
}

void MainWindow::changeUser()
{
    emit toLogin();
    close();
}

MainWindow::~MainWindow()
{

}

