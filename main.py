from modules import loader, profile, alphabet_dict




files = ['data/nucleotide/MT019529.1.fasta', 'data/nucleotide/MT450872.1.fasta']
dictionary = alphabet_dict.AlphabetInfo()
loader = loader.Loader()
sequences = loader.load_sequences(files)
profile = [profile.sequence_to_profile(sequence) for sequence in sequences]
