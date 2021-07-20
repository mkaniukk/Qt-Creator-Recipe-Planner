#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <recipedata.h>
#include <QListWidgetItem>
#include <QtWidgets>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void initializeWindow(const QModelIndex &index, RecipeData *data, QString *filename);
    void updateIngridientsData(const Ingridient &i);
    Recipe updateRecipe();

private slots:

    void on_addButton_clicked();

    void on_headerNameLineEdit_textChanged(const QString &arg1);

    void on_descriptionTextEdit_textChanged();

    void on_saveButton_clicked();

    void on_pushButton_clicked();

    void on_deleteButton_clicked();

    void resizeEvent(QResizeEvent *event);

private:

    Ui::Dialog *ui;
    Recipe *recipe;
    RecipeData *data;
    QString *filename;

};

#endif // DIALOG_H
