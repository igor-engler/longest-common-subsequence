#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <list>

// 16mb
// g++ -O3 -Wl,--stack,67108864 -o recursive.exe recursive.cpp

int lcs_recursive(std::string str1, std::string str2, int size_str1, int size_str2, std::string &output, int &cont, int &mil)
{
    cont++;

    if (cont >= 100000000)
    {
        cont = 0;
        mil++;
    }
    if (size_str1 == 0 || size_str2 == 0)
    {
        return 0;
    }
    if (str1[size_str1 - 1] == str2[size_str2 - 1])
    {
        output.insert(0, 1, str1[size_str1 - 1]);
        return 1 + lcs_recursive(str1, str2, size_str1 - 1, size_str2 - 1, output, cont, mil);
    }
    else
    {
        // strings temporarias
        std::string output1, output2;
        int len1 = lcs_recursive(str1, str2, size_str1 - 1, size_str2, output1, cont, mil);
        int len2 = lcs_recursive(str1, str2, size_str1, size_str2 - 1, output2, cont, mil);
        output.insert(0, len1 > len2 ? output1 : output2); // adiciona o caractere correto na frente da string
        return std::max(len1, len2);
        // return std::max(lcs_recursive(str1, str2, size_str1, size_str2 - 1, output), lcs_recursive(str1, str2, size_str1 - 1, size_str2, output));
    }
}

int main()
{
    // contador de comparações
    // std::list<std::string> dirlist({"Strings10.txt", "Strings12.txt", "Strings15.txt", "Strings17.txt", "Strings20.txt", "Strings25.txt"});
    std::list<std::string> dirlist({"18.txt", "19.txt", "20.txt", "21.txt", "22.txt", "23.txt", "24.txt"});
    for (std::string val : dirlist)
    {
        // std::cout << val << std::endl;
        for (int i = 0; i < 4; i++)
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
            auto res = lcs_recursive(entrada1, entrada2, entrada1.length(), entrada2.length(), output, cont, mil);
            auto end = std::chrono::steady_clock::now();
            auto millis = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
            std::ofstream fileOUT("recursive.csv", std::ios::app);
            fileOUT << val << ',' << cont << ',' << mil << ',' << millis.count() << ',' << res << ',' << output << ',' << '\n';

            fileOUT.flush();
            fileOUT.close();
        }
    }
    return 0;
}
