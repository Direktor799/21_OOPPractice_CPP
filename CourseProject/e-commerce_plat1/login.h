#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QKeyEvent>
#include <QButtonGroup>
#include <QRadioButton>
#include <QErrorMessage>
#include "mainwindow.h"
#include "user.h"

class Login : public QWidget
{
    Q_OBJECT
private:
    MainWindow *now_window;
    QLineEdit *username_box;
    QLabel *username_text;
    QLineEdit *password_box;
    QLabel *password_text;
    QLabel *error_text;
    QPushButton *login_btn;
    QPushButton *sign_up_btn;
    QButtonGroup *user_type_btngrp;
    QRadioButton *seller_btn;
    QRadioButton *buyer_btn;
    QVector<User *> user_list;
    void logIn();
    void signUp();
public:
    explicit Login(MainWindow *w, QWidget *parent = nullptr);
    void setDefaultAndShow();
    ~Login();

protected:
    virtual void keyPressEvent(QKeyEvent *ev);

signals:
    void loggedIn(User *now_user);

};

#endif // LOGIN_H
