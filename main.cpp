#include "dialogue.hpp"

int main() {
    // Открываем файл с данными в формате JSON
    std::ifstream file("../ChatExport_2024-04-13/small_result№0.json");
    
    // Парсим JSON из файла в объект json
    json data;
    file >> data;
    
    // Пример обработки данных: выводим содержимое JSON
    //std::cout << "Содержимое JSON:" << std::endl;
    //std::cout << data.dump(2) << std::endl; // dump позволяет красиво форматировать JSON при выводе

    //std:: cout << data["messages"][0].dump(2);
    //std::cout<<massege.size();

    //std::cout << data["messages"].size();


    //Date date("2023-09-30T19:51:06");
    //message mes(data["messages"][0]["date"], data["messages"][0]["from"]);
    //mes.dump();
    dialogue dio(data);
    dio.dump();
    std::cout <<"size: "<< dio.get_size();
    Date start(data["messages"][0]["date"]);
    start.dump();
    ++start;
    start.dump();
    //Date start = data
    return 0;
}