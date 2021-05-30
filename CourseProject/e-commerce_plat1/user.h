#ifndef USER_H
#define USER_H
#include <QString>

class User
{
private:
    QString m_username;
    QString m_password;
    double m_balance;

public:
    User(QString username, QString password, double balance);
    QString getUserName() const;
    QString getPassword() const;
    double getBalance() const;
    void setPassword(const QString new_password);
    void setBalance(const double new_balance);
    bool isPasswordCorrect(const QString password) const;
    virtual QString getUserType() const = 0;
    virtual ~User(){};
};

class Seller : public User
{
private:

public:
    Seller(QString username, QString password, double balance);
    virtual QString getUserType() const override;
    virtual ~Seller(){};
};

class Buyer : public User
{
private:

public:
    Buyer(QString username, QString password, double balance);
    virtual QString getUserType() const override;
    virtual ~Buyer(){};
};

#endif // USER_H
