#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Item/item.hpp"
#include <iostream>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void CreateItemFromTXT(QString filename);


private slots:
    void on_Name_textChanged(const QString &arg1);

    void on_Description_textChanged();

    void on_CurStrenght_textChanged(const QString &arg1);

    void on_StsrtStranght_textChanged(const QString &arg1);

    void on_Rare_textChanged(const QString &arg1);

    void on_Prise_textChanged(const QString &arg1);

    void on_FromTxt_clicked();

    void on_Save_clicked();

private:
    Ui::MainWindow *ui;
    std::string title_ = "";
    std::string description_ = "";
    std::string curStrenght_ = "";
    std::string startStrenght_ = "";
    std::string rare_ = "";
    std::string  prise_ = "";
};
#endif // MAINWINDOW_H
