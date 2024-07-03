/*****************************************************************/
/* Filename: IT.cpp                                              */
/* Abstract: Laboratory work #5, task 4                          */
/* Description: Accounting system for IT company employeesy      */
/* Create Date: 16.06.2020                                       */
/* Author: Tikhonov Viktor                                       */
/* Notes / Platform / Copyright UNIX/Linux, FreeWare             */
/* Version: 1.3.0.0                                              */
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
    
    TString operator +(TString str){//перегрузка оператора +
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


class Worker{//Базовый класс "Категории работников"
    public:
    string name;//ФИО
    virtual void enterPerson(){
        cout<<"Enter the Worker:\n";
        getline(cin, name);
        cout<<endl;
    }
    virtual void showPerson(){
        cout<<green<<"are workers"<<reset<<endl;
    }

};

class Student : public Worker{//Производный класс "Стажёр(студент)"
    public:
    void enterPerson() override{
        cout<<"Enter the Student:\n";
        getline(cin, name);
        cout<<endl;
    }
    void showPerson() override{
        cout<<green<<"are students"<<reset<<endl;
    }    
};

class Programmer : public Worker{//Производный класс "Программист
    void enterPerson() override{
        cout<<"Enter the Programmer:\n";
        getline(cin, name);;
        cout<<endl;
    }
    void showPerson() override{ 
        cout<<green<<"are programmers"<<reset<<endl;
    }
};

class Tester : public Worker{//Производный класс "Тестировщик ПО"
    public:
    void enterPerson() override{
        cout<<"Enter the Tester:\n";
        getline(cin, name);
        cout<<endl;
    }
    void showPerson() override{
        cout<<green<<"are testers"<<reset<<endl;
    }
};

class Director : public Worker{//Производный класс "Руководитель отдела"
    public:
    void enterPerson() override{
        cout<<"Enter the Director:\n";
        getline(cin, name);
        cout<<endl;
    }
    void showPerson() override{
        cout<<green<<"are directors"<<reset<<endl;
    }
};

int main(){
    logo();
    cout<<"Select the recording mode"<<endl;
    cout<<green<<"1 - student\n2 - programmer\n3 - tester\n4 - director\n"<<reset<<endl;
    unsigned int mode;
    while (!(cin>>mode)||(cin.peek()!='\n')||(sizeof(mode)!=sizeof(int))||mode<=0||mode>4){
        cin.clear();
        while (cin.get()!='\n');
        cout<<red<<"Error!"<<endl<<cyan<<"Select and enter one of the following recording modes:"<<endl<<green<<"1 - student\n2 - programmer\n3 - tester\n4 - director\n"<<reset;
    }

    cout<<"Enter the number of entries"<<endl;
    unsigned int N;
    while (!(cin>>N)||(cin.peek()!='\n')||(sizeof(N)!=sizeof(int))||N<=0){
        cin.clear();
        while (cin.get()!='\n');
        cout<<red<<"Error!"<<endl<<cyan<<"Enter a positive integer!"<<endl<<reset;
    }
    Worker* person[N];
    ofstream database;
    switch(mode){
        case 1:
            getchar();
            for(int q=0; q<N; q++){
                person[q]=new Student;
                person[q]->enterPerson();
            }
            
            database.open("Students.txt");
            database<<"__________________________\n";
            database<<"|    №"<<"|              NAME|\n";
    	    for (int i = 0; i<N; i++){
    	        database<<"__________________________\n";
    	        database<<"|"<<setw(5)<<(i+1)<<"|"<<setw(18)<<person[i]->name<<"|"<<endl;
    	    }
    	    database<<"__________________________\n";
    	    database.close();
            person[N-1]->showPerson();
        break;
        case 2:
            getchar();
            for(int q=0; q<N; q++){
                person[q]=new Programmer;
                person[q]->enterPerson();
            }
            
            database.open("Programmers.txt");
            database<<"__________________________\n";
            database<<"|    №"<<"|              NAME|\n";
    	    for (int i = 0; i<N; i++){
    	        database<<"__________________________\n";
    	        database<<"|"<<setw(5)<<(i+1)<<"|"<<setw(18)<<person[i]->name<<"|"<<endl;
    	    }
    	    database<<"__________________________\n";
    	    database.close();
            person[N-1]->showPerson();
        break;
        case 3:
            getchar();
            for(int q=0; q<N; q++){
                person[q]=new Tester;
                person[q]->enterPerson();
            }
            
            database.open("Testers.txt");
            database<<"__________________________\n";
            database<<"|    №"<<"|              NAME|\n";
    	    for (int i = 0; i<N; i++){
    	        database<<"__________________________\n";
    	        database<<"|"<<setw(5)<<(i+1)<<"|"<<setw(18)<<person[i]->name<<"|"<<endl;
    	    }
    	    database<<"__________________________\n";
    	    database.close();
            person[N-1]->showPerson();
        break;
        case 4:
            getchar();
            for(int q=0; q<N; q++){
                person[q]=new Director;
                person[q]->enterPerson();
            }
            
            database.open("Directors.txt");
            database<<"__________________________\n";
            database<<"|    №"<<"|              NAME|\n";
    	    for (int i = 0; i<N; i++){
    	        database<<"__________________________\n";
    	        database<<"|"<<setw(5)<<(i+1)<<"|"<<setw(18)<<person[i]->name<<"|"<<endl;
    	    }
    	    database<<"__________________________\n";
    	    database.close();
            person[N-1]->showPerson();
        break;
        default:
            cout<<red<<"ERROR!"<<reset;
            exit(1);
        break;
    }
    return 0;
}

