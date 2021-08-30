/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    Dict<string, int> hashTable(512);
    while (infile.good()){
        string word = infile.getNextWord();
        hashTable[word]++;
    }

    vector<pair<string, int>> ret;
    typename Dict<string, int>::iterator it;
    for (it = hashTable.begin(); it != hashTable.end(); it++ ) {
        if (it->second >= threshold)
            ret.push_back(*it);
    }


    //(void) threshold; // prevent warnings... When you implement this function, remove this line.
    return ret;
}
