#include "product.h"

int Product::discount_ratio;
int BookProduct::discount_ratio;
int ElectronicProduct::discount_ratio;
int ClothingProduct::discount_ratio;

Product::Product(QString name, QString describe, double price, int amount, QString type)
{
    m_name = name;
    m_type = type;
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

void Product::setOriginalPrice(const double new_price)
{
    m_price = new_price;
}

void Product::setAmount(const int new_amount)
{
    m_amount = new_amount;
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

double Product::getOriginalPrice() const
{
    return m_price;
}

double Product::getPrice() const
{
    return m_price * getDiscount() / 100;
}

int Product::getAmount() const
{
    return m_amount;
}

int Product::getDiscount()
{
    return discount_ratio;
}

void Product::setDiscount(const int new_discount)
{
    discount_ratio = new_discount;
}

BookProduct::BookProduct(QString name, QString describe, double price, int amount) : Product(name, describe, price, amount, "Book")
{

}

double BookProduct::getPrice() const
{
    return Product::getPrice() * getDiscount() / 100;
}

int BookProduct::getDiscount()
{
    return discount_ratio;
}

void BookProduct::setDiscount(const int new_discount)
{
    discount_ratio = new_discount;
}

ElectronicProduct::ElectronicProduct(QString name, QString describe, double price, int amount) : Product(name, describe, price, amount, "Electronic")
{

}

double ElectronicProduct::getPrice() const
{
    return Product::getPrice() * getDiscount() / 100;
}

int ElectronicProduct::getDiscount()
{
    return discount_ratio;
}

void ElectronicProduct::setDiscount(const int new_discount)
{
    discount_ratio = new_discount;
}

ClothingProduct::ClothingProduct(QString name, QString describe, double price, int amount) : Product(name, describe, price, amount, "Clothing")
{

}

double ClothingProduct::getPrice() const
{
    return Product::getPrice() * getDiscount() / 100;
}

int ClothingProduct::getDiscount()
{
    return discount_ratio;
}

void ClothingProduct::setDiscount(const int new_discount)
{
    discount_ratio = new_discount;
}
