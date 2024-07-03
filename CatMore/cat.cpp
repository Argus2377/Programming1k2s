
#include <iostream>
#include <fstream>
#include <string>
#include "colors.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc==1){//Защита
        cout<<red<<"Enter the file name as the second argument\n"<<reset;
        return 0;
    }
    
    
    string nameOfFile{argv[1]}, str;
    
    if (argc==2){
        ifstream conclusion;
        conclusion.open(argv[1]);
        if (!conclusion){//Проверка на открытие файла
            cout<<red<<"Error! Cannot open file\n"<<reset;
            }
        else{
            if (conclusion.peek()==EOF){//Проверка на содержание
                cout<<cyan<<"Empty file\n"<<reset;
            }
            else{
                while(conclusion.peek()!=EOF){
                    getline(conclusion,str);
                    cout<<str<<endl;
                }
                conclusion.close();
            }
        }
    }
    if (argc>2){
        ifstream conclusion;
        for(int i=1; i<argc; i++){
            conclusion.open(argv[i]);
            if (!conclusion){//Проверка на открытие файла
                cout<<red<<"Error! Cannot open file\n"<<reset;
            }
            else{
                cout<<green<<"File "<<i<<":\n"<<reset;
                cout<<"\n";
                if (conclusion.peek()==EOF){//Проверка на содержание
                    cout<<cyan<<"Empty file\n"<<reset;
                    cout<<endl;
                }
                else{
                    while(conclusion.peek()!=EOF){
                        getline(conclusion,str);
                        cout<<str<<endl;
                    }
                    conclusion.close();
                    cout<<endl;
                }
            }
        }
    }
    return 0;
}
