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
    load_from_file();
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

void MainWindow::load_from_file()
{
    QFile file{"data.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    ui->tbwStudents->clearContents();
    ui->tbwStudents->setRowCount(0);
    QTextStream in(&file);
    int current_field = 0;
    Student current_student;
    while (!in.atEnd())
    {
       QString line = in.readLine();
       switch (current_field) {
       case 0:
           current_student.setSurname(line);
           break;
       case 1:
           current_student.setName(line);
           break;
       case 2:
           current_student.setGroup(line);
           break;
       case 3:
           current_student.setAvgGrade(line.toDouble());
           break;
       case 4:
           current_field = -1;
           add_student_to_table(current_student);
           break;
       }
       current_field++;
    }
    file.close();
}

void MainWindow::on_btnLoad_clicked()
{
    load_from_file();
}

void MainWindow::on_btnDetails_clicked()
{
    Student student{ui->inpSurname->text(),
                   ui->inpName->text(),
                   ui->inpGroup->currentText(),
                   ui->inpAvgGrade->value()};
    detailsWindow.setStudent(student);
    detailsWindow.show();
}
