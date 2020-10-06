#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "student.h"

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
    void on_btnSave_clicked();

    void on_btnClear_clicked();

    void on_btnLoad_clicked();

private:
    Ui::MainWindow *ui;

    void add_student_to_table(const Student& student);
    void load_from_file();
};

#endif // MAINWINDOW_H
