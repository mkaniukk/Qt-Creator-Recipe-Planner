#include <recipe.h>

void Recipe::addIngridient(const Ingridient &i){
    if(i.getName().isEmpty())
            return;
    this->ingridients.append(i);
}

void Recipe::setDescription(QJsonArray description){
    this->description = description;
}

void Recipe::removeIngridient(const Ingridient &i){

    int j = 0;
    foreach(auto const ing, ingridients){
        if(ing.getName()==i.getName()){
            ingridients.removeAt(j);
            return;
        }
        j++;
    }
}

void Recipe::removeIngridient(const QString name){

    int j = 0;
    foreach(auto const ing, ingridients){
        if(ing.getName()==name){
            ingridients.removeAt(j);
            return;
        }
        j++;
    }
}



