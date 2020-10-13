#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

signals:

public slots:
    void save(const QString& surname, const QString& name, const QString& group, double avgGrade);
};

#endif // BACKEND_H
