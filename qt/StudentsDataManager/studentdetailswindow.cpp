#include "studentdetailswindow.h"
#include "ui_studentdetailswindow.h"

StudentDetailsWindow::StudentDetailsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentDetailsWindow)
{
    ui->setupUi(this);
}

StudentDetailsWindow::~StudentDetailsWindow()
{
    delete ui;
}

Student StudentDetailsWindow::getStudent() const
{
    return student;
}

void StudentDetailsWindow::setStudent(const Student &student)
{
    this->student = student;
    ui->lblName->setText(student.fullName());
}

void StudentDetailsWindow::on_btnSaveClose_clicked()
{
    student.setDescription(ui->txeDescription->toPlainText());
    this->hide();
}
