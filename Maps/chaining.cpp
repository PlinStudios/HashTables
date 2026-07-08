#include "Map.h"

//HashMap implementado con chaining
template<typename K>
class ChainHashMap : public Map<K>{
private:
    //funciones hash para distribuir keys
    unsigned hash(unsigned k){
        return k*p % M;
    }
    unsigned hash(std::string ks){
        if (ks.empty()) return 0;
        unsigned k=ks[ks.length()-1];
        //acumulacion polinomial
        for (int i=ks.length()-2; i>=0; i--){
            k = k*53 + ks[i];
        }

        return hash(k);
    }


    //nodo de la lista enlazada
    struct chain
    {
        K key;
        int value;

        chain *next = nullptr;

        chain(K key, int value){
            this->key = key;
            this->value = value;
        }

        ~chain(){
            delete next;
        }
    };

    unsigned n=0;
    unsigned M;
    unsigned p;

    chain **arr;
public:
    ChainHashMap(unsigned capacity){
        M = capacity;
        arr = new chain*[M];
        for (unsigned i = 0; i < M; i++){
            arr[i] = nullptr;
        }
        
        //numero primo usado en la funcion hash
        //se asegura que no sea igual a M
        p = 2147483647;
        if (M==p) p=2147483629;
    }

    //acceder a elemento
    int& operator[](K key) override {
        //donde insertar
        unsigned dest = hash(key);

        chain *node = arr[dest];
        //crea el primer nodo
        if (node == nullptr){
            arr[dest] = new chain(key,0);
            n++;
            return arr[dest]->value;
        }
        //recorre lista enlazada
        while (true)
        {
            if (node->key == key)
                return node->value;
            else
                //si hay otro nodo continua
                if (node->next)
                    node = node->next;
                else
                    break;
        }
        //no encontro el nodo
        //crea uno nuevo
        node->next = new chain(key,0);
        n++;
        return node->next->value;
    }

    //verifica si key esta presente
    //misma estructura de [] pero retorna bool
    bool contains(K key) override {
        //donde deberia estar
        unsigned dest = hash(key);

        chain *node = arr[dest];
        //el primer nodo
        if (node == nullptr){
            return false;
        }
        //recorre lista enlazada
        while (true)
        {
            if (node->key == key)
                return true;
            else
                //si hay otro nodo continua
                if (node->next)
                    node = node->next;
                else
                    return false;
        }
    }

    //remueve elemento pr key
    //retorna true si el elemto se removio, false si no existe 
    bool remove(K key) override {
        //donde deberia estar
        unsigned dest = hash(key);

        chain *node = arr[dest];
        //si el primer nodo es null, la clave no existe
        if (node == nullptr){
            return false;
        }else{
            //si es el primer nodo
            if (node->key == key){
                arr[dest] = node->next;
                //apunta el nodo a null para destruirlo seguramente
                node->next = nullptr;
                delete node;
                n--;
                return true;
            }
        }
        //recorre lista enlazada
        chain *prevnode = node;
        node = node->next;
        if (node == nullptr) return false;
        while (true)
        {
            if (node->key == key){
                prevnode->next = node->next;
                node->next = nullptr;
                delete node;
                n--;
                return true;
            }else
                //si hay otro nodo continua
                if (node->next){
                    prevnode = node;
                    node = node->next;
                }
                else
                    return false;
        }
    }

    int size() override {return n;}
    int capacity() override {return M;}

    std::string type() override {
        return "Chaining";
    }

    ~ChainHashMap(){
        delete[] arr;
    }
};

