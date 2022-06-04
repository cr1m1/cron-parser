#include <iostream>
#include <sstream>
#include "parser.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("error: string pattern is not specified.");
        return 0;
    }

    // splitting argument into array
    string pattern[6];
    stringstream ssin(argv[1]);
    int i = 0;
    while (ssin.good() && i < 6)
    {
        ssin >> pattern[i];
        i++;
    }

    for (int i = 0; i < 6; i++)
    {
        if (pattern[i].empty())
        {
            printf("error: not enough arguments.\nexample: \"*/15 0 1,15 * 1-5 /usr/bin/find\"");
        }
    }

    Parser parser(
        pattern[0],
        pattern[1],
        pattern[2],
        pattern[3],
        pattern[4],
        pattern[5]);
    parser.print();
}