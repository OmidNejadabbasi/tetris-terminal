#include <iostream>

using namespace std;

wstring tetrominos[7];
int fieldWidth = 12;
int fieldHeight = 18;
unsigned char *pField = nullptr;

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

    pField = new unsigned char[fieldHeight * fieldWidth];
    for (int x = 0; x < fieldWidth; x++)
        for (int y = 0; y < fieldHeight; y++)
            pField[y * fieldWidth + x] = (x == 0 || x == fieldWidth - 1 || y == fieldHeight - 1) ? 9 : 0;

    return 0;
}