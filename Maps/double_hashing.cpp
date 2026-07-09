#include "Map.h"

//HashMap implementado con Quadratic Probing
template<typename K>
class DoubleHashingHashMap : public Map<K>{
private:
    //Funciones hash para distribuir keys
    //Para unsigneds (user_id), usamos función MAD
    unsigned hash(unsigned k){
        return k*p % M;
    }
    //Para la 2da funcion hash, usamos MAD con otro coeficiente
    unsigned hash2(unsigned k){
        return k*p2 % M;
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
    unsigned p2;

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

    long long nextPowerOf2(int mm) {
    long long m= (long long) mm;
    m-- ;
    m |= m >> 1 ;
    m |= m >> 2 ;
    m |= m >> 4 ;
    m |= m >> 8 ;
    m |= m >> 16 ;
    m |= m >> 32 ;
    m++ ;
    return m ;
}
public:
    QuadraticProbingHashMap(unsigned capacity){
        M = capacity;
        arr = new Entry*[M];
        for (unsigned i = 0; i < M; i++){
            arr[i] = nullptr;
        }
        
        //numero primo usado en la funcion hash
        //se asegura que no sea igual a M
        p = 2147483647;
        if (M==p) p=2147483629;
        p2 = 761633;
        if (M==p2) p2= 762257;
    }

    //Para acceder a elemento
    int& operator[](K key) override {
        if (((double)n)/M>=0.7) rehash();
        //Usamos funcion hash para tener idx de donde revisar
        unsigned dest = hash(key);
        unsigned dest_hash2 = hash2(key);
        unsigned lp_dest;
        Entry* entrada;
        //Se revisa todo el arreglo hasta encontrar un exito
        //Se realiza el ciclo de 0 hasta M, como aparecen en los apuntes de clases de diccionarios
        for (long long i = 0; i<=M; i++){
            lp_dest = (dest + dest_hash2*i)%M;
            entrada = arr[lp_dest];
            //Crea la entrada en caso de que haya un puntero nulo, y devuelve cero
            if (entrada == nullptr){
                arr[lp_dest] = new Entry(key,0);
                n++;
                return arr[lp_dest]->value;
            }
            //si es que la llave si esté almacenada, se devuelve el valor correspondiente
            if (entrada->key == key){
                return entrada->value;
            }
        }
        //Este caso es extremadamente improbable que ocurra, pero es posible que el double hashing solo revise casillas ya ocupadas
        throw std::out_of_range("Double Hashing did not find value");
    }

    //Verifica si key esta presente, misma estructura de [] pero retorna bool
    bool contains(K key) override {
        //Usamos funcion hash para tener idx de donde revisar
        unsigned dest = hash(key);
        unsigned dest_hash2 = hash2(key);
        unsigned lp_dest;
        Entry* entrada;
        //Se revisa todo el arreglo hasta encontrar un exito
        //Se realiza el ciclo de 0 hasta M, como aparecen en los apuntes de clases de diccionarios
        for (long long i = 0; i<=M; i++){
            lp_dest = (dest + dest_hash2*i)%M;
            entrada = arr[lp_dest];
            //Crea la entrada en caso de que haya un puntero nulo, y devuelve cero
            if (entrada == nullptr){
                return true
            }
            //si es que la llave si esté almacenada, se devuelve el valor correspondiente
            if (entrada->key == key){
                return false;
            }
        }
        //Si revisó todo el arreglo y no encuentra el valor correspondiente, es porque no está almacenado
        return false;
    }

    void rehash() {
        Entry** oldArray = arr;
        unsigned oldCapacity = M;

        M *= 2;
        n = 0;

        arr = new Entry*[M];
        for (unsigned i = 0; i < M; ++i) {
            arr[i] = nullptr;
        }

        for (unsigned i = 0; i < oldCapacity; ++i) {
            if (oldArray[i] != nullptr) {
                Entry* entry = oldArray[i];

                unsigned pos = hash(entry->key);
                while (arr[pos] != nullptr) {
                    pos = (pos + 1) % M;
                }

                arr[pos] = new Entry(entry->key, entry->value);
                ++n;
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

