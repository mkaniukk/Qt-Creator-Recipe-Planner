#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H

#include <QDialog>
#include <recipedata.h>

namespace Ui {
class ShoppingList;
}

class ShoppingList : public QDialog
{
    Q_OBJECT

public:
    explicit ShoppingList(QWidget *parent = nullptr);
    ~ShoppingList();

    void initialize(RecipeData *d);
    void addToIngridients(Ingridient i);
    void sort();

private slots:
    void on_pushButton_clicked();

    void resizeEvent(QResizeEvent *event);

private:
    Ui::ShoppingList *ui;
    RecipeData *data;
    QList<Ingridient> *ingridients;

};

#endif // SHOPPINGLIST_H
