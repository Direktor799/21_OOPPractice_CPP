#ifndef PRODUCT_H
#define PRODUCT_H
#include <QString>

class Product   //商品基类
{
private:
    QString m_name;     //商品名称
    QString m_type;     //商品类型
    QString m_describe; //商品描述
    double m_price;     //商品价格
    int m_amount;       //商品数量
    static int discount_ratio;  //全局打折幅度
protected:
public:
    Product(QString name, QString describe, double price, int amount, QString type = "None");
    void setName(const QString new_name);   //设置商品名称
    void setDescribe(const QString new_describe);   //设置商品描述
    void setOriginalPrice(const double new_price);  //设置商品原价
    void setAmount(const int new_amount);           //设置商品数量
    QString getName() const;                //返回商品名称
    QString getType() const;                //返回商品类型
    QString getDescribe() const;            //返回商品描述
    double getOriginalPrice() const;        //返回商品原价
    virtual double getPrice() const;        //返回商品价格
    int getAmount() const;                  //返回商品数量
    static int getDiscount();               //返回全局打折幅度
    static void setDiscount(const int new_discount);    //设置全局打折力幅度
    virtual ~Product(){};
};

class BookProduct : public Product  //图书商品类
{
private:
    static int discount_ratio;  //图书打折幅度
public:
    BookProduct(QString name, QString describe, double price, int amount);
    virtual double getPrice() const;    //返回图书价格
    static int getDiscount();           //返回图书打折幅度
    static void setDiscount(const int new_discount);    //设置图书打折幅度
    virtual ~BookProduct(){};
};

class ElectronicProduct : public Product    //电子商品类
{
private:
    static int discount_ratio;  //电子商品打折幅度
public:
    ElectronicProduct(QString name, QString describe, double price, int amount);
    virtual double getPrice() const;    //返回电子商品价格
    static int getDiscount();           //返回电子商品打折幅度
    static void setDiscount(const int new_discount);    //设置电子商品打折幅度
    virtual ~ElectronicProduct(){};
};

class ClothingProduct : public Product      //服装商品类
{
private:
    static int discount_ratio;  //服装商品打折幅度
public:
    ClothingProduct(QString name, QString describe, double price, int amount);
    virtual double getPrice() const;    //返回服装价格
    static int getDiscount();           //返回服装打折幅度
    static void setDiscount(const int new_discount);    //设置服装打折幅度
    virtual ~ClothingProduct(){};
};
#endif // PRODUCT_H
