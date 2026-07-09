#include "Map.h"

//HashMap implementado con Double Hashing
template<typename K>
class DoubleHashingHashMap : public Map<K>{
private:
    //Funciones hash para distribuir keys
    //Para unsigneds (user_id), usamos función MAD
    unsigned hash(unsigned k){
        return k*p % M;
    }
    //Para la 2da funcion hash, usamos un paso que siempre sea distinto de cero y coprimo con M
    unsigned hash2(unsigned k){
        return 1 + (k % (M - 1));
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
    //Usamos acumulación polinomial con otro coeficiente, y con la funcion de hash2()
    unsigned hash2(std::string ks){
        if (ks.empty()) return 0;
        unsigned k=ks[ks.length()-1];
        for (int i=ks.length()-2; i>=0; i--){
            k = k*67 + ks[i];
        }
        return hash2(k);
    }

    unsigned n=0;
    unsigned M;
    unsigned p;

    void updateHashParams(){
        p = 2147483647;
        if (M == p) p = 2147483629;
    }

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
    //Se añade una funcion para calcular el proximo número primo, pues eso es un requerimiento del double hashing
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
    DoubleHashingHashMap(unsigned capacity){
        M = nextPrime(capacity);
        arr = new Entry*[M];
        for (unsigned i = 0; i < M; i++){
            arr[i] = nullptr;
        }

        updateHashParams();
    }

    //Para acceder a elemento
    int& operator[](K key) override {
        //Usamos funcion hash para tener idx de donde revisar
        if (((double)n)/M >= 0.7) rehash();

        unsigned dest = hash(key);
        unsigned dest_hash2 = hash2(key);

        for (unsigned i = 0; i < M; ++i) {
            unsigned lp_dest = (dest + dest_hash2 * i) % M;
            Entry* entrada = arr[lp_dest];

            if (entrada == nullptr) {
                arr[lp_dest] = new Entry(key, 0);
                ++n;
                return arr[lp_dest]->value;
            }
            //si es que la llave si esté almacenada, se devuelve el valor correspondiente
            if (entrada->key == key){
                return entrada->value;
            }
        }
        //Este caso es extremadamente improbable que ocurra, pero es posible que el double hashing solo revise casillas ya ocupadas
        throw std::out_of_range("Double Hashing no encontro una casilla disponible");
    }

    //Verifica si key esta presente, misma estructura de [] pero retorna bool
    bool contains(K key) override {
        unsigned dest = hash(key);
        unsigned dest_hash2 = hash2(key);

        for (unsigned i = 0; i < M; ++i) {
            unsigned lp_dest = (dest + dest_hash2 * i) % M;
            Entry* entrada = arr[lp_dest];

            if (entrada == nullptr) {
                return false;
            }
            //si es que la llave si esté almacenada, se devuelve el valor correspondiente
            if (entrada->key == key){
                return true;
            }
        }
        //Si revisó todo el arreglo y no encuentra el valor correspondiente, es porque no está almacenado
        return false;
    }

    void rehash() {
        Entry** oldArray = arr;
        unsigned oldCapacity = M;

        // Aumentar la capacidad con un tamaño primo para mantener el doble hashing válido
        M = nextPrime(oldCapacity * 2);
        updateHashParams();

        // Crear el nuevo arreglo
        arr = new Entry*[M];
        for (unsigned i = 0; i < M; i++) {
            arr[i] = nullptr;
        }

        // Reiniciar el número de elementos
        n = 0;

        // Reinsertar todos los elementos usando la misma secuencia de doble hashing
        for (unsigned i = 0; i < oldCapacity; i++) {
            if (oldArray[i] != nullptr) {
                Entry* entry = oldArray[i];

                unsigned h1 = hash(entry->key);
                unsigned h2 = hash2(entry->key);

                bool inserted = false;
                for (unsigned j = 0; j < M; j++) {
                    unsigned pos = (h1 + j * h2) % M;

                    if (arr[pos] == nullptr) {
                        arr[pos] = new Entry(entry->key, entry->value);
                        n++;
                        inserted = true;
                        break;
                    }
                }

                if (!inserted) {
                    throw std::out_of_range("Double Hashing rehash no pudo agregar un elemento");
                }

                delete entry;
            }
        }

        delete[] oldArray;
    }

    int size() override {return n;}
    int capacity() override {return M;}

    std::string type() override {
        return "DoubleHashing";
    }

    bool remove(K key) override {
        return false;
    }

    ~DoubleHashingHashMap(){
        for (unsigned i = 0; i < M; i++){
            delete arr[i];
        }
        delete[] arr;
    }
};

