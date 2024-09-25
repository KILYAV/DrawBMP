#include "DrawBMP.h"

#include <iostream>

int main(int argc, char* argv[])
{
    constexpr UINT COUNT_ARGC = 2;
    if (COUNT_ARGC != argc)
        throw std::invalid_argument{"Too many/few arguments"};

    DrawBMP drawBMP;
    drawBMP.OpenBMP(argv[1]);
    drawBMP.DisplayBMP();
    drawBMP.CloseBMP();
}
