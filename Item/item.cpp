#include "item.hpp"
#include <fstream>

Item::Item(std::string title, std::string description, std::string curStrenght, std::string startStrenght, std::string rare, std::string prise):title_(title), description_(description),
curStrenght_(curStrenght), startStrenght_(startStrenght), rare_(rare), prise_(prise){}
std::string Item::getTitle(){
    return title_;
}
std::string Item::getDescription(){
    return description_;
}
std::string Item::getCurStrenght(){
    return curStrenght_;
}
std::string Item::getStartStrenght(){
    return startStrenght_;
}
std::string Item::getRare(){
    return rare_;
}
std::string Item::getPrise(){
    return prise_;
}

void AddToJson(std::shared_ptr<Item> item, std::string filename){
    std::ifstream checked_file_existense(filename);
    bool flag;
    if (checked_file_existense.is_open()){
        std::string inp;
        checked_file_existense>>inp;
        if (inp != ""){
            flag = true;
        }
        else{
            flag = false;
        }
    }
    else{
        flag = false;
    }
    checked_file_existense.close();
    std::ofstream output;
    if (flag){
        std::ifstream tmp(filename);
        json arr;
        tmp>>arr;
        tmp.close();
        output.open(filename);
        std::string title = item->getTitle();
        std::string description = item->getDescription();
        std::string curStrenght = item->getCurStrenght();
        std::string stersStrenght = item->getStartStrenght();
        std::string rare = item->getRare();
        std::string prise = item->getPrise();
        json obj = json::object({
            {"title",title}, {"description", description}, {"curStrenght", curStrenght},
            {"startStrenght", stersStrenght}, {"rare", rare}, {"prise", prise}
        });
        arr.emplace_back(obj);
        output<<arr.dump(4);
        output.close();
    }
    else{
        json arr = json::array();
        output.open(filename);
        std::string title = item->getTitle();
        std::string description = item->getDescription();
        std::string curStrenght = item->getCurStrenght();
        std::string stersStrenght = item->getStartStrenght();
        std::string rare = item->getRare();
        std::string prise = item->getPrise();
        json obj = json::object({
            {"title",title}, {"description", description}, {"curStrenght", curStrenght},
            {"startStrenght", stersStrenght}, {"rare", rare}, {"prise", prise}
        });
        arr.emplace_back(obj);
        output<<arr.dump(4);
        output.close();
    }
}

