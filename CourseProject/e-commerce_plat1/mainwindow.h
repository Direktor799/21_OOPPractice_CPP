#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "accountmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    User *now_user;
    QPushButton *login_btn;
    QLabel *user_text;
    QLabel *balance_text;
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
