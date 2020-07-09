#ifndef PROFILE_HPP
#define PROFILE_HPP
#include <string>



class Profile {

    public :    
        Profile(std::string sequence);
        Profile(Profile& profile_1, Profile& profile_2);
        ~Profile();
        int get_profile_score();
        void set_profile_score(int score);
        std::string* str_array;
        int str_array_length;
    
    private :
        int score;
};

#endif