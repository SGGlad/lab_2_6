#ifndef ITEM_HPP
#define ITEM_HPP

#include "nlohman/json.hpp"
#include <iostream>'
#include <memory>
using json = nlohmann::json;

class Item
{
public:
    Item() = default;
    Item(std::string title, std::string description, std::string curStrenght, std::string startStrenght, std::string rare, std::string prise);
    std::string getTitle();
    std::string getDescription();
    std::string getCurStrenght();
    std::string getStartStrenght();
    std::string getRare();
    std::string getPrise();

private:
    std::string title_ = "";
    std::string description_ = "";
    std::string curStrenght_ = "";
    std::string startStrenght_ = "";
    std::string rare_ = "";
    std::string prise_ = "";
};
void AddToJson(std::shared_ptr<Item> item, std::string filename);
void ClearJson(std::string filename);

#endif // ITEM_HPP
