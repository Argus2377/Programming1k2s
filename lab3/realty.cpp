/*************************************************************************/
/* Filename: realty.cpp                                                  */
/* Abstract: Laboratory work #3, task 22                                 */
/* Description: Database of apartments in a real estate Agency(binary)   */
/* Create Date: 21.05.2020                                               */
/* Author: Tikhonov Viktor                                               */
/* Notes / Platform / Copyright UNIX/Linux, FreeWare                     */
/* Version: 1.0.0.0                                                      */
/*************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "logo.h"
#include "colors.h"

using namespace std;


class realty{ //Структура, отвечающая за хранение информации о квартирах
    private:
    char adress[256];//Адрес
    double area; //Площадь
    char side[16];//Сторона света
    double price;//Цена
    int level;//Этаж
    int room;//Количество комнат
    
    public:
    void enter(){//меод ввода
        cout<<"ADRESS: ";
        cin.getline(adress, 256);
        cout<<"LEVEL: ";
        cin>>level;
        cout<<"SIDE: ";
        cin>>side;
        cout<<"ROOM: ";
        cin>>room;
        cout<<"AREA: ";
        cin>>area;
        cout<<"PRICE: ";
        cin>>price;	
        cin.get();
        cout<<endl;
    }
    
    void show(int q){//метод вывода
	cout<<"|"<<setw(5)<<q<<"|"<<setw(20)<<adress<<"|"<<setw(5)<<level<<"|"<<setw(5)<<side<<"|"<<setw(4)<<room<<"|"<<setw(11)<<area<<"|"<<setw(19)<<price<<"$|"<<endl;
	cout<<"______________________________________________________________________________\n";//Запись в файл
    }
};

void head(){
    cout<<"______________________________________________________________________________\n";
    cout<<"|    №"<<"|              ADRESS"<<"|LEVEL"<<"| SIDE"<<"|ROOM"<<"|AREA(sq.m.)"<<"|PRICE($ per 1 sq.m.)|\n";
	cout<<"______________________________________________________________________________\n";
}

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
        if ((argv[1]==help)&&(argc==2)){
            q=1;
        }
        if ((argv[1]==create)&&(argc==4)){
            q=2;
        }
        if ((argv[1]==read)&&(argc==4)){
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
                FILE* writing;
			    writing=fopen(argv[3], "ab");//открытие файла с возможностью записи в бинарном виде
			    if (writing==NULL){ //проверка на создание или открытие файла
				    cout<<red<<"Error! Cannot open or create file\n"<<reset;
			    }
			    else {
				    int quantity=1;//переменная для перемещения курсора
				    fwrite(&amount, sizeof(int), 1, writing);//запись числа экземпляров класса
				    fseek(writing, sizeof(int), SEEK_SET);//передвижение курсора в начало
				    for (int q=0; q<amount; q++) {
					    flat[q].enter();//ввод данных
					    fwrite(&flat[q], sizeof(realty), 1, writing);//запись в файл
					    fseek(writing, quantity*sizeof(realty), SEEK_CUR);
					    quantity++;
				    }
			    }
			    fclose(writing);//закрытие файла
                }
                break;
            case 3:
                {//Просмотр объектов
                int amount=stoi(argv[2]);
                realty flat[amount]={};
		        FILE* reading;
			    reading=fopen(argv[3], "rb");//открытие файла в режиме чтение
			    if (reading==NULL){//проверка открытия файла
			        cout<<red<<"Error! Cannot read  file.\x1B[0m Could the name be entered incorrectly?\n"<<reset;
			    }
			    else{
				    int quantity=1;
					head();
					fseek(reading, sizeof(int), SEEK_SET);
					for (int q=0; q<amount; q++){
						fread(&flat[q], sizeof(realty), 1, reading);//чтение экземпляра класса
						fseek(reading, quantity*sizeof(realty), SEEK_CUR);
						flat[q].show(q+1);//вывод
						quantity++; 
					}
					fclose(reading); //закрываем файл
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