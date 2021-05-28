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
#include "user.h"

class Login : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *username_box;
    QLabel *username_text;
    QLineEdit *password_box;
    QLabel *password_text;
    QLabel *error_label;
    QPushButton *login_btn;
    QVector<User *> user_list;
    void checkPassword();

public:
    explicit Login(QWidget *parent = nullptr);

protected:
    virtual void keyPressEvent(QKeyEvent *ev);

signals:

};

#endif // LOGIN_H
