import os

class AlphabetInfo :

	def __init__(self, dirpath='constants'):
		
		self.__dirpath = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
		self.__dirpath = os.path.join(self.__dirpath, dirpath)
		self.__load_alphabet()
		self.__load_score()
	
	def __load_score(self):
		
		score_filename = "score"
		score_filename = os.path.join(self.__dirpath, score_filename)
		with open(score_filename) as f :
			content = f.read().splitlines()
			f.close()
			
		n_alphabet = len(self.__alphabet_dict)
		self.__score_matrix = [[int(x) for x in content[i].split(' ')] for i in range(n_alphabet)]
	
	def __load_alphabet(self):
		alphabet_filename = "alphabet"
		alphabet_filename = os.path.join(self.__dirpath, alphabet_filename)
		with open(alphabet_filename) as f :
			content = f.readline()
			f.close()
		
		self.__alphabet_dict = {}
		for i in range(len(content)) :
			self.__alphabet_dict[content[i]] = i
		
		self.__alphabet_dict['_'] = len(content)