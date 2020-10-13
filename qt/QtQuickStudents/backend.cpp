#include "backend.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

Backend::Backend(QObject *parent) : QObject(parent)
{

}

void Backend::save(const QString &surname, const QString &name, const QString &group, double avgGrade)
{
    QFile file{"data.txt"};
    if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
            return;
    QTextStream stream(&file);
    stream<< surname<<"\n"
          << name<<"\n"
          << group<<"\n"
          << avgGrade<<"\n\n";
    file.close();
}
