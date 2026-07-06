#include "Map.h"

//no hace nada, para probar el tiempo base de leer los tweets
template<typename K>
class NullMap : public Map<K>{
private:
    int count;
public:
    NullMap(unsigned capacity){
    }

  
    int& operator[](K key) override {
        return count;
    }

    bool contains(K key) override {
        return true;
    }

    bool remove(K key) override {
        return false;
    }

    int size() override {return 1;}
    int capacity() override {return 1;}

    std::string type() override {
        return "Control";
    }

    ~NullMap(){
    }
};

