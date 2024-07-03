/*****************************************************************/
/* Filename: environ.cpp                                         */
/* Abstract: Laboratory work #1, task 17                         */
/* Description: Database of apartments in a real estate Agency   */
/* Create Date: 17.04.2020                                       */
/* Author: Tikhonov Viktor                                       */
/* Notes / Platform / Copyright UNIX/Linux, FreeWare             */
/* Version: 1.0.1                                                */
/*****************************************************************/
#include <iostream>
#include <cstdlib>
#include <unistd.h>//в этом заголовочном файле определён массив переменных окружения
#include <fstream>
#include <string>
#include "logo.h"
#include "colors.h"

using namespace std;

void printInformation(string nameOfFile);

int main(int argc, char** argv) {
    logo();
    
    if (argc==1){//Защита
        cout<<red<<"Error! The second argument is invalid or missing. Please choose one of the following options:\n"<<reset;
        cout<<"Help: ./environ -h\n";
        return 0;
    }
    
    if (argc>2){//Защита
        cout<<red<<"Error! Too many arguments. Please choose one of the following options:\n"<<reset;
        cout<<"Help: ./environ -h\n";
        return 0;
    }
    
    string nameOfFile{argv[1]}, help{"-h"};
    
    if (argc==2){
        
        if (argv[1]==help){//Вывод на экран информации об использовании программы
            cout<<magenta<<"HELP:\n";
            cout<<"How to use this program:\n";
            cout<<"To output environment variables to a file, enter «./environ file.txt» without quotes\n";
            cout<<"Where file.txt is the file name where environment variables will be written\n"<<reset;
        }
        else{
            ofstream env;
            env.open(argv[1]);
            if (!env){//Проверка на открытие файла
                cout<<"Error! Cannot open file\n";
            }
            else{
                printInformation(nameOfFile);
            }
        }
    }
    
    return 0;
}

void printInformation(string nameOfFile){//Функция, записывабщая информацию в файл
    ofstream env; //ОбЪект класса ofstream
    env.open(nameOfFile); //Связываем объект с файлом
    int q=0;
    while (__environ[q] != NULL) {//Прогон массива переменных окружения
        env<<__environ[q]<<endl;
        q++;
    }
	env.close();//Завершаем работу с файлом
}
