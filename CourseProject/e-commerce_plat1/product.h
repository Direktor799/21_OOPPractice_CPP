#ifndef PRODUCT_H
#define PRODUCT_H
#include <QString>

class Product
{
private:
    QString m_name;
    QString m_describe;
    double m_price;
    int m_amount;
protected:
    QString m_type;
public:
    Product(QString name, QString describe, double price, int amount);
    void setName(const QString new_name);
    void setDescribe(const QString new_describe);
    void setPrice(const double new_price);
    void setAmount(const int new_amount);
    QString getName() const;
    QString getType() const;
    QString getDescribe() const;
    virtual double getPrice() const;
    int getAmount() const;
    virtual ~Product(){};
};

class BookProduct : public Product
{
public:
    BookProduct(QString name, QString describe, double price, int amount);
    virtual ~BookProduct(){};
};

class ElectronicProduct : public Product
{
public:
    ElectronicProduct(QString name, QString describe, double price, int amount);
    virtual ~ElectronicProduct(){};
};

class ClothingProduct : public Product
{
public:
    ClothingProduct(QString name, QString describe, double price, int amount);
    virtual ~ClothingProduct(){};
};
#endif // PRODUCT_H
