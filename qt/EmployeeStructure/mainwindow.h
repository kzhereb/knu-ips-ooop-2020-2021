#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QHash>
#include <QItemSelectionModel>

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

    void on_btnDelete_clicked();
    void on_treeEmployees_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    Ui::MainWindow *ui;
    QStandardItemModel * model;
    QHash<QString,QStandardItem*> employees;


    void addBoss(QString name);
    void addEmployee(QString name, QString supervisorName);
};

#endif // MAINWINDOW_H
