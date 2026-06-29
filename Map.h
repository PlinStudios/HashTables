#pragma once

template<typename K>
class Map
{
public:
    virtual bool contains(K key) = 0;
    virtual int& operator[](K key) = 0;

    virtual int size() = 0;
    virtual int capacity() = 0;
    virtual float loadFactor() {return size()/(float)capacity();};

    virtual ~Map() = default;
};