// codigo hecho con gemini
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <string>

// Estructura para agrupar por cantidad de tweets y tipo de dato
struct ExperimentoKey {
    int n_tweet;
    std::string estructura;

    // Operador necesario para usar la estructura como clave en un std::map
    bool operator<(const ExperimentoKey& other) const {
        if (n_tweet != other.n_tweet)
            return n_tweet < other.n_tweet;
        return estructura < other.estructura;
    }
};

// Estructura para almacenar las métricas crudas de cada línea
struct Metricas {
    double tiempo;
    double memoria;
};

int main() {
    // ==========================================
    // PARTE 1: PROCESAR TIMESHLL.CSV
    // ==========================================
    std::ifstream archivo_entrada("results/timesll.csv");
    if (!archivo_entrada.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada: results/timesll.csv" << std::endl;
        return 1;
    }

    std::map<ExperimentoKey, std::vector<Metricas>> datos;
    std::string linea;

    std::getline(archivo_entrada, linea); // Descartar cabecera

    while (std::getline(archivo_entrada, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string token;
        
        int n_tweet;
        std::string estructura;
        double tiempo;
        double memoria;

        std::getline(ss, token, ';'); n_tweet = std::stoi(token);
        std::getline(ss, estructura, ';');
        std::getline(ss, token, ';'); tiempo = std::stod(token);
        std::getline(ss, token, ';'); memoria = std::stod(token);

        ExperimentoKey key = {n_tweet, estructura};
        datos[key].push_back({tiempo, memoria});
    }
    archivo_entrada.close();

    std::ofstream salida_tiempo("results/tiempos_estadisticos.csv");
    std::ofstream salida_memoria("results/memoria_estadistica.csv");

    salida_tiempo << "n_tweet;estructura;promedio_tiempo;desviacion_tiempo\n";
    salida_memoria << "n_tweet;estructura;promedio_memoria;desviacion_memoria\n";

    for (const auto& [key, lista_metricas] : datos) {
        size_t N = lista_metricas.size();

        double suma_tiempo = 0.0;
        double suma_memoria = 0.0;
        for (const auto& m : lista_metricas) {
            suma_tiempo += m.tiempo;
            suma_memoria += m.memoria;
        }
        double promedio_tiempo = suma_tiempo / N;
        double promedio_memoria = suma_memoria / N;

        double suma_var_tiempo = 0.0;
        double suma_var_memoria = 0.0;
        for (const auto& m : lista_metricas) {
            suma_var_tiempo += std::pow(m.tiempo - promedio_tiempo, 2);
            suma_var_memoria += std::pow(m.memoria - promedio_memoria, 2);
        }
        
        double desviacion_tiempo = (N > 1) ? std::sqrt(suma_var_tiempo / (N - 1)) : 0.0;
        double desviacion_memoria = (N > 1) ? std::sqrt(suma_var_memoria / (N - 1)) : 0.0;

        salida_tiempo << key.n_tweet << ";" << key.estructura << ";" << promedio_tiempo << ";" << desviacion_tiempo << "\n";
        salida_memoria << key.n_tweet << ";" << key.estructura << ";" << promedio_memoria << ";" << desviacion_memoria << "\n";
    }
    salida_tiempo.close();
    salida_memoria.close();


    //procesamos timesstr.csv
    std::ifstream archivo_entrada2("results/timesstr.csv");
    if (!archivo_entrada2.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada: results/timesstr.csv" << std::endl;
        return 1;
    }

    std::map<ExperimentoKey, std::vector<Metricas>> datos2; // Mapa secundario
    std::string linea2;

    std::getline(archivo_entrada2, linea2); // Descartar cabecera

    while (std::getline(archivo_entrada2, linea2)) {
        if (linea2.empty()) continue;

        std::stringstream ss(linea2);
        std::string token2;
        
        int n_tweet2;
        std::string estructura2;
        double tiempo2;
        double memoria2;

        std::getline(ss, token2, ';'); n_tweet2 = std::stoi(token2);
        std::getline(ss, estructura2, ';');
        std::getline(ss, token2, ';'); tiempo2 = std::stod(token2);
        std::getline(ss, token2, ';'); memoria2 = std::stod(token2);

        ExperimentoKey key = {n_tweet2, estructura2};
        datos2[key].push_back({tiempo2, memoria2}); // CORREGIDO: Se usa datos2
    }
    archivo_entrada2.close();

    std::ofstream salida_tiempo2("results/tiempos_estadisticos2.csv");
    std::ofstream salida_memoria2("results/memoria_estadistica2.csv");

    salida_tiempo2 << "n_tweet;estructura;promedio_tiempo;desviacion_tiempo\n";
    salida_memoria2 << "n_tweet;estructura;promedio_memoria;desviacion_memoria\n";

    for (const auto& [key, lista_metricas] : datos2) { // Ahora iterará correctamente porque datos2 tiene información
        size_t N = lista_metricas.size();

        double suma_tiempo = 0.0;
        double suma_memoria = 0.0;
        for (const auto& m : lista_metricas) {
            suma_tiempo += m.tiempo;
            suma_memoria += m.memoria;
        }
        double promedio_tiempo = suma_tiempo / N;
        double promedio_memoria = suma_memoria / N;

        double suma_var_tiempo = 0.0;
        double suma_var_memoria = 0.0;
        for (const auto& m : lista_metricas) {
            suma_var_tiempo += std::pow(m.tiempo - promedio_tiempo, 2);
            suma_var_memoria += std::pow(m.memoria - promedio_memoria, 2);
        }
        
        double desviacion_tiempo = (N > 1) ? std::sqrt(suma_var_tiempo / (N - 1)) : 0.0;
        double desviacion_memoria = (N > 1) ? std::sqrt(suma_var_memoria / (N - 1)) : 0.0;

        salida_tiempo2 << key.n_tweet << ";" << key.estructura << ";" << promedio_tiempo << ";" << desviacion_tiempo << "\n";
        salida_memoria2 << key.n_tweet << ";" << key.estructura << ";" << promedio_memoria << ";" << desviacion_memoria << "\n";
    }
    salida_tiempo2.close();
    salida_memoria2.close();


    return 0;
}