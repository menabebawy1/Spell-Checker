//Mena Bebawy
//This program uses double hashing to implement a spell checker

#include "quadratic_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

void MakeDictionary(const string &dictionary_filename, HashTableDouble<string> &words)
{
    words.MakeEmpty(); //empty the hashtable

    string line;
    ifstream file(dictionary_filename); //ifstream the given file
    // Read the file line-by-line:
    while (file >> line) //as long as there are more lines to be read
    {
        if (line == "") //if we have an empty line, do nothing
        {
            continue;
        }

        words.Insert(line); //Otherwise insert the words into the table
    }
}

void Clean(string &word) //cleans the given word (i.e. removes all non alphabet charachters before and after the word + sets all letters to lowercase)
{
    while (!isalpha(word[word.length() - 1]) || word[word.length() - 1] == '\n') //while the last letter of the word is not an alphabetical character or is a new line
    {
        word.erase(word.length() - 1, 1); //remove one charachter starting at the end of the word
    }
    while (!isalpha(word[0])) //while the first chrachter is not alphabetical
    {
        word.erase(0, 1); //remove the first charachter
    }
    for (size_t i = 0; i < word.length(); i++) ///traverse the word
    {
        word[i] = tolower(word[i]); //if a charachter is captial --> make it small case
    }
}

void correctWord(const string &word, const HashTableDouble<string> &dictionary)
{
    string combination;

    //Case A --> Adding one character in any possible position
    for (size_t i = 0; i < word.length() + 1; i++) //the number of possible places to insert a letter is 1 more than the number of letters in the word
    {                                              //so we traverse the word n+1 times where n is the number of letters in the word
        for (int j = 97; j < 123; j++)             //for each location that we select, insert all possible letters in the alphabet which span 97-123 in ASCII
        {
            combination = word.substr(0, i) + char(j) + word.substr(i, word.length()); //This string splits the word in 2, the letters before the location of the charachter, and the etters after the location of the charachter. Between that we add the actual charachter.
            if (dictionary.Contains(combination))                                      //If our dictionary has the new combination
            {
                cout << combination << endl;
            }
        }
    }

    //Case B --> Removing one character from the word
    for (size_t i = 0; i < word.length(); i++) //traverse the word
    {
        combination = word;
        if (dictionary.Contains(combination.erase(i, 1))) //If our dictionary has the new combination which is 1 deleted letter at location i
        {
            cout << combination << endl;
        }
    }

    //Case C --> Swapping adjacent characters in the word
    for (size_t i = 0; i < word.length() - 1; i++)
    {
        combination = word;
        swap(combination[i], combination[i + 1]); //We swap the letters at the location we specify
        if (dictionary.Contains(combination))     //If our dictionary has the new combination
        {
            cout << combination << endl;
        }
    }

    //Case D --> Swapping each charachter with the alphabet
    for (size_t i = 0; i < word.length(); i++)
    {
        for (int j = 97; j < 123; j++)
        {
            combination = word;
            combination[i] = char(j);             //We swap the letters at the location we specify
            if (dictionary.Contains(combination)) //If our dictionary has the new combination
            {
                cout << combination << endl;
            }
        }
    }
}

void SpellChecker(const HashTableDouble<string> &dictionary, const string &document_filename)
{
    int wrong = 0;
    int lineNumber = 1;
    int wordNumber = 0;
    string line;
    ifstream file(document_filename); //ifstream the given file
    // Read the file line-by-line:
    while (getline(file, line)) //as long as there are more lines to be read
    {
        if (line == "") //if we have an empty line, do nothing
        {
            continue;
        }
        wordNumber = 0;
        lineNumber++;
        stringstream ss(line);         //Otherwise string stream the line we have
        while (getline(ss, line, ' ')) //Read each word up until we have a space
        {
            wordNumber++;
            Clean(line); //clean the word
            if (dictionary.Contains(line))
            {
            }
            else
            {
                wrong++;
                cout << "On line " << lineNumber << " word number " << wordNumber << " is INCORRECT. Word: " << line << endl;
                cout << "Did you mean? " << endl;
                correctWord(line, dictionary); //If the word is not found, check cases A, B, and C.
                cout << endl;
            }
        }
    }

    cout << wrong << " incorrect words" << endl;
}
int testSpellingWrapper(int argument_count, char **argument_list)
{
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary;
    MakeDictionary(dictionary_filename, dictionary);
    SpellChecker(dictionary, document_filename);

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
             << endl;
        return 0;
    }

    testSpellingWrapper(argc, argv);

    return 0;
}
