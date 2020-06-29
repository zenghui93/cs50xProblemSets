from sys import argv
import csv


def main():
    # Open my text file 
    txtfile = open(argv[2])
    sequences = txtfile.readline()
    
    # Open my csv file and read as dict
    csvfile = open(argv[1]) 
    reader = csv.DictReader(csvfile)
    headers = reader.fieldnames
    
    # my_fields is the list of fieldnames in my first row
    my_fields = headers[1: len(headers)].copy()
    # frequencies is a list contaning the number of times a determinate STR is appeared consecutively in the dna in examine
    frequencies = count(sequences, my_fields)
    # found the match name
    found = False
    
    for row in reader:
        # match is the list of the fieldnames
        match = list(row.values())[1: len(row.values())]
        if match == frequencies:
            found = True
            name = row['name']
    
    if found == True:
        print(name)
    else:
        print("No match")
    
        
# s = sequences
def count_seq(seq, STR):
    # i is the index, it starts at index 0
    i = 0
    # counter counts how many times a specific STR is appeared in the dna string
    counter = 0
    start = False
    # frequencies is a list contaning how many times a specific STR is appeared in the dna string consecutively
    frequencies = []
    length_STR = len(STR)
    while True:
        if len(seq) - i >= length_STR:
            if seq[i: i + length_STR] == STR:
                counter += 1
                i += length_STR
                start = True
            elif start == True:
                frequencies.append(str(counter))
                start = False
                counter = 0
                i += 1
            else:
                i += 1
                counter = 0
        elif start == True:
            frequencies.append(str(counter))
            break
        else:
            break
 
    if len(frequencies) == 0:
        return 0
    else:
        return max(frequencies)        
    
    
def count(seq, fields):
    frequencies = []
    for f in fields:
        frequencies.append(count_seq(seq, f))
    return frequencies


main()