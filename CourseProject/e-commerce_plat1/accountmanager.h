#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QValidator>
#include <QKeyEvent>
#include "user.h"

class AccountManager : public QWidget
{
    Q_OBJECT
protected:
    User *now_user;
    QPushButton *submit_btn;
    virtual void keyPressEvent(QKeyEvent *ev);
public:
    explicit AccountManager(User *user, QWidget *parent = nullptr);
signals:

};

class PasswordChanger : public AccountManager
{
    Q_OBJECT
private:
    QLabel *old_password_text;
    QLineEdit *old_password_box;
    QLabel *new_password_text;
    QLineEdit *new_password_box;
    QLabel *confirm_password_text;
    QLineEdit *confirm_password_box;
    QLabel *error_text;
    void changePassword();
public:
    explicit PasswordChanger(User *user, QWidget *parent = nullptr);
signals:
};

class WalletTopUper : public AccountManager
{
    Q_OBJECT
private:
    QLabel *balance_text;
    QLabel *top_up_text;
    QLineEdit *top_up_box;
    QString getBalanceString() const;
    void topUpWallet();
public:
    explicit WalletTopUper(User *user, QWidget *parent = nullptr);
signals:
};

#endif // ACCOUNTMANAGER_H
