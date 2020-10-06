#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
private:
    QString _surname;
    QString _name;
    QString _group;
    double _avgGrade;
public:
    Student();
    explicit Student(const QString &surname,
                     const QString &name,
                     const QString &group,
                     double avgGrade) :
        _surname(surname), _name(name), _group(group), _avgGrade(avgGrade) {}
    QString surname() const;
    void setSurname(const QString &surname);
    QString name() const;
    void setName(const QString &name);
    QString group() const;
    void setGroup(const QString &group);
    double avgGrade() const;
    void setAvgGrade(double avgGrade);
};

#endif // STUDENT_H
