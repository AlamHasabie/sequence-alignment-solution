#include "profile.hpp"
Profile::Profile(std::string sequence){
    this->str_array_length = sequence.length(); 
    this->str_array = new std::string[sequence.length()];

    for(int i = 0 ; i< this->str_array_length ; i++){
        this->str_array[i] = sequence[i];
    }
    this->score = 0;
}

Profile::~Profile(){

}

int Profile::get_profile_score(){
    return this->score;
}

void Profile::set_profile_score(int score){ 
    this->score = score;
}
