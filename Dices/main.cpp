#include <iostream>
#include <cstdlib>
#include <ctime>
#include "numbers.h"

using namespace std;

int main(){
    int dice1, dice2;
    double bet;
    bool start, parity;
    BEGIN:
    cout<<"Enter 1 to start"<<endl<<"Enter 0 to finish"<<endl;
    while ((!(cin >> start) || (cin.peek() != '\n')))
          {
             cin.clear();
             while (cin.get() != '\n');
             cout << "Error!" << endl;
             cout << "Enter again" << endl;
          }
    
    if (start==0){
        goto END;
    }
    if (start==1){
        cout<<"Enter the bet amount"<<endl;
        while ((!(cin >> bet) || (cin.peek() != '\n')))
          {
             cin.clear();
             while (cin.get() != '\n');
             cout << "Error!" << endl;
             cout << "Enter again" << endl;
          }
        cout<<"You bet "<<bet<<"$"<<endl;
        cout<<"Enter 0 to bet on even numbers"<<endl<<"Enter 1 to bet on odd numbers"<<endl;
        while ((!(cin >> parity) || (cin.peek() != '\n')))
         {
             cin.clear();
             while (cin.get() != '\n');
             cout << "Error!" << endl;
             cout << "Enter again" << endl;
         }
        srand(time(0));
        dice1=1+(rand()%6);
        dice2=1+(rand()%6);
        cout<<"dice1: "<< dice1<<endl;
        switch (dice1){
            case 1: one(); break;
            case 2: two(); break;
            case 3: three(); break;
            case 4: four(); break;
            case 5: five(); break;
            case 6: six(); break;
        }
        cout<<"dice2: "<< dice2<<endl;
        switch (dice2){
            case 1: one(); break;
            case 2: two(); break;
            case 3: three(); break;
            case 4: four(); break;
            case 5: five(); break;
            case 6: six(); break;
        }
        if((parity==0) && (((dice1+dice2)%2)==0)){
            cout<<endl;
            cout<<"O.O You won "<<bet<<"$ O.O";
            cout<<endl<<endl;
        }
        if((parity==1) && (((dice1+dice2)%2)!=0)){
            cout<<endl;
            cout<<"O.O You won "<<bet<<"$ O.O";
            cout<<endl<<endl;
        }
        if((parity==0) && (((dice1+dice2)%2)!=0)){
            cout<<endl;
            cout<<"-_- You lost "<<bet<<"$ -_-";
            cout<<endl<<endl;
        }
        if((parity==1) && (((dice1+dice2)%2)==0)){
            cout<<endl;
            cout<<"-_- You lost "<<bet<<"$ -_-";
            cout<<endl<<endl;
        }
        goto BEGIN;
    }
    END:
    return 0;
}
