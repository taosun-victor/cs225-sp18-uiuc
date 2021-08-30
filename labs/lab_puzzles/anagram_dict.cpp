/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict( string& filename)
{
    /* Your code goes here! */
    ifstream words_file(filename);
    string word;
    vector<std::string> words;

    if (words_file.is_open()){
        while (getline(words_file, word)){
            words.push_back(word);
        }
    }

    for (unsigned i=0; i<words.size(); i++){
        string tmp_s = words[i];
        std::sort(tmp_s.begin(), tmp_s.end());

        auto lookup = dict.find(tmp_s);
        if (lookup == dict.end()){
            vector<string> tmp_v;
            tmp_v.push_back(words[i]);
            dict.insert(std::pair<string, vector<string>>(tmp_s, tmp_v));
        }
        else{
            dict[tmp_s].push_back(words[i]);
        }
    }


}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */

    for (unsigned i=0; i<words.size(); i++){
        string tmp_s = words[i];
        std::sort(tmp_s.begin(), tmp_s.end());

        auto lookup = dict.find(tmp_s);
        if (lookup == dict.end()){
            vector<string> tmp_v;
            tmp_v.push_back(words[i]);
            dict.insert(std::pair<string, vector<string>>(tmp_s, tmp_v));
        }
        else{
            dict[tmp_s].push_back(words[i]);
        }
    }


}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string tmps = word;
    std::sort(tmps.begin(), tmps.end());
    auto lookup = dict.find(tmps);
    if (lookup != dict.end() && lookup->second.size()>1)
        return lookup->second;
    else
        return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> anags_all;
    for (auto & key_val : dict){
        if (key_val.second.size() > 1)
            anags_all.push_back(key_val.second);
    }

    return anags_all;
}
