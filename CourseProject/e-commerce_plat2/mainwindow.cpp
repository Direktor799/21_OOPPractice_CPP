#include "mainwindow.h"

MainWindow::MainWindow(User *user, QWidget *parent) : QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(700, 500);

    now_user = user;
    account_manager_bar = new AccountManagerBar(now_user, this);
    connect(account_manager_bar, &AccountManagerBar::toLogin, this, &MainWindow::recvToLogin);

    product_manager = new ProductManagerWidget(now_user, this);
    product_manager->move(0, 24);

    if (now_user != nullptr)
    {
        transaction_manager = new TransactionManagerWidget(now_user, this);
        connect(product_manager, &ProductManagerWidget::addToCart, transaction_manager, &TransactionManagerWidget::recvAddToCart);
        transaction_manager->move(520, 260);
    }
}

void MainWindow::recvToLogin()
{
    emit toLogin();
    close();
}




MainWindow::~MainWindow()
{

}

