#include "mainwindow.h"
#include "ui_mainwindow.h"

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
