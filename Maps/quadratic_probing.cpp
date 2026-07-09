#include "Map.h"

//HashMap implementado con Quadratic Probing
template<typename K>
class QuadraticProbingHashMap : public Map<K>{
private:
    //Funciones hash para distribuir keys
    //Para unsigneds (user_id), usamos función MAD
    unsigned hash(unsigned k){
        return k*p % M;
    }
    //Para strings (user_screen_name), usamos acumulación polinomial y MAD
    unsigned hash(std::string ks){
        if (ks.empty()) return 0;
        unsigned k=ks[ks.length()-1];
        for (int i=ks.length()-2; i>=0; i--){
            k = k*53 + ks[i];
        }
        //Volvemos a usar la función hash, pero para unsigneds
        return hash(k);
    }

    unsigned n=0;
    unsigned M;
    unsigned p;

    //Usamos struct de entrada, almacena llave generica y el valor entero

    struct Entry {
        K key;
        int value;

        Entry(K key, int value){
            this->key = key;
            this->value = value;
        }
    };

    Entry** arr;

    unsigned nextPrime(unsigned n) {
        if (n <= 1) return 2;
        if (n % 2 == 0) ++n;

        while (true) {
            bool prime = true;
            for (unsigned i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                    break;
                }
            }
            if (prime) return n;
            n += 2;
        }
    }

public:
    QuadraticProbingHashMap(unsigned capacity){
        M = nextPrime(capacity);
        arr = new Entry*[M];
        for (unsigned i = 0; i < M; i++){
            arr[i] = nullptr;
        }
        
        //numero primo usado en la funcion hash
        //se asegura que no sea igual a M
        p = 2147483647;
        if (M==p) p=2147483629;
    }

    //Para acceder a elemento
    int& operator[](K key) override {
        if (((double)n)/M>=0.7) rehash();
        //Usamos funcion hash para tener idx de donde revisar
        unsigned dest = hash(key);
        for (unsigned i = 0; i < M; ++i) {
            unsigned lp_dest = (dest + (i + i * i) / 2) % M;
            Entry* entrada = arr[lp_dest];

            if (entrada == nullptr) {
                arr[lp_dest] = new Entry(key, 0);
                ++n;
                return arr[lp_dest]->value;
            }

            if (entrada->key == key) {
                return entrada->value;
            }
        }
        //Este caso es extremadamente improbable que ocurra, pero es posible que el probing cuadratico solo revisa casillas ya ocupadas
        throw std::out_of_range("Quadratic Probing no encontro una casilla disponible");
    }

    //Verifica si key esta presente, misma estructura de [] pero retorna bool
    bool contains(K key) override {
        //Usamos funcion hash para tener idx de donde revisar
        unsigned dest = hash(key);
        for (unsigned i = 0; i < M; ++i) {
            unsigned lp_dest = (dest + (i + i * i) / 2) % M;
            Entry* entrada = arr[lp_dest];

            if (entrada == nullptr) {
                return false;
            }

            if (entrada->key == key) {
                return true;
            }
        }
        //Si revisó todo el arreglo y no encuentra el valor correspondiente, es porque no está almacenado
        return false;
    }

    void rehash() {
        Entry** oldArray = arr;
        unsigned oldCapacity = M;

        M = nextPrime(oldCapacity * 2);
        n = 0;
        arr = new Entry*[M];
        for (unsigned i = 0; i < M; ++i) {
            arr[i] = nullptr;
        }

        for (unsigned i = 0; i < oldCapacity; ++i) {
            if (oldArray[i] != nullptr) {
                Entry* entry = oldArray[i];

                unsigned dest = hash(entry->key);
                bool inserted = false;
                for (unsigned j = 0; j < M; ++j) {
                    unsigned pos = (dest + (j + j * j) / 2) % M;
                    if (arr[pos] == nullptr) {
                        arr[pos] = new Entry(entry->key, entry->value);
                        ++n;
                        inserted = true;
                        break;
                    }
                }

                if (!inserted) {
                    throw std::out_of_range("Quadratic probing rehash no pudo colocar un elemento");
                }
            }
        }

        for (unsigned i = 0; i < oldCapacity; ++i) {
            delete oldArray[i];
        }
        delete[] oldArray;
    }

    int size() override {return n;}
    int capacity() override {return M;}

    std::string type() override {
        return "QuadraticProbing";
    }

    bool remove(K key) override {
        return false;
    }

    ~QuadraticProbingHashMap(){
        for (unsigned i = 0; i < M; i++){
            delete arr[i];
        }
        delete[] arr;
    }
};

