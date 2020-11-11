#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QStandardItemModel)
{
    ui->setupUi(this);
    ui->treeEmployees->setModel(model);

    ui->btnDelete->setEnabled(false);
    connect(ui->treeEmployees->selectionModel(),&QItemSelectionModel::selectionChanged,
            this, &MainWindow::on_treeEmployees_selectionChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addBoss(QString name)
{
    int count = model->rowCount();
    model->setRowCount(count+1);
    QStandardItem * bossItem = new QStandardItem;
    bossItem->setText(name);
    model->setItem(count,bossItem);
    employees[name] = bossItem;

}

void MainWindow::addEmployee(QString name, QString supervisorName)
{
    QStandardItem * employeeItem = new QStandardItem;
    employeeItem->setText(name);
    QStandardItem * parentItem = employees[supervisorName];
    parentItem->appendRow(employeeItem);
    employees[name] = employeeItem;
}

void MainWindow::on_btnAddBoss_clicked()
{
    addBoss("Main Boss");
    addEmployee("Subordinate", "Main Boss");
    addEmployee("Sub2", "Subordinate");
}

void MainWindow::on_btnDelete_clicked()
{
    QModelIndexList indexes = ui->treeEmployees->selectionModel()->selectedIndexes();
    if (indexes.size() > 0) {
        QModelIndex selectedIndex = indexes.at(0);
        QStandardItem* selectedItem = model->itemFromIndex(selectedIndex);
        //qDebug()<<selectedItem->text();
        employees.remove(selectedItem->text());
        model->removeRow(selectedIndex.row(),selectedIndex.parent());

    }
}

void MainWindow::on_treeEmployees_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList indexes = ui->treeEmployees->selectionModel()->selectedIndexes();
    if (indexes.size() > 0) {
        ui->btnDelete->setEnabled(true);
    } else {
        ui->btnDelete->setEnabled(false);
    }
}
