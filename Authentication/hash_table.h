#pragma once

#include <string>
#include "sha1.h"
using namespace std;



class HashTable { // хэш таблица
public:

    HashTable();
    ~HashTable();
    void add(string login, string passwd);
    void del(string login);
    string find(string login);

    
private:

    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair { // пара ключ-значение

        Pair() :
            login(""),
            passwd(""),
            status(enPairStatus::free)
        {}
        Pair(string _login, string _passwd) :
            login(_login),
            passwd(_passwd),
            status(enPairStatus::engaged) {
            
        }
        Pair& operator = (const Pair& other) {
            login = other.login;
            passwd = other.passwd;
            status = other.status;

            return *this;
        }

        bool operator == (const Pair& other) {
            return status == other.status && (login == other.login && passwd == other.passwd);
        }

        string login; 
        string passwd;

        enPairStatus status;
    };

    void resize();
    int hash_func(string login, int offset);

    

    Pair* array;
    int mem_size;
    int count;
};