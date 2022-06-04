#include <string>
#include <sstream>
#include <iostream>

#include "parser.h"

#define IS_TRUE(x)                                                                    \
    {                                                                                 \
        if (!(x))                                                                     \
            std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; \
        else                                                                          \
            std::cout << __FUNCTION__ << " is passed " << std::endl;                  \
    }

std::string test_parser(std::string min,
                        std::string hour,
                        std::string dom,
                        std::string mon,
                        std::string dow,
                        std::string command)
{
    Parser parser(min, hour, dom, mon, dow, command);
    return parser.getOutput();
}

// all *
void test1()
{
    std::string pattern[6];
    std::stringstream ssin("* * * * * /usr/bin/find");
    int i = 0;
    while (ssin.good() && i < 6)
    {
        ssin >> pattern[i];
        i++;
    }

    IS_TRUE(test_parser(pattern[0],
                        pattern[1],
                        pattern[2],
                        pattern[3],
                        pattern[4],
                        pattern[5]) == "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59\n0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23\n1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31\n1 2 3 4 5 6 7 8 9 10 11 12\n1 2 3 4 5 6 7\n/usr/bin/find\n");
}

// coma
void test2()
{
    std::string pattern[6];
    std::stringstream ssin("1,2,15,30,45 12,14,16 1,2 6 1,3,5,7 /usr/bin/find");
    int i = 0;
    while (ssin.good() && i < 6)
    {
        ssin >> pattern[i];
        i++;
    }

    IS_TRUE(test_parser(pattern[0],
                        pattern[1],
                        pattern[2],
                        pattern[3],
                        pattern[4],
                        pattern[5]) == "1 2 15 30 45\n12 14 16\n1 2\n6\n1 3 5 7\n/usr/bin/find\n");
}

// dash "-"
void test3()
{
    std::string pattern[6];
    std::stringstream ssin("15-20 12-14 1-2 6 2-4 /usr/bin/find");
    int i = 0;
    while (ssin.good() && i < 6)
    {
        ssin >> pattern[i];
        i++;
    }

    IS_TRUE(test_parser(pattern[0],
                        pattern[1],
                        pattern[2],
                        pattern[3],
                        pattern[4],
                        pattern[5]) == "15 16 17 18 19 20\n12 13 14\n1 2\n6\n2 3 4\n/usr/bin/find\n");
}

// slash "/"
void test4()
{
    std::string pattern[6];
    std::stringstream ssin("*/15 12/2 1/5 10/11 */4 /usr/bin/find");
    int i = 0;
    while (ssin.good() && i < 6)
    {
        ssin >> pattern[i];
        i++;
    }

    IS_TRUE(test_parser(pattern[0],
                        pattern[1],
                        pattern[2],
                        pattern[3],
                        pattern[4],
                        pattern[5]) == "0 15 30 45\n12 14 16 18 20 22\n1 6 11 16 21 26 31\n10\n1 5\n/usr/bin/find\n");
}

// all combined
void test5()
{
    std::string pattern[6];
    std::stringstream ssin("*/15 0-6 * 1,2-4,5-7 4 /usr/bin/find");
    int i = 0;
    while (ssin.good() && i < 6)
    {
        ssin >> pattern[i];
        i++;
    }

    IS_TRUE(test_parser(pattern[0],
                        pattern[1],
                        pattern[2],
                        pattern[3],
                        pattern[4],
                        pattern[5]) == "0 15 30 45\n0 1 2 3 4 5 6\n1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31\n1 2 3 4 5 6 7\n4\n/usr/bin/find\n");
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
}