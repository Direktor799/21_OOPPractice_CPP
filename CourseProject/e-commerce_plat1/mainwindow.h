#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "accountmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    User *now_user;
    Login *login_window;
    QPushButton *account_btn;
    QPushButton *logout_btn;
    AccountManager *my_account;
    void setUser(User *user);
    void toLogin();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
