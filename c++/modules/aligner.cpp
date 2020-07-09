#include "aligner.hpp"
#include <vector>
#include <iostream>
#include <algorithm>


Aligner::Aligner(SequenceDictionary *s){
    this->s = s;
}

int Aligner::get_score(Profile& s1, Profile& s2){

    int n_row = s1.str_array_length + 1;
    int n_col = s1.str_array_length + 1;

    int prof_len_row = s1.str_array[0].length();
    int prof_len_col = s2.str_array[0].length();

    int current_score[n_col];
    int new_score[n_col];
    int score;
    std::vector<int> square_score_list;
    for(int i = 0 ; i < n_col; i++){
        current_score[i] = 0;
        new_score[i] = 0;
    } 
    for (int row = 0 ; row < n_row ; row++){
        std::cout << "\rRow " << row + 1 << " of " << n_row;
        for (int col = 0; col < n_col ; col++){
            square_score_list.clear();
            if((col==0)&&(row==0)){
                square_score_list.push_back(0);
            } else {
                if(col>0){
                    // Fetch score from left
                    std::string gap = "";
                    for (int k = 0; k < prof_len_row; k++){gap+="_";}
                    score = this->get_profile_score(gap, s2.str_array[col-1]);
                    score += new_score[col-1];
                    square_score_list.push_back(score);
                }

                if(row > 0){
                    // Fetch score from above
                    std::string gap = "";
                    for (int k = 0; k < prof_len_col; k++){gap+="_";}
                    score = this->get_profile_score(gap, s1.str_array[row-1]);
                    score += current_score[col];
                    square_score_list.push_back(score);
                }

                if((col>0)&&(row>0)){
                    score = this->get_profile_score(s1.str_array[row-1], s2.str_array[col-1]);
                    score += current_score[col-1];
                    square_score_list.push_back(score);
                }
            }
            new_score[col] = (int) *(std::max_element(square_score_list.begin(), square_score_list.end()));
        }
        for(int i = 0 ; i < n_col ; i++){
            current_score[i] = new_score[i];
        }
    }
    return current_score[n_col-1];
}

int Aligner::get_profile_score(std::string& s1, std::string& s2){
    std::string scoring_string = s1 + s2;
    int score = 0;

    int string_len = scoring_string.length();
    for(int i = 0 ; i < string_len ; i++){
        for(int j = i+1; j < string_len ; j++){
            score += this->s->getScore(scoring_string[i], scoring_string[j]);
        }
    }
    return score;
}