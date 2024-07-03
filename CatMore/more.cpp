#include <iostream>
#include <fstream>
#include <string>
#include "colors.h"

using namespace std;

int main(int argc, char** argv)
{
    const int size=20;
    if (argc==1){//Защита
        cout<<red<<"Enter the file name as the second argument\n"<<reset;
        return 0;
    }
    if (argc>2){//Защита
        cout<<"Error! Too many arguments\n";
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
                int counter=0;
                while(conclusion.peek()!=EOF){
                    getline(conclusion,str);
                    counter++;
                }
                conclusion.close();
                conclusion.open(argv[1]);
                
                int lin=counter/size;
                int lin1=counter%size;
                
                while (lin!=0){
                    for(int line=0; line<size; line++){
                        getline(conclusion,str);
                        cout<<str<<endl;
                    }
                    getchar();
                    system("clear");
                    lin--;
                }
                for(int line=0; line<lin1; line++){
                    getline(conclusion,str);
                    cout<<str<<endl;
                }
            conclusion.close();
            }
        }
    }
    
    return 0;
}