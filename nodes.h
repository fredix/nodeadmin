#ifndef NODE_H
#define NODE_H

#include <QDialog>
#include <QDebug>
#include "nodecast_api.h"

namespace Ui {
class Nodes;
}

class Nodes : public QDialog
{
    Q_OBJECT
    
public:
    explicit Nodes(QWidget *parent = 0);
    ~Nodes();
    

signals:
    void add_node(QString nodename);

private slots:
    void on_buttonBox_accepted();
    void select_users(QVariantMap user);

private:
    Ui::Nodes *ui;
    Nodecast_api *m_nodeapi;
};

#endif // NODE_H
