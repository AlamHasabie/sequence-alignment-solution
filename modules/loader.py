import os


class Loader :
	
	
	def file_abs(self, filepaths) : 
		abs_filepaths = []
		dirpath = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
		for filepath in filepaths :
			abs_filepaths.append(os.path.join(dirpath, filepath))
			
		return abs_filepaths
		
		
	def load_sequence(self, filepath) :
		with open(filepath) as f :
			content = f.read().splitlines()
			string = ""
			for line in content[1:] :
				string += line
			
		return string
		
	def load_sequences(self, filepaths) :
		sequences = []
		abs_filepaths = self.file_abs(filepaths)
		for filepath in filepaths :
			sequences.append(self.load_sequence(filepath))
		
		return sequences
	