#include <iostream>

#include "LoadData.cpp"
#include "chaining.cpp"

int main(){
    OpenFile();

    std::string user_id,user_screen_name;
    std::string Puser_id,Puser_screen_name;

    ChainHashMap chain = ChainHashMap<long long>(13);

    while (ReadEntry(user_id,user_screen_name)){
        long long uid = stoll(user_id);
        
        if (chain.contains(uid))
            chain[uid]+=1;
        else
            chain[uid]=1;
    }

    std::cout << chain[944465451727314944];
}