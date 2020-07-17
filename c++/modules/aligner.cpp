#include "aligner.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>


std::pair<char, int> getMaxPair(std::vector<std::pair<char, int> >& list);

Aligner::Aligner(SequenceDictionary *s){
    this->s = s;
}

int Aligner::get_pairwise_score(Profile* s1, Profile* s2){

    int n_row = s1->str_array_length + 1;
    int n_col = s1->str_array_length + 1;

    int prof_len_row = s1->str_array[0].length();
    int prof_len_col = s2->str_array[0].length();

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
                    score = this->get_profile_column_score(gap, s2->str_array[col-1]);
                    score += new_score[col-1];
                    square_score_list.push_back(score);
                }

                if(row > 0){
                    // Fetch score from above
                    std::string gap = "";
                    for (int k = 0; k < prof_len_col; k++){gap+="_";}
                    score = this->get_profile_column_score(gap, s1->str_array[row-1]);
                    score += current_score[col];
                    square_score_list.push_back(score);
                }

                if((col>0)&&(row>0)){
                    score = this->get_profile_column_score(s1->str_array[row-1], s2->str_array[col-1]);
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

int Aligner::get_profile_column_score(std::string& s1, std::string& s2){
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



Profile* Aligner::global_align(Profile** align, int n_profiles){


}


// Linear memory alignment

Profile* Aligner::pairwise_align(Profile* p1, Profile *p2){
    
    // Do brute_force if col_wide = 1
    // For now, testing using brute force first
    std::vector<char> backtrack;
    std::pair<int, int> start_point = std::make_pair(0,0);
    std::pair<int, int> end_point = std::make_pair(3,2);

    std::cout << std::endl;
    this->brute_align(p1, p2, start_point, end_point, backtrack);

    for (int i = 0 ; i < backtrack.size() ; i++){
        std::cout << backtrack[i];
    }
    std::cout << std::endl;


}

// Do brute alignment
// If 

void Aligner::brute_align(
    Profile *p_row, 
    Profile *p_col, 
    std::pair<int,int>& start_point,
    std::pair<int,int>& end_point,
    std::vector<char>& directions){

        int square_score;
        int start_row = start_point.first;
        int start_col = start_point.second;
        int end_row = end_point.first;
        int end_col = end_point.second;

        int row_prof_len = p_row->str_array[0].length();
        int col_prof_len = p_col->str_array[0].length();


        std::string row_gap = "";
        std::string col_gap = "";

        for(int i = 0 ; i < row_prof_len ; i++){row_gap+='_';}
        for(int i = 0 ; i < col_prof_len ; i++){col_gap+='_';}

        std::vector<std::pair<char,int> > square_score_list;
        int max_score[end_row-start_row+1][end_col-start_col+1];
        char backtrack[end_row-start_row+1][end_col-start_col+1];

        for(int row = start_row; row <= end_row ; row++){
            std::cout << "\rPairwise align - row " << row + 1 << " of " << end_row - start_row;
            for(int col = start_col; col <= end_col ; col++){
                square_score_list.clear();
                if((row==start_row)&&(col==start_col)){
                    square_score_list.push_back(std::make_pair('t',0));
                } else {
                    // Fetch from left
                    if (col > start_col){
                        square_score = this->get_profile_column_score(row_gap, p_col->str_array[col-1]);
                        square_score += max_score[row-start_row][col-start_col-1];
                        square_score_list.push_back(std::make_pair('l',square_score));
                    }

                    // Fetch from above
                    if (row > start_row){
                        square_score = this->get_profile_column_score(col_gap, p_row->str_array[row-1]);
                        square_score += max_score[row-start_row-1][col-start_col];
                        square_score_list.push_back(std::make_pair('u', square_score));
                    }

                    if((row>0)&&(col>0)){
                        square_score = this->get_profile_column_score(p_row->str_array[row-1], p_col->str_array[col-1]);
                        square_score += max_score[row-start_row-1][col-start_col-1];
                        square_score_list.push_back(std::make_pair('d', square_score));
                    }
                }

                std::pair<char,int> max_pair = getMaxPair(square_score_list);
                backtrack[row-start_row][col-start_col] = max_pair.first;
                max_score[row-start_row][col-start_col] = max_pair.second;
            }
        }


        // Build the string
        int current_row = end_row - start_row;
        int current_col = end_col - start_col;
        char c = backtrack[current_row][current_col];
        while(c!='t'){
            directions.push_back(c);
            switch (c)
            {
            case 'l':
                current_col-=1;
                break;
            
            case 'u' :
                current_row-=1;
                break;

            case 'd' :
                current_row-=1;
                current_col-=1;
                break;
            
            default:
                break;
            }
            c = backtrack[current_row][current_col];
        }
        // Terminate
        directions.push_back('t');
}

// Get max pair from a vector of pairs
std::pair<char, int> getMaxPair(std::vector<std::pair<char, int> >& list){
    char direction = '_';
    int max_value;
    for (std::vector<std::pair<char,int> >::iterator i = list.begin(); i != list.end() ; i++){
        if(direction = '_'){
            direction = i->first;
            max_value = i->second;
        } else {
            if (max_value < i->second){
                direction = i->first;
                max_value = i->second;
            }
        }
    }

    return std::make_pair(direction, max_value);
}

