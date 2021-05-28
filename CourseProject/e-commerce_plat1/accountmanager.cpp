#include "accountmanager.h"

AccountManager::AccountManager(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_QuitOnClose,false);
    setFixedSize(200, 200);
    setWindowTitle("AccountManager");
    username_label = new QLabel(this);
    username_label->move(20, 30);
    password_label = new QLabel(this);
    password_label->move(20, 60);
    balance_label = new QLabel(this);
    balance_label->move(20, 90);
}

void AccountManager::display()
{
    username_label->setText("用户名:" + now_user->getUserName());
    password_label->setText("密码:" + now_user->getPassword());
    balance_label->setText("余额:" + QString::number(now_user->getBalance()));
    show();
}

void AccountManager::setUser(User *user)
{
    now_user = user;
}
