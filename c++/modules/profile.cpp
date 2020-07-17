#include "profile.hpp"
Profile::Profile(std::string sequence){
    this->str_array_length = sequence.length(); 
    this->str_array = new std::string[sequence.length()];

    for(int i = 0 ; i< this->str_array_length ; i++){
        this->str_array[i] = sequence[i];
    }
}

Profile::Profile(){
    //do nothing
}

Profile::~Profile(){

}
