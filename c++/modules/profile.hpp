#ifndef PROFILE_HPP
#define PROFILE_HPP
#include <string>
#include <vector>


class Profile {

    public :    
        Profile();
        Profile(std::string sequence);
        Profile(Profile* profile_1, Profile* profile_2, std::vector<char> reverse_direction);
        ~Profile();
        std::string* str_array;
        int str_array_length;
};

#endif