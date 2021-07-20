#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Address picker");
    ui->cityComboBox->addItem("London");
    ui->cityComboBox->addItem("Paris");
    ui->cityComboBox->addItem("Viena");
    ui->cityComboBox->addItem("Berlin");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveToFile(QString filename)
{
    QFile file;
    file.setFileName(filename);

    if(!file.open(QIODevice::WriteOnly | QFile::Append))
        return;

    file.write(ui->firstnameLineEdit->text().toUtf8()+";");
    file.write(ui->lastnameLineEdit->text().toUtf8()+";");
    file.write(ui->cityComboBox->currentText().toUtf8()+";");
    file.write(ui->streetLineEdit->text().toUtf8()+";");
    file.write(ui->noLineEdit->text().toUtf8()+";");
    if(ui->maleRadioButton->isChecked())
        file.write("male");
    else if(ui->femaleRadioButton_2->isChecked())
        file.write("female");
    file.write(("\n"));

    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    saveToFile("address.txt");
}

void MainWindow::on_pushButton_clicked()
{
    ui->firstnameLineEdit->clear();
    ui->lastnameLineEdit->clear();
    ui->streetLineEdit->clear();
    ui->noLineEdit->clear();
}

void MainWindow::on_maleRadioButton_clicked()
{
    ui->femaleRadioButton_2->setChecked(false);
}

void MainWindow::on_femaleRadioButton_2_clicked()
{
    ui->maleRadioButton->setChecked(false);
}
