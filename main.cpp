#include <iostream>
#include <windows.h>
#include <thread>
#include <vector>
using namespace std;

wstring tetrominos[7];
int fieldWidth = 12;
int fieldHeight = 18;
unsigned char *pField = nullptr;

int nScreenWidth = 80;
int nScreenHeight = 30;

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

bool DoesPieceFit(int idTetromino, int rotation, int posX, int posY)
{
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
        {
            int pi = Rotate(x, y, rotation);

            int fi = (posY + y) * fieldWidth + posX + x;

            if (posX + x >= 0 && posX + x < fieldWidth)
            {
                if (posY + y < fieldHeight && posY + y >= 0)
                {
                    if (tetrominos[idTetromino][pi] == L'X' && pField[fi] != 0)
                    {
                        return false;
                    }
                }
            }
        }

    return true;
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

    wchar_t *screen = new wchar_t[nScreenWidth * nScreenHeight];
    for (int i = 0; i < nScreenHeight * nScreenWidth; i++)
        screen[i] = L' ';

    HANDLE Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                               0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(Console);

    DWORD dwBytesWritten = 0;

    int currentPiece = 4;
    int currentRotation = 0;
    int currentX = fieldWidth / 2;
    int currentY = 0;

    bool bKey[4];
    bool rotateHold = false;

    int speed = 20;
    int speedCounter = 0;
    bool forceThePieceDown = false;

    vector<int> lines;
    bool gameOver = false;
    while (!gameOver)
    {

        // GAME TIMING =======================================
        this_thread::sleep_for(50ms);
        speedCounter++;
        forceThePieceDown = (speedCounter == speed);

        // INPUT =============================================
        for (int k = 0; k < 4; k++) //     R   L   D  Z
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)"\x27\x25\x28Z"[k])) != 0;

        // GAME LOGIC ========================================
        if (bKey[1])
            if (DoesPieceFit(currentPiece, currentRotation, currentX - 1, currentY))
                currentX--;
        if (bKey[0])
            if (DoesPieceFit(currentPiece, currentRotation, currentX + 1, currentY))
                currentX++;
        if (bKey[2])
            if (DoesPieceFit(currentPiece, currentRotation, currentX, currentY + 1))
                currentY++;
        if (bKey[3])
        {

            if (!rotateHold && DoesPieceFit(currentPiece, currentRotation + 1, currentX, currentY))
            {
                currentRotation++;
            }
            rotateHold = true;
        }
        else
            rotateHold = false;

        if (forceThePieceDown)
        {
            if (DoesPieceFit(currentPiece, currentRotation, currentX, currentY + 1))
                currentY++;
            else
            {

                // Lock the current piece down
                for (int px = 0; px < 4; px++)
                    for (int py = 0; py < 4; py++)
                        if (tetrominos[currentPiece][Rotate(px, py, currentRotation)] == L'X')
                        {
                            pField[(currentY + py) * fieldWidth + currentX + px] = currentPiece + 1;
                        }
                // check if we got a line
                for (int py = 0; py < 4; py++)
                {
                    if (currentY + py < fieldHeight - 1)
                    {
                        bool line = true;
                        for (int px = 1; px < fieldWidth - 1; px++)
                            line &= (pField[(currentY + py) * fieldWidth + px] != 0);

                        if (line)
                        {
                            for (int px = 1; px < fieldWidth - 1; px++)
                                pField[(currentY + py) * fieldWidth + px] = 8;

                            lines.push_back(currentY + py);
                        }
                    }
                }

                // choose the next piece
                currentY = 0;
                currentX = fieldWidth / 2 - 1;
                currentPiece = rand() % 7;
                currentRotation = 0;

                // if game over
                gameOver = !DoesPieceFit(currentPiece, currentRotation, currentX, currentY);
            }
            speedCounter = 0;
        }
        // RENDER ============================================
        // Draw the screen
        for (int x = 0; x < fieldWidth; x++)
        {
            for (int y = 0; y < fieldHeight; y++)
            {
                screen[(y + 2) * nScreenWidth + x + 2] = L" ABCDEFG=#"[pField[y * fieldWidth + x]];
            }
        }

        // Draw the current piece
        for (int px = 0; px < 4; px++)
            for (int py = 0; py < 4; py++)
                if (tetrominos[currentPiece][Rotate(px, py, currentRotation)] == L'X')
                {
                    screen[(currentY + py + 2) * nScreenWidth + currentX + px + 2] = currentPiece + 65;
                }

        if (!lines.empty())
        {
            WriteConsoleOutputCharacterW(Console, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);

            this_thread::sleep_for(400ms); // delay a bit
            for (auto &v : lines)
                for (int px = 1; px < fieldWidth - 1; px++)
                {
                    for (int py = v; py > 0; py--)
                    {
                        pField[py * fieldWidth + px] = pField[(py - 1) * fieldWidth + px];
                    }
                    pField[px] = 0;
                }
            lines.clear();
        }
        // Disply console frame
        WriteConsoleOutputCharacterW(Console, screen, nScreenHeight * nScreenWidth, {0, 0}, &dwBytesWritten);
    }
    return 0;
}