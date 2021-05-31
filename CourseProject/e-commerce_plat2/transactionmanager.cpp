#include "transactionmanager.h"

TransactionManagerWidget::TransactionManagerWidget(User *user, QWidget *parent) : QWidget(parent)
{
    now_user = user;

    setFixedSize(280, 100);

    if (now_user->getUserType() == "Buyer")
    {
        cart_btn = new QPushButton("购物车", this);
        cart_btn->move(10, 0);
        connect(cart_btn, &QPushButton::clicked, this, &TransactionManagerWidget::OpenCart);
        order_btn = new QPushButton("我的订单", this);
        order_btn->move(95, 0);
    }
    else if (now_user->getUserType() == "Seller")
    {
        order_btn = new QPushButton("订单管理", this);
        order_btn->move(50, 0);
    }
}

void TransactionManagerWidget::OpenCart()
{
    new TransactionManager(now_user, cart_list);
}

void TransactionManagerWidget::CloseCart()
{
}


void TransactionManagerWidget::recvAddToCart(Product *product, int amount)
{
    bool found = false;
    for (auto i = cart_list.begin(); i < cart_list.end(); i++)
        if (i->first == product)
        {
            found = true;
            i->second += amount;
        }
    if (!found)
        cart_list.push_back(qMakePair(product, amount));
}


TransactionManager::TransactionManager(User *user, QVector<QPair<Product *, int> > &list, QWidget *parent)
    : QWidget(parent), my_list(list)
{
    now_user = user;

    setAttribute(Qt::WA_QuitOnClose,false);
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(370, 240);
    setWindowTitle("购物车");

    total_price_text = new QLabel(this);
    QFont ft;
    ft.setPointSize(12);
    ft.setBold(true);
    total_price_text->setFont(ft);
    total_price_text->move(20, 210);

    table_widget = new QTableWidget(my_list.size(), 4, this);
    table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table_widget->verticalHeader()->setHidden(true);
    table_widget->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    table_widget->setColumnWidth(0, 180);
    table_widget->setColumnWidth(1, 70);
    table_widget->setColumnWidth(2, 75);
    table_widget->setColumnWidth(3, 20);
    table_widget->setFixedSize(369, 200);
    QStringList header;
    header << "商品名" << "价格" << "数量" << " ";
    table_widget->setHorizontalHeaderLabels(header);
    table_widget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#dddddd;}");
    for (int i = 0; i < my_list.size(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(my_list[i].first->getName());
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 0, item);
        item = new QTableWidgetItem(QString::number(my_list[i].first->getPrice()));
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 1, item);
        QuantityWidget *quantity_widget = new QuantityWidget(1, my_list[i].first->getAmount());
        quantity_widget->setValue(my_list[i].second);
        connect(quantity_widget, &QuantityWidget::valueChanged, this, &TransactionManager::refreshTotalPrice);
        connect(quantity_widget, &QuantityWidget::valueChanged, this, &TransactionManager::updateCartList);
        table_widget->setCellWidget(i, 2, quantity_widget);
        item = new QTableWidgetItem(" ×");
        table_widget->setItem(i, 3, item);
    }
    connect(table_widget, &QTableWidget::cellClicked, this, &TransactionManager::deleteProductInCart);
    connect(table_widget, &QTableWidget::clicked, this, &TransactionManager::refreshTotalPrice);
    refreshTotalPrice();

    submit_btn = new QPushButton("提交订单", this);
    submit_btn->move(280, 207);
    show();
}

void TransactionManager::deleteProductInCart(int row, int col)
{
    if (col == 3)
    {
        table_widget->removeRow(row);
        my_list.erase(my_list.begin() + row);
    }
}

void TransactionManager::refreshTotalPrice()
{
    double total_price = 0;
    for (int i = 0; i < table_widget->rowCount(); i++)
        total_price += table_widget->item(i, 1)->text().toDouble() * ((QuantityWidget *)table_widget->cellWidget(i, 2))->value();
    total_price_text->setText("金额总计:" + QString::number(total_price) + "元");
    total_price_text->adjustSize();
}

void TransactionManager::updateCartList()
{
    for (int i = 0; i < table_widget->rowCount(); i++)
    {
        my_list[i].second = ((QuantityWidget *)table_widget->cellWidget(i, 2))->value();
    }
}
