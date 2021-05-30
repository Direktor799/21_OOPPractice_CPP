#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "accountmanager.h"
#include "product.h"
#include "productmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    User *now_user;
    AccountManagerBar *account_manager_bar;
    ProductManager *product_manager;
    void recvToLogin();
public:
    MainWindow(User *user, QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void toLogin();
};
#endif // MAINWINDOW_H
