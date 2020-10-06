#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "student.h"

#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tbwStudents->setHorizontalHeaderLabels({"Surname",
                                               "Name",
                                               "Group",
                                               "Avg. Grade"});
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
    add_student_to_table(student);

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

void MainWindow::on_btnClear_clicked()
{
    ui->inpSurname->clear();
    ui->inpName->clear();
    ui->inpGroup->setCurrentIndex(0);
    ui->inpAvgGrade->setValue(75);
}

void MainWindow::add_student_to_table(const Student &student)
{
    int rows = ui->tbwStudents->rowCount();
    ui->tbwStudents->setRowCount(rows+1);

    QTableWidgetItem* item = new QTableWidgetItem(student.surname());
    ui->tbwStudents->setItem(rows, 0, item);

    item = new QTableWidgetItem(student.name());
    ui->tbwStudents->setItem(rows, 1, item);

    item = new QTableWidgetItem(student.group());
    ui->tbwStudents->setItem(rows, 2, item);

    item = new QTableWidgetItem(QString::number(student.avgGrade()));
    ui->tbwStudents->setItem(rows, 3, item);
}
