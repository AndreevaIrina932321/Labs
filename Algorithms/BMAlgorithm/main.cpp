#include <iostream>
#include <string>
#include <vector>

void outputVector(const std::vector<int> &v)
{
    for(int i; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
}

void outputTable(int *table)
{
    int i;
    for (i = 97; i <= 122; ++i)
        std::cout << (char)i << ' ';
    std::cout << std::endl;
    for (i = 97; i <= 122; ++i)
        std::cout << table[i] << ' ';
    std::cout << std::endl;
}

void setTable(int *table, const std::string &sample)
{
    int i, lengthOfSample = sample.size();
    for (i = 0; i < 256; i++)
    {
        table[i] = lengthOfSample;
    }
    for (i = lengthOfSample - 1; i >= 0; i--)
    {
        table[sample[i]] = lengthOfSample - sample.rfind(sample[i], lengthOfSample - 2) - 1;
    }
}

void findIndex(int *table, const std::string &inputString, const std::string &sample, int &i, int &j)
{
    int lengthOfSample = sample.size();
    int k;
    for (k = i, j = lengthOfSample - 1; j >= 0; j--, k--)
    {
        if (inputString[k] != sample[j])
        {
            i += table[inputString[i]];
            j = lengthOfSample - 1;
            break;
        }
    }
}

int getFirstIndexOfSample(int *table, const std::string &inputString, const std::string &sample)
{

    int lengthOfSample = sample.size(), i = lengthOfSample - 1, j = lengthOfSample - 1;
    while (i < inputString.size() && j >= 0)
        findIndex(table, inputString, sample, i, j);
    if (j < 0)
        return i + 1 - lengthOfSample;
    return -1;
}

void getAllIndexesInAB(int *table, const std::string &inputString, const std::string &sample, std::vector<int> &indexes, int leftBound, int rightBound)
{
    int lengthOfSample = sample.size();
    int i = lengthOfSample - 1 + leftBound, j = lengthOfSample - 1;
    while (i <= rightBound)
    {
        findIndex(table, inputString, sample, i, j);
        if (j < 0)
        {
            indexes.push_back(i + 1 - lengthOfSample);
            i += table[inputString[i]];
        }
    }
}


int main()
{
    bool debug = true;
    int firstIndex, leftBound, rightBound;
    int table[256];
    std::string inputString, sample;
    std::vector<int> indexes;
    std::cout << "Введите строку для поиска в ней подстроки: ";
    getline(std::cin, inputString);
    std::cout << "Введите искомую подстроку: ";
    getline(std::cin, sample);
    setTable(table, sample);
    if (debug)
    {
        outputTable(table);
        firstIndex = getFirstIndexOfSample(table, inputString, sample);
        std::cout << "Индекс первого вхождения: " << firstIndex << std::endl;
    }
    std::cout << "Введите левую и правую границы: ";
    std::cin >> leftBound >> rightBound;
    if (leftBound >= rightBound || leftBound < 0 || rightBound > inputString.size() - 1)
    {
        std::cout << "Вы неверно ввели границы, поиск будет производиться по всей строке\n";
        leftBound = 0;
        rightBound = inputString.size() - 1;
    }
    getAllIndexesInAB(table, inputString, sample, indexes, leftBound, rightBound);
    if (!indexes.empty())
    {
        std::cout << "Список индексов вхождений подстроки: ";
        outputVector(indexes);
    }
    else std::cout << "Подстрока не найдена";
    return 0;
}
