#include "productmanager.h"

ProductManager::ProductManager(QWidget *parent) : QWidget(parent)
{
    //读取json并存入product_list
    QDir info_dir = QDir::currentPath();
    info_dir.cdUp();
    info_dir.cd("data");
    QFile product_file(info_dir.path() + "/product_info.json");
    if (!product_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QErrorMessage *error = new QErrorMessage();
        error->showMessage("商品文件读取错误");
    }
    QString value = product_file.readAll();
    QJsonArray array = QJsonDocument::fromJson(value.toUtf8()).object().value(QStringLiteral("product_info")).toArray();
    for (int i = 0; i < array.size(); i++)
    {
        Product *new_product;
        QString name = array[i].toObject()["name"].toString();
        QString type = array[i].toObject()["type"].toString();
        QString describe = array[i].toObject()["describe"].toString();
        double price = array[i].toObject()["price"].toDouble();
        int amount = array[i].toObject()["amount"].toInt();
        if (type == "Book")
            new_product = new BookProduct(name, describe, price, amount);
        else if (type == "Electronic")
            new_product = new ElectronicProduct(name, describe, price, amount);
        else if (type == "Clothing")
            new_product = new ClothingProduct(name, describe, price, amount);
        else
            new_product = new Product(name, describe, price, amount);
        product_list.push_back(new_product);
    }
    product_file.close();

    //界面
    table_widget = new QTableWidget(10, 4, this);
    table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table_widget->setColumnWidth(0, 200);
    table_widget->setColumnWidth(1, 100);
    table_widget->setColumnWidth(2, 100);
    table_widget->setColumnWidth(3, 100);
    table_widget->setFixedSize(550, 450);
    QStringList header;
    header << "商品名" << "类别" << "价格" << "数量";
    table_widget->setHorizontalHeaderLabels(header);
    table_widget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#dddddd;}");
    for (int i = 0; i < product_list.size(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(product_list[i]->getName());
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 0, item);
        item = new QTableWidgetItem(product_list[i]->getType());
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 1, item);
        item = new QTableWidgetItem(QString::number(product_list[i]->getPrice()));
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 2, item);
        item = new QTableWidgetItem(QString::number(product_list[i]->getAmount()));
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 3, item);
    }
    setFixedSize(900, 450);


}

ProductManager::~ProductManager()
{
    //保存商品信息
    QDir info_dir = QDir::currentPath();
    info_dir.cdUp();
    info_dir.cd("data");
    QFile product_file(info_dir.path() + "/product_info.json");
    product_file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QJsonArray array;
    for (auto i = product_list.begin(); i < product_list.end(); i++)
    {
        QJsonObject object;
        object["name"] = (*i)->getName();
        object["type"] = (*i)->getType();
        object["describe"] = (*i)->getDescribe();
        object["price"] = (*i)->getPrice();
        object["amount"] = (*i)->getAmount();
        array.push_back(object);
    }
    QJsonObject object;
    object["product_info"] = array;
    QByteArray data = QJsonDocument(object).toJson(QJsonDocument::Indented);
    product_file.write(data);
    product_file.close();
    //释放内存
    for (auto i = product_list.begin(); i < product_list.end(); i++)
        delete *i;
}
