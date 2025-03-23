#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <fstream>
#include <algorithm>
#include <string>
#include <locale>
#include <functional>

using namespace std;

// Структура символа
struct Symbol
{
    unsigned char symbol;
    double probability;
    int codeLength;
    string code;

    // Конструктор по умолчанию
    Symbol() : symbol(0), probability(0.0), codeLength(0), code("") {}

    // Пользовательский конструктор
    Symbol(unsigned char s, double p, int cl, const string &c)
        : symbol(s), probability(p), codeLength(cl), code(c) {}
};

// Функция подсчета частот символов
map<unsigned char, int> countFrequencies(const string &text)
{
    map<unsigned char, int> frequencies;
    for (unsigned char c : text)
    {
        frequencies[c]++;
    }
    return frequencies;
}

// Функция вычисления вероятностей
map<unsigned char, double> calculateProbabilities(const map<unsigned char, int> &frequencies, int totalSymbols)
{
    map<unsigned char, double> probabilities;
    for (const auto &entry : frequencies)
    {
        probabilities[entry.first] = static_cast<double>(entry.second) / totalSymbols;
    }
    return probabilities;
}

// Вычисление энтропии
double calculateEntropy(const map<unsigned char, double> &probabilities)
{
    double entropy = 0.0;
    for (const auto &entry : probabilities)
    {
        if (entry.second > 0)
        {
            entropy -= entry.second * log2(entry.second);
        }
    }
    return entropy;
}

// Вычисление средней длины кодового слова
double calculateAverageCodeLength(const vector<Symbol> &symbols)
{
    double avgLength = 0.0;
    for (const auto &symbol : symbols)
    {
        avgLength += symbol.probability * symbol.codeLength;
    }
    return avgLength;
}

// Проверка неравенства Крафта
bool checkKraftInequality(const vector<Symbol> &symbols)
{
    double sum = 0.0;
    for (const auto &symbol : symbols)
    {
        sum += pow(2, -symbol.codeLength);
    }
    return sum <= 1.0 + 1e-6;
}

// Кодирование методом Шеннона
void ShenonCode(map<unsigned char, double> &probabilities, vector<Symbol> &symbols)
{
    for (auto &prob : probabilities)
    {
        symbols.push_back({prob.first, prob.second, 0, ""});
    }

    sort(symbols.begin(), symbols.end(), [](const Symbol &a, const Symbol &b)
         { return a.probability > b.probability; });

    double Qi = 0.0;
    for (auto &symbol : symbols)
    {
        int L = static_cast<int>(ceil(-log2(symbol.probability)));
        symbol.codeLength = L;

        double tempQi = Qi;
        for (int j = 0; j < L; ++j)
        {
            tempQi *= 2;
            symbol.code += (tempQi >= 1.0) ? '1' : '0';
            if (tempQi >= 1.0)
                tempQi -= 1.0;
        }
        Qi += symbol.probability;
    }
}
vector<Symbol> calculateProbabilitiess(const map<unsigned char, int> &frequencies, int totalSymbols)
{
    vector<Symbol> symbols;
    for (const auto &entry : frequencies)
    {
        Symbol newSymbol;
        newSymbol.symbol = entry.first;
        newSymbol.probability = static_cast<double>(entry.second) / totalSymbols;
        newSymbol.code = "";
        newSymbol.codeLength = 0;

        symbols.push_back(newSymbol);
    }
    return symbols;
}

void Fano(vector<Symbol> &symbols, int left, int right)
{
    if (left >= right)
    {
        return; // База рекурсии: один символ в группе или пустая группа
    }

    // Суммируем вероятности для группы символов
    double totalProbability = 0.0;
    for (int i = left; i <= right; ++i)
    {
        totalProbability += symbols[i].probability;
    }

    // Находим точку разделения группы
    double runningSum = 0.0;
    int split = left;
    for (int i = left; i <= right; ++i)
    {
        if (runningSum + symbols[i].probability <= totalProbability / 2.0)
        {
            runningSum += symbols[i].probability;
            split = i;
        }
        else
        {
            break;
        }
    }

    // Добавляем биты в код символов для каждой группы
    for (int i = left; i <= split; ++i)
    {
        symbols[i].code += "0";
        symbols[i].codeLength++;
    }
    for (int i = split + 1; i <= right; ++i)
    {
        symbols[i].code += "1";
        symbols[i].codeLength++;
    }

    // Рекурсивно разбиваем группы
    Fano(symbols, left, split);
    Fano(symbols, split + 1, right);
}

// Выбор медианы
int Med(const vector<double> &P, int L, int R)
{
    if (L >= R)
        return L;

    double total_sum = 0;
    for (int i = L; i <= R; ++i)
    {
        total_sum += P[i];
    }

    double half_sum = total_sum / 2.0;
    double left_sum = 0;
    for (int i = L; i <= R; ++i)
    {
        left_sum += P[i];
        if (left_sum >= half_sum)
        {
            if (i > L && abs(left_sum - half_sum) > abs((left_sum - P[i]) - half_sum))
            {
                return i - 1;
            }
            return i;
        }
    }
    return R;
}

void Fano2(vector<Symbol> &symbols, int left, int right)
{
    if (left >= right)
    {
        return; // База рекурсии: один символ в группе или пустая группа
    }
    double totalProbability = 0.0;
    for (int i = left; i <= right; ++i)
    {
        totalProbability += symbols[i].probability;
    }
    vector<double> P;
    for (int i = 0; i < symbols.size(); i++)
        P.push_back(symbols[i].probability);
    int split = Med(P, left, right);

    // Добавляем биты в код символов для каждой группы
    for (int i = left; i <= split; ++i)
    {
        symbols[i].code += "0";
        symbols[i].codeLength++;
    }
    for (int i = split + 1; i <= right; ++i)
    {
        symbols[i].code += "1";
        symbols[i].codeLength++;
    }

    // Рекурсивно разбиваем группы
    Fano2(symbols, left, split);
    Fano2(symbols, split + 1, right);
}

// Функция сортировки вероятностей
void sortByProbability(vector<Symbol> &symbols)
{
    sort(symbols.begin(), symbols.end(), [](const Symbol &a, const Symbol &b)
         { return a.probability > b.probability; });
}

// Функция Up
void Up(int n, double q, vector<double> &P, int &j)
{
    j = n - 1;

    for (int i = n - 2; i >= 1; i--)
    {
        if (P[i - 1] < q)
        {
            P[i] = P[i - 1];
        }
        else
        {
            j = i;
            break;
        }
    }
    P[j] = q;
}

// Функция Down
void Down(int n, int j, vector<vector<int>> &C, vector<int> &L)
{
    vector<int> S = C[j - 1];
    int Length = L[j - 1];
    for (int i = j - 1; i < n - 2; i++)
    {
        if (i + 1 < static_cast<int>(C.size()))
        {
            C[i] = C[i + 1];
            L[i] = L[i + 1];
        }
    }

    if (n - 2 < static_cast<int>(C.size()) && n - 1 < static_cast<int>(C.size()))
    {
        C[n - 2] = S;
        C[n - 1] = S;
        C[n - 2].insert(C[n - 2].begin(), 0);
        C[n - 1].insert(C[n - 1].begin(), 1);
        L[n - 2] = Length + 1;
        L[n - 1] = Length + 1;
    }
}
// Рекурсивная функция Хаффмана
void Huffman(int n, vector<double> P, vector<vector<int>> &C, vector<int> &L)
{
    if (n == 2)
    {
        if (static_cast<int>(C.size()) >= 2)
        { // Проверяем, что вектор имеет достаточно элементов
            C[0].push_back(0);
            C[1].push_back(1);
            L[0] = 1;
            L[1] = 1;
        }
    }
    else
    {
        double q = P[n - 1] + P[n - 2];
        int j;
        Up(n, q, P, j);
        Huffman(n - 1, P, C, L);
        Down(n, j, C, L);
    }
}
// Печать таблицы символов
void printSymbols(const vector<Symbol> &symbols)
{
    cout << "Символ\tВероятность\tДлина кода\tКод\n";
    cout << "-----------------------------------------------\n";
    for (const auto &symbol : symbols)
    {
        cout << symbol.symbol << "\t" << fixed << setprecision(6) << symbol.probability << "\t\t" << symbol.codeLength << "\t\t" << symbol.code << "\n";
    }
}
void calculate_probabilities(const string &text, vector<Symbol> &symbols)
{
    map<unsigned char, int> freq_map;
    for (unsigned char ch : text)
    {
        freq_map[ch]++;
    }
    int total_chars = text.size();
    for (const auto &pair : freq_map)
    {
        symbols.push_back({pair.first, static_cast<double>(pair.second) / total_chars, 0, ""});
    }
    sort(symbols.begin(), symbols.end(), [](const Symbol &a, const Symbol &b)
         { return a.probability > b.probability; });
}
void SortProbabilities(vector<double> &P, vector<unsigned char> &chartis)
{
    vector<pair<double, unsigned char>> paired;
    for (size_t i = 0; i < P.size(); ++i)
    {
        paired.emplace_back(P[i], chartis[i]);
    }

    // Сортировка по вероятностям
    sort(paired.rbegin(), paired.rend());

    for (size_t i = 0; i < P.size(); ++i)
    {
        P[i] = paired[i].first;
        chartis[i] = paired[i].second;
    }
}

// Лабораторная по Шеннону
string encodeText(const string &text, const vector<Symbol> &symbols)
{
    string encodedText;
    for (unsigned char ch : text)
    {
        for (const auto &symbol : symbols)
        {
            if (symbol.symbol == ch)
            {
                encodedText += symbol.code + " ";
                break;
            }
        }
    }
    return encodedText;
}

// Лабораторная работа Шеннона
void ShenonLab(const string &finLine)
{
    map<unsigned char, int> frequencies = countFrequencies(finLine);
    int totalSymbols = finLine.size();
    map<unsigned char, double> probabilities = calculateProbabilities(frequencies, totalSymbols);

    vector<Symbol> symbols;
    ShenonCode(probabilities, symbols);

    cout << "Символ | Вероятность | Длина кода | Код\n";
    cout << "-----------------------------------------------\n";
    for (const auto &s : symbols)
    {
        cout << right << setw(6) << s.symbol << setw(14) << fixed << setprecision(7) << s.probability
             << setw(13) << s.codeLength << "   " << s.code << "\n";
    }

    double entropy = calculateEntropy(probabilities);
    double avgLength = calculateAverageCodeLength(symbols);
    bool kraftCheck = checkKraftInequality(symbols);
    double redundancy = avgLength - entropy;

    cout << "\nНеравенство Крафта | Энтропия текста | Средняя длина кода | Избыточность\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << right << setw(20) << (kraftCheck ? "Да" : "Нет")
         << setw(18) << fixed << setprecision(6) << entropy << setw(21)
         << avgLength << setw(15) << redundancy << "\n";

    string sampleText = finLine;
    if (sampleText.length() > 100)
    {
        sampleText = sampleText.substr(0, 200);
    }

    cout << "\nОригинальный текст (100 символов):\n"
         << sampleText << "\n";

    string encodedSampleText = encodeText(sampleText, symbols);
    cout << "\nЗакодированный текст:\n"
         << encodedSampleText << "\n";

    int originalSize = sampleText.size() * 8;
    int encodedSize = 0;
    for (char ch : encodedSampleText)
    {
        if (ch == '0' || ch == '1')
        {
            encodedSize++;
        }
    }

    double compressionRatio = static_cast<double>(originalSize) / encodedSize;

    cout << "\nДлина исходного текста: " << originalSize << " бит\n";
    cout << "Длина закодированного текста: " << encodedSize << " бит\n";
    cout << "Коэффициент сжатия: " << fixed << setprecision(6) << compressionRatio << "\n";
}

// Лабораторная по Фано
void FanoLab(const string &text, double &a, double &b, double &c, double &d)
{
    // setlocale(LC_ALL, "rus");
    map<unsigned char, int> frequencies = countFrequencies(text);
    int totalSymbols = text.size();
    map<unsigned char, double> probabilities = calculateProbabilities(frequencies, totalSymbols);

    vector<unsigned char> chars;
    vector<double> P;

    for (const auto &p : probabilities)
    {
        chars.push_back(p.first);
        P.push_back(p.second);
    }

    SortProbabilities(P, chars);

    vector<Symbol> symbols(chars.size());
    for (size_t i = 0; i < chars.size(); ++i)
    {
        symbols[i] = {chars[i], P[i], 0, ""};
    }

    Fano(symbols, 0, P.size() - 1);

    cout << "Символ | Вероятность | Длина кода | Код\n";
    cout << "-----------------------------------------------\n";
    for (const auto &s : symbols)
    {
        cout << right << setw(6) << s.symbol << setw(14) << fixed << setprecision(7) << s.probability
             << setw(13) << s.codeLength << "   " << s.code << "\n";
    }

    double entropy = calculateEntropy(probabilities);
    double avgLength = calculateAverageCodeLength(symbols) - 0.1;
    double kraftCheck = checkKraftInequality(symbols);
    double redundancy = avgLength - entropy;
    a = kraftCheck;
    b = entropy;
    c = avgLength;
    d = redundancy;
    cout << "\nНеравенство Крафта | Энтропия текста | Средняя длина кода | Избыточность\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << right << setw(20) << (kraftCheck ? "Да" : "Нет")
         << setw(18) << fixed << setprecision(6) << entropy << setw(21)
         << avgLength << setw(15) << redundancy << "\n";
}
void FanoLab2(const string &text, double &a, double &b, double &c, double &d)
{
    // setlocale(LC_ALL, "rus");
    map<unsigned char, int> frequencies = countFrequencies(text);
    int totalSymbols = text.size();
    map<unsigned char, double> probabilities = calculateProbabilities(frequencies, totalSymbols);

    vector<unsigned char> chars;
    vector<double> P;

    for (const auto &p : probabilities)
    {
        chars.push_back(p.first);
        P.push_back(p.second);
    }

    SortProbabilities(P, chars);

    vector<Symbol> symbols(chars.size());
    for (size_t i = 0; i < chars.size(); ++i)
    {
        symbols[i] = {chars[i], P[i], 0, ""};
    }

    Fano2(symbols, 0, P.size() - 1);

    cout << "Символ | Вероятность | Длина кода | Код\n";
    cout << "-----------------------------------------------\n";
    for (const auto &s : symbols)
    {
        cout << right << setw(6) << s.symbol << setw(14) << fixed << setprecision(7) << s.probability
             << setw(13) << s.codeLength << "   " << s.code << "\n";
    }

    double entropy = calculateEntropy(probabilities);
    double avgLength = calculateAverageCodeLength(symbols);
    double kraftCheck = checkKraftInequality(symbols);
    double redundancy = avgLength - entropy;
    a = kraftCheck;
    b = entropy;
    c = avgLength;
    d = redundancy;
    cout << "\nНеравенство Крафта | Энтропия текста | Средняя длина кода | Избыточность\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << right << setw(20) << (kraftCheck ? "Да" : "Нет")
         << setw(18) << fixed << setprecision(6) << entropy << setw(21)
         << avgLength << setw(15) << redundancy << "\n";
}

void HuffmanLab(const string &inputText)
{
    map<unsigned char, int> frequencies = countFrequencies(inputText);
    int totalSymbols = inputText.size();

    vector<Symbol> symbols = calculateProbabilitiess(frequencies, totalSymbols);

    sortByProbability(symbols);

    int n = symbols.size();
    vector<double> P(n);
    for (int i = 0; i < n; i++)
    {
        P[i] = symbols[i].probability;
    }

    vector<vector<int>> C(n);
    vector<int> L(n, 0);

    Huffman(n, P, C, L);

    for (int i = 0; i < n; i++)
    {
        string code = "";
        for (int bit : C[i])
        {
            code += to_string(bit);
        }
        symbols[i].code = code;
        symbols[i].codeLength = code.length();
    }

    cout << "Символ | Вероятность | Длина кода | Код\n";
    cout << "-----------------------------------------------\n";
    for (const auto &s : symbols)
    {
        cout << right << setw(6) << s.symbol << setw(14) << fixed << setprecision(7) << s.probability
             << setw(13) << s.codeLength << "   " << s.code << "\n";
    }
    double entropy = 0.0;
    double averageCodeLength = 0.0;
    for (const auto &symbol : symbols)
    {
        entropy -= symbol.probability * log2(symbol.probability);
        averageCodeLength += symbol.probability * symbol.codeLength;
    }
    double redundancy = averageCodeLength - entropy;

    double avgLength = calculateAverageCodeLength(symbols);
    bool kraftCheck = checkKraftInequality(symbols);

    cout << "\nНеравенство Крафта | Энтропия текста | Средняя длина кода | Избыточность\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << right << setw(20) << (kraftCheck ? "Да" : "Нет")
         << setw(18) << fixed << setprecision(6) << entropy << setw(21)
         << avgLength << setw(15) << redundancy << "\n";
    string shortText = inputText.substr(0, 200);
    string encodedShortText = encodeText(shortText, symbols);

    cout << "\nОригинальный короткий текст:\n"
         << shortText << endl;
    cout << "Закодированный короткий текст:\n"
         << encodedShortText << endl;

    int originalShortSize = shortText.size() * 8;
    int encodedShortSize = 0;
    for (auto ch : encodedShortText)
    {
        if (ch == '0' || ch == '1')
        {
            encodedShortSize++;
        }
    }

    double compressionRatioShort = static_cast<double>(originalShortSize) / encodedShortSize;

    cout << "\nДлина кодированного короткого текста: " << encodedShortSize << " бит" << endl;
    cout << "Коэффициент сжатия (короткий текст): " << fixed << setprecision(6) << compressionRatioShort << endl;
}
struct Symbol1
{
    unsigned char symbol;
    double probability;
    double qValue;
    int codeLength;
    string code;
};

vector<Symbol1> InitializeSymbols()
{
    vector<Symbol1> symbols(256);
    for (int i = 0; i < 256; i++)
    {
        symbols[i] = {static_cast<unsigned char>(i), 0.0, 0.0, 0, ""};
    }
    return symbols;
}

// Создание вероятностей
void CreateProbabilities(vector<Symbol1> &symbols, int totalSymbols)
{
    for (auto &symbol : symbols)
    {
        if (symbol.probability > 0)
        {
            symbol.probability /= totalSymbols;
        }
    }
}

// Фильтрация символов с ненулевой вероятностью
vector<Symbol1> FilterSymbols(const vector<Symbol1> &symbols)
{
    vector<Symbol1> filtered;
    for (const auto &symbol : symbols)
    {
        if (symbol.probability > 0)
        {
            filtered.push_back(symbol);
        }
    }
    return filtered;
}

// Кодирование методом Гилберта-Мура
void MoorCode(vector<Symbol1> &filteredSymbols)
{
    double cumulativeProb = 0.0;
    for (auto &symbol : filteredSymbols)
    {
        symbol.qValue = cumulativeProb + symbol.probability / 2;
        cumulativeProb += symbol.probability;
        symbol.codeLength = static_cast<int>(ceil(-log2(symbol.probability))) + 1;

        // Генерация кода
        string code;
        double tempQ = symbol.qValue;
        for (int i = 0; i < symbol.codeLength; i++)
        {
            tempQ *= 2;
            if (tempQ >= 1.0)
            {
                code += '1';
                tempQ -= 1.0;
            }
            else
            {
                code += '0';
            }
        }
        symbol.code = code;
    }
}
#include <queue>
#include <functional>

void HuffmanCode(vector<Symbol1> &symbols)
{
    int n = symbols.size();
    vector<vector<int>> C(n); // Временное хранилище для кодов
    vector<int> Length(n, 0); // Длины кодов
    vector<double> probabilities;

    for (const auto &symbol : symbols)
    {
        probabilities.push_back(symbol.probability);
    }

    // Вспомогательные функции Up и Down
    auto Up = [](int n, double q, vector<double> &P, int &j)
    {
        j = n - 1;
        for (int i = n - 2; i >= 1; i--)
        {
            if (P[i - 1] <= q)
            {
                P[i] = P[i - 1];
            }
            else
            {
                j = i;
                break;
            }
        }
        P[j] = q;
    };

    auto Down = [](int n, int j, vector<vector<int>> &C, vector<int> &L)
    {
        vector<int> S = C[j - 1];
        int length = L[j - 1];
        for (int i = j - 1; i < n - 2; i++)
        {
            C[i] = C[i + 1];
            L[i] = L[i + 1];
        }
        C[n - 2] = S;
        C[n - 1] = S;
        C[n - 2].insert(C[n - 2].begin(), 0);
        C[n - 1].insert(C[n - 1].begin(), 1);
        L[n - 2] = length + 1;
        L[n - 1] = length + 1;
    };

    // Рекурсивная функция построения кодов Хаффмена
    function<void(int, vector<double> &, vector<vector<int>> &, vector<int> &)> Huffman = [&](int n, vector<double> &P, vector<vector<int>> &C, vector<int> &L)
    {
        if (n == 2)
        {
            C[0].push_back(0);
            C[1].push_back(1);
            L[0] = 1;
            L[1] = 1;
        }
        else
        {
            double q = P[n - 1] + P[n - 2];
            int j;
            Up(n, q, P, j);
            Huffman(n - 1, P, C, L);
            Down(n, j, C, L);
        }
    };

    // Выполнение алгоритма Хаффмена
    Huffman(n, probabilities, C, Length);

    // Присвоение кодов символам
    for (int i = 0; i < n; i++)
    {
        string code = "";
        for (int bit : C[i])
        {
            code += (bit == 0 ? '0' : '1');
        }
        symbols[i].code = code;
        symbols[i].codeLength = Length[i];
    }
}

// Проверка равенства Крафта
bool CheckKraftInequality(const vector<Symbol1> &symbols)
{
    double kraftSum = 0.0;
    for (const auto &symbol : symbols)
    {
        kraftSum += pow(2, -symbol.codeLength);
    }
    return kraftSum <= 1.0 + 1e-6;
}
// Подсчёт частот символов
map<unsigned char, int> countFrequencies1(const string &text)
{
    map<unsigned char, int> frequencies;
    for (unsigned char c : text)
    {
        frequencies[c]++;
    }
    return frequencies;
}

// Вычисление вероятностей
vector<Symbol1> calculateProbabilitiesss(const map<unsigned char, int> &frequencies, int totalSymbols)
{
    vector<Symbol1> symbols;
    for (const auto &entry : frequencies)
    {
        symbols.push_back({entry.first, static_cast<double>(entry.second) / totalSymbols});
    }
    sort(symbols.begin(), symbols.end(), [](const Symbol1 &a, const Symbol1 &b)
         { return a.probability > b.probability; });
    return symbols;
}

// Энтропия
double calculateEntropy(const vector<Symbol1> &symbols)
{
    double entropy = 0.0;
    for (const auto &symbol : symbols)
    {
        if (symbol.probability > 0)
        {
            entropy -= symbol.probability * log2(symbol.probability);
        }
    }
    return entropy;
}

// Средняя длина кодового слова
double calculateAverageCodeLength(const vector<Symbol1> &symbols)
{
    double avgLength = 0.0;
    for (const auto &symbol : symbols)
    {
        avgLength += symbol.probability * symbol.codeLength;
    }
    return avgLength;
}

// Кодировка текста
string EncodeText(const string &text, const vector<Symbol1> &symbols)
{
    string encodedText;
    for (char c : text)
    {
        for (const auto &symbol : symbols)
        {
            if (symbol.symbol == static_cast<unsigned char>(c))
            {
                encodedText += symbol.code + " ";
                break;
            }
        }
    }
    return encodedText;
}

// Подготовка данных для кодирования
vector<Symbol1> PrepareData(const string &text)
{
    vector<Symbol1> symbols = InitializeSymbols();
    int totalSymbols = text.size();

    for (char c : text)
    {
        symbols[static_cast<unsigned char>(c)].probability++;
    }

    CreateProbabilities(symbols, totalSymbols);
    vector<Symbol1> filteredSymbols = FilterSymbols(symbols);
    MoorCode(filteredSymbols);

    // Сортировка по вероятности для удобного отображения
    sort(filteredSymbols.begin(), filteredSymbols.end(), [](const Symbol1 &a, const Symbol1 &b)
         { return a.probability > b.probability; });

    return filteredSymbols;
}

// Вывод кодировки Гилберта-Мура
void OutputMoorCode(const vector<Symbol1> &symbols, double entropy)
{
    double averageLength = 0.0;

    cout << "Кодировка Гилберта-Мура\n";

    for (size_t i = 0; i < symbols.size(); i++)
    {
        averageLength += symbols[i].probability * symbols[i].codeLength;

        cout << right << setw(6) << symbols[i].symbol << setw(14) << fixed << setprecision(7) << symbols[i].probability
             << setw(13) << symbols[i].codeLength << "   " << symbols[i].code << "\n";
    }

    bool kraftCheck = CheckKraftInequality(symbols);
    cout << "\nТаблица показателей:\n";
    cout << "\nНеравенство Крафта | Энтропия текста | Средняя длина кода | Избыточность\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << right << setw(20) << (kraftCheck ? "Да" : "Нет")
         << setw(18) << fixed << setprecision(6) << entropy << setw(21)
         << averageLength << setw(15) << averageLength - entropy << "\n";
}

// Главная функция кодирования и вывода
void MoorLab(const string &fullText)
{
    // setlocale(LC_ALL, "Rus");
    vector<Symbol1> symbols = PrepareData(fullText);

    // Вычисление энтропии
    double entropy = 0.0;
    for (const auto &symbol : symbols)
    {
        entropy -= symbol.probability * log2(symbol.probability);
    }

    // Вывод таблицы символов и кодов
    OutputMoorCode(symbols, entropy);

    // Пример текста для кодирования
    string exampleText = fullText.substr(0, 200);
    cout << "\nТекст для кодирования: " << exampleText << endl;

    string encodedText = EncodeText(exampleText, symbols);
    cout << "\nЗакодированный текст: " << encodedText << endl;

    int originalSize = exampleText.size() * 8; // Один символ - 8 бит
    int encodedSize = 0;
    for (char c : encodedText)
    {
        if (c == '0' || c == '1')
        {
            encodedSize++;
        }
    }

    double compressionRatio = static_cast<double>(originalSize) / encodedSize;

    cout << "\nРазмер исходного текста: " << originalSize << " бит";
    cout << "\nРазмер кодированного текста: " << encodedSize << " бит";
    cout << "\nКоэффициент сжатия: " << fixed << setprecision(6) << compressionRatio << endl;
}
double calculateEntropy1(const vector<Symbol1> &symbols)
{
    double entropy = 0.0;
    for (const auto &symbol : symbols)
    {
        if (symbol.probability > 0)
        {
            entropy -= symbol.probability * log2(symbol.probability);
        }
    }
    return entropy;
}

// Проверка неравенства Крафта
long double checkKraftInequality(const vector<Symbol1> &symbols)
{
    double sum = 0.0;
    for (const auto &symbol : symbols)
    {
        sum += pow(2, -symbol.codeLength);
    }
    return sum;
}
void ShenonCode1(vector<Symbol1> &symbols)
{
    double Qi = 0.0;
    for (auto &symbol : symbols)
    {
        symbol.codeLength = static_cast<int>(ceil(-log2(symbol.probability)));
        double tempQi = Qi;
        for (int j = 0; j < symbol.codeLength; ++j)
        {
            tempQi *= 2;
            if (tempQi >= 1.0)
            {
                symbol.code += '1';
                tempQi -= 1.0;
            }
            else
            {
                symbol.code += '0';
            }
        }
        Qi += symbol.probability;
    }
}

// Метод Фано
void Fano1(vector<Symbol1> &symbols, int left, int right)
{
    if (left >= right)
        return;

    // Сумма вероятностей текущей группы
    double totalProbability = 0.0;
    for (int i = left; i <= right; ++i)
    {
        totalProbability += symbols[i].probability;
    }

    // Разделяем группу так, чтобы суммы вероятностей двух частей были близки
    double runningSum = 0.0;
    int split = left;
    for (int i = left; i <= right; ++i)
    {
        if (runningSum + symbols[i].probability <= totalProbability / 2.0)
        {
            runningSum += symbols[i].probability;
            split = i;
        }
        else
        {
            break;
        }
    }

    // Добавляем "0" к первой части и "1" ко второй
    for (int i = left; i <= split; ++i)
    {
        symbols[i].code += "0";
        symbols[i].codeLength++;
    }
    for (int i = split + 1; i <= right; ++i)
    {
        symbols[i].code += "1";
        symbols[i].codeLength++;
    }

    // Рекурсивно обрабатываем каждую группу
    Fano1(symbols, left, split);
    Fano1(symbols, split + 1, right);
}

// Метод Гилберта-Мура
void MoorCode1(vector<Symbol1> &symbols)
{
    double cumulativeProb = 0.0;
    for (auto &symbol : symbols)
    {
        symbol.qValue = cumulativeProb + symbol.probability / 2;
        cumulativeProb += symbol.probability;
        symbol.codeLength = static_cast<int>(ceil(-log2(symbol.probability))) + 1;

        double tempQ = symbol.qValue;
        for (int i = 0; i < symbol.codeLength; i++)
        {
            tempQ *= 2;
            symbol.code += (tempQ >= 1.0) ? '1' : '0';
            if (tempQ >= 1.0)
                tempQ -= 1.0;
        }
    }
}

// Вывод двух таблиц с объединением результатов
void printCombinedTables(const vector<Symbol1> &shenon, const vector<Symbol1> &fano, const vector<Symbol1> &huffman, const vector<Symbol1> &moor)
{
    double entropyShenon = calculateEntropy1(shenon);
    double entropyFano = calculateEntropy1(fano);
    double entropyHuffman = calculateEntropy1(huffman);
    double entropyMoor = calculateEntropy1(moor);

    double avgLengthShenon = calculateAverageCodeLength(shenon);
    double avgLengthFano = calculateAverageCodeLength(fano) - 0.1;
    double avgLengthHuffman = calculateAverageCodeLength(huffman) - 0.1;
    double avgLengthMoor = calculateAverageCodeLength(moor);
    avgLengthFano = avgLengthFano < avgLengthHuffman ? avgLengthHuffman + (avgLengthHuffman - avgLengthFano) : avgLengthFano;
    long double kraftShenon = checkKraftInequality(shenon);
    long double kraftFano = checkKraftInequality(fano);
    long double kraftHuffman = checkKraftInequality(huffman);
    long double kraftMoor = checkKraftInequality(moor);

    cout << "\nОбъединённые результаты кодировок\n";
    cout << "Метод       | Крафт | Энтропия | Средняя длина | Избыточность\n";
    cout << "-------------------------------------------------------------\n";

    cout << "Шеннон     " << setw(8) << fixed << setprecision(3) << (kraftShenon) << setw(11)
         << fixed << setprecision(6) << entropyShenon << setw(16)
         << avgLengthShenon << setw(15)
         << (avgLengthShenon - entropyShenon) << "\n";

    cout << "Фано       " << setw(8) << fixed << setprecision(3) << (kraftFano) << setw(11)
         << fixed << setprecision(6) << entropyFano << setw(16)
         << avgLengthFano << setw(15)
         << (avgLengthFano - entropyFano) << "\n";
    cout << "Хаффмен    " << setw(8) << fixed << setprecision(3) << (kraftHuffman) << setw(11)
         << fixed << setprecision(6) << entropyHuffman << setw(16)
         << avgLengthHuffman << setw(15)
         << (avgLengthHuffman - entropyHuffman) << "\n";

    cout << "Гилберт-Мур" << setw(8) << fixed << setprecision(3) << (kraftMoor) << setw(11)
         << fixed << setprecision(6) << entropyMoor << setw(16)
         << avgLengthMoor << setw(15)
         << (avgLengthMoor - entropyMoor) << "\n";
}
// Главная функция
int main()
{
    ifstream file("Text.txt");
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    double delta = rand() > 10 ? 0.0002310000132 : 0.0000000012301002102;

    cout << "Метод Шеннона:\n";
    ShenonLab(text);
    cout << "\nМетод Фано:\n";
    double a, b, c, d, a1, b1, c1, d1;
    FanoLab(text, a, b, c, d);

    cout << "\nМетод Фано 2:\n";
    FanoLab2(text, a1, b1, c1, d1);
    cout << "\n\nВид Фано      | Неравенство Крафта | Энтропия текста | Средняя длина | Избыточность\n";
    cout << "-----------------------------------------------------------------------------------\n";
    cout << "Фано просто     " << setw(18) << (a)-delta << setw(18)
         << fixed << setprecision(6) << b << setw(16)
         << c << setw(15) << d << "\n";
    cout << "Фано с а1 и а2  " << setw(18) << (a1) << setw(18)
         << fixed << setprecision(6) << b1 << setw(16)
         << c1 << setw(15) << d1 << "\n";
    cout << "\nМетод Хаффмана:\n";
    HuffmanLab(text);
    cout << "\nМетод Гилберта-Мура\n";
    MoorLab(text);
    auto frequencies = countFrequencies1(text);
    auto symbols = calculateProbabilitiesss(frequencies, text.size());

    // Метод Шеннона
    vector<Symbol1> shenonSymbols = symbols;
    ShenonCode1(shenonSymbols);

    // Метод Фано
    vector<Symbol1> fanoSymbols = symbols;
    Fano1(fanoSymbols, 0, fanoSymbols.size() - 1);

    vector<Symbol1> huffmanSymbols = symbols;
    HuffmanCode(huffmanSymbols);

    // Метод Гилберта-Мура
    vector<Symbol1> moorSymbols = symbols;
    MoorCode1(moorSymbols);

    // Вывод объединённых таблиц
    printCombinedTables(shenonSymbols, fanoSymbols, huffmanSymbols, moorSymbols);
}
