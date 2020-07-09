#include "dictionary.hpp"
#include <fstream>
#include <iostream>


SequenceDictionary::SequenceDictionary(std::string alphabet_file, std::string score_file){

    std::ifstream afile(alphabet_file.c_str());
    std::ifstream sfile(score_file.c_str());

    while(std::getline(afile, this->alphabet));
    this->alphabet_to_int = new std::map<char,int>;

    for(int i = 0 ; i < this->alphabet.length(); i++){
        (*(this->alphabet_to_int))[this->alphabet[i]] = i;
    }

    this->score_matrix = new int*[this->alphabet.length()];
    for(int i = 0 ; i < this->alphabet.length(); i++){
        this->score_matrix[i] = new int[this->alphabet.length()];
        for(int j = 0; j < this->alphabet.length(); j++){
            sfile >> score_matrix[i][j];
        }
    }
}

int SequenceDictionary::getScore(char c1, char c2){
    return this->score_matrix[(*(this->alphabet_to_int))[c1]][(*(this->alphabet_to_int))[c2]];
}


std::string SequenceDictionary::getAlphabet(){
    return this->alphabet;
}