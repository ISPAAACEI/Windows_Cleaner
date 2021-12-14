#include <iostream> 
#include <string>
#include <fstream>
#include <stdio.h>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
using namespace std;
namespace fs = experimental::filesystem;

int main()
{
    setlocale(LC_ALL, "Russian"); // позволяет сканировать и выводить файлы и папки с русскими названиями
    bool bl = true; // задаем булевую переменную
    int n = 1 , ln = -1;
    string dirlist[4];
    dirlist[0] = "C:/Users/USER/Downloads";
    dirlist[1] = "C:/Users/USER/Documents";
    dirlist[2] = "C:/Users/USER/Videos";
    dirlist[3] = "C:/Users/USER/Pictures";
    string path = "C:/Users/USER/Desktop"; // задаем директорию, по которой будем искать папки и файлы
    while (n == 1) {
        for (const auto& entry : fs::directory_iterator(path)) { // for, который сканирует все файлы в директории рабочего стола
            if ((entry.path() == ("C:/Users/USER/Desktop/desktop.ini")) or (entry.path() == ("C:/Users/USER/Documents/desktop.ini")) or (entry.path() == ("C:/Users/USER/Downloads/desktop.ini")) or (entry.path() == ("C:/Users/USER/Videos/desktop.ini"))) { // проверяет файл если он является необходимым
                bl = false; // если он необходим, то отправляем в булевую переменную ложь
            }
            else bl = true; // если же нет, то отправляем в булевую переменную правду
            if (fs::is_directory(entry.path())) { // если это папка, то
                error_code errorCode; // задаем переменную для проверки ошибки
                if (!fs::remove_all(entry.path(), errorCode)) { // удаляет дерикторию и все файлы в ней
                    cout << errorCode.message() << endl; // вывод сообщения ошибки
                }
            }
            else if (bl) { // если же это одиночный файл и он не необходим, то
                error_code errorCode1; // задаем еще одну переменную для проверки ошибки
                if (!fs::remove(entry.path(), errorCode1)) { // удаляет только файл
                    cout << errorCode1.message() << endl; // вывод сообщения ошибки 
                }
            }
            //cout << entry.path() << endl; // вывод всех удаленных файлов
        }
        ln = ln + 1;
        if (ln == 4) {
            n = 0; 
        }
        path = dirlist[ln];
    }
}
