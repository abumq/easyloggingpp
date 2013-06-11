// Experimental hashmap for fast registry for issue #62
// Progress:
//    * Needs hash function
//    * Needs resizable table - (chunk resize by constant)

#include <cstdlib>
#include "../../easylogging++.h"

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
