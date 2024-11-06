#ifndef MAP_H
#define MAP_H

#include <vector>

template<typename T, typename K>
class Map {
public:
    Map() {}
    ~Map() {
        for(auto &pair : pairs) {
            delete pair.key;
            delete pair.value;
            delete pair;
        }
        delete pairs;
    }

    const K& get(const T& key) {
        for(auto &pair : pairs) {
            if(pair.key == key) return pair.value;
        }
        throw "Key " + key + " out of map keys";
    }

    void set(const T& key, const K& value) {
        for(auto &pair : pairs) {
            if(pair.key == key) {
                pair.value = value;
            }
        }
        pairs.push_back(Pair(key, value));
    }

    int count(const T& key) {
        for(auto &pair : pairs) {
            if(pair.key == key) return 1;
        }
        return 0;
    }

private:
    class Pair {
    public:
        Pair(T key, K value) : key(key), value(value) {}
        T key;
        K value;
    };

    std::vector<Pair> pairs;
};

#endif // MAP_H
