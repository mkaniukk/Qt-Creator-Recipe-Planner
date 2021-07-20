#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    data->saveToFile(*filename);
    delete ui;    
}

void Dialog::initializeWindow(const QModelIndex &index, RecipeData *d, QString *filename){

    data = d;
    this->filename = filename;
    recipe = new Recipe();
    *recipe = data->getRecipe(index.data().toString());
    ui->headerNameLineEdit->setText(recipe->getName());

    foreach(auto const el, recipe->getDescription()){
        ui->descriptionTextEdit->insertPlainText(el.toString()+"\n");
    }

    int i = 0;

    ui->ingridientsTableWidget->setColumnCount(2);
    ui->ingridientsTableWidget->insertColumn(ui->ingridientsTableWidget->columnCount());
    ui->ingridientsTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("name"));
    ui->ingridientsTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("quantity"));
    ui->ingridientsTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("unit"));
    foreach(auto const element, recipe->getIngridients()){
        ui->ingridientsTableWidget->insertRow((ui->ingridientsTableWidget->rowCount()));
        ui->ingridientsTableWidget->setItem(i, 0, new QTableWidgetItem(element.getName()));
        ui->ingridientsTableWidget->setItem(i, 1, new QTableWidgetItem(element.getQuantity()));
        ui->ingridientsTableWidget->setItem(i, 2, new QTableWidgetItem(element.getUnit()));
        i++;
    }
    ui->ingridientsTableWidget->setColumnWidth(0, this->width()/3);
    ui->ingridientsTableWidget->setColumnWidth(1, this->width()/3);
    ui->ingridientsTableWidget->setColumnWidth(2, this->width()/3);
}

void Dialog::on_addButton_clicked(){

    QString name = ui->nameLineEdit->text();
    QString quantity = ui->quantityLineEdit->text();
    QString unit = ui->unitLineEdit->text();
    if(name.isEmpty())
        return;
    updateIngridientsData(Ingridient(name, quantity, unit));
}


void Dialog::updateIngridientsData(const Ingridient &i){

    ui->ingridientsTableWidget->insertRow((ui->ingridientsTableWidget->rowCount()));
    ui->ingridientsTableWidget->setItem(ui->ingridientsTableWidget->rowCount()-1, 0, new QTableWidgetItem(i.getName()));
    ui->ingridientsTableWidget->setItem(ui->ingridientsTableWidget->rowCount()-1, 1, new QTableWidgetItem(i.getQuantity()));
    ui->ingridientsTableWidget->setItem(ui->ingridientsTableWidget->rowCount()-1, 2, new QTableWidgetItem(i.getUnit()));
    recipe->addIngridient(i);
    data->addRecipe(*recipe);
}

Recipe Dialog::updateRecipe(){
    return *recipe;
}

void Dialog::on_headerNameLineEdit_textChanged(const QString &arg1){

    QString text = ui->headerNameLineEdit->text();
    QString prev = recipe->getName();
    recipe->setName(text);
    data->updateRecipe(*recipe, prev);
    data->saveToFile(*filename);
}

void Dialog::on_descriptionTextEdit_textChanged(){

    QStringList l = ui->descriptionTextEdit->toPlainText().split("\n");
    QJsonArray arr = QJsonArray::fromStringList(l);
    recipe->setDescription(arr);
    data->addRecipe(*recipe);

}

void Dialog::on_saveButton_clicked()
{
    data->saveToFile(*filename);
    emit accepted();
}

void Dialog::on_pushButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    foreach(auto it, data->getIngridients(ui->headerNameLineEdit->text())){
        if(it.getName()==name){
            recipe->removeIngridient(it);
            it.setUnit(ui->unitLineEdit->text());
            it.setQuantity(ui->quantityLineEdit->text());
            recipe->addIngridient(it);
        }
    }

    int i = 0;

    ui->ingridientsTableWidget->setColumnCount(2);
    ui->ingridientsTableWidget->insertColumn(ui->ingridientsTableWidget->columnCount());
    ui->ingridientsTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("name"));
    ui->ingridientsTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("quantity"));
    ui->ingridientsTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("unit"));

    foreach(auto const element, recipe->getIngridients()){
        ui->ingridientsTableWidget->setItem(i, 0, new QTableWidgetItem(element.getName()));
        ui->ingridientsTableWidget->setItem(i, 1, new QTableWidgetItem(element.getQuantity()));
        ui->ingridientsTableWidget->setItem(i, 2, new QTableWidgetItem(element.getUnit()));
        i++;
    }
    ui->ingridientsTableWidget->removeRow(i);
    ui->ingridientsTableWidget->setColumnWidth(0, this->width()/3);
    ui->ingridientsTableWidget->setColumnWidth(1, this->width()/3);
    ui->ingridientsTableWidget->setColumnWidth(2, this->width()/3);
    data->addRecipe(*recipe);
    emit accepted();
}

void Dialog::on_deleteButton_clicked()
{
    int row = ui->ingridientsTableWidget->currentRow();
    if(row==-1)
        return;
    QString name = ui->ingridientsTableWidget->item(row, 0)->text();
    if(name.isEmpty())
        return;

    recipe->removeIngridient(name);
    data->addRecipe(*recipe);
    ui->ingridientsTableWidget->clear();

    int i = 0;

    ui->ingridientsTableWidget->setColumnCount(2);
    ui->ingridientsTableWidget->insertColumn(ui->ingridientsTableWidget->columnCount());
    ui->ingridientsTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("name"));
    ui->ingridientsTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("quantity"));
    ui->ingridientsTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("unit"));

    foreach(auto const element, recipe->getIngridients()){
        ui->ingridientsTableWidget->setItem(i, 0, new QTableWidgetItem(element.getName()));
        ui->ingridientsTableWidget->setItem(i, 1, new QTableWidgetItem(element.getQuantity()));
        ui->ingridientsTableWidget->setItem(i, 2, new QTableWidgetItem(element.getUnit()));
        i++;
    }
    ui->ingridientsTableWidget->removeRow(i);
    ui->ingridientsTableWidget->setColumnWidth(0, this->width()/3);
    ui->ingridientsTableWidget->setColumnWidth(1, this->width()/3);
    ui->ingridientsTableWidget->setColumnWidth(2, this->width()/3);
}

void Dialog::resizeEvent(QResizeEvent *event){
    ui->ingridientsTableWidget->setColumnWidth(0, this->width()/3);
    ui->ingridientsTableWidget->setColumnWidth(1, this->width()/3);
    ui->ingridientsTableWidget->setColumnWidth(2, this->width()/3);
}
