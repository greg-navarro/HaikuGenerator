/*
Name: Gregory Litman-Navarro
Class: CECS 282
Instructor: Minhthong Nguyen
Purpose of the program: To generate a random haiku using words provided by words.txt
Last updated: 9/15/19
*/

#include <iostream>
#include <fstream>
#include <random>
using namespace std;
int countSyllables(string word);
int isVowelOrConsonant(char letter);
string makeHaiku(string fileLocation);
bool exceptionsExist(string word);
int findSize(string file);
string getRandomWord(string file);

// Generates random haiku.
int main()
{
    string const fileLocation = "words.txt";

    srand(time(0));     //seed random numbers for the getRandomWord() function

    string newHaiku = makeHaiku(fileLocation);      // generate haiku

    cout << newHaiku << endl;
    return 0;
}


// This function takes uses a list of words (found in the directory at fileLocation)
// and picks words at random in order to generate an original haiku, which it returns
// as a string.
string makeHaiku(string fileLocation)
{
    int syllableCount = 0;
    string haiku = "";
    string currentWord;
    // syllables in current word
    int currentSyllables;
    // number of syllables in current line
    int target = 5;

    while(syllableCount < target)       // build haiku
    {
        currentWord = getRandomWord(fileLocation);
        currentSyllables = countSyllables(currentWord);
        if(syllableCount + currentSyllables <= target)
        {
            haiku = haiku + currentWord + " ";
            syllableCount = syllableCount + currentSyllables;
        }

        if(syllableCount == 12)         // end of second line
        {
            target = 17;
            haiku = haiku + '\n';
        }
        else if(syllableCount == 5)     // end of first line
        {
            target = 12;
            haiku = haiku + '\n';
        }
    }
    haiku = haiku + '\n';               // end of third line
    return haiku;
}

// This function accepts a word (as a string) and uses the patterns of vowels
// and consonants to count the syllables in the word.
// This function accepts a word (as a string) and uses the patterns of vowels
// and consonants to count the syllables in the word.
int countSyllables(string word)
{
    bool containsLetters = false;
    int sizeOfWord = word.length();
    int letterType;
    int syllableCount = 0;
    bool inSyllable = false;

    for (int i = 0; i < sizeOfWord; i++)
    {
        letterType = isVowelOrConsonant(word[i]);
        if (letterType > 0)
            containsLetters = true;
        if (letterType == 1 && inSyllable == false)
        {
            syllableCount++;
            inSyllable = true;
        } else if (letterType == 0 && inSyllable == true)
        {
            inSyllable = false;
        }
    }

    if(exceptionsExist(word))       // check for patterns that fool this function
        syllableCount--;

    if(containsLetters == true and syllableCount == 0)      // every word has at least one syllable
        syllableCount = 1;

    return syllableCount;
}

// Returns 0 for consonant, 1 for vowel, and -1 for a non-letter character.
int isVowelOrConsonant(char letter)
{
    int returnCode = -1;
    char vowels [] = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};
    char consonants [] = {'q', 'Q', 'w', 'W', 'r', 'R', 't', 'T', 'p', 'P', 's',
                          'S', 'd', 'D', 'f', 'F', 'g', 'G', 'h', 'H', 'j', 'J',
                          'k', 'K', 'l', 'L', 'z', 'Z', 'x', 'X', 'c', 'C', 'v',
                          'V', 'b', 'B', 'n', 'N', 'm', 'M'};

    for (int i = 0; i < 12; i++)
    {
        if (letter == vowels[i])
        {
            return 1;
        }
    }
    for (int i = 0; i < 40; i++)
    {
        if (letter == consonants[i])
        {
            return 0;
        }
    }
    return returnCode;
}

// This function has several trends that serve as exceptions to the
// typical rules of phonetics.  If this function returns true, countSyllables(word)
// will subtract one from its syllable count.
bool exceptionsExist(string word)
{
    bool decrement = false;
    int sizeOfWord = word.length();
    int lastIndex = sizeOfWord - 1;


    if(word[lastIndex] == 'e' && sizeOfWord > 2)
    {
        decrement = true;
        if(word[lastIndex-1] == 'l' && isVowelOrConsonant(word[lastIndex-2]) == 0)
        {
            decrement = false;
        }
    } // endif 'e'
    else if(word[lastIndex-1] == 'e' && word[lastIndex] == 's' && sizeOfWord > 3)
    {
        if(isVowelOrConsonant(word[lastIndex-2]) != 0 || isVowelOrConsonant(word[lastIndex-3]) != 0)
        {
            decrement = true;
        }
    }// endif 'es'
    else if(word[lastIndex-2] == 'e' && word[lastIndex-1] == 'l' && word[lastIndex] == 'y')
    {
        decrement = true;
    }// endif 'ely'

    return decrement;
}

// This function finds the number of lines in a given file.
// It is used to by the getRandomWord() function to generate in-
// bounds random numbers.
int findSize(string file)
{
    fstream in;
    in.open(file);
    int count = 0;
    string container;
    while(in.good())
    {
        in >> container;
        count++;
    }
    in.close();
    return count;
}

// Given a the name of a file that contains a list of words,
// this function selects a random word from the list and
// returns it to its caller.
string getRandomWord(string file)
{
    int wordsInFile = findSize(file);
    fstream in;
    in.open(file);
    int count = 0;
    string nextWord;
    int interval = rand() % wordsInFile + 1;  // generates an in-bounds line number to pick a word from
    int index = 0;
    while (index < interval)
    {
        if(in.good())
        {
            in >> nextWord;
        }
        else
        {
            in.close();
            in.open(file);
        }
        index++;
    }
    in >> nextWord;
    in.close();
    return nextWord;
}

