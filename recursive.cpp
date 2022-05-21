#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <chrono>

// g++ -Wl,--stack,4194304 -o main main.cpp

int lcs_recursive(std::string str1, std::string str2, int size_str1, int size_str2, std::string &output)
{
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
        return 1 + lcs_recursive(str1, str2, size_str1 - 1, size_str2 - 1, output);
    }
    else
    {
        // strings temporarias
        std::string output1, output2;
        int len1 = lcs_recursive(str1, str2, size_str1 - 1, size_str2, output1);
        int len2 = lcs_recursive(str1, str2, size_str1, size_str2 - 1, output2);
        output.insert(0, len1 > len2 ? output1 : output2); // adiciona o caractere correto na frente da string
        return std::max(len1, len2);
        // return std::max(lcs_recursive(str1, str2, size_str1, size_str2 - 1, output), lcs_recursive(str1, str2, size_str1 - 1, size_str2, output));
    }
}

int main()
{
    std::ifstream file("Strings25.txt");
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
    auto res = lcs_recursive(entrada1, entrada2, entrada1.length(), entrada2.length(), output);
    auto elapsed = std::chrono::steady_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed - start).count();

    std::cout << "LCS: " << output << " of size " << res << std::endl;
    std::cout << "Time elapsed: " << millis << " ms" << std::endl;

    return 0;
}