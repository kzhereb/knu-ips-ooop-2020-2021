#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    void number_clicked(int number);
};

#endif // MAINWINDOW_H
