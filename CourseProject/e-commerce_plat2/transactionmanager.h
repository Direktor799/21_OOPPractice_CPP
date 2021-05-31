#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QPair>
#include <QHeaderView>
#include <QLabel>
#include "user.h"
#include "product.h"
#include "quantitywidget.h"

class TransactionManagerWidget : public QWidget
{
    Q_OBJECT
private:
    User *now_user;
    QVector<QPair<Product *, int> > cart_list;
    QPushButton *cart_btn;
    QPushButton *order_btn;
    void OpenCart();
    void CloseCart();
public:
    explicit TransactionManagerWidget(User *user, QWidget *parent = nullptr);
    void recvAddToCart(Product *product, int amount);

signals:

};

class TransactionManager : public QWidget
{
    Q_OBJECT
private:
    User *now_user;
    QVector<QPair<Product *, int> > &my_list;
    QTableWidget *table_widget;
    QLabel *total_price_text;
    QPushButton *submit_btn;
    void deleteProductInCart(int row, int col);
    void refreshTotalPrice();
    void updateCartList();
public:
    explicit TransactionManager(User *user, QVector<QPair<Product *, int> > &list, QWidget *parent = nullptr);

signals:

};

#endif // TRANSACTIONMANAGER_H
