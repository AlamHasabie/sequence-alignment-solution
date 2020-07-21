#include "profile.hpp"
Profile::Profile(std::string sequence){
    this->str_array_length = sequence.length(); 
    this->str_array = new std::string[sequence.length()];

    for(int i = 0 ; i< this->str_array_length ; i++){
        this->str_array[i] = sequence[i];
    }
}

Profile::Profile(Profile* profile_1, Profile* profile_2, std::vector<char> reverse_direction){

    this->str_array_length = reverse_direction.size();
    this->str_array = new std::string[this->str_array_length];

    int row_profile_str_len = profile_1->str_array[0].length();
    int col_profile_str_len = profile_2->str_array[0].length();
    std::string row_gap, col_gap = "";
    for(int i = 0 ; i < row_profile_str_len ; i++){row_gap += "_";}
    for(int i = 0 ; i < col_profile_str_len ; i++){col_gap += "_";}

    int current_row = profile_1->str_array_length;
    int current_col = profile_2->str_array_length;

    for(int i = this->str_array_length-1 ; i >= 0; i--){
        switch (reverse_direction[i])
        {
        case 'd':
            current_row--;
            current_col--;
            this->str_array[i] = profile_1->str_array[current_row] + profile_2->str_array[current_col];
            break;

        case 'u' :
            current_row--;
            this->str_array[i] = profile_1->str_array[current_row] + col_gap;
            break;
        case 'l' : 
            current_col--;
            this->str_array[i] = row_gap + profile_2->str_array[current_col];
            break;
        }
    }
}

Profile::~Profile(){

}
