#include "nodes.h"
#include "ui_nodes.h"

Nodes::Nodes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nodes)
{
    ui->setupUi(this);

    m_nodeapi = new Nodecast_api("10.211.55.3", "8000", this);
    connect(m_nodeapi, SIGNAL(users_Changed(QVariantMap)), this, SLOT(select_users(QVariantMap)), Qt::DirectConnection);
    //connect(m_nodeapi, SIGNAL(nodes_Changed(QVariantMap)), this, SLOT(refresh_users(QVariantMap)), Qt::QueuedConnection);
    //connect(m_nodeapi, SIGNAL(nodes_Changed(QVariantMap)), this, SLOT(refresh_nodes(QVariantMap)), Qt::QueuedConnection);

    //m_nodeapi->moveToThread(m_thread);
    //m_thread->start();

    m_nodeapi->users_get("e5c71ae4-533a-474c-acb1-84fc688ff707");


}

Nodes::~Nodes()
{
    m_nodeapi->deleteLater();
    qDebug() << "Nodes::deleteLater";
    delete ui;
}


void Nodes::select_users(QVariantMap user)
{
    qDebug() << "Nodes::select_users REFRESH USERS !!";
    qDebug() << "Nodes::select_users M EMAIL  : " << user["email"].toString();
    qDebug() << "Nodes::select_users M TOKEN  : " << user["token"].toString();

    QStringList row;
   // row << user["email"].toString() <<  user["login"].toString() << user["token"].toString();

    row << user["email"].toString();

    ui->comboBox->addItems(row);

    //QTreeWidgetItem *pRow = new QTreeWidgetItem(row);

    //ui->treeWidget->addTopLevelItem(pRow);
}


void Nodes::on_buttonBox_accepted()
{
    qDebug() << "OK !!!! : " << ui->lineEdit_node->text();
    emit add_node(ui->lineEdit_node->text());
}
