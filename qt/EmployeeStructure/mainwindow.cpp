#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QStandardItemModel)
{
    ui->setupUi(this);
    ui->treeEmployees->setModel(model);

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
}

void MainWindow::on_btnAddBoss_clicked()
{
    addBoss("Main Boss");
    addEmployee("Subordinate", "Main Boss");
}
