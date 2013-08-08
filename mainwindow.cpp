#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodes.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //m_nodeapi = new Nodecast_api("loadbalancer.ncs.pumit.com", "8000", this);

    m_nodeapi = new Nodecast_api("10.211.55.3", "8000", this);
    connect(m_nodeapi, SIGNAL(users_Changed(QVariantMap)), this, SLOT(refresh_users(QVariantMap)), Qt::QueuedConnection);
    connect(m_nodeapi, SIGNAL(nodes_Changed(QVariantMap)), this, SLOT(refresh_nodes(QVariantMap)), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    m_nodeapi->deleteLater();
    qDebug() << "m_nodeapi deleted";
    delete ui;
}

void MainWindow::on_actionRefresh_triggered()
{
    qDebug() << "REFRESH !!!";

    qDebug() << "INDEX : " << ui->tabWidget->currentIndex();

    if (ui->tabWidget->currentIndex() == 0)
    {
        ui->treeWidget->clear();
        m_nodeapi->users_get("e5c71ae4-533a-474c-acb1-84fc688ff707");
    }
    else if (ui->tabWidget->currentIndex() == 2)
    {
        ui->treeWidget_nodes->clear();
        m_nodeapi->nodes_get("e5c71ae4-533a-474c-acb1-84fc688ff707");
    }
}


void MainWindow::refresh_users(QVariantMap user)
{
    qDebug() << "REFRESH USERS !!";
    qDebug() << "M EMAIL  : " << user["email"].toString();
    qDebug() << "M TOKEN  : " << user["token"].toString();

    QStringList row;
    row << user["email"].toString() <<  user["login"].toString() << user["token"].toString();

    QTreeWidgetItem *pRow = new QTreeWidgetItem(row);

    ui->treeWidget->addTopLevelItem(pRow);
}



void MainWindow::refresh_nodes(QVariantMap node)
{
    qDebug() << "REFRESH NODES !!";
    qDebug() << "M NODENAME  : " << node["nodename"].toString();
    qDebug() << "M UUID  : " << node["node_uuid"].toString();

    QStringList row;
    row << node["nodename"].toString() <<  node["email"].toString() << node["node_uuid"].toString() << node["node_password"].toString() << "test";

    QTreeWidgetItem *pRow = new QTreeWidgetItem(row);

    ui->treeWidget_nodes->addTopLevelItem(pRow);
}


void MainWindow::on_pushButton_refresh_clicked()
{
    qDebug() << "REFRESH !!!";
    qDebug() << "INDEX : " << ui->tabWidget->currentIndex();

    if (ui->tabWidget->currentIndex() == 0)
    {
        ui->treeWidget->clear();
        m_nodeapi->users_get("e5c71ae4-533a-474c-acb1-84fc688ff707");
    }
    else if (ui->tabWidget->currentIndex() == 2)
    {
        ui->treeWidget_nodes->clear();
        m_nodeapi->nodes_get("e5c71ae4-533a-474c-acb1-84fc688ff707");
    }
}

void MainWindow::on_pushButton_add_clicked()
{
    qDebug() << "ADD INDEX : " << ui->tabWidget->currentIndex();

    if (ui->tabWidget->currentIndex() == 0)
    {
    }
    else if (ui->tabWidget->currentIndex() == 2)
    {
        Nodes nodes(this);
        connect(&nodes, SIGNAL(add_node(QString)), this, SLOT(create_node(QString)));
        nodes.exec();
    }
}



void MainWindow::create_node(QString node_name)
{
    qDebug() << "CREATE NODE : " << node_name;
    m_nodeapi->node_post(node_name);
    ui->treeWidget_nodes->clear();
    m_nodeapi->nodes_get("e5c71ae4-533a-474c-acb1-84fc688ff707");
}

void MainWindow::on_pushButton_delete_clicked()
{
    qDebug() << "ADD INDEX : " << ui->tabWidget->currentIndex();

    if (ui->tabWidget->currentIndex() == 0)
    {
    }
    else if (ui->tabWidget->currentIndex() == 2)
    {

        qDebug() << "DELETE : " << ui->treeWidget_nodes->currentItem()->text(0);

    }
}
