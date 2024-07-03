/*****************************************************************/
/* Filename: realty.cpp                                          */
/* Abstract: Laboratory work #4, task 22                         */
/* Description: Database of apartments in a real estate Agency   */
/* Create Date: 29.05.2020                                       */
/* Author: Tikhonov Viktor                                       */
/* Notes / Platform / Copyright UNIX/Linux, FreeWare             */
/* Version: 2.0                                                  */
/*****************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "logo.h"
#include "colors.h"

using namespace std;

class TCharArray{//класс для хранения элементов типа char
    protected:
    char* arr;
    int size;
    
    public:
    TCharArray(){//конструктор без параметров
        cout<<red<<"Index invalid or missing\n"<<reset;
        exit(1);
    }
    
    TCharArray(int size1){//конструктор с одним параметром
        arr=new char[size1];
        for(int q=0; q<size; q++){
            arr[q]=' '; 
        return;
        }
    }

    ~TCharArray(){//деструктор
        delete []arr;
        return;
    }

    char& operator [](int n){//перегрузка операции []
    if((n<0)||(n>=size)){
        cout<<red<<"\nInvalid index!"<<reset; 
        exit(1);
    }
    return arr[n]; 
    }
    
    void enter(){//метод ввода
        cin>>arr;
    }
    
    void at(int n){//метод at для доступа к элементам массива
        if((n<0)||(n>=size)){
        cout<<red<<"\nInvalid index!"<<reset; 
        exit(1);
        }
        cout<<arr[n];
    }
};

class TString : public TCharArray{//дочерний класс для хранения строк
    public:
    ~TString(){//деструктор
        delete [] arr;
    }
    
    size_t TStrlen(const char* str){//определение длины строки
        size_t i=0U;
        while(str[i]!='\n'){
            i++;
        }
        return i;
    }
    
    char* TStrcpy(char* dest, const char* str){//копирование строки в строку
        size_t i=0;
        while (str[i]!=0){
            dest[i]=str[i]; 
            i++;
        }
    return dest;
    }
    
    char* TStrcat(char* str1, const char* str2){//объединение строк
        size_t i=0U, j=0U;
        while(str1[i++]!='\n');
        while(str2[j]!='\n'){
            str1[i]=str2[j];
            i++;
            j++;
        }
        str1[i]='\n';
        return str1;
    }
    
    int TStrcmp(const char* str1, const char* str2){//сравнение строк
        int res=0;
        size_t len1=TStrlen(str1), len2=TStrlen(str2), i;
        size_t len=(len1>len2? len1 : len2);
        for(i=0U; i<len; i++){
            res=str1[i]-str2[i];
            if(res!=0){
                break;
            }
        }
        return res;
    }

    void enterStr(char* str){//метод ввода строки
        for(int q=0; str[q]!='\n'; q++){
		    size=q;
        }
        arr=new char[size+1];//создаём новый массив размером size+1
        for (int q=0; q<size; q++){
            arr[q]=str[q];//заполняем новый массив
        }
        arr[size]='\n';//делаем из символьного массива строку
		return;
    }
    
    TString& operator +(TString str){//перегрузка оператора +
        TString sum;
        if(TStrlen(arr)+TStrlen(str.arr)<size){ 
            TStrcpy(sum.arr, arr);// копируем содержимое первой строки
            TStrcat(sum.arr, str.arr);// добавляем содержимое второй строки
        } 
        else{ 
            cout<<red<<"\nError! Overflow!"<<reset; 
            exit(1); 
        } 
        return sum;// возвращаем результат
    } 
    
    bool operator ==(TString str){//перегрузка оператора ==
        return(TStrcmp(arr, str.arr)==0)? true : false; 
    }
    
     bool operator !=(TString str){//перегрузка оператора !=
        return(TStrcmp(arr, str.arr)!=0)? true : false; 
    }
    
     bool operator >(TString str){//перегрузка оператора >
        return(TStrcmp(arr, str.arr)>0)? true : false; 
    }
    
     bool operator <(TString str){//перегрузка оператора <
        return(TStrcmp(arr, str.arr)<0)? true : false; 
    }
};

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
        cout<<red<<"Error! The second argument is invalid or missing. Please choose one of the following options:\n";
        cout<<cyan<<"Help: ./realty -h\n";
        cout<<"Create: ./realty -c\n";
        cout<<"Read: ./realty -r\n"<<reset;
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
                cout<<magenta<<"HELP:\n";
                cout<<"How to use this program:\n";
                cout<<"To create a new object in file, enter «./realty -c N file.txt» without quotes\n";
                cout<<"To read the file data, enter «./realty -r N file.txt» without quotes\n";
                cout<<"Where N is the number of objects, and name.txt is the file name\n"<<reset;
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
                        cout<<red<<"Error! Cannot open file\n"<<reset;
                        }
                    else{
                        if (databank.peek()==EOF){//Проверка на содержание
                        cout<<cyan<<"Empty file\n"<<reset;
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
            cout<<red<<"Error! The second argument is invalid or missing. Please choose one of the following options:\n";
            cout<<cyan<<"Help: ./realty -h\n";
            cout<<"Create: ./realty -c\n";
            cout<<"Read: ./realty -r\n"<<reset;    
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