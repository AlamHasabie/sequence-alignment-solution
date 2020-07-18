#ifndef ALIGNER_HPP
#define ALIGNER_HPP

#include "profile.hpp"
#include "dictionary.hpp"

#include <vector>
#include <utility>

class Aligner {

    public :

        Aligner(SequenceDictionary* s);
        int get_pairwise_score(Profile* s1, Profile* s2);
        int get_profile_score(Profile *s1);
        Profile* global_align(Profile** align, int n_profiles);
        Profile* pairwise_align(Profile* p1, Profile *p2);


    private :
        SequenceDictionary* s;
        int get_profile_column_score(std::string& s1, std::string& s2);
		void get_left_score(Profile *s1, Profile *s2, std::vector<int>& column_score, std::pair<int,int>& start_point, std::pair<int,int>& end_point);
		void get_right_score(Profile *s1, Profile *s2, std::vector<int>& column_score, std::pair<int,int>& start_point, std::pair<int,int>& end_point);
        void brute_align(Profile *p_row, Profile *p_col, std::pair<int,int>& start_point, std::pair<int,int>& end_point, std::vector<char>& directions);
};

#endif