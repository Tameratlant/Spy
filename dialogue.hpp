#include <iostream>
#include "date.hpp"
#include <fstream>
#include <list>
#include </home/tamerlan/workspace/json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;




struct message {
private:
    Date date;
    std::string name;
public:
    message(std::string date_, std::string name_): date(date_), name(name_) {}
    void dump() {
        std:: cout << "Message from:\n" << name << '\n'; date.dump();
    }
    inline Date get_date() {
        return date;
    }
    inline std::string get_name() {
        return name;
    }
};

class dialogue{
    std::vector <message> data;
    size_t size;
    //std::unordered_map <Date, int> map;
    
    int search(const Date date) {           //тут будет бинпоиск, честно
        for (int i = 0; i < size; ++i) {
            if ((data[i].get_date() < date) & (data[i+1].get_date() > date))
                return i;
        }


    }
    
public:
    dialogue(json data_) {
        size_t len = data_["messages"].size();
        //std::cout << "len in const" << len <<'\n';
        size = len;
        
        for (int i = 0; i < len; ++i) {
            message buf(data_["messages"][i]["date"], data_["messages"][i]["from"]);
            data.push_back(buf);
        }

        //fill_map();
        
    }

    void dump() {
        for (int i = 0; i < size; ++i) {
            printf("Dump\n");
            data[i].dump();
            printf("-------------------------------------\n");
        }
    }

    inline size_t get_size() {
        return size;
    }

    void append(json data_) {
        size_t len = data_["messages"].size();
        //std::cout << "len in const" << len <<'\n';
        size += len;
        
        for (int i = 0; i < len; ++i) {
            message buf(data_["messages"][i]["date"], data_["messages"][i]["from"]);
            data.push_back(buf);
        }
        printf("Boss, you ate the child\n");
    }


    inline void count(Date l, Date r, std::string name, int* count_name, int* count_total) {
        int left = search(l);
        int right = search(r);
        int count = 0;
        for (int i = left; i < right; ++i) {
            if (data[i].get_name() == name) count++;
        }
        *count_name = count;
        *count_total = right - left;
    }
    /*
    void fill_map() {
        
        size_t len = data.size();
        Date start = data[0].get_date();
        Date end = data[len-1].get_date();
        for (Date i = start; i < end; ++i) {
            map[i] = this->search(i);
        }
    }
    

    void count(Date l, Date r) {
        return map[r] - map[l];
    }
    */

};