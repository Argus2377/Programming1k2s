#ifndef _mylib_H_
#define _mylib_H_
#include <iostream>

const std::string reset("\x1B[0m");

const std::string black("\x1B[0;30m");
const std::string red("\x1B[0;31m");
const std::string green("\x1B[0;32m");
const std::string brown("\x1B[0;33m");
const std::string blue("\x1B[0;34m");
const std::string magenta("\x1B[0;35m");
const std::string cyan("\x1B[0;36m");
const std::string white("\x1B[0;37m");

void logo(){
    char logo[]=
    "............................................\n" 
    ".                         *                .\n"
    ".                         **               .\n"
    ".                         ****             .\n"
    ".                         ******           .\n"
    ".                         ********         .\n"
    ".                        **********        .\n"
    ".                        ************      .\n"
    ".                       ***************    .\n"
    ".                      *****************   .\n"
    ".                     *******************  .\n"
    ".           **       ********************  .\n"
    ".     ******         *******************   .\n"
    ".    *****          ******************     .\n"
    ".   ** ***         *****************       .\n"
    ".   *  ****       ***************          .\n"
    ".     ******     *************             .\n"
    ".   *********   ***********                .\n"
    ".  *********** *********                   .\n"
    ".  *****************                       .\n"
    ".  ***************                         .\n"
    ".  *************                           .\n"
    ".  ************                            .\n"
    ".   **********                             .\n"
    ".    *********                             .\n"
    ".     *******                              .\n"
    ".    ** ****                               .\n"
    ".       ****                  A            .\n"
    ".      ******                 R            .\n"
    ".     ********                G            .\n"
    ".    **********               U            .\n"
    ".      *    *                 S            .\n"
    ".       *    *                             .\n"
    ".        *    *                            .\n"
    ".        *    *                            .\n"
    ".       *    *                             .\n"
    ".      *     *                             .\n"
    ".      *      *                            .\n"
    ".      **     **                           .\n"
    ".     *##*   *##*                          .\n"
    ".     *##*   *##*                          .\n"
    ".      **     **                           .\n"
    "............................................\n";
    std::cout<<std::endl<<red<<logo<<reset<<std::endl;
}

template <typename T>
T enter(T& value){
    while(!(std::cin>>value)||(std::cin.peek()!='\n')){
        std::cin.clear();
        while(std::cin.get()!='\n');
        std::cout<<red<<"Error!"<<reset<<std::endl;
    }
    return value;
}

#endif