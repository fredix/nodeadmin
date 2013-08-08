#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "nodecast_api.h"
#include "nodes.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionRefresh_triggered();
    void refresh_users(QVariantMap user);
    void refresh_nodes(QVariantMap node);

    void on_pushButton_refresh_clicked();
    void on_pushButton_add_clicked();
    void create_node(QString nodemame);

    void on_pushButton_delete_clicked();

private:
    Ui::MainWindow *ui;
    Nodecast_api *m_nodeapi;
};

#endif // MAINWINDOW_H
