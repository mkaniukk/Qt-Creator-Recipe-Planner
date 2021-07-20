#ifndef RECIPE_H
#define RECIPE_H
#include <QJsonArray>
#include <QDebug>
#include <ingridient.h>

class Recipe{

public:

    Recipe(){};
    Recipe(QString name, QJsonArray description, QList<Ingridient> ingridients){
        this->name = name;
        this->description = description;
        this->ingridients = ingridients;
    }
    ~Recipe(){ };

    void addIngridient(const Ingridient &i);
    void removeIngridient(const Ingridient &i);
    void removeIngridient(const QString name);
    void setDescription(QJsonArray description);
    QJsonArray getDescription() const {return description;};
    void setName(QString name){ this->name = name; };
    QString getName() const { return name; };
    void setIngridients(QList<Ingridient> ingridients){ this->ingridients = ingridients; };
    QList<Ingridient> getIngridients() const { return ingridients; };

private:
    QString name;
    QJsonArray description;
    QList<Ingridient> ingridients;

};

#endif // RECIPE_H
