#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

typedef struct {
    string _name;
    string _phoneNumber;
    string _Rayon;
    string _street;
} phoneEntry;

void printPhoneDict (const phoneEntry dict[], size_t size);
void printPhoneDict(const phoneEntry dict[], size_t size, const int indexArr[]);
void printPhoneDict(const phoneEntry dict[], const vector<int>& indexArr);
void SearchByKey(const phoneEntry dict[], size_t size, int sortedIndexesNamePhone[], int sortedIndexesAddress[]);
void SortByComplexKey(const phoneEntry dict[], size_t size);
void SortTelephoneDictionary(const phoneEntry dict[], size_t size, int *indexArr, bool (*compare)(const phoneEntry &, const phoneEntry &));
bool lessNamePhone(const phoneEntry& a, const phoneEntry& b);
bool lessAddress(const phoneEntry& a, const phoneEntry& b);

int main() {
    const size_t N = 5;
    phoneEntry dict[] = {
                    {"Banina Natalia Valerievna", "+7-111-222-33-44", "Zaelcovskiy", "Pushkina, 1"},
                    {"Speransky Artem Alexandrovich",   "+7-777-666-55-44", "Oktyabrskiy", "Kirova, 4"},
                    {"Safarov Arthur Victorovich", "+7-777-666-55-22", "Kalininskiy", "Kropotkina, 138"},
                    {"Banina Natalia Valerievna","+7-888-666-55-22", "Kalininskiy", "Kropotkina, 138"},
                    {"Speransky Artem Alexandrovich",     "+7-777-666-55-33", "Kalininskiy", "Kropotkina, 120"}
    };
    int sortedIndexesNamePhone[N], sortedIndexesAddress[N];
    SortTelephoneDictionary(dict, N, sortedIndexesNamePhone, lessNamePhone);
    SortTelephoneDictionary(dict, N, sortedIndexesAddress, lessAddress);
    while (true){
        system("clear");
        cout << "Изначальный справочник:\n";
        printPhoneDict(dict, N);
        cout << "\nВыберите опцию:"
                "\n1 - Вывести отсортированный по ключу справочник"
                "\n2 - Найти элемент по заданному ключу"
                "\n0 - Выйти из программы\n";
        char ch;
        cin >> ch;
        system("clear");
        switch (ch) {
            case '1': {
                SortByComplexKey(dict, N);
                getchar();
                getchar();
                break;
            }
            case '2': {
                SearchByKey(dict, N, sortedIndexesNamePhone, sortedIndexesAddress);
                getchar();
                getchar();
                break;
            }
            case '0': {
                return 0;
            }
            default:
                break;
        }
    }
}

void SortTelephoneDictionary(const phoneEntry dict[], size_t size, int *indexArr, bool (*compare)(const phoneEntry &, const phoneEntry &))
{
    for (int i = 0; i < size; i++)
        indexArr[i] = i;
    for (int i = 1; i < size; i++)
    {
        auto temp = indexArr[i];
        int j = i - 1;
        while (j >= 0 && compare(dict[temp], dict[indexArr[j]]))
        {
            indexArr[j + 1] = indexArr[j];
            j--;
        }
        indexArr[j + 1] = temp;
    }
}

//bool lessName(const phoneEntry& a, const phoneEntry& b)
//{
//    return a._name < b._name;
//}
//
//bool lessStreet(const phoneEntry& a, const phoneEntry& b)
//{
//    return a._street < b._street;
//}
//
//bool lessPhone(const phoneEntry& a, const phoneEntry& b)
//{
//    return a._phoneNumber < b._phoneNumber;
//}
//
//bool lessRayon(const phoneEntry& a, const phoneEntry& b)
//{
//    return a._Rayon < b._Rayon;
//}

bool lessNamePhone(const phoneEntry& a, const phoneEntry& b)
{
    if (a._name < b._name)
        return true;
    if (a._name > b._name)
        return false;
    if (a._phoneNumber < b._phoneNumber)
        return true;
    return false;
}

bool moreNamePhone(const phoneEntry& a, const phoneEntry& b)
{
    if (a._name > b._name)
        return true;
    if (a._name < b._name)
        return false;
    if (a._phoneNumber > b._phoneNumber)
        return true;
    return false;
}

bool lessAddressPhone(const phoneEntry& a, const phoneEntry& b)
{
    if (a._Rayon < b._Rayon)
        return true;
    if (a._Rayon > b._Rayon)
        return false;
    if (a._street < b._street)
        return true;
    if (a._street > b._street)
        return false;
    return a._phoneNumber < b._phoneNumber;
}

bool moreAddressPhone(const phoneEntry& a, const phoneEntry& b)
{
    if (a._Rayon > b._Rayon)
        return true;
    if (a._Rayon < b._Rayon)
        return false;
    if (a._street > b._street)
        return true;
    if (a._street < b._street)
        return false;
    return a._phoneNumber > b._phoneNumber;
}

bool lessAddress(const phoneEntry& a, const phoneEntry& b)
{
    if (a._Rayon < b._Rayon)
        return true;
    if (a._Rayon > b._Rayon)
        return false;
    return a._street < b._street;
}

bool moreAddress(const phoneEntry& a, const phoneEntry& b)
{
    if (a._Rayon > b._Rayon)
        return true;
    if (a._Rayon < b._Rayon)
        return false;
    return a._street > b._street;
}

void printPhoneDict (const phoneEntry dict[], size_t size)
{
    cout << setw(40) << left << "Name" << setw(18) << "Phone number"
         << setw(15) << "Rayon" << "Street" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(40) << dict[i]._name << setw(18) << dict[i]._phoneNumber << setw(15) << dict[i]._Rayon << dict[i]._street << endl;
    }
}

void printPhoneDict(const phoneEntry dict[], size_t size, const int indexArr[])
{
    cout << setw(40) << left << "Name" << setw(18) << "Phone number"
         << setw(15) << "Rayon" << "Street" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(40) << dict[indexArr[i]]._name << setw(18) << dict[indexArr[i]]._phoneNumber << setw(15) << dict[indexArr[i]]._Rayon << dict[indexArr[i]]._street << endl;
    }
}

void printPhoneDict(const phoneEntry dict[], const vector<int>& indexArr)
{
    cout << setw(40) << left << "Name" << setw(18) << "Phone number"
         << setw(15) << "Rayon" << "Street" << endl;
    for (auto i : indexArr) {
        cout << setw(40) << dict[i]._name << setw(18) << dict[i]._phoneNumber << setw(15) << dict[i]._Rayon << dict[i]._street << endl;
    }
}

vector<int> BSearchAllName (const phoneEntry dict[], const int indexArr[], size_t size, const string& key)
{
    std::vector<int> indexes(0);
    int L = 0, R = (int)size - 1;
    while (L < R){
        int m = floor((double)(L + R) / 2);
        if (dict[indexArr[m]]._name < key)
            L = m + 1;
        else
            R = m;
    }
    if (dict[indexArr[R]]._name == key) {
        while (R < size && dict[indexArr[R]]._name == key) {
            indexes.push_back(indexArr[R]);
            R++;
        }
    }
    return indexes;
}

vector<int> BSearchAllAddress (const phoneEntry dict[], const int indexArr[], size_t size, const string& key)
{
    std::vector<int> indexes(0);
    int L = 0, R = (int)size - 1;
    while (L < R){
        int m = floor((double)(L + R) / 2);
        if (dict[indexArr[m]]._street < key)
            L = m + 1;
        else
            R = m;
    }
    if (dict[indexArr[R]]._street == key) {
        while (R < size && dict[indexArr[R]]._street == key) {
            indexes.push_back(indexArr[R]);
            R++;
        }
    }
    return indexes;
}

void SearchByKey(const phoneEntry dict[], size_t size, int sortedIndexesNamePhone[], int sortedIndexesAddress[]){
    char keyType;
    string key;
    vector<int> foundedRecords(0);
    cout << "Введите поле, по ключу которого будет осуществлён поиск:\n1 - ФИО\n2 - Адресс\n";
    cin >> keyType;
    cout << "Введите ключ: ";
    getline(cin, key);
    getline(cin, key);
    switch (keyType) {
        case '1':{
            foundedRecords = BSearchAllName(dict, sortedIndexesNamePhone, size, key);
            break;
        }
        case '2':{
            foundedRecords = BSearchAllAddress(dict, sortedIndexesAddress, size, key);
            break;
        }
        default:{
            cout << "Неверная опция\n";
            return;
        }
    }
    cout << "Найденные записи:\n";
    printPhoneDict(dict, foundedRecords);
}

void SortByComplexKey(const phoneEntry dict[], size_t size)
{
    int sortedIndexes[size];
    bool isDecreasing = false;
    char ch;
    cout << "Выберите направление сортировки: 0 - по возрастанию, 1 - по убыванию\n";
    cin >> isDecreasing;
    cout << "\nВыберите сложный ключ для сортировки:\n1 - ФИО, Номер телефона\n2 - Адрес, Номер телефона\n3 - Район, Улица\n";
    cin >> ch;
    switch (ch) {
        case '1':
            isDecreasing ? SortTelephoneDictionary(dict, size, sortedIndexes, moreNamePhone):
            SortTelephoneDictionary(dict, size, sortedIndexes, lessNamePhone);
            break;
        case '2':
            isDecreasing ? SortTelephoneDictionary(dict, size, sortedIndexes, moreAddressPhone):
            SortTelephoneDictionary(dict, size, sortedIndexes, lessAddressPhone);
            break;
        case '3':
            isDecreasing ? SortTelephoneDictionary(dict, size, sortedIndexes, moreAddress):
            SortTelephoneDictionary(dict, size, sortedIndexes, lessAddress);
            break;
        default:
            cout << "Неверная опция\n";
            return;
    }
    cout << "\nОтсортированный справочник\n";
    printPhoneDict(dict, size, sortedIndexes);
}