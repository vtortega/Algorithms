#include "myVector.hpp"

template <typename Key, typename Value>
class Map {
private:
    Vector<Pair<Key, Value>> data;

public:
    Map() {}

    Map(const Map& other) : data(other.data) {}

    Map& operator=(const Map& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    ~Map() {}

    void insert(const Key& key, const Value& value) {
        for (auto& pair : data) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        data.push_back(Pair<Key, Value>(key, value));
    }

    Value& operator[](const Key& key) {
        for (auto& pair : data) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        data.push_back(Pair<Key, Value>(key, Value()));
        return data.back().second;
    }

    bool contains(const Key& key) const {
        for (const auto& pair : data) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    void erase(const Key& key) {
        auto it = data.begin();
        while (it != data.end()) {
            if (it->first == key) {
                it = data.erase(it);
            } else {
                ++it;
            }
        }
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    typedef typename Vector<Pair<Key, Value>>::iterator iterator;
    typedef typename Vector<Pair<Key, Value>>::const_iterator const_iterator;

    iterator begin() {
        return data.begin();
    }

    const_iterator begin() const {
        return data.begin();
    }

    iterator end() {
        return data.end();
    }

    const_iterator end() const {
        return data.end();
    }
};
