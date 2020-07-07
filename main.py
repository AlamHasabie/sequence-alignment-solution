from modules import loader




files = ['data/nucleotide/MT019529.1.fasta']
loader = loader.Loader()
sequence = loader.load_sequences(files)