#include "shoppinglist.h"
#include "ui_shoppinglist.h"

ShoppingList::ShoppingList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShoppingList)
{
    ui->setupUi(this);
    ingridients = new QList<Ingridient>;
}

ShoppingList::~ShoppingList()
{
    delete ui;
}

void ShoppingList::initialize(RecipeData *d){

    data = d;
    foreach (auto el, data->getRecipeNames()) {
        ui->comboBox->addItem(el);
    }
}

void ShoppingList::on_pushButton_clicked(){

        bool changed = false;
        for(int i = 0; i < ui->listWidget->count() ; i++){
            QStringList arr = ui->listWidget->item(i)->text().split(" ");
            if(arr[0]==ui->comboBox->currentText()){
                changed = true;
                if(arr.length()==1){
                   ui->listWidget->item(i)->setText(ui->listWidget->item(i)->text() + " x 2");
                }else{
                    int count = (arr[2].toInt()+1);
                    arr[2] = QString::number(count);
                    ui->listWidget->item(i)->setText(ui->comboBox->currentText() + " x " + arr[2]);
                }
            }
        }
        if(!changed)
            ui->listWidget->addItem(ui->comboBox->currentText());

        foreach(auto el, data->getIngridients(ui->comboBox->currentText()))
            addToIngridients(el);

        sort();
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);

        int i = 0;
        ui->tableWidget->setColumnCount(2);
        ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("name"));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("quantity"));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("unit"));
        for(auto element = ingridients->begin() ; element!=ingridients->end() ; element++){

            ui->tableWidget->insertRow((ui->tableWidget->rowCount()));
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(element->getName()));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(element->getQuantity()));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(element->getUnit()));
            i++;
         }
        ui->tableWidget->setColumnWidth(0, ui->tableWidget->width()/3);
        ui->tableWidget->setColumnWidth(1, ui->tableWidget->width()/3);
        ui->tableWidget->setColumnWidth(2, ui->tableWidget->width()/3);
}

void ShoppingList::addToIngridients(Ingridient i){
    for(auto element = ingridients->begin() ; element!=ingridients->end() ; element++){
        if(element->getName()==i.getName()&&element->getUnit()==i.getUnit()){
            float quan = element->getQuantity().toFloat() + i.getQuantity().toFloat();
            element->setQuantity(QString::number(quan));
            return;
        }
    }
    ingridients->append(i);
}

void ShoppingList::resizeEvent(QResizeEvent *event){
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width()/3);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->width()/3);
    ui->tableWidget->setColumnWidth(2, ui->tableWidget->width()/3);
}

void ShoppingList::sort(){
    if(ingridients->isEmpty())
        return;

    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0; i<ingridients->size()-1; i++){
            if(ingridients->at(i).getName()>ingridients->at(i+1).getName()){
                ingridients->swap(i,i+1);
                sorted = false;
            }
        }
    }
}
