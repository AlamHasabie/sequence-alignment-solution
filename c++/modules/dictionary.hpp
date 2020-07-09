#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <fstream>
#include <string>
#include <map>

class SequenceDictionary {

    public :
        SequenceDictionary(std::string alphabet_file, std::string score_file);
        int getScore(char c1, char c2);
        std::string getAlphabet();    
    private :
        std::string alphabet;
        int** score_matrix;
        std::map<char, int>* alphabet_to_int;
};

#endif