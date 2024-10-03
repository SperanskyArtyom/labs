#include <keywords.h>
#include <string-tree.h>

#include <fstream>
#include <vector>
#include <iostream>

bool binary_search(std::string *strlist, std::string key, int num);

int main()
{
    std::string bufer;
    std::vector<std::string> foundedKeywords;
    std::string filepath;
    std::cout << "Введите путь до файла: ";
    std::cin >> filepath;
    std::ifstream in(filepath);
    if (in.is_open())
        while (!in.eof())
        {
            in >> bufer;
            if (binary_search(KEYWORDS, bufer, KEYWORDS_NUMBER))
                foundedKeywords.push_back(bufer);
        }
    else
    {
        std::cout << "Файл не найден\n";
        return -1;
    }
    in.close();
    Vertex *root = createSDP(foundedKeywords);
    std::cout << "Словарь ключевых слов и их частот:\n";
    printVertexMap(root);

    return 0;
}

bool binary_search(std::string *strlist, std::string key, int num)
{
    int L = 0;
    int R = num;
    int m = L;
    do
    {
        if (strlist[m] == key)
            return true;
        if (strlist[m] > (key))
            R = m;
        else if (strlist[m] < key)
            L = m;
        m = (L + R) / 2;
    } while ((R - L) > 1);
    return false;
}
