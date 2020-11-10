#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QHash>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddBoss_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel * model;
    QHash<QString,QStandardItem*> employees;


    void addBoss(QString name);
    void addEmployee(QString name, QString supervisorName);
};

#endif // MAINWINDOW_H
