#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>

//#define BIG_FILE "Wolf.json"
#define MAX_SIZE 100
#define OUTPUT_NAME "small_result№"
#define HEADER_NAME "header"
#define HEAD_SIZE 5

//Создает файл с заголовком из исходного файла
void header_create(std::ifstream& source_file) {
    if (!source_file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    std::ofstream header (HEADER_NAME);
    std::string line;
    for (int i = 0; i < HEAD_SIZE; ++i) {
        if (std::getline(source_file, line)) {
            header << line << std::endl;
        } else {
            break;  // Если достигнут конец файла раньше, чем скопировано 5 строк
        }
    }
    header.close();
    return;

}

//Копирует заголвок в целевые файлы
void head_copy(std::ofstream& target_file, std::ifstream& header, int number) {
    std::cout << "head copy called to file " << number <<'\n';
    if (!header.is_open() || !target_file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }

    // Копируем 5 верхних строк из одного файла в другой
    std::string line;
    for (int i = 0; i < HEAD_SIZE; ++i) {
        if (std::getline(header, line)) {
            target_file << line << std::endl;
        } else {
            break;  // Если достигнут конец файла раньше, чем скопировано 10 строк
        }
    }
    header.close();
    return;
}

//Копирует по MAX_SIZE из исходного файла в целевые 
std::string copy_massages(std::ifstream& source_file,std::ofstream& target_file, int number) {
    std::vector<std::string> lines;
    std::string line;
    int count  = 0;
    while(count < MAX_SIZE) {
        if (!std::getline(source_file, line)) {
            printf("End of file\n");
            return "";
        }
        if (line.find("\"id:\"") != std::string::npos) {
            printf("!");
            count++;
        }
        target_file << line << std::endl;
    }

    while(std::getline(source_file, line)) {
        if (line.find("\"id:\"") == std::string::npos)
                lines.push_back(line);
        else {
            lines.pop_back();
            lines[lines.size() - 2].pop_back();
            for (std::string &tmp : lines) {
                target_file << line << std::endl;
            }
            lines.clear();
            lines.push_back("  {");
            lines.push_back(line);
            break;
        }
    }
    target_file << "]" << std::endl;
    target_file << "}" << std::endl;
    target_file.close();
    return lines[lines.size()-1];
}

//делит на файлы по MAX_SIZE сообщений и выводит число созданных файлов
int separater(std::ifstream& source_file) {                
    int count = 0;
    header_create(source_file);
    std::string last_string;
    while (count < 1000) {
        std::string num = std::to_string(count);
        std::ofstream target_file (OUTPUT_NAME+num);
        target_file << last_string << std::endl;
        std::ifstream header (HEADER_NAME);
        std::cout<<"Created file "<< OUTPUT_NAME+num <<'\n';
        head_copy(target_file, header, count);
        count++;
        
        last_string = copy_massages(source_file, target_file, count);

        if (last_string.empty())
            break;
    }
    return count;
}

int main () {
    std::string filename = "init.txt";
    std::string path;
    std::ifstream file("init.txt");
    if (file.is_open()) {
        std::getline(file, path); // Считываем одну строку
        file.close();
    } else {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
    }
    std::ifstream source_file(path);
    printf("Total number = %d",separater(source_file));
}

