#include "profile.hpp"
Profile::Profile(std::string sequence){
    this->str_array_length = sequence.length(); 
    this->str_array = new std::string[sequence.length()];

    for(int i = 0 ; i< this->str_array_length ; i++){
        this->str_array[i] = sequence[i];
    }
}
Profile::Profile(Profile& profile_1, Profile& profile_2){


}
Profile::~Profile(){

}
