#include "crypt.h"

std::array<int, 2> Crypt::findIndex(std::array<std::array<QChar, 5>, 5>& square, QChar& letter)
{
    if (letter == 'J')
        return findIndex(square, letter = 'I');

    for (int i = 0; i < 25; i++)
        if (square[i / 5][i % 5] == letter)
            return {i / 5, i % 5};
}

QString Crypt::atbash()
{
    QString result;
    initText = initText.toUpper().replace(" ", "");

    for (auto it = initText.begin(); it != initText.end(); it++)
        result.append(alphabet[alphabet.size() - alphabet.indexOf(*it) - 1]);

    return result;
}

QString Crypt::caesar(int shift, bool flag)
{
    QString result;
    initText = initText.toUpper().replace(" ", "");

    int curr = 0;
    for (auto it = initText.begin(); it != initText.end(); it++)
    {
        curr = alphabet.indexOf(*it);
        if (flag)
            result.append(alphabet[(curr + shift) % alphabet.size()]);
        else
            result.append(alphabet[(curr - shift) % alphabet.size()]);
    }

    return result;
}

QString Crypt::playfair(QString key, bool flag)
{
    QString tempAlphabet = alphabet;

    initText = initText.toUpper().replace(" ", "");
    key = key.toUpper().replace(" ", "");

    std::vector<std::array<QChar, 2>> pairs;
    std::array<std::array<QChar, 5>, 5> square;

    for (int i = 0; i < initText.size() - 1; i++)
        if (initText[i] == initText[i+1] && i % 2 == 0)
        {
            initText.insert(i+1, 'X');
            i++;
        }

    if (initText.size() % 2 != 0)
        initText.append('X');

    pairs.resize(initText.size() / 2);

    for (int i = 0; i < initText.size(); i++)
        pairs[i / 2][i % 2] = initText[i];

    QString keyUnique = "";
    for (auto it = key.begin(); it != key.end(); it++)
        if (!keyUnique.contains(*it))
        {
            keyUnique.append(*it);
            tempAlphabet.replace(*it, "");
        }

    keyUnique.append(tempAlphabet);

    if (keyUnique.contains("I") && keyUnique.contains("J"))
            keyUnique.replace("J", "");

    for (int i = 0; i < keyUnique.size(); i++)
        square[i / 5][i % 5] = keyUnique[i];

    std::array<int, 2> a, b;
    for (auto it = pairs.begin(); it != pairs.end(); it++)
    {
        a = findIndex(square, (*it)[0]);
        b = findIndex(square, (*it)[1]);

        if (flag)
            if (a[0] == b[0])
            {
                if (a[1] == 4)
                    (*it)[0] = square[a[0]][0];
                else
                    (*it)[0] = square[a[0]][a[1]+1];

                if (b[1] == 4)
                    (*it)[1] = square[b[0]][0];
                else
                    (*it)[1] = square[b[0]][b[1]+1];
            }
            else if (a[1] == b[1])
            {
                if (a[0] == 4)
                    (*it)[0] = square[0][a[1]];
                else
                    (*it)[0] = square[a[0]+1][a[1]];

                if (b[0] == 4)
                    (*it)[1] = square[0][b[1]];
                else
                    (*it)[1] = square[b[0]+1][b[1]];
            }
            else
            {
                (*it)[0] = square[a[0]][b[1]];
                (*it)[1] = square[b[0]][a[1]];
            }
        else
            if (a[0] == b[0])
            {
                if (a[1] == 0)
                    (*it)[0] = square[a[0]][4];
                else
                    (*it)[0] = square[a[0]][a[1]-1];

                if (b[1] == 0)
                    (*it)[1] = square[b[0]][4];
                else
                    (*it)[1] = square[b[0]][b[1]-1];
            }
            else if (a[1] == b[1])
            {
                if (a[0] == 0)
                    (*it)[0] = square[4][a[1]];
                else
                    (*it)[0] = square[a[0]-1][a[1]];

                if (b[0] == 0)
                    (*it)[1] = square[4][b[1]];
                else
                    (*it)[1] = square[b[0]-1][b[1]];
            }
            else
            {
                (*it)[0] = square[a[0]][b[1]];
                (*it)[1] = square[b[0]][a[1]];
            }
    }

    QString result;
    for (auto it = pairs.begin(); it != pairs.end(); it++)
        result.append((*it)[0]).append((*it)[1]);

    return result;
}

QString Crypt::vigenere(QString key, bool flag)
{
    initText = initText.toUpper().replace(" ", "");
    key = key.toUpper().replace(" ", "");

    QString tempAlphabet = alphabet;
    std::array<QString, 26> square;
    QChar replaceLetter;
    for (int i = 0; i < 26; i++)
    {
        square[i] = tempAlphabet;
        replaceLetter = tempAlphabet.front();
        tempAlphabet.remove(replaceLetter).append(replaceLetter);
    }

    QString keyText;
    for (int i = 0; i < initText.size(); i++)
        keyText.append(key[i % key.size()]);

    int a, b;
    QString result;

    if (flag)
        for (int i = 0; i < initText.size(); i++)
        {
            a = alphabet.indexOf(keyText[i]);
            b = alphabet.indexOf(initText[i]);
            result.append(square[a][b]);
        }
    else
        for (int i = 0; i < initText.size(); i++)
        {
            a = alphabet.indexOf(keyText[i]);
            b = square[a].indexOf(initText[i]);
            result.append(alphabet[b]);
        }

    return result;
}
