from modules import loader, profile, alphabet_dict, aligner




files = ['../data/nucleotide/MT019529.1.fasta', '../data/nucleotide/MT450872.1.fasta']
dictionary = alphabet_dict.AlphabetInfo()
loader = loader.Loader()
sequences = loader.load_sequences(files)
profiles = [profile.sequence_to_profile(sequence) for sequence in sequences]
nucleotide_aligner = aligner.Aligner(dictionary)
print(nucleotide_aligner.get_score(profiles[0], profiles[1]))
