#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include<fstream>
#include <string>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList headers{"название","описание","текущая\nпрочность","начальная\nпрочность","редкость","цена"};
    ui->setupUi(this);
    ui->Correct->setColumnCount(6);
    ui->Correct->setRowCount(0);
    ui->Correct->setHorizontalHeaderLabels(headers);
    ui->Wrong->setColumnCount(6);
    ui->Wrong->setRowCount(0);
    ui->Wrong->setHorizontalHeaderLabels(headers);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadJson_clicked()
{
    try{
        if (correctItems.size()!=0){
            correctItems.clear();
        }
        if (wrongItems.size() != 0){
            wrongItems.clear();
        }
        if (items.size() !=0){
            items.clear();
        }
        ui->Correct->setRowCount(0);
        ui->Wrong->setRowCount(0);
        ClearJson(correct_file);
        ClearJson(wrong_file);
    }catch(...){
        qInfo()<<"error";
    }
    QString filename = QFileDialog::getOpenFileName(this, "Choose file");
    CreateItem(filename.toStdString(), items);
    sort(items);
    //qInfo()<<items.size();
    try{
        setTabls(items);
    }catch(...){
        qInfo()<<"table";
    }

}

void MainWindow::CreateItem(std::string filename, std::vector<std::shared_ptr<Item>>& items){
    std::ifstream input;
    input.open(filename);
    if(input.is_open()){
        json data = json::parse(input);
        for (auto elem : data){
            std::shared_ptr<Item> item = std::make_shared<Item>(elem["title"].get<std::string>(), elem["description"].get<std::string>(), elem["curStrenght"].get<std::string>(),
                elem["startStrenght"].get<std::string>(), elem["rare"].get<std::string>(), elem["prise"].get<std::string>());
            items.emplace_back(item);
        }
        input.close();
    }
    else{
        qInfo()<<"file not open";
    }
}

void MainWindow::sort(std::vector<std::shared_ptr<Item>>& items){
    for(int i = 0; i < items.size(); ++i){
        for(int j = i; j < items.size(); ++j){
            if(items[i]->getTitle() < items[j]->getTitle()){
                swap(items[i], items[j]);
            }
        }
    }
}
bool MainWindow::isItemRight(std::shared_ptr<Item> item){
    if(item->getTitle() == ""){return false;}
    if(item->getDescription() == ""){return false;}
    if(item->getRare() == ""){return false;}
    try{
        float tmp{std::stof(item->getCurStrenght())};
        if ((tmp > 100.0)||(tmp < 0.0000001)){
            return false;
        }
    }catch(...){return false;}
    try{
        float tmp{std::stof(item->getStartStrenght())};
        if ((tmp > 100.0)||(tmp < 0.0000001)){
            return false;
        }
    }catch(...){return false;}
    try{
        int tmp{std::stoi(item->getPrise())};
        if (tmp < 0){
            return false;
        }
    }catch(...){return false;}
    return true;
}
void MainWindow::setTabls(std::vector<std::shared_ptr<Item>>& items){
    for(int i = 0; i < items.size(); ++i){
        auto item = items[i];
        if(isItemRight(item)){
            correctItems.emplace_back(item);
        }
        else{
            wrongItems.emplace_back(item);
        }
    }
    //qInfo()<<correctItems.size() << "cr";
    //qInfo()<<wrongItems.size()<< "wr";
    for (int i = 0; i < correctItems.size(); ++i){
        auto item = correctItems[i];
        ui->Correct->setRowCount(ui->Correct->rowCount()+1);
        ui->Correct->setItem(i, 0,  new QTableWidgetItem(QString::fromStdString(item->getTitle())));
        ui->Correct->setItem(i, 1,  new QTableWidgetItem(QString::fromStdString(item->getDescription())));
        ui->Correct->setItem(i, 2,  new QTableWidgetItem(QString::fromStdString(item->getCurStrenght())));
        ui->Correct->setItem(i, 3,  new QTableWidgetItem(QString::fromStdString(item->getStartStrenght())));
        ui->Correct->setItem(i, 4,  new QTableWidgetItem(QString::fromStdString(item->getRare())));
        ui->Correct->setItem(i, 5,  new QTableWidgetItem(QString::fromStdString(item->getPrise())));
        try{
        AddToJson(item, correct_file);
        }catch(...){
            qInfo()<<"cr write " <<item->getTitle();
        }
    }
    for(int i = 0; i < wrongItems.size(); ++i){
        auto item = wrongItems[i];
        ui->Wrong->setRowCount(ui->Wrong->rowCount()+1);
        ui->Wrong->setItem(i, 0,  new QTableWidgetItem(QString::fromStdString(item->getTitle())));
        if (item->getTitle() ==  ""){
            QTableWidgetItem* tmp = ui->Wrong->item(i, 0);
            tmp->setBackground(QBrush(QColor(255,0,0)));
        }
        ui->Wrong->setItem(i, 1,  new QTableWidgetItem(QString::fromStdString(item->getDescription())));
        if (item->getDescription() ==  ""){
            QTableWidgetItem* tmp = ui->Wrong->item(i, 1);
            tmp->setBackground(QBrush(QColor(255,0,0)));
        }
        ui->Wrong->setItem(i, 2,  new QTableWidgetItem(QString::fromStdString(item->getCurStrenght())));
        try{
            float tmp{std::stof(item->getCurStrenght())};
            float tmp2;
            try{
                tmp2 = std::stof(item->getStartStrenght());
            }catch(...){
                tmp2 = tmp;
            }
            if ((tmp < 0.000001)||(tmp > 100.0) || (tmp > tmp2)){
                QTableWidgetItem* tmp1 = ui->Wrong->item(i, 2);
                tmp1->setBackground(QBrush(QColor(255,0,0)));
            }
        }catch(...){
            QTableWidgetItem* tmp = ui->Wrong->item(i, 2);
            tmp->setBackground(QBrush(QColor(255,0,0)));
        }
        ui->Wrong->setItem(i, 3,  new QTableWidgetItem(QString::fromStdString(item->getStartStrenght())));
        try{
            float tmp{std::stof(item->getStartStrenght())};
            if ((tmp < 0.000001)||(tmp > 100.0)){
                QTableWidgetItem* tmp1 = ui->Wrong->item(i, 3);
                tmp1->setBackground(QBrush(QColor(255,0,0)));
            }
        }catch(...){
            QTableWidgetItem* tmp = ui->Wrong->item(i, 3);
            tmp->setBackground(QBrush(QColor(255,0,0)));
        }
        ui->Wrong->setItem(i, 4,  new QTableWidgetItem(QString::fromStdString(item->getRare())));
        if (item->getRare() ==  ""){
            QTableWidgetItem* tmp = ui->Wrong->item(i, 4);
            tmp->setBackground(QBrush(QColor(255,0,0)));
        }
        ui->Wrong->setItem(i, 5,  new QTableWidgetItem(QString::fromStdString(item->getPrise())));
        try{
            int tmp{std::stoi(item->getPrise())};
            if (tmp<0){
                QTableWidgetItem* tmp1 = ui->Wrong->item(i, 5);
                tmp1->setBackground(QBrush(QColor(255,0,0)));
            }
        }catch(...){
            QTableWidgetItem* tmp = ui->Wrong->item(i, 5);
            tmp->setBackground(QBrush(QColor(255,0,0)));
        }
        try{
            AddToJson(item, wrong_file);
        }catch(...){
            qInfo()<<"wr write "<<item->getTitle();
        }
    }
}

void MainWindow::ClearJson(std::string filename){
    std::ifstream tmp(filename);
    if (tmp.is_open())
        tmp.close();
    std::ofstream out(filename);
    out.clear();
    out.close();
}

