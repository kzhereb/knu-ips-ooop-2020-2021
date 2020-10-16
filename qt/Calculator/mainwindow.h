#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
//#include <QStringListModel>
#include <QStandardItemModel>


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
    void on_btnPlus_clicked();

    void on_btnEquals_clicked();




    void on_lsvHistory_doubleClicked(const QModelIndex &index);

    void on_btnClear_clicked();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::MainWindow *ui;

    //QStringListModel *model;
    QStandardItemModel *model;

    int operand1;
    QString operation="";

    const int MAX_HISTORY_SIZE = 9;

    void add_number_buttons();

    void number_clicked(int number);
    void operation_clicked(QString operation);
    int calculate(QString const& operation, int operand1, int operand2);
    void add_history(QString const& operation, int operand1, int operand2, int result);
};

#endif // MAINWINDOW_H
