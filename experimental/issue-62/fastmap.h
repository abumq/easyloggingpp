// Experimental hashmap for fast registry for issue #62
// Progress:
//    * Needs hash function
//    * Needs resizable table - (chunk resize by constant)

#include <cstdlib>
#include "../../easylogging++.h"
#include <map>

int SIZE = 100; // Needs to be pulled off by Level::Count

template <typename _ValueT>
class FastMap {
public:
    FastMap(void){
        table = new std::pair<unsigned int, _ValueT>*[SIZE];
        for (int i = 0; i < SIZE; i++)
            table[i] = NULL;
        count = 0;
    }

    _ValueT get(unsigned int level_) {
        if (table[level_] != NULL) {
            return table[level_]->second;
        }
        return table[easyloggingpp::Level::All]->second;
    }

    void put(unsigned int level_, const _ValueT& value) {
        if (table[level_] != NULL) {
            --count;
            delete table[level_];
            table[level_] = NULL;
        }
        table[level_] = new std::pair<unsigned int, _ValueT>(level_, value);
        ++count;
    }

    ~FastMap() {
        for (int i = 0; i < SIZE; ++i) {
            delete table[i];
        }
        delete[] table;
    }

    size_t size() {
        return count;
    }

private:
    std::pair<unsigned int, _ValueT>** table;
    size_t count;
};
