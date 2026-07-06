#include "Map.h"
#include "unordered_map"

//clase para envolver implementacion estandar
//de unordered_map
template<typename K>
class stdMap : public Map<K>{
private:
    std::unordered_map<K,int> map;
public:
    stdMap(unsigned capacity){
        map.reserve(capacity);
    }

    //acceder a elemento
    int& operator[](K key) override {
        return map[key];
    }

    //verifica si key esta presente
    bool contains(K key) override {
        return (map.find(key)!=map.end());
    }

    //remueve elemento pr key
    //retorna true si el elemto se removio, false si no existe 
    bool remove(K key) override {
        return (map.erase(key)>0);
    }

    int size() override {return map.size();}
    int capacity() override {
        return map.bucket_count() * map.max_load_factor();
    }

    float loadFactor() override{
        return map.load_factor();
    }

    std::string type() override {
        return "STD";
    }

    ~stdMap(){}
};

