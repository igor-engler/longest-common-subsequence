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
            cont++;
            if (i == 0 || j == 0)
                table[i][j] = 0;
            else if (str1[i - 1] == str2[j - 1])
                table[i][j] = table[i - 1][j - 1] + 1;
            else
                table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
        }
    }

    // para printar a sequencia
    int index = table[size_str1][size_str2];

    int i = size_str1, j = size_str2;
    while (i > 0 && j > 0)
    {
        if (str1[i - 1] == str2[j - 1])
        {
            output.insert(0, 1, str1[i - 1]);
            i--;
            j--;
        }
        else if (table[i - 1][j] > table[i][j - 1])
        {
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
    std::list<std::string> dirlist({"Strings12.txt", "Strings15.txt", "Strings17.txt", "Strings20.txt", "Strings25.txt", "Strings10000.txt"});

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
            auto elapsed = std::chrono::steady_clock::now();
            auto millis = std::chrono::duration_cast<std::chrono::microseconds>(elapsed - start).count();
            std::ofstream fileOUT("dynamic.txt", std::ios::app);
            // std::cout << "File " << val << "done" << std::endl;
            fileOUT << "----------------------------------------------------------------" << std::endl;
            fileOUT << "File: " << val << std::endl;
            fileOUT << "LCS: " << output << " of size " << res << std::endl;
            fileOUT << "Comparisons: " << cont << std::endl;
            // fileOUT << "100 million * " << mil << std::endl;
            fileOUT << "Time elapsed: " << millis << " ms" << std::endl;
            fileOUT.close();
        }
    }
    //getchar();
    return 0;
}
