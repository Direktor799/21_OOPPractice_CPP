#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "user.h"

class AccountManager : public QWidget
{
    Q_OBJECT
private:
    User *now_user;
    QLabel *username_label;
    QLabel *password_label;
    QLabel *balance_label;
    QPushButton *change_password_btn;
    QPushButton *top_up_btn;
public:
    explicit AccountManager(QWidget *parent = nullptr);
    void display();
    void setUser(User *user);
signals:

};

#endif // ACCOUNTMANAGER_H
