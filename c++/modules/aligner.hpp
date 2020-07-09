#ifndef ALIGNER_HPP
#define ALIGNER_HPP

#include "profile.hpp"
#include "dictionary.hpp"

class Aligner {

    public :

        Aligner(SequenceDictionary* s);
        int get_score(Profile& s1, Profile& s2);
        Profile* pairwise_align(Profile& s1, Profile& s2);

    private :
        SequenceDictionary* s;
        int get_profile_score(std::string& s1, std::string& s2);
};

#endif