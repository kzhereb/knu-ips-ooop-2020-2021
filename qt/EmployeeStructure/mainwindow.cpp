#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <vector>


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
    addEmployee("Sub3", "Subordinate");
    addBoss("Another Boss");
    addEmployee("Developer", "Another Boss");
    addEmployee("Tester", "Another Boss");
}

void MainWindow::on_btnDelete_clicked()
{
    QModelIndexList indexes = ui->treeEmployees->selectionModel()->selectedIndexes();

    if (indexes.size() > 0) {
        std::vector<QStandardItem*> toDelete;

        for (int i=0; i<indexes.size(); i++) {
            QModelIndex selectedIndex = indexes.at(i);
            QStandardItem* selectedItem = model->itemFromIndex(selectedIndex);
            toDelete.push_back(selectedItem);
        }
        for (auto selectedItem:toDelete) {
            QModelIndex selectedIndex = selectedItem->index();
            qDebug()<<selectedItem->text();
            employees.remove(selectedItem->text());
            model->removeRow(selectedIndex.row(),selectedIndex.parent());
        }

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
