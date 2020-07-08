import numpy as np

# Create profile from sequence when loading sequence for aligning
def sequence_to_profile(sequence) :		
	return np.array([np.array([x]) for x in sequence])
	