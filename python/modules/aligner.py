import sys
class Aligner :

    def __init__(self,  alphabet_info) :
        self.__alphabet_info = alphabet_info

    def get_score(self, profile_1, profile_2) :
        n_row = len(profile_1)
        n_col = len(profile_2)

        # Get profile el
        profile_1_n_el = len(profile_1[0])
        profile_2_n_el = len(profile_2[0])
        current_score = [0 for _ in range(n_col+1)]
        for i in range(n_row+1) :
            sys.stdout.write("\rRow " + str(i+1) + " of " + str(n_row+1))
            sys.stdout.flush()
            new_score = []
            for j in range(n_col+1) :
                square_score = []
                if i == 0 and j == 0 :
                    square_score.append(0)
                else :
                    # Get from above
                    # Gap on the column profile (profile_2)
                    # Add score current_score
                    if i>0 : 
                        score = self.__score_profile(profile_1[i-1], ['_'] * profile_2_n_el)
                        score += current_score[j]
                        square_score.append(score)
                    
                    # Get from left
                    # Use previous square score
                    # Gap on the row profile (profile_1)
                    if j>0 :
                        score = self.__score_profile(['_'] * profile_1_n_el, profile_2[j-1])
                        score += new_score[j-1]
                        square_score.append(score)

                    # Diagonal
                    # Get score from previous
                    if i>0 and j>0:
                        score = self.__score_profile(profile_1[i-1], profile_2[j-1])
                        score += current_score[j-1]
                        square_score.append(score)

                new_score.append(max(square_score))
            current_score = new_score
        sys.stdout.write("\n")
        sys.stdout.flush()
        return current_score[-1]
            

                    





    def __score_profile(self, profile_1, profile_2) :
        combined_profile = profile_1 + profile_2
        score = 0
        combined_profile_length = len(combined_profile)
        for i in range(combined_profile_length) :
            for j in range(i+1,combined_profile_length):
                score += self.__alphabet_info.get_score(combined_profile[i], combined_profile[j])
    
        return score
                
