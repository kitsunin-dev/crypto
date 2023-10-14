#include "encrypt.h"

std::array<int, 2> findIndex(std::array<std::array<QChar, 5>, 5>& square, QChar& letter)
{
    if (letter == 'J')
        return findIndex(square, letter = 'I');
    else
        for (int i = 0; i < 25; i++)
            if (square[i / 5][i % 5] == letter)
                return {i / 5, i % 5};

    return {};
}

QString Encrypt::atbash()
{
    QString result;
    initText = initText.toUpper().replace(" ", "");

    for (auto it = initText.begin(); it != initText.end(); it++)
        for (int i = 0; i < alphabet.size(); i++)
            if (alphabet[i] == *it)
            {
                result.append(alphabet[alphabet.size() - i - 1]);
                break;
            }

    return result;
}

QString Encrypt::caesar(int shift)
{
    QString result;
    initText = initText.toUpper().replace(" ", "");

    for (auto it = initText.begin(); it != initText.end(); it++)
        for (int i = 0; i < alphabet.size(); i++)
            if (alphabet[i] == *it)
            {
                result.append(alphabet[(i + shift) % alphabet.size()]);
                break;
            }

    return result;
}


QString Encrypt::playfair(QString key)
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
    }

    QString result;
    for (auto it = pairs.begin(); it != pairs.end(); it++)
        result.append((*it)[0]).append((*it)[1]);

    return result;
}

QString Encrypt::vigenere(QString key)
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
    for (int i = 0; i < initText.size(); i++)
    {
        for (int j = 0; j < alphabet.size(); j++)
            if (alphabet[j] == initText[i])
                a = j;
            else if (alphabet[j] == keyText[i])
                b = j;
        result.append(square[a][b]);
    }

    return result;
}
