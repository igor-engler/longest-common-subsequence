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

    // se o tamanho de uma das strings for 0, retorna 0
    if (size_str1 == 0 || size_str2 == 0)
    {
        return 0;
    }
    // se os ultimos caracteres são iguais, remove eles
    // e encontra a subsequencia do restante da astring
    if (str1[size_str1 - 1] == str2[size_str2 - 1])
    {
        // insere o caractere igual na frente da string
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
    std::list<std::string> dirlist({"Strings10.txt", "Strings12.txt", "Strings15.txt", "Strings17.txt", "Strings20.txt", "Strings25.txt"});

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

            // std::cout << entrada1 << std::endl;
            // std::cout << entrada2 << std::endl;

            std::string output = "";
            auto start = std::chrono::steady_clock::now();
            auto res = lcs_recursive(entrada1, entrada2, entrada1.length(), entrada2.length(), output, cont, mil);
            auto elapsed = std::chrono::steady_clock::now();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed - start).count();
            std::ofstream fileOUT("recursive.txt", std::ios::app);
            // std::cout << "File " << val << "done" << std::endl;
            fileOUT << "----------------------------------------------------------------" << std::endl;
            fileOUT << "File: " << val << std::endl;
            fileOUT << "LCS: " << output << " of size " << res << std::endl;
            fileOUT << "Comparisons: " << cont << std::endl;
            fileOUT << "100 million * " << mil << std::endl;
            fileOUT << "Time elapsed: " << millis << " ms" << std::endl;
            fileOUT.close();
        }
    }
    // getchar();
    return 0;
}
