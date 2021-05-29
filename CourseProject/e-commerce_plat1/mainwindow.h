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
    QPushButton *password_change_btn;
    QPushButton *top_up_btn;
    QPushButton *logout_btn;
    PasswordChanger *password_changer;
    WalletTopUper *wallet_top_uper;
    void changePassword();
    void changePasswordDone();
    void topUpWallet();
    void topUpWalletDone();
    void changeUser();
public:
    MainWindow(User *user, QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void toLogin();
};
#endif // MAINWINDOW_H
