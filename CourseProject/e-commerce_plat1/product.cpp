#include "product.h"

Product::Product(QString name, QString describe, double price, int amount)
{
    m_name = name;
    m_type = "";
    m_describe= describe;
    m_price = price;
    m_amount = amount;
}

void Product::setName(const QString new_name)
{
    m_name = new_name;
}

void Product::setDescribe(const QString new_describe)
{
    m_describe = new_describe;
}

void Product::setPrice(const double new_price)
{
    m_price = new_price;
}

QString Product::getName() const
{
    return m_name;
}

QString Product::getDescribe() const
{
    return m_describe;
}

QString Product::getType() const
{
    return m_type;
}

double Product::getPrice() const
{
    return m_price;
}

int Product::getAmount() const
{
    return m_amount;
}

BookProduct::BookProduct(QString name, QString describe, double price, int amount) : Product(name, describe, price, amount)
{
    m_type = "Book";
}

ElectronicProduct::ElectronicProduct(QString name, QString describe, double price, int amount) : Product(name, describe, price, amount)
{
    m_type = "Electronic";
}

ClothingProduct::ClothingProduct(QString name, QString describe, double price, int amount) : Product(name, describe, price, amount)
{
    m_type = "Clothing";
}
