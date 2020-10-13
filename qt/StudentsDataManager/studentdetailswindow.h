#ifndef STUDENTDETAILSWINDOW_H
#define STUDENTDETAILSWINDOW_H

#include "student.h"

#include <QMainWindow>

namespace Ui {
class StudentDetailsWindow;
}

class StudentDetailsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentDetailsWindow(QWidget *parent = nullptr);
    ~StudentDetailsWindow();
    Student getStudent() const;
    void setStudent(const Student& student);

private slots:
    void on_btnSaveClose_clicked();

private:
    Ui::StudentDetailsWindow *ui;
    Student student;
};

#endif // STUDENTDETAILSWINDOW_H
