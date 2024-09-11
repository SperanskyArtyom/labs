#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int SIZE_OF_HASH_TABLE = 101;
const int PRIME_SIZES[] = { 11, 13, 17, 19, 23, 29, 31, 43, 71, 101 };
int Coll = 0;
vector<string> str;
long long hash_func(const string& S) {
    long long h = 0;
    for (char i : S) {
        h = (h * 256 + i) % SIZE_OF_HASH_TABLE;
    }
    return h;
}

struct list {
    list* next{};
    string data;
};

struct hash_table {
    long long hash;
    list* data;
    hash_table* next;
};

void addToTheTable(hash_table*& head, string str) {
    long long hash = hash_func(str);
    hash_table* find = head;

    short int flag = 0;
    while (find != nullptr) {
        if (find->hash == hash) {
            flag = 1;
            if (find->data != nullptr) {
                Coll++;
            }
            break;
        }
        find = find->next;
    }

    if (flag) {
        list* newList = new list;
        newList->data = str;
        newList->next = find->data;
        find->data = newList;
    }
    else {
        auto* newHash = new hash_table;
        newHash->hash = hash;
        list* newList = new list;
        newList->data = str;
        newList->next = nullptr;
        newHash->data = newList;
        newHash->next = head;
        head = newHash;
    }
}
void genStr()
{
    int len = rand() % 25;
    string s = "";
    int i = 0;
    for (i = 0; i < len + 1; i++)
    {
        switch (rand() % 3)
        {
            case 0:
                s.push_back(rand() % 26 + 65);
                break;
            case 1:
                s.push_back(rand() % 10 + 48);
                break;
            case 2:
                s.push_back(rand() % 26 + 97);
                break;
        }
    }
    str.push_back(s);
}
void genStr(vector<string>str1)
{
    int len = rand() % 10;
    string s = "";
    int i = 0;
    for (i = 0; i < len + 1; i++)
    {
        switch (rand() % 3)
        {
            case 0:
                s.push_back(rand() % 26 + 65);
                break;
            case 1:
                s.push_back(rand() % 10 + 48);
                break;
            case 2:
                s.push_back(rand() % 26 + 97);
                break;
        }
    }
    str1.push_back(s);
}
void printHashTable(hash_table* head) {
    cout << "Хеш-таблица:" << endl;
    for (int i = 0; i < SIZE_OF_HASH_TABLE; ++i) {
        hash_table* current = head;
        cout << i << " -> ";
        while (current != nullptr) {
            if (current->hash == i) {
                list* currentList = current->data;
                while (currentList != nullptr) {
                    cout << currentList->data<<" -> ";
                    currentList = currentList->next;
                }
            }
            current = current->next;
        }
        cout << endl;
    }
}
int hashSearch(hash_table* head, string str)
{
    long long input = hash_func(str);
    int i;
    list* answer = nullptr;
    while (head != nullptr)
    {
        i = 1;
        if (head->hash == input)
        {
            answer = head->data;
            while (answer != nullptr)
            {
                if (answer->data == str)
                {
                    return i;
                }
                i++;
                answer = answer->next;
            }
            return 0;
        }
        head = head->next;
    }
    return 0;
}
int main() {
    srand(time(nullptr));
    float percentage;
    hash_table* head = nullptr;
    for (int i = 0; i < 100; i++) {
        genStr();
    }
    for(string s : str) {
        addToTheTable(head, s);
    }
    string str1;
    str1 = str[rand() % 20];
    cout << "Поиск в хеш таблице " << hashSearch(head, str1) << endl;
    cout << "Поиск бинарным поиском " << (int)log2(100) << endl;
    float diff = ((int)log2(100) / hashSearch(head, str1)) * 100;
    cout << "Поиск в хеш таблице быстрее на " << diff << "%" << endl;
    //printHashTable(head);
    // Выведем количество коллизий
    // cout << "Число коллизий: " << Coll << endl;
    cout << "Размер Хеш-Таблицы\tКоличество исх. символов\tКоличество коллизий" << endl;
    int a = rand()%(400-300)+300;
    for (int i = 0; i < a; i++) {
        genStr();
    }
    for (int size : PRIME_SIZES) {
        a = rand()%(400-300)+300;
        SIZE_OF_HASH_TABLE = size;
        head = nullptr;
        for (const string& symbol : str) {
            addToTheTable(head, symbol);
        }
        int collisions = Coll;
        //printHashTable(head);
        cout << "\t" << size << "\t\t\t\t\t" << str.size() << "\t\t\t\t\t\t" << collisions << endl;
        Coll = 0;
        str = {};
        for (int i = 0; i < a; i++) {
            genStr();
        }
    }
    return 0;
}