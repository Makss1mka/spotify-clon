#ifndef MAP_H
#define MAP_H

#include <vector>

template<typename T, typename K>
class Map {
private:
    class Pair {
    public:
        Pair(T key, K value) : key(key), value(value) {}
        T key;
        K value;
    };

    std::vector<Pair> pairs;
public:
    Map() {}
    ~Map() {}

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

    class Iterator {
    public:
        Iterator(typename std::vector<Pair>::iterator initIter) {
            this->iter = initIter;
        }

        Pair& operator *() {
            return *iter;
        }

        Iterator& operator ++() {
            ++iter;
            return *this;
        }

        Iterator operator ++(int) {
            Iterator temp = *this;
            ++iter;
            return temp;
        }

        Iterator& operator --() {
            Iterator temp = *this;
            --iter;
            return temp;
        }

        Iterator operator --(int) {
            --iter;
            return *this;
        }

        bool operator !=(const Iterator& otherIter) const {
            return iter != otherIter.iter;
        }

        bool operator ==(const Iterator& otherIter) const {
            return iter == otherIter.iter;
        }
    private:
        typename std::vector<Pair>::iterator iter;
    };

    class RevrseIterator {
    public:
        RevrseIterator(typename std::vector<Pair>::iterator initIter) {
            this->iter = initIter;
        }

        Pair& operator *() {
            return *iter;
        }

        RevrseIterator& operator ++() {
            --iter;
            return *this;
        }

        RevrseIterator operator ++(int) {
            RevrseIterator temp = *this;
            --iter;
            return temp;
        }

        RevrseIterator& operator --() {
            RevrseIterator temp = *this;
            ++iter;
            return temp;
        }

        RevrseIterator operator --(int) {
            ++iter;
            return *this;
        }

        bool operator !=(const RevrseIterator& otherIter) const {
            return iter != otherIter.iter;
        }

        bool operator ==(const RevrseIterator& otherIter) const {
            return iter == otherIter.iter;
        }
    private:
        typename std::vector<Pair>::iterator iter;
    };

    class ConstIterator {
    public:
        ConstIterator(typename std::vector<Pair>::iterator initIter) {
            this->iter = initIter;
        }

        const Pair& operator *() {
            return *iter;
        }

        ConstIterator& operator ++() {
            ++iter;
            return *this;
        }

        ConstIterator operator ++(int) {
            ConstIterator temp = *this;
            ++iter;
            return temp;
        }

        ConstIterator& operator --() {
            ConstIterator temp = *this;
            --iter;
            return temp;
        }

        ConstIterator operator --(int) {
            --iter;
            return *this;
        }

        bool operator !=(const Iterator& otherIter) const {
            return iter != otherIter.iter;
        }

        bool operator ==(const Iterator& otherIter) const {
            return iter == otherIter.iter;
        }
    private:
        typename std::vector<Pair>::iterator iter;
    };

    class ConstRevrseIterator {
    public:
        ConstRevrseIterator(typename std::vector<Pair>::iterator initIter) {
            this->iter = initIter;
        }

        const Pair& operator *() {
            return *iter;
        }

        ConstRevrseIterator& operator ++() {
            --iter;
            return *this;
        }

        ConstRevrseIterator operator ++(int) {
            ConstRevrseIterator temp = *this;
            --iter;
            return temp;
        }

        ConstRevrseIterator& operator --() {
            ++iter;
            return *this;
        }

        ConstRevrseIterator operator --(int) {
            ConstRevrseIterator temp = *this;
            ++iter;
            return temp;
        }

        bool operator !=(const ConstRevrseIterator& otherIter) const {
            return iter != otherIter.iter;
        }

        bool operator ==(const ConstRevrseIterator& otherIter) const {
            return iter == otherIter.iter;
        }
    private:
        typename std::vector<Pair>::iterator iter;
    };

    Iterator begin() {
        return Iterator(pairs.begin());
    }
    Iterator end() {
        return Iterator(pairs.end());
    }
    RevrseIterator reverseBegin() {
        return RevrseIterator(pairs.end());
    }
    RevrseIterator reverseEnd() {
        return RevrseIterator(pairs.begin());
    }
    ConstIterator constBegin() {
        return ConstIterator(pairs.begin());
    }
    ConstIterator constEnd() {
        return ConstIterator(pairs.end());
    }
    ConstRevrseIterator constReverseBegin() {
        return ConstRevrseIterator(pairs.end());
    }
    ConstRevrseIterator constReverseEnd() {
        return ConstRevrseIterator(pairs.begin());
    }

    bool iterSearch(Iterator iter, T searchingKey) {
        try {
            while(true) {
                if((*iter).key == searchingKey) {
                    return true;
                }
                iter++;
            }
        } catch (...) {
            return false;
        }
    }
};

#endif // MAP_H
