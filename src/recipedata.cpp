#include <recipedata.h>

void RecipeData::initializeData(QString fileName){
    if(fileName.isEmpty()){
        return;
    }

    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    QString data = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
    jsonData = document.object();
    initializeDataFromFile();
}

void RecipeData::initializeDataFromFile(){
    recipeNames = getRecipeNames();
    foreach (auto const el, recipeNames)
        addRecipe(el, getDescription(el), getIngridients(el));
}

void RecipeData::refreshData(QStringList r){
    recipeNames = r;
    foreach (auto const el, recipeNames)
        addRecipe(el, getDescription(el), getIngridients(el));
}

QStringList RecipeData::getRecipeNames(){
    if (jsonData.isEmpty())
        return QStringList();

    QStringList dataList = jsonData.keys();
    return dataList;
}

QJsonArray RecipeData::getDescription(QString name){
    if (jsonData.isEmpty())
        return QJsonArray();

    QJsonArray arr;
    for (auto it = jsonData.begin() ; it != jsonData.end() ; it++) {
        if(it.key()==name){
            QJsonObject element = it->toObject();
            for(auto iter = element.begin() ; iter != element.end() ; iter++){
                if(iter.key()=="recipe"){
                    arr = iter.value().toArray();
                }
            }
        }
    }
    return arr;
}

void RecipeData::addRecipe(QString name, QJsonArray description, QList<Ingridient> ingridients){

    Recipe *recipe = new Recipe(name, description, ingridients);
    recipesList.append(*recipe);

}

QList<Ingridient> RecipeData::getIngridients(QString name){
    if (jsonData.isEmpty()){
        return QList<Ingridient>();
    }

    QList<Ingridient> ingridientList;
    for (auto it = jsonData.begin() ; it != jsonData.end() ; it++) {
        if(it.key()==name){
            QJsonObject element = it->toObject();
            for(auto iter = element.begin() ; iter != element.end() ; iter++){
                if(iter.key()!="recipe"){
                   QString ingridient = iter.value().toString();
                   QStringList arr = ingridient.split((" "));
                   QString quantity = arr[0];
                   QString unit = "";
                   for(int i = 1; i < arr.length(); i++)
                       unit += arr[i] + " ";
                   unit.chop(1);
                   ingridientList.append(Ingridient(iter.key(), quantity, unit));
                }
            }
        }
    }
    return ingridientList;
}

void RecipeData::addRecipe(Recipe r) {

    int i = 0;
    foreach(auto const el, recipesList){
        if(el.getName()==r.getName()){
            recipesList.replace(i, r);
            return;
        }
        i++;
    }
    recipesList.append(r);
};

void RecipeData::updateRecipe(Recipe r, QString prev_name) {
    if(prev_name.isEmpty()){
        recipesList.append(r);
    }
    int i = 0;
    foreach(auto const el, recipesList){
        if(el.getName()==prev_name){
            recipesList.replace(i, r);
            return;
        }
        i++;
    }
};

void RecipeData::clearData(){
     recipesList.clear();
}

Recipe RecipeData::getRecipe (QString name){
    if (jsonData.isEmpty()){
        return Recipe();
    }

    foreach(auto el, recipesList)
        if(el.getName()==name){
            return el;
    }
    return Recipe();
}

void RecipeData::saveToFile(QString filename){

    QFile file;
    file.setFileName(filename);

    if(!file.open(QIODevice::WriteOnly | QFile::Text))
        return;

    QJsonObject obj;
    foreach (const auto recipe, this->recipesList) {
        QJsonObject obj2;
        QJsonObject obj3;
        obj2["recipe"] = recipe.getDescription();
        QList<Ingridient> ingredients = recipe.getIngridients();
        for (auto it = ingredients.begin(); it != ingredients.end(); ++it)
        {
             obj2[it->getName()] = it->getQuantity() + " " + it->getUnit();
        }
             obj[recipe.getName()] = obj2;
    }
    QJsonDocument doc(obj);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}



void RecipeData::remove(QString name){

    int i = 0;
    foreach(auto const el, recipesList){
        if(el.getName()==name){
            recipesList.removeAt(i);
            return;
        }
        i++;
    }
}

