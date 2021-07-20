#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFileDialog>
#include <recipedata.h>
#include <dialog.h>
#include <shoppinglist.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void fillTableWithNamesUsingFile();
    void fillTableWithNames();
    void updateRecipe();

private slots:

    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void setup();

    void on_actionNew_triggered();

    void on_actionClose_triggered();

    void on_actionNew_2_triggered();

    void on_actionShopping_List_triggered();

private:

    Ui::MainWindow *ui;
    Dialog *dialog;
    QStandardItemModel *model;
    RecipeData *data;
    QString *filename;
    ShoppingList *shoppinglist;
};
#endif // MAINWINDOW_H
