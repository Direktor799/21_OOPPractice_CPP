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
#include "product.h"

class ProductManager : public QWidget
{
    Q_OBJECT
private:
    QVector <Product *> product_list;
    QTableWidget *table_widget;
public:
    explicit ProductManager(QWidget *parent = nullptr);
    ~ProductManager();
signals:

};

#endif // PRODUCTMANAGER_H
