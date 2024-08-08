#include "dialogue.hpp"

int main() {
    // Открываем файл с данными в формате JSON
    std::ifstream file("../ChatExport_2024-04-13/small_result№0.json");
    
    // Парсим JSON из файла в объект json
    json data;
    file >> data;
    dialogue dio(data);
    dio.dump();
    std::cout <<"size: "<< dio.get_size();
    Date start(data["messages"][0]["date"]);
    start.dump();
    //++start;
    start.dump();
    return 0;
}
