#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Item/item.hpp"
#include <QListWidget>
#include <vector>
#include <memory>

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

    void CreateItem(std::string filename, std::vector<std::shared_ptr<Item>>& items);
    void sort(std::vector<std::shared_ptr<Item>>& items);
    bool isItemRight(std::shared_ptr<Item> item);
    void setTabls(std::vector<std::shared_ptr<Item>>& items);
    void ClearJson(std::string filename);
private slots:
    void on_LoadJson_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::shared_ptr<Item>> items{};
    std::vector<std::shared_ptr<Item>> correctItems{};
    std::vector<std::shared_ptr<Item>> wrongItems{};
    std::string correct_file = "outputCorrect.json";
    std::string wrong_file = "outputWrong.json";
};
#endif // MAINWINDOW_H
