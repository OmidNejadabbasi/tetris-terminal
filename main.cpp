#include <iostream>

using namespace std;

wstring tetrominos[7];

int Rotate(int px, int py, int r)
{
    switch (r % 4)
    {
    case 0:
        return 4 * py + px;
    case 1:
        return 12 + py - (px * 4);
    case 2:
        return 15 - (py * 4) - px;
    case 3:
        return 3 - py + (px * 4);
    }
    return 0;
}

int main(int argc, const char **argv)
{

    // Create assets
    tetrominos[0].append(L"..X.");
    tetrominos[0].append(L"..X.");
    tetrominos[0].append(L"..X.");
    tetrominos[0].append(L"..X.");

    tetrominos[1].append(L"..X.");
    tetrominos[1].append(L".XX.");
    tetrominos[1].append(L".X..");
    tetrominos[1].append(L"....");

    tetrominos[2].append(L".X..");
    tetrominos[2].append(L".XX.");
    tetrominos[2].append(L"..X.");
    tetrominos[2].append(L"....");

    tetrominos[3].append(L"....");
    tetrominos[3].append(L".XX.");
    tetrominos[3].append(L".XX.");
    tetrominos[3].append(L"....");

    tetrominos[4].append(L"..X.");
    tetrominos[4].append(L".XX.");
    tetrominos[4].append(L"..X.");
    tetrominos[4].append(L"....");

    tetrominos[5].append(L"....");
    tetrominos[5].append(L".XX.");
    tetrominos[5].append(L"..X.");
    tetrominos[5].append(L"..X.");

    tetrominos[6].append(L"....");
    tetrominos[6].append(L"..XX");
    tetrominos[6].append(L"..X.");
    tetrominos[6].append(L"..X.");

    return 0;
}