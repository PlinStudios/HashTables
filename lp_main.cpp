#include <iostream>
#include <fstream>

#include "LoadData.cpp"
#include "linear_probing.cpp"

std::ofstream expfile;

#include <chrono>
void Experiment(Map<long long>& map, unsigned max_tweets){
    OpenFile();

    std::string user_id,user_screen_name;
    unsigned n_tweet = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (ReadEntry(user_id,user_screen_name)){
        if (n_tweet>=max_tweets) break;
        n_tweet++;

        //actualiza map
        long long uid = stoll(user_id);
        if (map.contains(uid))
            map[uid]+=1;
        else
            map[uid]=1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    expfile << n_tweet << ';' << map.type() << ';' << time  << ';'<<"X;" << map.loadFactor() << std::endl;
}

int main(){
    expfile = std::ofstream("times.csv");
    expfile << "n_tweet;estructura_de_datos;tiempo_de_ejecucion(us);memory_usage(B);load_factor" << std::endl;

    for (int i=0; i<2; i++){
        for (unsigned i=1; i<=18; i++){
            LinearProbingHashMap<long long>* lp = new LinearProbingHashMap<long long>(25000);
            Experiment(*lp,10000*i);
            std::cout << (*lp)[944465451727314944] << std::endl;
            delete lp;
        }
    }

    return 0;
}