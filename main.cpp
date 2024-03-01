#include <iostream>
#include <fstream>
#include <vector>
#include "kmp.h"

using namespace std;

void inputRead(charArray& text, charArray& pattern, charArray& replacepattern)
{
    text.readFromFile("text_input_01.in");
    pattern.readFromFile("pattern_input_01.in");
    replacepattern.readFromFile("replacepattern_input_01.in");
}

void writeConsole(charArray& pattern, charArray& replacepattern, vector<unsigned long long> appearances)
{
    cout << "'" << pattern << "' appears " << appearances.size() << " times in the current input file." << endl;
    cout << "All appearances of '" << pattern << "' successfully replaced with '" << replacepattern << "'." << endl;
}

void writeOutput(charArray text, const char* filename)
{
    ofstream fos(filename);

    fos << text;
}

charArray replacePattern(charArray text, charArray pattern, charArray replacepattern, vector<unsigned long long> appearances)
{
    unsigned long long newtextlength = text.getLength() + (appearances.size()) * (replacepattern.getLength() - pattern.getLength());
    charArray newtext(newtextlength);
    unsigned long long api = 0, ini = 0;
    unsigned long long i = 0;
    while (i < newtext.getLength())
    {
        if (i != appearances[api])
        {
            newtext[i] = text[ini];
            ++ini;
        }
        else
        {
            unsigned long long newpi = 0;
            while (newpi < replacepattern.getLength())
            {
                newtext[i] = replacepattern[newpi];
                ++newpi;
                ++i;
            }
            --i;
            ini += pattern.getLength();
            if (api < appearances.size() - 1)
            {
                ++api;
                appearances[api] += api * (replacepattern.getLength() - pattern.getLength());
            }
        }
        ++i;
    }
    
    return newtext;
}

int main()
{
    charArray text, pattern, replacepattern;
    inputRead(text, pattern, replacepattern);

    vector<unsigned long long> appearances;
    text.searchKMP(pattern, appearances);
    writeConsole(pattern, replacepattern, appearances);

    charArray newtext = replacePattern(text, pattern, replacepattern, appearances);

    writeOutput(newtext, "output_01.out");

    return 0;
}
