#include "item.hpp"
#include <fstream>
#include <memory>

int main(){
    Item item1{"1", "123", "43", "44", "43", "43"};
    Item item2{"2","","","","",""};
    std::string file = "test.json";
    std::fstream out;
    try{
    out.open(file, std::ios::out);
    if (out.is_open()){
        std::cout<<"open\n";
        out.close();
        out.open(file, std::ios::in);
        std::string d;
        out>> d;
        std::cout<<"in file: "<<d;
    }
    
    AddToJson(std::make_shared<Item>(item2), file);
    }catch(...){
        std::cout<<"rer\n";
    }
    try{
    ClearJson(file);
    }catch(...){
        std::cout<<"error\n";
    }
    try{
    AddToJson(std::make_shared<Item>(item1), file);
    }catch(...){
        std::cout<<"er\n";
    }
    std::cout<<"done";
}