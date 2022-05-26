#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <list>
#include <vector>

int dynamic(std::string str1, std::string str2, int size_str1, int size_str2, std::string &output, int &cont)
{
    // int table[size_str1 + 1][size_str2 + 1];
    std::vector<std::vector<int>> table(size_str1 + 1, std::vector<int>(size_str2 + 1, 0));

    for (int i = 0; i <= size_str1; i++)
    {
        for (int j = 0; j <= size_str2; j++)
        {

            if (i == 0 || j == 0)
            {
                table[i][j] = 0;
            }
            else if (str1[i - 1] == str2[j - 1])
            {
                cont++;
                table[i][j] = table[i - 1][j - 1] + 1;
            }
            else
            {
                cont++;
                table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
            }
        }
    }

    // para printar a sequencia
    int index = table[size_str1][size_str2];

    int i = size_str1, j = size_str2;
    while (i > 0 && j > 0)
    {
        // cont++;
        if (str1[i - 1] == str2[j - 1])
        {
            cont++;
            output.insert(0, 1, str1[i - 1]);
            i--;
            j--;
        }
        else if (table[i - 1][j] > table[i][j - 1])
        {
            // cont++;
            i--;
        }
        else
        {
            j--;
        }
    }
    return table[size_str1 - 1][size_str2 - 1];
}

int main()
{
    // contador de comparações
    std::list<std::string> dirlist({"10.txt", "25.txt", "50.txt", "100.txt", "150.txt", "200.txt", "300.txt", "500.txt", "750.txt", "1000.txt", "2000.txt", "3000.txt", "5000.txt", "7500.txt", "10000.txt"});
    // std::list<std::string> dirlist({"10.txt", "11.txt", "12.txt", "13.txt", "14.txt", "15.txt", "16.txt", "17.txt", "18.txt", "19.txt", "20.txt", "21.txt", "22.txt", "23.txt", "24.txt"});
    for (std::string val : dirlist)
    {
        // std::cout << val << std::endl;
        for (int i = 0; i < 5; i++)
        {
            int cont = 0;
            // contador de milhões de comparações, quando aumenta zera o cont
            int mil = 0;
            std::ifstream file(val);
            std::string entrada1 = "";
            std::string entrada2 = "";
            {
                std::string str1;
                std::string str2;
                std::getline(file, str1);
                std::getline(file, str2);
                std::stringstream ss1(str1);
                char temp;
                while (ss1 >> temp)
                {
                    entrada1 += temp;
                };
                std::stringstream ss2(str2);
                while (ss2 >> temp)
                {
                    entrada2 += temp;
                };
            }
            file.close();

            std::string output = "";
            auto start = std::chrono::steady_clock::now();
            auto res = dynamic(entrada1, entrada2, entrada1.length(), entrada2.length(), output, cont);
            // auto elapsed = std::chrono::steady_clock::now();
            auto end = std::chrono::steady_clock::now();
            auto millis = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
            // auto millis = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            std::ofstream fileOUT("dynamic.csv", std::ios::app);
            // std::cout << millis.count() << std::endl;
            // fileOUT << val << ',' << cont << ',' << millis.count() << '\n';
            fileOUT << val << ';' << cont << ';' << mil << ';' << millis.count() << ';' << res << ';' << output << '\n';

            fileOUT.flush();
            fileOUT.close();
        }
    }
    // getchar();
    return 0;
}
