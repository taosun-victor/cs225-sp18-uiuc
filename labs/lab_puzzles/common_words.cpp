/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        for (size_t j=0; j<words.size(); j++){
            file_word_maps[i][words[j]] += 1;
        }

    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */

    for (size_t i=0; i<file_word_maps.size(); i++){
        for (std::pair<const std::string, unsigned int> & key_val : file_word_maps[i]){
            common[key_val.first] += 1;
        }
    } 

}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    vector<string> out_potential;
    /* Your code goes here! */
    unsigned num_files = file_word_maps.size();
    for (const std::pair<std::string, unsigned int> & key_val : common){
    //for (auto & key_val : common){
        if (key_val.second == num_files){
            out_potential.push_back(key_val.first);
        }
    }

    for (size_t i=0; i<out_potential.size(); i++){
        unsigned validate = 0;
        for (size_t j=0; j<file_word_maps.size(); j++){
            map<std::string, unsigned int>::const_iterator lookup = file_word_maps[j].find(out_potential[i]);
            //auto lookup = file_word_maps[j].find(out_potential[i]);
            if (lookup->second >= n)
                validate += 1;
        }
        if (validate == num_files)
            out.push_back(out_potential[i]);
    }

    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
