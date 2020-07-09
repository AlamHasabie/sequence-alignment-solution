#ifndef ALIGNER_HPP
#define ALIGNER_HPP

#include "profile.hpp"
#include "dictionary.hpp"

#include <vector>
#include <utility>

class Aligner {

    public :

        Aligner(SequenceDictionary* s);
        int get_score(Profile* s1, Profile* s2);
        Profile* global_align(Profile** align, int n_profiles);

    private :
        SequenceDictionary* s;
        int get_profile_score(std::string& s1, std::string& s2);
        void brute_align(Profile *p_row, Profile *p_col, std::pair<int,int>& start_point, std::pair<int,int>& end_point, std::vector<char>& directions);
};

#endif