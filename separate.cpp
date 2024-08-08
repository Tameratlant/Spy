#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>

#define BIG_FILE "Wolf.json"
#define MAX_SIZE 100
#define OUTPUT_NAME "small_result№"
#define HEADER_NAME "header"
#define HEAD_SIZE 5

void header_create(std::ifstream& big_file) {
    if (!big_file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    std::ofstream header (HEADER_NAME);
    std::string line;
    for (int i = 0; i < HEAD_SIZE; ++i) {
        if (std::getline(big_file, line)) {
            header << line << std::endl;
        } else {
            break;  // Если достигнут конец файла раньше, чем скопировано 5 строк
        }
    }
    header.close();
    return;

}

void head_copy(std::ofstream& small_file, std::ifstream& header, int number) {
    std::cout << "head copy called to file " << number <<'\n';
    if (!header.is_open() || !small_file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }

    // Копируем 5 верхних строк из одного файла в другой
    std::string line;
    for (int i = 0; i < HEAD_SIZE; ++i) {
        if (std::getline(header, line)) {
            small_file << line << std::endl;
        } else {
            break;  // Если достигнут конец файла раньше, чем скопировано 10 строк
        }
    }
    header.close();
    return;
}

std::string copy_massages(std::ifstream& big_file,std::ofstream& small, int number) {               //Копирует из большого в маленькие по MAX_SIZE сообщений 
    std::string line;
    std::vector<std::string> lines;
    int count  = 0;
    while(count < MAX_SIZE) {
        if (!std::getline(big_file, line)) {
            printf("End of file\n");
            return "";
        }
        if (line.find("\"id:\"") != std::string::npos) {
            printf("!");
            count++;
        }
        small << line << std::endl;
    }

    while(std::getline(big_file, line)) {
        if (line.find("\"id:\"") == std::string::npos)
                lines.push_back(line);
        else {
            lines.pop_back();
            lines[lines.size() - 2].pop_back();
            for (std::string &tmp : lines) {
                small << line << std::endl;
            }
            lines.clear();
            lines.push_back("  {");
            lines.push_back(line);
            break;
        }
    }
    small << "]" << std::endl;
    small << "}" << std::endl;
    small.close();
    return lines[lines.size()-1];
}

int separater(std::ifstream& big_file) {                //делит на файлы по MAX_SIZE сообщений и выводит число созданных файлов
    int count = 0;
    
    //std::cout << "Header copied for file № " << number << '\n';
    header_create(big_file);
    std::string last_string;
    while (count < 1000) {
        std::string num = std::to_string(count);
        std::ofstream small (OUTPUT_NAME+num);
        small << last_string << std::endl;
        std::ifstream header (HEADER_NAME);
        std::cout<<"Created file "<< OUTPUT_NAME+num <<'\n';
        head_copy(small, header, count);
        count++;
        
        last_string = copy_massages(big_file, small, count);

        if (last_string.empty())
            break;
    }
    return count;
}

int main () {
   std::ifstream big(BIG_FILE);
   printf("Total number = %d",separater(big));
}

