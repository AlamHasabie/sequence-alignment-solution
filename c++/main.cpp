#include "modules/loader.hpp"
#include "modules/dictionary.hpp"
#include "modules/aligner.hpp"
#include <iostream>

int main(){

    std::string* files;
    std::string filename;
    int n_files;


    std::cout << "Input number of files : ";
    std::cin >> n_files;
    files = new std::string[n_files];
    for(int i = 0 ; i < n_files; i++){
        std::cout << "Input file-" << i << " : ";
        std::cin >> filename;
        files[i] = filename;
    }
    
    // For testing purposes
    Profile* profiles[2];
    std::string test_files[] = {"../data/nucleotide/MT019529.1.fasta", "../data/nucleotide/MT044258.1.fasta"};
    
    std::string score_file = "constants/score.txt";
    std::string alphabet_file = "constants/alphabet.txt";

    SequenceDictionary* sd = new SequenceDictionary(alphabet_file, score_file);
    for(int i = 0 ; i < 2; i++){
       profiles[i] = FASTASequenceLoader::load(test_files[i],sd->getAlphabet());
    }
    Aligner aligner(sd);
    
    std::cout << "Score : " << aligner.get_pairwise_score(profiles[0], profiles[1]) << std::endl;
    return 0;
}
