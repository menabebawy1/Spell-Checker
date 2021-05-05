// Mena Bebawy
//This program checks if a set of words is a subset of another

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename)
{
    // cout << "TestFunctionForHashTables..." << endl;
    // cout << "Words filename: " << words_filename << endl;
    // cout << "Query filename: " << query_filename << endl;
    hash_table.MakeEmpty();

    string line;
    ifstream file(words_filename); //ifstream the given file
    // Read the file line-by-line:
    while (getline(file, line)) //as long as there are more lines to be read
    {
        if (line == "") //if we have an empty line, do nothing
        {
            continue;
        }
        hash_table.Insert(line); //Otherwise insert the line into the table
    }

    cout << "number_of_elements: " << hash_table.returnCurrentSize() << endl;
    cout << "size_of_table: " << hash_table.returnArraySize() << endl;
    cout << "load_factor: " << (float)hash_table.returnCurrentSize() / (float)hash_table.returnArraySize() << endl;
    cout << "average_collisions: " << (float)hash_table.returnNumberOfCollisions() / (float)hash_table.returnCurrentSize() << endl;
    cout << "total_collisions: " << hash_table.returnNumberOfCollisions() << endl;
    cout << endl;

    ifstream file2(query_filename); //ifstream the given file
    // Read the file line-by-line:
    while (getline(file2, line)) //as long as there are more lines to be read
    {
        if (line == "") //if we have an empty line, do nothing
        {
            continue;
        }
        string found = hash_table.Contains(line) ? "Found" : "Not_Found"; //Determine if we found the word or not
        cout << line << " " << found << " " << hash_table.returnNumberOfProbes() << endl;
    }
}

// namespace PROTECTED {

int testHashingWrapper(int argument_count, char **argument_list)
{
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 0;
    if (argument_count == 5)
    {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }

    if (param_flag == "linear")
    {
        //cout << "Linear:" << endl;
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "quadratic")
    {
        //cout << "Quadratic:" << endl;
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "double")
    {

        //cout << "Double:" << endl;
        HashTableDouble<string> double_probing_table;
        double_probing_table.SetR(R);
        cout << "r_value: " << double_probing_table.returnRValue() << endl;
        TestFunctionForHashTable(double_probing_table, words_filename,
                                 query_filename);
    }
    else
    {
        cout << "Unknown hash type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 4 and argc != 5)
    {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}

//};  // namespace PROTECTED
