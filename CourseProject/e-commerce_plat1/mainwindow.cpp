#include "mainwindow.h"

MainWindow::MainWindow(User *user, QWidget *parent) : QMainWindow(parent)
{
    now_user = user;
    password_changer = nullptr;
    wallet_top_uper = nullptr;
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(800, 600);
    if (now_user != nullptr)
    {
        user_text = new QLabel("欢迎您，" + now_user->getUserName(), this);
        user_text->adjustSize();
        user_text->move(10, 7);
        balance_text = new QLabel("当前余额: " + QString::number(now_user->getBalance(), 'f', 2) + "元", this);
        balance_text->adjustSize();
        balance_text->move(100, 7);

        top_up_btn = new QPushButton("余额充值", this);
        connect(top_up_btn, &QPushButton::clicked, this, &MainWindow::topUpWallet);
        top_up_btn->move(300, 0);

        password_change_btn = new QPushButton("修改密码", this);
        connect(password_change_btn, &QPushButton::clicked, this, &MainWindow::changePassword);
        password_change_btn->move(400, 0);

        logout_btn = new QPushButton("切换用户", this);
        connect(logout_btn, &QPushButton::clicked, this, &MainWindow::changeUser);
        logout_btn->move(500, 0);
    }
    else
    {
        login_btn = new QPushButton("登录", this);
        connect(login_btn, &QPushButton::clicked, this, &MainWindow::changeUser);
    }
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
    balance_text->setText("当前余额: " + QString::number(now_user->getBalance(), 'f', 2) + "元");
    balance_text->adjustSize();
}

void MainWindow::changeUser()
{
    emit toLogin();
    close();
}

MainWindow::~MainWindow()
{

}

