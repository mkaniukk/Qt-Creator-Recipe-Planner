#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "recipedata.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    filename = new QString();
    setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    dialog = new Dialog();
    connect(dialog, SIGNAL(accepted()), this, SLOT(setup()));
    dialog->initializeWindow(QModelIndex(), data, filename);
    dialog->show();
    fillTableWithNames();
}

void MainWindow::on_editButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if(index.isValid())
        on_tableView_doubleClicked(index);
    fillTableWithNames();
    setup();
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    QString name = index.data().toString();
    data->remove(name);
    data->saveToFile(*filename);
    fillTableWithNamesUsingFile();
    ui->tableView->update();
    setup();

}

void MainWindow::fillTableWithNamesUsingFile(){

    int i = 0;
    foreach (auto const el, data->getRecipes()) {
        QModelIndex index = model->index(i++, 0, QModelIndex());
        model->setData(index, el.getName(), Qt::EditRole);
    }
}

void MainWindow::fillTableWithNames(){

    int i = 0;
    foreach (auto const el, data->getRecipes()) {
        QModelIndex index = model->index(i++, 0, QModelIndex());
        model->setData(index, el.getName(), Qt::EditRole);
    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    dialog = new Dialog();
    connect(dialog, SIGNAL(accepted()), this, SLOT(setup()));
    dialog->initializeWindow(index, data, filename);
    dialog->show();
    setup();
}

void MainWindow::updateRecipe(){

    Recipe r = dialog->updateRecipe();
    data->getRecipes().append(r);
    fillTableWithNames();
}

void MainWindow::setup(){

    data = new RecipeData();
    data->initializeData(*filename);
    model = new QStandardItemModel(data->getRecipes().length(), 1, this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Recipe"));
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    fillTableWithNames();
}


void MainWindow::on_actionNew_triggered()
{
    *filename = QFileDialog::getOpenFileName(this, "Open file", tr("(*.*)"), tr("(*.json)"));
    setup();
}

void MainWindow::on_actionClose_triggered()
{
    *filename = "";
    setup();
}

void MainWindow::on_actionNew_2_triggered()
{
    *filename = QFileDialog::getSaveFileName(this, "New file", tr(".json"), tr("(*.json)"));
    data->saveToFile(*filename);
    setup();
}

void MainWindow::on_actionShopping_List_triggered()
{
    shoppinglist = new ShoppingList();
    shoppinglist->initialize(data);
    shoppinglist->show();
}
