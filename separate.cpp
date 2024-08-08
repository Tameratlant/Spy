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
/*
inline void copy_message(std::ofstream& target_file, std::ofstream& source_file) {
    std::string line;
    std::vector <std::string> lines;
    while (std::getline(source_file, line)) {
        lines.push_back(line);
        if (line.find("\"id\": ") != std::string::npos) {
            break; // Прерываем цикл, если встретили строку с "id: "
            if (lines.size() > 1) {
                lines.pop_back();
            }
        }
        targetFile << line << std::endl;
    }
} 

int main() {

    std::string sourceFile = "source.txt";  // Замените на ваше имя исходного файла
    std::string targetFile = "target.txt"; // Замените на ваше имя целевого файла
    std::ifstream inFile(sourceFile);
    std::ofstream outFile(targetFile);
    std::string line;
    std::vector<std::string> lines;
    while (getline(inFile, line)) {
        if (line.find("id: ") != string::npos) {
            // Закрываем и открываем целевой файл для перезаписи
            outFile.close();
            outFile.open(targetFile, ios::out | ios::trunc);
            // Читаем все строки, кроме последней, в вектор
            lines.clear();
            while (getline(inFile, line)) {
                lines.push_back(line);
            }
            // Удаляем последний символ из предпоследнего элемента
            if (lines.size() > 1) {
                lines[lines.size() - 2].pop_back();
            }
            // Записываем содержимое вектора в файл
            for (const string& l : lines) {
                outFile << l << endl;
            }
            break;
        } else {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();
    return 0;
}
*/
std::string copy_massages(std::ifstream& big_file,std::ofstream& small, int number) {               //Копирует из большого в маленькие по MAX_SIZE сообщений 
    std::string line;
    std::vector<std::string> lines;
    int count  = 0;
    /*
    std::string num = std::to_string(number);
    std::ofstream small (OUTPUT_NAME+num);
    std::cout<<"Created file "<< OUTPUT_NAME+num <<'\n';
    int count = 0;
    //std::cout << "Header copied for file № " << number << '\n';
    head_copy(small, big_file, number);
    */
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

int separater(std::ifstream& big_file) {                //делит на файлы по 3000 сообщений и выводит число созданных файлов
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

/*
std::string line;
    int count = 0;
    while(count < MAX_SIZE) {
        if (std::getline(big_file, line)) {
            if (line.back() == ',' & line[line.length() - 2] == '}') {
                count++;
                small_file
            }
            small_file << line << std::endl;
        } else {
            break;  // Если достигнут конец файла раньше, чем скопировано 10 строк
        }
    }
*/

int main () {
    /*
    std::string s= "String№";
    s = s + std::to_string(123);
    std::cout << s << '\n';
    */
   /*
   int status = mkdir("JSON_data", 0777);
    if (status == 0) {
        std::cout << "Папка создана успешно!" << std::endl;
        return true;
    } else {
        std::cerr << "Ошибка при создании папки!" << std::endl;
        return false;
    }
    */
   std::ifstream big(BIG_FILE);
   //std::ofstream small(OUTPUT_NAME);
   //copy_massages(big, small, 0);
   printf("Total number = %d",separater(big));
}

