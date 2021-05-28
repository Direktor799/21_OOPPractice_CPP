#include "login.h"

Login::Login(QWidget *parent) : QWidget(parent)
{
    //读取json数据并存入user_list
    QDir info_dir = QDir::currentPath();
    info_dir.cdUp();
    info_dir.cd("data");
    QFile user_file(info_dir.path() + "/user_info.json");
    user_file.open(QIODevice::ReadWrite | QIODevice::Text);
    QString value = user_file.readAll();
    QJsonArray array = QJsonDocument::fromJson(value.toUtf8()).object().value(QStringLiteral("user_info")).toArray();
    for (int i = 0; i < array.size(); i++)
    {
        User *new_user;
        QString username = array[i].toObject()["username"].toString();
        QString password = array[i].toObject()["password"].toString();
        double balance = array[i].toObject()["balance"].toDouble();
        if (array[i].toObject()["type"].toString() == "Seller")
            new_user = new Seller(username, password, balance);
        else
            new_user = new Buyer(username, password, balance);
        user_list.push_back(new_user);
    }

    //窗口布局
    setAttribute(Qt::WA_QuitOnClose, true);
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    setWindowTitle("login");
    setFixedSize(200, 120);
    username_box = new QLineEdit(this);
    username_box->move(50, 15);
    username_text = new QLabel("用户名", this);
    username_text->move(10, 15);

    password_box = new QLineEdit(this);
    password_box->move(50, 45);
    password_text = new QLabel("密码", this);
    password_box->setEchoMode(QLineEdit::Password);
    password_text->move(20, 45);

    error_label = new QLabel(this);
    error_label->move(50,70);
    error_label->setStyleSheet("color:#ff0000;");
    error_label->hide();

    login_btn = new QPushButton("登录", this);
    login_btn->move(65, 90);
    connect(login_btn, &QPushButton::clicked, this, &Login::checkPassword);

    show();
}

void Login::checkPassword()
{
    QString username_trying = username_box->text();
    QString password_trying = password_box->text();
    for (auto i = user_list.begin(); i < user_list.end(); i++)
        if ((*i)->getUserName() == username_trying)
        {
            if ((*i)->isPasswordCorrect(password_trying))
            {
                error_label->hide();
            }
            else
            {
                error_label->setText("密码错误");
                error_label->show();
            }
        }
        else
        {
            error_label->setText("用户名错误");
            error_label->show();
        }
}

void Login::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Enter)
        login_btn->click();
    QWidget::keyPressEvent(ev);
}
