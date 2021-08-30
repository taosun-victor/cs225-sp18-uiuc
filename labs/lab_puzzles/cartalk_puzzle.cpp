/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */
#include <iostream>
#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream words_file(word_list_fname);
    string word;
    vector<std::string> words;

    if (words_file.is_open()){
        while (getline(words_file, word)){
            words.push_back(word);
        }
    }

/*
    for (size_t i=0; i<words.size(); i++){
        std::cout << words[i] << std::endl;
    }
*/

    for (size_t i=0; i<words.size(); i++){
        std::string test0 = words[i];
        if (test0.size() >2 ){
            std::string test1 = test0.substr(1, test0.size()-1);
            std::string test2 = test0.substr(2, test0.size()-2);
            test2 = test0[0] + test2;

            //cout << test0 << " "<< test1 << " " << test2 << endl;
            if (d.homophones(test0, test1) && (d.homophones(test1, test2)) )
                ret.push_back(std::make_tuple(test0, test1, test2));    
        }
    }


    return ret;
}
