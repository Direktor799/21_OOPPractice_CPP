#include "productmanager.h"

ProductDisplayer::ProductDisplayer(QVector<Product *> &list, int index, QWidget *parent) : QWidget(parent), product_list(list), now_index(index)
{
    setAttribute(Qt::WA_QuitOnClose,false);
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(250, 200);
    setWindowTitle("商品信息");

    product_name_text = new QLabel("商品名称: " + product_list[now_index]->getName(), this);
    product_name_text->setWordWrap(true);
    product_name_text->setFixedSize(210,25);
    product_name_text->move(20, 12);

    product_type_text = new QLabel("商品类型: " + product_list[now_index]->getType(), this);
    product_type_text->setWordWrap(true);
    product_type_text->setFixedSize(210,25);
    product_type_text->move(20, 42);

    product_describe_text = new QLabel("商品描述: " + product_list[now_index]->getDescribe(), this);
    product_describe_text->setWordWrap(true);
    product_describe_text->setFixedSize(210,50);
    product_describe_text->move(20, 62);

    product_price_text = new QLabel("商品价格: " + QString::number(product_list[now_index]->getPrice()), this);
    product_price_text->setWordWrap(true);
    product_price_text->setFixedSize(210,25);
    product_price_text->move(20, 132);

    product_amount_text = new QLabel("商品数量: " + QString::number(product_list[now_index]->getAmount()), this);
    product_amount_text->setWordWrap(true);
    product_amount_text->setFixedSize(210,25);
    product_amount_text->move(20, 162);
    show();
}

ProductDiscounter::ProductDiscounter(QVector<Product *> &list, QWidget *parent) : QWidget(parent), product_list(list)
{
    setAttribute(Qt::WA_QuitOnClose,false);
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(250, 200);
    setWindowTitle("商品打折");

    product_type_text = new QLabel("请选择打折品类:", this);
    product_type_text->move(20, 12);
    product_type_box = new QComboBox(this);
    product_type_box->addItem("Book");
    product_type_box->addItem("Electronic");
    product_type_box->addItem("Clothing");
    product_type_box->addItem("All");
    product_type_box->setEditable(false);
    product_type_box->move(115, 10);
    connect(product_type_box, &QComboBox::currentTextChanged, this, &ProductDiscounter::setSlider);

    product_discount_text = new QLabel("请选择打折幅度:", this);
    product_discount_text->move(20, 42);
    product_discount_slider = new QSlider(Qt::Horizontal, this);
    product_discount_slider->setRange(0, 100);
    product_discount_slider->setValue(BookProduct::getDiscount());
    product_discount_slider->move(115, 40);

    value_text = new QLabel(QString::number(BookProduct::getDiscount()), this);
    value_text->move(210, 42);
    connect(product_discount_slider, &QSlider::valueChanged, this, &ProductDiscounter::displaySliderValue);
    connect(product_discount_slider, &QSlider::valueChanged, this, &ProductDiscounter::discountProduct);
    show();
}

void ProductDiscounter::setSlider(const QString &s)
{
    if (s == "Book")
        product_discount_slider->setValue(BookProduct::getDiscount());
    else if (s == "Electronic")
        product_discount_slider->setValue(ElectronicProduct::getDiscount());
    else if (s == "Clothing")
        product_discount_slider->setValue(ClothingProduct::getDiscount());
    else if (s == "All")
        product_discount_slider->setValue(Product::getDiscount());
}

void ProductDiscounter::displaySliderValue(int value)
{
    value_text->setText(QString::number(value));
    value_text->adjustSize();
}

void ProductDiscounter::discountProduct()
{
    if (product_type_box->currentText() == "Book")
        BookProduct::setDiscount(product_discount_slider->value());
    else if (product_type_box->currentText() == "Electronic")
        ElectronicProduct::setDiscount(product_discount_slider->value());
    else if (product_type_box->currentText() == "Clothing")
        ClothingProduct::setDiscount(product_discount_slider->value());
    else if (product_type_box->currentText() == "All")
        Product::setDiscount(product_discount_slider->value());
}

ProductManager::ProductManager(QVector<Product *> &list, QWidget *parent) : QWidget(parent), product_list(list)
{
    setAttribute(Qt::WA_QuitOnClose,false);
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(250, 250);

    product_name_text = new QLabel("商品名称:", this);
    product_name_text->move(20, 12);
    product_name_box = new QLineEdit(this);
    product_name_box->move(80, 10);

    product_type_text = new QLabel("商品类型:", this);
    product_type_text->move(20, 42);
    product_type_box = new QComboBox(this);
    product_type_box->addItem("Book");
    product_type_box->addItem("Electronic");
    product_type_box->addItem("Clothing");
    product_type_box->addItem("None");
    product_type_box->setEditable(false);
    product_type_box->move(80, 42);

    product_describe_text = new QLabel("商品描述:", this);
    product_describe_text->move(20, 72);
    product_describe_box = new QTextEdit(this);
    product_describe_box->setFixedSize(150, 50);
    product_describe_box->move(80, 72);

    product_price_text = new QLabel("商品价格:", this);
    product_price_text->move(20, 132);
    product_price_box = new QLineEdit(this);
    product_price_box->setValidator(new QDoubleValidator(0, 20000, 2, this));
    product_price_box->setMaxLength(10);
    product_price_box->setFixedSize(80, 20);
    product_price_box->move(80, 132);

    product_amount_text = new QLabel("商品数量:", this);
    product_amount_text->move(20, 162);
    product_amount_box = new QLineEdit(this);
    product_amount_box->setValidator(new QIntValidator(0, 10000, this));
    product_amount_box->setMaxLength(10);
    product_amount_box->setFixedSize(80, 20);
    product_amount_box->move(80, 162);

    submit_btn = new QPushButton("提交", this);
    submit_btn->move(90, 200);
}

void ProductManager::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter)
        submit_btn->click();
    QWidget::keyPressEvent(ev);
}

ProductAdder::ProductAdder(QVector<Product *> &list, QWidget *parent) : ProductManager(list, parent)
{
    setWindowTitle("添加商品");
    connect(submit_btn, &QPushButton::clicked, this, &ProductAdder::addProduct);
    show();
}

void ProductAdder::addProduct()
{
    QString name = product_name_box->text();
    QString type = product_type_box->currentText();
    QString describe = product_describe_box->toPlainText();
    double price = product_price_box->text().toDouble();
    int amount = product_amount_box->text().toInt();

    Product *new_product;
    if (type == "Book")
        new_product = new BookProduct(name, describe, price, amount);
    else if (type == "Electronic")
        new_product = new ElectronicProduct(name, describe, price, amount);
    else if (type == "Clothing")
        new_product = new ClothingProduct(name, describe, price, amount);
    else
        new_product = new Product(name, describe, price, amount);
    product_list.push_back(new_product);
    close();
}

ProductModifier::ProductModifier(QVector<Product *> &list, int index, QWidget *parent) : ProductManager(list, parent), now_index(index)
{
    setWindowTitle("修改商品");
    product_name_box->setText(product_list[now_index]->getName());
    product_type_box->setCurrentText(product_list[now_index]->getType());
    product_type_box->setDisabled(true);
    product_describe_box->setText(product_list[now_index]->getDescribe());
    product_price_box->setText(QString::number(product_list[now_index]->getOriginalPrice()));
    product_amount_box->setText(QString::number(product_list[now_index]->getAmount()));
    submit_btn->move(45, 200);
    connect(submit_btn, &QPushButton::clicked, this, &ProductModifier::modifyProduct);
    stop_sale_btn = new QPushButton("下架", this);
    stop_sale_btn->move(135, 200);
    connect(stop_sale_btn, &QPushButton::clicked, this, &ProductModifier::deleteProduct);
    show();
}

void ProductModifier::modifyProduct()
{
    QString name = product_name_box->text();
    QString describe = product_describe_box->toPlainText();
    double price = product_price_box->text().toDouble();
    int amount = product_amount_box->text().toInt();
    product_list[now_index]->setName(name);
    product_list[now_index]->setDescribe(describe);
    product_list[now_index]->setOriginalPrice(price);
    product_list[now_index]->setAmount(amount);
    close();
}

void ProductModifier::deleteProduct()
{
    product_list.erase(product_list.begin() + now_index);
    close();
}

ProductManagerWidget::ProductManagerWidget(User *user, QWidget *parent) : QWidget(parent)
{
    now_user = user;
    product_adder = nullptr;
    product_modifier = nullptr;
    product_displayer = nullptr;
    product_discounter = nullptr;

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
    int discount = QJsonDocument::fromJson(value.toUtf8()).object().value(QStringLiteral("all_discount")).toInt();
    Product::setDiscount(discount);
    discount = QJsonDocument::fromJson(value.toUtf8()).object().value(QStringLiteral("book_discount")).toInt();
    BookProduct::setDiscount(discount);
    discount = QJsonDocument::fromJson(value.toUtf8()).object().value(QStringLiteral("electronic_discount")).toInt();
    ElectronicProduct::setDiscount(discount);
    discount = QJsonDocument::fromJson(value.toUtf8()).object().value(QStringLiteral("clothing_discount")).toInt();
    ClothingProduct::setDiscount(discount);
    product_file.close();

    //界面
    table_widget = new QTableWidget(10000, 4, this);
    table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table_widget->horizontalHeader()->setSortIndicatorShown(true);
    table_widget->verticalHeader()->setHidden(true);
    connect(table_widget->horizontalHeader(), &QHeaderView::sortIndicatorChanged, table_widget, &QTableWidget::sortItems);
    table_widget->setColumnWidth(0, 200);
    table_widget->setColumnWidth(1, 100);
    table_widget->setColumnWidth(2, 100);
    table_widget->setColumnWidth(3, 100);
    table_widget->setFixedSize(519, 450);
    QStringList header;
    header << "商品名" << "类别" << "价格" << "数量";
    table_widget->setHorizontalHeaderLabels(header);
    table_widget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#dddddd;}");
    refreshTable();

    if (now_user != nullptr && now_user->getUserType() == "Seller")
    {
        add_product_btn = new QPushButton("添加商品", this);
        add_product_btn->move(600, 100);
        connect(add_product_btn, &QPushButton::clicked, this, &ProductManagerWidget::addProduct);

        discount_product_btn = new QPushButton("商品打折", this);
        discount_product_btn->move(600, 150);
        connect(discount_product_btn, &QPushButton::clicked, this, &ProductManagerWidget::discountProduct);

        connect(table_widget, &QTableWidget::itemDoubleClicked, this, &ProductManagerWidget::modifyProduct);
    }
    else
        connect(table_widget, &QTableWidget::itemDoubleClicked, this, &ProductManagerWidget::displayProduct);

    setFixedSize(900, 450);

}

void ProductManagerWidget::refreshTable()
{
    table_widget->clearContents();
    for (int i = 0; i < product_list.size(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(product_list[i]->getName());
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 0, item);
        item = new QTableWidgetItem(product_list[i]->getType());
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 1, item);
        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, product_list[i]->getPrice());
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 2, item);
        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, product_list[i]->getAmount());
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        table_widget->setItem(i, 3, item);
    }
    table_widget->horizontalHeader()->setSortIndicator(0,Qt::SortOrder::AscendingOrder);
}

void ProductManagerWidget::addProduct()
{
    if (product_adder == nullptr)
    {
        product_adder = new ProductAdder(product_list);
        connect(product_adder, &ProductAdder::destroyed, this, &ProductManagerWidget::addProductDone);
    }
}

void ProductManagerWidget::addProductDone()
{
    product_adder = nullptr;
    refreshTable();
}

void ProductManagerWidget::modifyProduct(QTableWidgetItem *item)
{
    if (product_modifier == nullptr)
    {
        for (int i = 0; i < product_list.size(); i++)
        {
            if (product_list[i]->getName() == table_widget->item(item->row(), 0)->text())
            {
                product_modifier = new ProductModifier(product_list, i);
                connect(product_modifier, &ProductModifier::destroyed, this, &ProductManagerWidget::modifyProductDone);
                break;
            }
        }
    }
}

void ProductManagerWidget::modifyProductDone()
{
    product_modifier = nullptr;
    refreshTable();
}

void ProductManagerWidget::displayProduct(QTableWidgetItem *item)
{
    if (product_displayer == nullptr)
    {
        for (int i = 0; i < product_list.size(); i++)
        {
            if (product_list[i]->getName() == table_widget->item(item->row(), 0)->text())
            {
                product_displayer = new ProductDisplayer(product_list, i);
                connect(product_displayer, &ProductDisplayer::destroyed, this, &ProductManagerWidget::displayProductDone);
                break;
            }
        }
    }
}

void ProductManagerWidget::displayProductDone()
{
    product_displayer = nullptr;
}

void ProductManagerWidget::discountProduct()
{
    if (product_discounter == nullptr)
    {
        product_discounter = new ProductDiscounter(product_list);
        connect(product_discounter, &ProductDiscounter::destroyed, this, &ProductManagerWidget::discountProductDone);
    }
}

void ProductManagerWidget::discountProductDone()
{
    product_discounter = nullptr;
    refreshTable();
}

ProductManagerWidget::~ProductManagerWidget()
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
        object["price"] = (*i)->getOriginalPrice();
        object["amount"] = (*i)->getAmount();
        array.push_back(object);
    }
    QJsonObject object;
    object["product_info"] = array;
    object["all_discount"] = Product::getDiscount();
    object["book_discount"] = BookProduct::getDiscount();
    object["electronic_discount"] = ElectronicProduct::getDiscount();
    object["clothing_discount"] = ClothingProduct::getDiscount();
    QByteArray data = QJsonDocument(object).toJson(QJsonDocument::Indented);
    product_file.write(data);
    product_file.close();
    //释放内存
    for (auto i = product_list.begin(); i < product_list.end(); i++)
        delete *i;
}
