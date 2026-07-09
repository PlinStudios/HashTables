## codigo hecho con gemini
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

// Función auxiliar para calcular el costo marginal leyendo los archivos ya promediados
void calcularCostoMarginal(const std::string& ruta_entrada, const std::string& ruta_salida, const std::string& nombre_columna_valor) {
    std::ifstream archivo_in(ruta_entrada);
    if (!archivo_in.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada: " << ruta_entrada << std::endl;
        return;
    }

    std::ofstream archivo_out(ruta_salida);
    if (!archivo_out.is_open()) {
        std::cerr << "Error al crear el archivo de salida: " << ruta_salida << std::endl;
        archivo_in.close();
        return;
    }

    std::string linea;
    std::getline(archivo_in, linea); // Leer cabecera original

    // Escribir nueva cabecera para el archivo incremental
    archivo_out << "n_tweet;estructura;" << nombre_columna_valor << ";costo_marginal\n";

    // Diccionario para recordar el último valor de cada estructura_de_datos (Y[i-1])
    std::map<std::string, double> ultimo_valor;

    while (std::getline(archivo_in, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string token;

        int n_tweet;
        std::string estructura;
        double valor_actual;
        double desviacion; // Se lee pero no la necesitamos para este cálculo

        // Parsear las 4 columnas del archivo estadístico tradicional
        std::getline(ss, token, ';'); n_tweet = std::stoi(token);
        std::getline(ss, estructura, ';');
        std::getline(ss, token, ';'); valor_actual = std::stod(token);
        std::getline(ss, token, ';'); desviacion = std::stod(token);

        double costo_marginal = 0.0;

        // Si ya registramos esta estructura antes, aplicamos (Y[i] - Y[i-1]) / 10000
        if (ultimo_valor.find(estructura) != ultimo_valor.end()) {
            costo_marginal = (valor_actual - ultimo_valor[estructura]) / 10000.0;
        } else {
            // Primer bloque (10000 tweets), asumimos que el estado inicial (0 tweets) era 0
            costo_marginal = valor_actual / 10000.0;
        }

        // Guardar la fila con la nueva métrica incremental
        archivo_out << n_tweet << ";" << estructura << ";" << valor_actual << ";" << costo_marginal << "\n";

        // Actualizar el historial para el siguiente tamaño de tweets
        ultimo_valor[estructura] = valor_actual;
    }

    archivo_in.close();
    archivo_out.close();
}

int main() {
    std::cout << "Procesando archivos incrementales desde fuentes estadísticas..." << std::endl;


    calcularCostoMarginal("results/tiempos_estadisticos.csv", 
                          "results/tiempos_incrementales1.csv", 
                          "promedio_tiempo");

    calcularCostoMarginal("results/memoria_estadistica.csv", 
                          "results/memoria_incremental1.csv", 
                          "promedio_memoria");


    calcularCostoMarginal("results/tiempos_estadisticos2.csv", 
                          "results/tiempos_incrementales2.csv", 
                          "promedio_tiempo");

    calcularCostoMarginal("results/memoria_estadistica2.csv", 
                          "results/memoria_incremental2.csv", 
                          "promedio_memoria");


    return 0;
}