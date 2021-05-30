#include "accountmanager.h"

AccountManager::AccountManager(User *user, QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_QuitOnClose,false);
    setAttribute(Qt::WA_DeleteOnClose);
    now_user = user;
}

void AccountManager::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter)
        submit_btn->click();
    QWidget::keyPressEvent(ev);
}

PasswordChanger::PasswordChanger(User *user, QWidget *parent) : AccountManager(user, parent)
{
    setFixedSize(250, 150);
    setWindowTitle("修改密码");
    old_password_text = new QLabel("输入旧密码:", this);
    old_password_text->move(20, 12);
    old_password_box = new QLineEdit(this);
    old_password_box->setEchoMode(QLineEdit::Password);
    old_password_box->move(90, 10);

    new_password_text = new QLabel("输入新密码:", this);
    new_password_text->move(20, 42);
    new_password_box = new QLineEdit(this);
    new_password_box->setEchoMode(QLineEdit::Password);
    new_password_box->move(90, 40);

    confirm_password_text = new QLabel("确认新密码:", this);
    confirm_password_text->move(20, 72);
    confirm_password_box = new QLineEdit(this);
    confirm_password_box->setEchoMode(QLineEdit::Password);
    confirm_password_box->move(90, 70);

    error_text = new QLabel(this);
    error_text->setStyleSheet("color: red;");
    error_text->move(100, 100);
    error_text->hide();
    submit_btn = new QPushButton("提交", this);
    submit_btn->move(90, 120);
    connect(submit_btn, &QPushButton::clicked, this, &PasswordChanger::changePassword);
    show();
}

void PasswordChanger::changePassword()
{
    QString old_password_trying = old_password_box->text();
    QString new_password_trying = new_password_box->text();
    QString confirm_password_trying = confirm_password_box->text();
    if (old_password_trying == now_user->getPassword())
    {
        if (new_password_trying != "")
        {
            if (new_password_trying  == confirm_password_trying)
            {
                now_user->setPassword(new_password_trying);
                close();
            }
            else
            {
                error_text->setText("两次输入不一致");
                error_text->adjustSize();
                error_text->show();
            }
        }
        else
        {
            error_text->setText("新密码不能为空");
            error_text->adjustSize();
            error_text->show();
        }
    }
    else
    {
        error_text->setText("旧密码错误");
        error_text->adjustSize();
        error_text->show();
    }
}

WalletTopUper::WalletTopUper(User *user, QWidget *parent) : AccountManager(user, parent)
{
    setFixedSize(200, 120);
    setWindowTitle("余额充值");
    balance_text = new QLabel(getBalanceString(), this);
    balance_text->move(20, 12);

    top_up_text = new QLabel("请输入充值金额:", this);
    top_up_text->move(20, 42);
    top_up_box = new QLineEdit(this);
    top_up_box->setValidator(new QDoubleValidator(0, 20000, 2, this));
    top_up_box->setMaxLength(10);
    top_up_box->setFixedSize(80, 20);
    top_up_box->move(110, 40);
    submit_btn = new QPushButton("确认充值", this);
    submit_btn->move(65, 75);
    connect(submit_btn, &QPushButton::clicked, this, &WalletTopUper::topUpWallet);
    show();
}

QString WalletTopUper::getBalanceString() const
{
    return "当前余额: " + QString::number(now_user->getBalance(), 'f', 2) + "元";
}

void WalletTopUper::topUpWallet()
{
    double top_up_amount = top_up_box->text().toDouble();
    now_user->setBalance(now_user->getBalance() + top_up_amount);
    close();
}
