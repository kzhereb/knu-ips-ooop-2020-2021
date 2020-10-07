#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btn_Num1_clicked();

    void on_btn_Num2_clicked();

    void on_btn_Num3_clicked();

    void on_btn_Num4_clicked();

    void on_btn_Num5_clicked();

    void on_btn_Num6_clicked();

    void on_btn_Num7_clicked();

    void on_btn_Num8_clicked();

    void on_btn_Num9_clicked();

    void on_btn_Num0_clicked();

    void on_btnPlus_clicked();

    void on_btnEquals_clicked();

    void on_lswHistory_itemDoubleClicked(QListWidgetItem *item);

    void on_lswHistory_doubleClicked(const QModelIndex &index);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::MainWindow *ui;

    QStringListModel *model;

    int operand1;
    QString operation="";

    const int MAX_HISTORY_SIZE = 9;

    void number_clicked(int number);
    void operation_clicked(QString operation);
    int calculate(QString const& operation, int operand1, int operand2);
    void add_history(QString const& operation, int operand1, int operand2, int result);
};

#endif // MAINWINDOW_H
