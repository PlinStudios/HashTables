#include <iostream>
#include <fstream>

#define P_ID 5 //index del parametro user_id
#define P_SN 6 //index del parametro user_screen_name

std::ifstream file;

void OpenFile(){
    //abre archivo
    file = std::ifstream("auspol2019.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    //salta linea que describe parametros
    std::string line;
    std::getline(file, line);
}

bool ReadEntry(std::string &user_id, std::string &user_screen_name){
    //lee archivo
    char c;
    int paramcount=0;
    user_id="";
    user_screen_name="";
    bool in_quotes=false;
    while (file.get(c))
    {
        if (in_quotes){
            if (c=='"') {in_quotes=false; continue;}
        }
        else{
            if (c=='"') {in_quotes=true; continue;}
            else if (c==',') {paramcount++; continue;}
            else if (c=='\n'){
                return true;
            }
        }

        if (paramcount==P_ID) user_id+=c;
        else if (paramcount==P_SN) user_screen_name+=c;
    }

    return false;
}