#include "Map.h"

//HashMap implementado con Linear Probing
template<typename K>
class LinearProbingHashMap : public Map<K>{
private:
    //Funciones hash para distribuir keys
    //Para unsigneds (user_id), usamos función MAD
    unsigned hash(unsigned k){
        return k*p % M;
    }
    //Para strings (user_screen_name), usamos acumulación polinomial y MAD
    unsigned hash(std::string ks){
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

    //Usamos struct de entrada para almacenar si es una celda vacia o no (codigo extraido de laboratorio 9)
    enum State { EMPTY, OCCUPIED, DELETED };

    struct Entry {
        K key;
        int value;
        State state;

        Entry(K key, int value, State st){
            this->key = key;
            this->value = value;
            this->state = st;
        }
    };

    Entry** arr;
public:
    LinearProbingHashMap(unsigned capacity){
        M = capacity;
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
        //Usamos funcion hash para tener idx de donde revisar
        unsigned dest = hash(key);
        unsigned lp_dest;
        Entry* entrada;
        //Se revisa todo el arreglo hasta encontrar un exito
        for (int i = 0; i<M; i++){
            lp_dest = (dest+i)%M;
            entrada = arr[lp_dest];
            //Crea la entrada en caso de que haya un puntero nulo, y devuelve cero
            if (entrada == nullptr){
                arr[lp_dest] = new Entry(key,0,EMPTY);
                return arr[lp_dest]->value;
            }
            //En caso de que encuentre una celda vacia, devuelve cero
            if (entrada->state == EMPTY){
                return 0;
            }
            //si es que la llave si esté almacenada y no esté en una celda borrada, se devuelve el valor correspondiente
            if (entrada->key == key && entrada->state == OCCUPIED){
                return entrada->value;
            }
        }
        //Si revisó todo el arreglo y no encuentra el valor correspondiente, es porque no está almacenado
        return 0;
    }

    //Verifica si key esta presente, misma estructura de [] pero retorna bool
    bool contains(K key) override {
        //Usamos funcion hash para tener idx de donde revisar
        unsigned dest = hash(key);
        unsigned lp_dest;
        Entry* entrada;
        //Se revisa todo el arreglo hasta encontrar un exito
        for (int i = 0; i<M; i++){
            lp_dest = (dest+i)%M;
            entrada = arr[lp_dest];
            //Si encuentra en una celda un puntero nulo, es equivalente a encontrar una celda vacia, devuelve falso
            if (entrada == nullptr){
                return false;
            }
            //En caso de encontrar una celda vacia, devuelve falso
            if (entrada->state == EMPTY){
                return false;
            }
            //si es que el elemento si está almacenado y no es una celda borrada, es porque si existe, devuelve verdadero
            if (entrada->key == key && entrada->state == OCCUPIED){
                return true;
            }
        }
        //Si revisó todo el arreglo y no encuentra el valor correspondiente, es porque no está almacenado
        return false;
    }

    int size() override {return n;}
    int capacity() override {return M;}

    ~ChainHashMap(){
        delete[] arr;
    }
};

