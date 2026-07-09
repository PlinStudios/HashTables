#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

// Estructura para agrupar las filas por cantidad de tweets y estructura
struct RegistroKey {
    int n_tweet;
    std::string estructura;

    bool operator<(const RegistroKey& other) const {
        if (n_tweet != other.n_tweet) return n_tweet < other.n_tweet;
        return estructura < other.estructura;
    }
};

// Función para unificar los promedios de tiempo y memoria restando Control
void consolidarArchivosNetos(const std::string& ruta_tiempo_in, 
                             const std::string& ruta_memoria_in, 
                             const std::string& ruta_salida_final) {
    
    std::map<RegistroKey, double> tiempos;
    std::map<RegistroKey, double> memorias;
    std::map<int, double> control_tiempo;
    std::map<int, double> control_memoria;
    std::vector<RegistroKey> orden_registros;

    std::string linea;
    std::string token;

    // 1. Leer archivo de tiempos estadísticos
    std::ifstream f_tiempo(ruta_tiempo_in);
    if (f_tiempo.is_open()) {
        std::getline(f_tiempo, linea); // Saltar cabecera
        while (std::getline(f_tiempo, linea)) {
            if (linea.empty()) continue;
            std::stringstream ss(linea);
            int n_tweet; std::string estructura; double promedio;

            std::getline(ss, token, ';'); n_tweet = std::stoi(token);
            std::getline(ss, estructura, ';');
            std::getline(ss, token, ';'); promedio = std::stod(token);

            RegistroKey key = {n_tweet, estructura};
            tiempos[key] = promedio;
            orden_registros.push_back(key); // Guardar orden para la salida

            if (estructura == "Control") {
                control_tiempo[n_tweet] = promedio;
            }
        }
        f_tiempo.close();
    } else {
        std::cerr << "Error al abrir: " << ruta_tiempo_in << std::endl;
        return;
    }

    // 2. Leer archivo de memoria estadística
    std::ifstream f_memoria(ruta_memoria_in);
    if (f_memoria.is_open()) {
        std::getline(f_memoria, linea); // Saltar cabecera
        while (std::getline(f_memoria, linea)) {
            if (linea.empty()) continue;
            std::stringstream ss(linea);
            int n_tweet; std::string estructura; double promedio;

            std::getline(ss, token, ';'); n_tweet = std::stoi(token);
            std::getline(ss, estructura, ';');
            std::getline(ss, token, ';'); promedio = std::stod(token);

            RegistroKey key = {n_tweet, estructura};
            memorias[key] = promedio;

            if (estructura == "Control") {
                control_memoria[n_tweet] = promedio;
            }
        }
        f_memoria.close();
    } else {
        std::cerr << "Error al abrir: " << ruta_memoria_in << std::endl;
        return;
    }

    // 3. Escribir el archivo único neto consolidado
    std::ofstream f_salida(ruta_salida_final);
    if (!f_salida.is_open()) {
        std::cerr << "Error al crear: " << ruta_salida_final << std::endl;
        return;
    }

    f_salida << "n_tweet;estructura;tiempo_neto;memoria_neto\n";

    for (const auto& key : orden_registros) {
        double t_neto = tiempos[key] - control_tiempo[key.n_tweet];
        double m_neto = memorias[key] - control_memoria[key.n_tweet];

        if (t_neto < 0) t_neto = 0.0;
        if (m_neto < 0) m_neto = 0.0;

        f_salida << key.n_tweet << ";" << key.estructura << ";" << t_neto << ";" << m_neto << "\n";
    }
    f_salida.close();
}

int main() {
    std::cout << "Consolidando datos netos en archivos únicos..." << std::endl;

    // Procesar y unificar todo lo perteneciente a LL
    consolidarArchivosNetos("results/tiempos_estadisticos.csv", 
                            "results/memoria_estadistica.csv", 
                            "results/timesll_neto.csv");

    // Procesar y unificar todo lo perteneciente a STR
    consolidarArchivosNetos("results/tiempos_estadisticos2.csv", 
                            "results/memoria_estadistica2.csv", 
                            "results/timesstr_neto.csv");

    std::cout << "¡Completado! Creados 'timesll_neto.csv' y 'timesstr_neto.csv'." << std::endl;
    return 0;
}