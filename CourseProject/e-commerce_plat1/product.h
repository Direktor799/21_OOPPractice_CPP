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
    static int discount_ratio;
protected:
    QString m_type;
public:
    Product(QString name, QString describe, double price, int amount);
    void setName(const QString new_name);
    void setDescribe(const QString new_describe);
    void setOriginalPrice(const double new_price);
    void setAmount(const int new_amount);
    QString getName() const;
    QString getType() const;
    QString getDescribe() const;
    double getOriginalPrice() const;
    virtual double getPrice() const;
    int getAmount() const;
    static int getDiscount();
    static void setDiscount(const int new_discount);
    virtual ~Product(){};
};

class BookProduct : public Product
{
private:
    static int discount_ratio;
public:
    BookProduct(QString name, QString describe, double price, int amount);
    virtual double getPrice() const;
    static int getDiscount();
    static void setDiscount(const int new_discount);
    virtual ~BookProduct(){};
};

class ElectronicProduct : public Product
{
private:
    static int discount_ratio;
public:
    ElectronicProduct(QString name, QString describe, double price, int amount);
    virtual double getPrice() const;
    static int getDiscount();
    static void setDiscount(const int new_discount);
    virtual ~ElectronicProduct(){};
};

class ClothingProduct : public Product
{
private:
    static int discount_ratio;
public:
    ClothingProduct(QString name, QString describe, double price, int amount);
    virtual double getPrice() const;
    static int getDiscount();
    static void setDiscount(const int new_discount);
    virtual ~ClothingProduct(){};
};
#endif // PRODUCT_H
