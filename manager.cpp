#include "manager.h"
#include "ui_manager.h"

manager::manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);
}

manager::~manager()
{
    delete ui;
}


void manager::on_BookQuery_clicked()//点击查询图书
{
    QString order1 = ui->QueryOrder1->text(); //order1是查询条件，用在where中
    QString order2 = ui->QueryOrder2->text(); //order2是区间用到，也是在where中
    QString condition = ui->QueryCondition->text(); //condition是排序顺序

    /*QString BOOKID = "BOOKID" ;
    QString CATEGORY = "CATEGORY" ;
    QString NAME = "NAME" ;
    QString PRESS = "PRESS" ;
    QString YEAR = "YEAR" ;
    QString AUTHOR = "AUTHOR" ;
    QString PRICE = "PRICE" ;
    QString COLLECTION = "COLLECTION" ;
    QString STOCK = "STOCK" ;*/

    if(order2 == nullptr)//没有区间，只用到condition条件进行排序
    {
        if(condition == nullptr)//默认按书号排序
        {
            condition = "BOOKID" ;
        }
        if(order1 == nullptr)//没有查询条件
        {
        QSqlQueryModel *model = new QSqlQueryModel;
        QString sqlstr = "select BOOKID,category,name,press,year,author,price,collection,stock from book order by ";
        sqlstr += condition ;
        sqlstr += " ;";
        model->setQuery(sqlstr);
        qDebug()<<sqlstr ;
        model->setHeaderData(0, Qt::Horizontal, tr("id"));
        model->setHeaderData(1, Qt::Horizontal, tr("category"));
        model->setHeaderData(2, Qt::Horizontal, tr("name"));
        model->setHeaderData(3, Qt::Horizontal, tr("press"));
        model->setHeaderData(4, Qt::Horizontal, tr("year"));
        model->setHeaderData(5, Qt::Horizontal, tr("author"));
        model->setHeaderData(6, Qt::Horizontal, tr("price"));
        model->setHeaderData(7, Qt::Horizontal, tr("collection"));
        model->setHeaderData(8, Qt::Horizontal, tr("stock"));

        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置成不可编辑
        }
        else //有查询条件
        {
            QSqlQueryModel *model = new QSqlQueryModel;
            QString sqlstr = "select * from book" ;
            sqlstr += " where " ;
            sqlstr += order1 ;
            sqlstr += " order by " ;
            sqlstr += condition ;
            sqlstr += " ;";
            model->setQuery(sqlstr);
            qDebug()<<sqlstr ;
            model->setHeaderData(0, Qt::Horizontal, tr("id"));
            model->setHeaderData(1, Qt::Horizontal, tr("category"));
            model->setHeaderData(2, Qt::Horizontal, tr("name"));
            model->setHeaderData(3, Qt::Horizontal, tr("press"));
            model->setHeaderData(4, Qt::Horizontal, tr("year"));
            model->setHeaderData(5, Qt::Horizontal, tr("author"));
            model->setHeaderData(6, Qt::Horizontal, tr("price"));
            model->setHeaderData(7, Qt::Horizontal, tr("collection"));
            model->setHeaderData(8, Qt::Horizontal, tr("stock"));

            ui->tableView->setModel(model);
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    }
    else //order2有，即为区间,必有order1
    {
        if(condition == nullptr)//默认按书号排序
        {
            condition = "BOOKID" ;
        }
        //有查询条件,order1,order2都有
        QSqlQueryModel *model = new QSqlQueryModel;
        QString sqlstr = "select * from book" ;
        sqlstr += " where " ;
        sqlstr += order1 ;
        sqlstr += " and " ;
        sqlstr += order2 ;
        sqlstr += " order by " ;
        sqlstr += condition ;
        sqlstr += " ;";
        model->setQuery(sqlstr);
        qDebug()<<sqlstr ;
        model->setHeaderData(0, Qt::Horizontal, tr("id"));
        model->setHeaderData(1, Qt::Horizontal, tr("category"));
        model->setHeaderData(2, Qt::Horizontal, tr("name"));
        model->setHeaderData(3, Qt::Horizontal, tr("press"));
        model->setHeaderData(4, Qt::Horizontal, tr("year"));
        model->setHeaderData(5, Qt::Horizontal, tr("author"));
        model->setHeaderData(6, Qt::Horizontal, tr("price"));
        model->setHeaderData(7, Qt::Horizontal, tr("collection"));
        model->setHeaderData(8, Qt::Horizontal, tr("stock"));

        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

/*
 * Sample:
 * ( book_no_1, Computer Science, Computer Architecture, xxx, 2004, xxx, 90.00, 2 )
*/
void manager::on_addOneBook_clicked() //点击单本入库
{
    QString bookinfo = ui->OneBookInfo->text();
    QSqlQueryModel *model = new QSqlQueryModel;
    QString sqlstr = "Insert into book (BOOKID,category,name,press,year,author,price,collection,stock) values " + bookinfo + ";" ;
    model->setQuery(sqlstr);
    qDebug()<<sqlstr ;
}

