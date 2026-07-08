#include <iostream>
#include <fstream>

#ifdef _WIN32
    #include "memory_windows.h"
#else
    #include "memory_linux.h"
#endif

#include "LoadData.cpp"
#include "Maps/control.cpp"
#include "Maps/STD.cpp"
#include "Maps/chaining.cpp"
#include "Maps/linear_probing.cpp"
#include "Maps/quadratic_probing.cpp"

//cuantas veces se repite el experimento
#define EXP_repeat 20
//cuantas veces se procesan los tweets
#define EXP_count 19
//cuantos tweets más se leen cada vez
#define EXP_step 10000
//cuanto se reserva antes de cada experimento
#define EXP_reserve 25000

std::ofstream expfile;

//metodos para diferenciar entre user_id y user_screen_name
inline void get_user(long long& target, std::string& user_id, std::string& user_screen_name){
    target = stoll(user_id);
}
inline void get_user(std::string& target, std::string& user_id, std::string& user_screen_name){
    target = user_screen_name;
}

#include <chrono>
template<typename K>
void Experiment(Map<K>& map, unsigned max_tweets, size_t mem_before){
    OpenFile();

    std::string user_id,user_screen_name;
    unsigned n_tweet = 0;

    auto start = std::chrono::high_resolution_clock::now();
    //size_t mem_before = memory_usage();

    while (ReadEntry(user_id,user_screen_name)){
        if (n_tweet>=max_tweets) break;
        n_tweet++;

        //actualiza map
        K user;
        get_user(user,user_id,user_screen_name);
        if (map.contains(user))
            map[user]+=1;
        else
            map[user]=1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    size_t mem_after = memory_usage();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    expfile << n_tweet << ';' << map.type() << ';' << time  << ';' << mem_after-mem_before  << ';' << map.loadFactor() << std::endl;
}

int main(){
    OpenFile();

    expfile = std::ofstream("timesll.csv");
    expfile << "n_tweet;estructura_de_datos;tiempo_de_ejecucion(us);memory_usage(B);load_factor" << std::endl;

    //probamos control
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            NullMap<long long>* control = new NullMap<long long>(EXP_reserve);
            Experiment(*control,EXP_step*i,mem_before);
            delete control;
        }
    }
    //probamos implementacion estandar
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            stdMap<long long>* standar = new stdMap<long long>(EXP_reserve);
            Experiment(*standar,EXP_step*i,mem_before);
            delete standar;
        }
    }
    //probamos chaining
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            ChainHashMap<long long>* chain = new ChainHashMap<long long>(EXP_reserve);
            Experiment(*chain,EXP_step*i,mem_before);
            delete chain;
        }
    }
    //probamos linear probing
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            LinearProbingHashMap<long long>* line = new LinearProbingHashMap<long long>(EXP_reserve);
            Experiment(*line,EXP_step*i,mem_before);
            delete line;
        }
    }
    //probamos quadratic probing
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            QuadraticProbingHashMap<long long>* quad = new QuadraticProbingHashMap<long long>(EXP_reserve);
            Experiment(*quad,EXP_step*i,mem_before);
            delete quad;
        }
    }



    //abrimos a un archivo distinto para pruebas en string
    expfile.close();
    expfile = std::ofstream("timesstr.csv");
    expfile << "n_tweet;estructura_de_datos;tiempo_de_ejecucion(us);memory_usage(B);load_factor" << std::endl;



     //probamos control
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            NullMap<std::string>* control = new NullMap<std::string>(EXP_reserve);
            Experiment(*control,EXP_step*i,mem_before);
            delete control;
        }
    }
    //probamos implementacion estandar
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            stdMap<std::string>* standar = new stdMap<std::string>(EXP_reserve);
            Experiment(*standar,EXP_step*i,mem_before);
            delete standar;
        }
    }
    //probamos chaining
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            ChainHashMap<std::string>* chain = new ChainHashMap<std::string>(EXP_reserve);
            Experiment(*chain,EXP_step*i,mem_before);
            delete chain;
        }
    }
    //probamos linear probing
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            LinearProbingHashMap<std::string>* line = new LinearProbingHashMap<std::string>(EXP_reserve);
            Experiment(*line,EXP_step*i,mem_before);
            delete line;
        }
    }
    //probamos quadratic probing
    for (int i=0; i<EXP_repeat; i++){
        for (unsigned i=1; i<=EXP_count; i++){
            size_t mem_before = memory_usage();
            QuadraticProbingHashMap<std::string>* quad = new QuadraticProbingHashMap<std::string>(EXP_reserve);
            Experiment(*quad,EXP_step*i,mem_before);
            delete quad;
        }
    }

    expfile.close();

    return 0;
}



// to do: experimentos de creación, graficos con python o gnuplot control? dividir por 10000 paraver tiempo de uno