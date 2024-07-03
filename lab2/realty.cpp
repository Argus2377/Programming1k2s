/*****************************************************************/
/* Filename: realty.cpp                                          */
/* Abstract: Laboratory work #2, task 22                         */
/* Description: Database of apartments in a real estate Agency   */
/* Create Date: 15.04.2020                                       */
/* Author: Tikhonov Viktor                                       */
/* Notes / Platform / Copyright UNIX/Linux, FreeWare             */
/* Version: 1.2.1                                                */
/*****************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "logo.h"

using namespace std;


struct realty{ //Структура, отвечающая за хранение информации о квартирах
    char* adress = new char[256];//Адрес с возможностью записи пробелов
    double area; //Площадь
    char side[16];//Сторона света
    double price;//Цена
    int level;//Этаж
    int room;//Количество комнат
};

void printInformation(const realty data[], int quantity, string nameOfFile);//Функция, записывабщая информацию в файл


int main(int argc, char** argv){
    
    logo();//Вывод логотипа
    
    string str, nameOfFile{argv[3]}, help{"-h"}, create{"-c"}, read{"-r"};
    
    if (argc==1){//Защита
        cout<<"Error! The second argument is invalid or missing. Please choose one of the following options:\n";
        cout<<"Help: ./realty -h\n";
        cout<<"Create: ./realty -c\n";
        cout<<"Read: ./realty -r\n";
    }
    else{
        int q=0;//Создаём переменную для использования  конструкции switch - case
        if (argv[1]==help){
            q=1;
        }
        if (argv[1]==create){
            q=2;
        }
        if (argv[1]==read){
            q=3;
        }
        switch (q){
            case 1:
                {//Вывод на экран информации об использовании программы
                cout<<"HELP:\n";
                cout<<"How to use this program:\n";
                cout<<"To create a new object in file, enter «./realty -c N file.txt» without quotes\n";
                cout<<"To read the file data, enter «./realty -r N file.txt» without quotes\n";
                cout<<"Where N is the number of objects, and name.txt is the file name\n";
                }
                break;
            case 2:   
                {//Создание объектов
                int amount=stoi(argv[2]);
                realty flat[amount]={};
                for (int q=0; q<amount; q++){
                    cout<<"ADRESS: ";
                    cin.getline(flat[q].adress, 256);
                    cout<<"LEVEL: ";
                    cin>>flat[q].level;
                    cout<<"SIDE: ";
                    cin>>flat[q].side;
                    cout<<"ROOM: ";
                    cin>>flat[q].room;
                    cout<<"AREA: ";
                    cin>>flat[q].area;
                    cout<<"PRICE: ";
                    cin>>flat[q].price;	
                    cin.get();
                    cout<<endl;
                }	
                printInformation(flat, amount, nameOfFile);
                }
                break;
            case 3:
                {//Просмотр объектов
                ifstream databank;
                databank.open(argv[3]);
                    if (!databank){//Проверка на открытие файла
                        cout<<"Error! Cannot open file\n";
                        }
                    else{
                        if (databank.peek()==EOF){//Проверка на содержание
                        cout<<"Empty file\n";
                        }
                        else{
                            for(int i=0;i<(stoi(argv[2])+1)*2+1;i++){
                                getline(databank,str);
                                cout<<str<<endl;
                            }
                            databank.close();
                        }
                    }
                }
                break;
            default:
            {
            cout<<"Error! The second argument is invalid or missing. Please choose one of the following options:\n";
            cout<<"Help: ./realty -h\n";
            cout<<"Create: ./realty -c\n";
            cout<<"Read: ./realty -r\n";    
            }
        }
    }
    return 0;
}

void printInformation(const realty data[], int quantity, string nameOfFile){//Функция, записывабщая информацию в файл
    ofstream database; //ОбЪект класса ofstream
    database.open(nameOfFile); //Связываем объект с файлом
    database<<"______________________________________________________________________________\n";
    database<<"|    №"<<"|              ADRESS"<<"|LEVEL"<<"| SIDE"<<"|ROOM"<<"|AREA(sq.m.)"<<"|PRICE($ per 1 sq.m.)|\n";
	for (int i = 0; i<quantity; i++){
	    database<<"______________________________________________________________________________\n";
	    database<<"|"<<setw(5)<<(i+1)<<"|"<<setw(20)<<data[i].adress<<"|"<<setw(5)<<data[i].level<<"|"<<setw(5)<<data[i].side<<"|"<<setw(4)<<data[i].room<<"|"<<setw(11)<<data[i].area<<"|"<<setw(19)<<data[i].price<<"$|"<<endl;
	}
	database<<"______________________________________________________________________________\n";//Запись в файл
	database.close();//Завершаем работу с файлом
}