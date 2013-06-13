// Experimental fastmap for fast conf access for issue #62

#include <cstdlib>
#include "../../easylogging++.h"
#include <map>

template <typename T>
class ConfigurationMap {
public:
    ConfigurationMap(void){
        table = new std::pair<unsigned int, T>*[easyloggingpp::Level::kMaxValid];
        for (int i = 0; i < easyloggingpp::Level::kMaxValid; i++)
            table[i] = NULL;
        count = 0;
    }

    const T& get(unsigned int level_) {
        if (table[level_] != NULL) {
            return table[level_]->second;
        }
        return table[easyloggingpp::Level::All]->second;
    }

    void set(unsigned int level_, const T& value) {
        if (table[level_] != NULL) {
            --count;
            delete table[level_];
            table[level_] = NULL;
        }
        table[level_] = new std::pair<unsigned int, T>(level_, value);
        ++count;
    }

    virtual ~ConfigurationMap(void) {
        for (int i = 0; i < easyloggingpp::Level::kMaxValid; ++i) {
            delete table[i];
        }
        delete[] table;
    }

    size_t size() {
        return count;
    }

private:
    std::pair<unsigned int, T>** table;
    size_t count;
};
