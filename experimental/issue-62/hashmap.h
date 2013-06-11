// Experimental hashmap for fast registry for issue #62
// Progress:
//    * Needs hash function
//    * Needs resizable table - (chunk resize by constant)

#include <cstdlib>
#include "../../easylogging++.h"

#include <stdint.h>
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif
uint32_t SuperFastHash (const char * data, int len) {
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
    case 3: hash += get16bits (data);
        hash ^= hash << 16;
        hash ^= ((signed char)data[sizeof (uint16_t)]) << 18;
        hash += hash >> 11;
        break;
    case 2: hash += get16bits (data);
        hash ^= hash << 11;
        hash += hash >> 17;
        break;
    case 1: hash += (signed char)*data;
        hash ^= hash << 10;
        hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}

template <typename T>
class Entry {
private:
    size_t key;
    T* value;
public:
    Entry(size_t key, T* value) {
        this->key = key;
        this->value = value;
    }
    ~Entry() {
        delete value;
    }
    size_t getKey() {
        return key;
    }
    T* getValue() {
        return value;
    }
};

const int SIZE = 128000; // Needs to be dynamic / resizable table

template <typename T> 
class HashMap {
private:
    Entry<T> **table;
public:
    HashMap(void) {
        table = new Entry<T>*[SIZE];
        for (int i = 0; i < SIZE; i++)
            table[i] = NULL;
    }

    T* get(int key) {
        int hash = (key % SIZE);
        while (table[hash] != NULL && table[hash]->getKey() != key) {
            hash = (hash + 1) % SIZE;
        }
        return (table[hash] == NULL) ? NULL : table[hash]->getValue();
    }

    void put(int key, T* value) {
        int hash = (key % SIZE);
        while (table[hash] != NULL && table[hash]->getKey() != key) {
            LINFO_EVERY_N(100) << "Calculating new hash for invalid hash [" << hash << "]";
            hash = (hash + 1) % SIZE;
        }
        if (table[hash] != NULL)
            delete table[hash];
        LINFO << "Putting hash [" << hash << "] [" << value << "]";
        table[hash] = new Entry<T>(key, value);
    }

    virtual ~HashMap() {
        for (int i = 0; i < SIZE; ++i)
            delete table[i];
        delete[] table;
    }
};
