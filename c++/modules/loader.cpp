#include "loader.hpp"
#include <fstream>
#include <iostream>


Profile* FASTASequenceLoader::load(std::string filename){
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
    return new Profile(sequence);
}