#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include<fstream>
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Name_textChanged(const QString &arg1)
{
    title_ = arg1.toStdString();
}

void MainWindow::on_Description_textChanged()
{
    description_ = ui->Description->toPlainText().toStdString();
}

void MainWindow::on_CurStrenght_textChanged(const QString &arg1)
{
    curStrenght_ = arg1.toStdString();
}

void MainWindow::on_StsrtStranght_textChanged(const QString &arg1)
{
    startStrenght_ = arg1.toStdString();
}

void MainWindow::on_Rare_textChanged(const QString &arg1)
{
    rare_ = arg1.toStdString();
}

void MainWindow::on_Prise_textChanged(const QString &arg1)
{
    prise_ = arg1.toStdString();
}

void MainWindow::on_FromTxt_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose file");
    std::ifstream input;
    input.open(filename.toStdString());
    std::vector<QString> str;
    for (std::string s; std::getline(input, s, '/');){
        str.emplace_back(QString::fromStdString(s));
    }
    ui->Name->setText(str[0]);
    ui->Description->setText(str[1]);
    ui->CurStrenght->setText(str[2]);
    ui->StsrtStranght->setText(str[3]);
    ui->Rare->setText(str[4]);
    ui->Prise->setText(str[5]);

}


void MainWindow::on_Save_clicked()
{
    std::string filename = "result.json";
    Item helmet(title_, description_, curStrenght_, startStrenght_, rare_, prise_);
    std::shared_ptr<Item>it = std::make_shared<Item>(helmet);
    AddToJson(it, filename);
}

