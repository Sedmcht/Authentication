#include "hash_table.h"

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
HashTable::~HashTable() {
    delete[] array;
}
int HashTable::hash_func(string login, int offset) {
    // вычисляем индекс
    int sum = 0;
    for (int i = 0; i < login.size(); i++) {
        sum += login[i];
    }
    
    const double A = 0.7;
    const int M = mem_size;
    sum = M * (A * sum - int(A * sum));

    // квадратичные пробы
    return (sum % mem_size + offset * offset) % mem_size;
}

void HashTable::add(string login, string passwd) 
{
    if (this->find(login) != "")
        return;

    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index].status == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }

    if (i >= mem_size) {
        resize();
        add(login, passwd);
    }
    else {
        array[index] = Pair(login, sha1(passwd));
        count++;
    }
}

void HashTable::resize() {

    Pair* save = array;
    int save_ms = mem_size;

    mem_size *= 2;
    array = new Pair[mem_size];
    count = 0;

    for (int i = 0; i < save_ms; i++) {
        Pair& old_pair = save[i];
        if (old_pair.status == enPairStatus::engaged) {
            add(old_pair.login, old_pair.passwd);
        }
    }

    delete[] save;
}

string HashTable::find(string login) 
{

    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(login, i);
        if (array[index].status == enPairStatus::engaged && array[index].login == login) 
        {
            return array[index].passwd;
        }
        else if (array[index].status == enPairStatus::free) {
            return "";
        }
    }
    return "";
}

void HashTable::del(string login) 
{
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index].status == enPairStatus::engaged && array[index].login == login) 
        {
            array[index].status = enPairStatus::deleted;
            count--;
            return;
        }
        else if (array[index].status == enPairStatus::free) {
            return;
        }
    }
}