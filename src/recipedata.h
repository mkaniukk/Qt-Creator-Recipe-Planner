#ifndef RECIPEDATA_H
#define RECIPEDATA_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QtDebug>
#include <recipe.h>


class RecipeData {

public:

    RecipeData(){ };
    ~RecipeData(){ };

    void initializeData(QString file);
    void initializeDataFromFile();
    void saveToFile(QString file);
    void addRecipe(QString namename, QJsonArray description, QList<Ingridient> ingridients);
    void addRecipe(Recipe r);
    void remove(Recipe &r);
    void remove(QString name);
    void refreshData(QStringList r);
    void updateRecipe(Recipe r, QString prev_name);
    QJsonObject getData() const { return jsonData; }
    QStringList getNames() const { return recipeNames; }
    QList<Recipe> getRecipes() const { return recipesList; }
    QJsonArray getDescription(QString name);
    QList<Ingridient> getIngridients(QString name);
    Recipe getRecipe(QString name);
    QStringList getRecipeNames();
    void clearData();

private:

    QStringList recipeNames;
    QList<Recipe> recipesList;
    QJsonObject jsonData;

};

#endif // RECIPEDATA_H
