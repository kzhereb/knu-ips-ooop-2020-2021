#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QStringListModel)
{
    ui->setupUi(this);

    add_number_buttons();

    ui->lsvHistory->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_number_buttons()
{
    for(int i=0;i<=9;i++) {
        QPushButton* button = new QPushButton(QString::number(i));
        int row = (i != 0) ? (i-1)/3 : 3;
        int column = (i != 0) ? (i-1) % 3: 1;
        connect(button, &QPushButton::clicked,
                [this, i] { this->number_clicked(i); });
        ui->gridNumbers->addWidget(button,row, column);
    }
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
    int history_size = model->rowCount();
    if (history_size >= MAX_HISTORY_SIZE) {
        model->removeRow(0);
        history_size--;
    }
    model->insertRow(history_size);
    QModelIndex index = model->index(history_size);
    model->setData(index,history);

}


void MainWindow::on_btnPlus_clicked()
{
    operation_clicked("+");
}

void MainWindow::on_btnEquals_clicked()
{
    if (this->operation == "") {return;}
    QString current_text = ui->lbl_Result->text();
    if (current_text.endsWith(this->operation)) {return;} //no second operand

    QStringList parts = current_text.split(this->operation);
    int operand2 = parts[1].toInt();

    int result = calculate(operation, operand1, operand2);
    add_history(operation, operand1, operand2, result);

    current_text = QString::number(result);
    ui->lbl_Result->setText(current_text);
    this->operation = "";

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString key = event->text();
    bool is_number;
    int result = key.toInt(&is_number);
    if (is_number) {
        number_clicked(result);
    }
}





void MainWindow::on_lsvHistory_doubleClicked(const QModelIndex &index)
{
    QString history_item = model->data(index).toString();
    QStringList parts = history_item.split(" = ");
    if (this->operation == "") {
        ui->lbl_Result->setText(parts[1]);
    } else {
        QString current_text = ui->lbl_Result->text();
        if (current_text.endsWith(this->operation)) { // no second operand
            current_text += parts[1];
            ui->lbl_Result->setText(current_text);
        } else {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,
                                          "Choose action",
                                          "Press Yes to replace entire expression, No to replace second operand, Cancel to keep current expression",
                                           QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
            if (reply == QMessageBox::Yes) {
               ui->lbl_Result->setText(parts[1]);
               this->operation = "";
            } else if (reply == QMessageBox::No) {
                QStringList expression_parts = current_text.split(this->operation);
                current_text = expression_parts[0] + this->operation + parts[1];
                ui->lbl_Result->setText(current_text);
            } else if (reply == QMessageBox::Cancel) {
                // do nothing - user asked us to keep previous expression
            }
        }

    }
}
