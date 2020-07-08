#include <string>



class Profile {

    public :    
        Profile(std::string sequence);
        Profile(Profile& profile_1, Profile& profile_2);
        ~Profile();

        std::string* str_array;
        int str_array_length;
};