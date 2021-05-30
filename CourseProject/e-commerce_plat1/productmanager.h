#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <QWidget>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QErrorMessage>
#include <QKeyEvent>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include "product.h"
#include "user.h"

class ProductManager : public QWidget
{
    Q_OBJECT
protected:
    QVector<Product *> &product_list;
    QLabel *product_name_text;
    QLineEdit *product_name_box;
    QLabel *product_type_text;
    QComboBox *product_type_box;
    QLabel *product_describe_text;
    QTextEdit *product_describe_box;
    QLabel *product_price_text;
    QLineEdit *product_price_box;
    QLabel *product_amount_text;
    QLineEdit *product_amount_box;
    QPushButton *submit_btn;
    virtual void keyPressEvent(QKeyEvent *ev);
public:
    explicit ProductManager(QVector<Product *> &list, QWidget *parent = nullptr);
    virtual ~ProductManager(){};
signals:

};

class ProductAdder : public ProductManager
{
    Q_OBJECT
private:
    void addProduct();
public:
    explicit ProductAdder(QVector<Product *> &list, QWidget *parent = nullptr);
    virtual ~ProductAdder(){};
signals:

};

class ProductModifier : public ProductManager
{
    Q_OBJECT
private:
    const int now_index;
    QPushButton *stop_sale_btn;
    void modifyProduct();
    void deleteProduct();
public:
    explicit ProductModifier(QVector<Product *> &list, int index, QWidget *parent = nullptr);
    virtual ~ProductModifier(){};
signals:

};

class ProductDisplayer : public QWidget
{
    Q_OBJECT
private:
    QVector<Product *> &product_list;
    const int now_index;
    QLabel *product_name_text;
    QLabel *product_type_text;
    QLabel *product_describe_text;
    QLabel *product_price_text;
    QLabel *product_amount_text;
public:
    explicit ProductDisplayer(QVector<Product *> &list, int index, QWidget *parent = nullptr);
    virtual ~ProductDisplayer(){};
signals:

};

class ProductManagerWidget : public QWidget
{
    Q_OBJECT
private:
    User *now_user;
    QVector <Product *> product_list;
    QTableWidget *table_widget;
    QPushButton *add_product_btn;
    ProductAdder *product_adder;
    ProductModifier *product_modifier;
    ProductDisplayer *product_displayer;
    void refreshTableWidget();
    void addProduct();
    void addProductDone();
    void modifyProduct(QTableWidgetItem *item);
    void modifyProductDone();
    void displayProduct(QTableWidgetItem *item);
    void displayProductDone();
public:
    explicit ProductManagerWidget(User *user, QWidget *parent = nullptr);
    ~ProductManagerWidget();
signals:

};

#endif // PRODUCTMANAGER_H
