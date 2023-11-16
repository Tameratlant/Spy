#include <iostream>
#include "date.hpp"
#include <fstream>
#include <list>
#include </home/tamerlan/workspace/Spy/json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;




struct message{
private:
    Date date;
    std::string name;
public:
    message(std::string date_, std::string name_): date(date_), name(name_) {
        /*Date date__(date_);
        date = date__;
        name = name_;*/
    }
    void dump() {
        std:: cout << "Message from:\n" << name << '\n'; date.dump();
    }
};

class dialogue{
    std::vector <message> data;
    size_t size;
public:
    dialogue(json data_) {
        size_t len = data_["messages"].size();
        std::cout << "len in const" << len <<'\n';
        size = len;
        
        for (int i = 0; i < len; ++i) {
            message buf(data_["messages"][i]["date"], data_["messages"][i]["from"]);
            data.push_back(buf);
        }
        
    }
    void dump() {
        for (int i = 0; i < size; ++i) {
            printf("Dump\n");
            data[i].dump();
            printf("-------------------------------------\n");
        }
    }
    size_t get_size() {
        return size;
    }
    std::vector <std::pair<int, int>>* count(Date l, Date r, std::string name) {

    }


};