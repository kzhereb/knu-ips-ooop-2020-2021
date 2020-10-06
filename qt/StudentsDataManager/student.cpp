#include "student.h"

QString Student::surname() const
{
    return _surname;
}

void Student::setSurname(const QString &surname)
{
    _surname = surname;
}

QString Student::name() const
{
    return _name;
}

void Student::setName(const QString &name)
{
    _name = name;
}

QString Student::group() const
{
    return _group;
}

void Student::setGroup(const QString &group)
{
    _group = group;
}

double Student::avgGrade() const
{
    return _avgGrade;
}

void Student::setAvgGrade(double avgGrade)
{
    _avgGrade = avgGrade;
}

Student::Student()
{

}
