#ifndef INGRIDIENT_H
#define INGRIDIENT_H
#include <QMainWindow>
#include <QPushButton>

class Ingridient{

public:

    Ingridient(QString name, QString quantity, QString unit){
        this->name = name;
        this->quantity = quantity;
        this->unit = unit;
    }
    ~Ingridient(){ };

    QString getName() const { return name; }
    QString getQuantity() const { return quantity; }
    QString getUnit() const { return unit; }
    void setName(const QString &name){ this->name = name; }
    void setQuantity(const QString &quantity){ this->quantity = quantity; }
    void setUnit(const QString &unit){ this->unit = unit; }

signals:

private slots:

    void valueChanged(int);

private:

    QString name;
    QString quantity;
    QString unit;

};

#endif // INGRIDIENT_H
