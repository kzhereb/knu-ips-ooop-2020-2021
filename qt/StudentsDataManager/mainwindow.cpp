#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "student.h"

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSave_clicked()
{
    Student student{ui->inpSurname->text(),
                   ui->inpName->text(),
                   ui->inpGroup->currentText(),
                   ui->inpAvgGrade->value()};
    QFile file{"data.txt"};
    if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
            return;
    QTextStream stream(&file);
    stream<< student.surname()<<"\n"
          << student.name()<<"\n"
          << student.group()<<"\n"
          << student.avgGrade()<<"\n\n";
    file.close();
}
