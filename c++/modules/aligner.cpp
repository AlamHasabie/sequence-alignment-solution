#include "aligner.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>


std::pair<char, int> getMaxPair(std::vector<std::pair<char, int> >& list);

Aligner::Aligner(SequenceDictionary *s){
    this->s = s;
}

std::pair<int,int> Aligner::get_middle_node(Profile *s1, Profile *s2, std::pair<int,int>& start_point, std::pair<int,int> end_point){
    std::vector<int> column_score;
    int max_score;
    int max_row;
    int middle_column = (start_point.second + end_point.second)/2;
    int n_rows = end_point.first - start_point.first + 1;
    for(int i = 0 ;  i < n_rows; i++){
        column_score.push_back(0);
    }
    this->get_middle_column_score(s1, s2, middle_column, column_score, start_point, end_point);
    max_row = -1;
    for(int i = 0; i < n_rows; i++){
        if(max_row==-1){
            max_row = i;
            max_score = column_score[i];
            continue;
        }

        if(max_score < column_score[i]){
            max_row = i;
            max_score = column_score[i];
        }
    }

    return std::make_pair(start_point.first + max_row, middle_column);
}

void Aligner::get_middle_column_score(Profile *s1, Profile *s2, int mid_column, std::vector<int>& column_score, std::pair<int, int>& start_point, std::pair<int,int>& end_point){

    int middle_column = (start_point.second + end_point.second)/2;
    int n_rows = end_point.first - start_point.first + 1;

    std::pair<int,int> left_score_end = std::make_pair(end_point.first, middle_column);
    std::pair<int,int> right_score_start = std::make_pair(start_point.first, middle_column);

    this->get_left_score(s1, s2, column_score, start_point, left_score_end);
    this->get_right_score(s1, s2, column_score, right_score_start, end_point);
}

void Aligner::get_left_score(Profile *s1, Profile *s2, std::vector<int>& column_score, std::pair<int,int>& start_point, std::pair<int,int>& end_point){
	
	int score;
    int max_score;
    bool is_init_score;

	int start_row = start_point.first;
	int start_col = start_point.second;
	int end_row = end_point.first;
	int end_col = end_point.second;
	
	int n_row = end_row - start_row + 1;
	int n_col = end_col - start_col + 1;
	
	int row_profile_str_len = s1->str_array[0].length();
	int col_profile_str_len = s2->str_array[0].length();
	
	int current_score[n_col];
	int new_score[n_col];
	
	std::string row_gap = "";
	std::string col_gap = "";
	
	for (int i = 0 ; i < row_profile_str_len ; i++){ row_gap += "_";}
	for (int i = 0 ; i < col_profile_str_len ; i++){ col_gap += "_";}
	
	for (int col = 0 ; col < n_col ; col++){
		new_score[col] = 0;
		current_score[col] = 0;
	}
	for (int row = start_row ; row <= end_row ; row++){
		for (int col = start_col ; col <= end_col ; col++){
			std::cout << "\rLeft score : Row " << row << " of " << end_row;
            is_init_score = false;
			if((row==start_row)&&(col==start_col)){
                max_score = 0;
                is_init_score = true;
			}
			if(row > start_row){
				score = this->get_profile_column_score(s1->str_array[row-1], col_gap) + current_score[col-start_col];
				if(!is_init_score){
                    max_score = score;
                    is_init_score = true;
                } else {
                    if(score > max_score){
                        max_score = score;
                    }
                }
			}
			
			if (col > start_col) {
				score = this->get_profile_column_score(row_gap, s2->str_array[col-1]) + new_score[col-start_col-1];
				if(!is_init_score){
                    max_score = score;
                    is_init_score = true;
                } else {
                    if(score > max_score){
                        max_score = score;
                    }
                }
			}

			if ((row > start_row)&&(col > start_col)) {
				score = this->get_profile_column_score(s1->str_array[row-1], s2->str_array[col-1]) + current_score[col-start_col-1];
				if(!is_init_score){
                    max_score = score;
                    is_init_score = true;
                } else {
                    if(score > max_score){
                        max_score = score;
                    }
                }
			}
			new_score[col-start_col] = max_score;
		}
		
		for (int col = 0 ; col < n_col ; col++){
			current_score[col] = new_score[col];
		}
		column_score[row-start_row] += current_score[n_col-1];
	}
	std::cout << std::endl;
}

void Aligner::get_right_score(Profile *s1, Profile *s2, std::vector<int>& column_score, std::pair<int, int>& start_point, std::pair<int,int>& end_point){
	
	int score;
    int max_score;
    bool is_init_score;

	int start_row = start_point.first;
	int start_col = start_point.second;
	int end_row = end_point.first;
	int end_col = end_point.second;
	
	int n_row = end_row - start_row + 1;
	int n_col = end_col - start_col + 1;
	
	int row_profile_str_len = s1->str_array[0].length();
	int col_profile_str_len = s2->str_array[0].length();
	
	int current_score[n_col];
	int new_score[n_col];
	
	std::string row_gap = "";
	std::string col_gap = "";

	
	for (int i = 0 ; i < row_profile_str_len ; i++){ row_gap += "_";}
	for (int i = 0 ; i < col_profile_str_len ; i++){ col_gap += "_";}
	
	for (int col = 0 ; col < n_col ; col++){
		new_score[col] = 0;
		current_score[col] = 0;
	}
	for (int row = end_row ; row >= start_row ; row--){
		for (int col = end_col ; col >= start_col ; col--){
			std::cout << "\rRight score : Row " << end_row - row << " of " << end_row - start_row;
            is_init_score = false;
			if((row==end_row)&&(col==end_col)){ 
                max_score = 0;
                is_init_score = true;
			}
			if(row < end_row){
				score = this->get_profile_column_score(s1->str_array[row], col_gap) + current_score[col-start_col];
				if(!is_init_score){
                    max_score = score;
                    is_init_score = true;
                } else {
                    if(score > max_score){
                        max_score = score;
                    }
                }
			}
			
			if (col < end_col) {
				score = this->get_profile_column_score(row_gap, s2->str_array[col]) + new_score[col-start_col+1];
				if(!is_init_score){
                    max_score = score;
                    is_init_score = true;
                } else {
                    if(score > max_score){
                        max_score = score;
                    }
                }
			}

			if ((row < end_row)&&(col < end_col)) {
				score = this->get_profile_column_score(s1->str_array[row], s2->str_array[col]) + current_score[col-start_col+1];
				if(!is_init_score){
                    max_score = score;
                    is_init_score = true;
                } else {
                    if(score > max_score){
                        max_score = score;
                    }
                }
			}
			new_score[col-start_col] = max_score;
		}
		
		for (int col = 0 ; col < n_col ; col++){
			current_score[col] = new_score[col];
		}
		
		column_score[row-start_row] += current_score[0];
	}
	std::cout << std::endl;
} 

int Aligner::get_pairwise_score(Profile* s1, Profile* s2){

	int start_row, start_col = 0;
    int end_row = s1->str_array_length;
    int end_col = s1->str_array_length;

	std::vector<int> row_score;
	for(int i = 0 ; i <= end_row - start_row ; i++){
		row_score.push_back(0);
	}
	
	std::pair<int,int> start_point = std::make_pair(start_row, start_col);
	std::pair<int,int> end_point = std::make_pair(end_row, end_col);
	
	this->get_left_score(s1, s2, row_score, start_point, end_point);
	
	return row_score[end_row];
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
    // Testing on getting middle nodes
    std::pair<int,int> start_point = std::make_pair(0,0);
    std::pair<int,int> end_point = std::make_pair(1000,1000);
    std::pair<int,int> middle_node = this->get_middle_node(align[0],align[1],start_point,end_point);

    std::cout << "Middle node : " << middle_node.first << "," << middle_node.second <<  std::endl;
    return 0;
}

void Aligner::recursive_pairwise_align(Profile *p1, Profile *p2, std::vector<char>& directions, std::pair<int,int>& startpoint, std::pair<int,int>& endpoint){

    std::cout << "Recursive , start point " << startpoint.first << " , " << startpoint.second << std::endl;
    std::cout << "Recursive , end point " << endpoint.first << " , " << endpoint.second << std::endl;

    int row_threshold = 10;
    if(endpoint.first - startpoint.first < row_threshold){
        this->brute_align(p1, p2, startpoint, endpoint, directions);
    }

    else {
        std::pair<int,int> middle_node;
        middle_node = this->get_middle_node(p1, p2, startpoint, endpoint);
        std::cout << "Middle node : " << middle_node.first << " , " << middle_node.second << std::endl;
        this->recursive_pairwise_align(p1,p2, directions, middle_node, endpoint);
        this->recursive_pairwise_align(p1, p2, directions, startpoint, middle_node);
    }
}

Profile* Aligner::pairwise_align(Profile* p1, Profile *p2){
    
    // Do brute_force if col_wide = 1
    // For now, testing using brute force first
    std::vector<char> backtrack;
    std::pair<int, int> start_point = std::make_pair(0,0);
    std::pair<int, int> end_point = std::make_pair(100,100);
    this->recursive_pairwise_align(p1, p2, backtrack,start_point,end_point);
    std::vector<char>::reverse_iterator it;
    std::cout << backtrack.size() << std::endl;
    for(it = backtrack.rbegin(); it != backtrack.rend(); it++){
        std::cout << *it << "->";
    }
}

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
        std::cout << "\rPairwise align - row " << row  << " of " << end_row - start_row;
        for(int col = start_col; col <= end_col ; col++){
            square_score_list.clear();
            if((row==start_row)&&(col==start_col)){
                square_score_list.push_back(std::make_pair('t',0));
            } else {
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

                if((row>start_row)&&(col>start_col)){
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

    std::cout << std::endl;
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

