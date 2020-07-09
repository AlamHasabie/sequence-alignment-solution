#include "loader.hpp"
#include <fstream>
#include <iostream>


Profile* FASTASequenceLoader::load(std::string filename, std::string alphabet){
    std::ifstream infile(filename.c_str());
    std::string line;
    std::string sequence = "";
    bool header = true;
    while(std::getline(infile, line)){
        if(header){
            header = false;
        } else {
            sequence += line;
        }
    }

    sequence = FASTASequenceLoader::sanitize(sequence, alphabet);
    return new Profile(sequence);
}


std::string FASTASequenceLoader::sanitize(std::string& sequence, std::string& alphabet){
    std::string clean_string = "";
    size_t found;
    for(int i = 0 ; i < sequence.length() ; i ++){
        found = alphabet.find(sequence[i]);
        if(found!=std::string::npos){
            clean_string.push_back(sequence[i]);
        }
    }

    return clean_string;
}