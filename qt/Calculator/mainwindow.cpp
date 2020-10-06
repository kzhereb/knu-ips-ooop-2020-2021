#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

void MainWindow::number_clicked(int number)
{
    QString current_text = ui->lbl_Result->text();
    if (current_text == "0") {
        current_text = "";
    }
    current_text += QString::number(number);
    ui->lbl_Result->setText(current_text);
}

void MainWindow::operation_clicked(QString operation)
{
    if (this->operation!="") {
        qDebug()<<"multiple operations not supported";
        return;
    }
    QString current_text = ui->lbl_Result->text();
    this->operand1 = current_text.toInt();
    this->operation = operation;
    current_text += operation;
    ui->lbl_Result->setText(current_text);
}

int MainWindow::calculate(const QString &operation, int operand1, int operand2)
{
    if (operation == "+") {
        return operand1+operand2;
    }
}

void MainWindow::add_history(const QString &operation, int operand1, int operand2, int result)
{
    QString history = QString("%1 %2 %3 = %4").arg(
                QString::number(operand1),
                operation,
                QString::number(operand2),
                QString::number(result));
    ui->lswHistory->addItem(history);
}

void MainWindow::on_btn_Num1_clicked()
{
    number_clicked(1);
}

void MainWindow::on_btn_Num2_clicked()
{
    number_clicked(2);
}

void MainWindow::on_btn_Num3_clicked()
{
    number_clicked(3);
}

void MainWindow::on_btn_Num4_clicked()
{
    number_clicked(4);
}

void MainWindow::on_btn_Num5_clicked()
{
    number_clicked(5);
}

void MainWindow::on_btn_Num6_clicked()
{
    number_clicked(6);
}

void MainWindow::on_btn_Num7_clicked()
{
    number_clicked(7);
}

void MainWindow::on_btn_Num8_clicked()
{
    number_clicked(8);
}

void MainWindow::on_btn_Num9_clicked()
{
    number_clicked(9);
}

void MainWindow::on_btn_Num0_clicked()
{
    number_clicked(0);
}

void MainWindow::on_btnPlus_clicked()
{
    operation_clicked("+");
}

void MainWindow::on_btnEquals_clicked()
{
    QString current_text = ui->lbl_Result->text();
    QStringList parts = current_text.split(this->operation);
    int operand2 = parts[1].toInt();

    int result = calculate(operation, operand1, operand2);
    add_history(operation, operand1, operand2, result);

    current_text = QString::number(result);
    ui->lbl_Result->setText(current_text);
    this->operation = "";

}
