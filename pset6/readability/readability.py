from cs50 import get_string


def main():
    # text is the text that user typed in 
    text = get_string("Text: ")
    # total_letter is an integer that contains how many letters are in the text
    total_letter = conta(text)
    # total_word is an integer that shows how many words are in the text
    total_words = count_words(text)
    # total_sentences is an integer that shows how many sentences are in the text
    total_sentences = count_sentences(text)
    
    L = (total_letter * 100) / total_words
    S = (total_sentences * 100) / total_words
    index = round((0.0588 * L) - (0.296 * S) - 15.8)
  
    if index < 1:
        print("Before Grade 1")
        
    elif index >= 16:
        print("Grade 16+")

    else:
        print("Grade " + '{:d}'.format(index))


# Count the number of letters


def conta(text):
    # counter_letter counts how many letters are in text
    count_letter = 0
    for letter in text:
        if letter.isalpha():
            count_letter += 1
        
    return count_letter


# Count the number of words in text

def count_words(text):
    # counter counts how many words are in the text
    counter = 0
    started = True
    for letter in text:
        if started and letter.isalpha():
            counter += 1
            started = False
        if letter.isspace():
            started = True
    return counter
    
    
# Count the number of sentences in a phrase

def count_sentences(text):
    # counter counts how many sentences are in text
    counter = 0
    started = True
    for letter in text:
        if started and letter in [".", "!", "?"]:
            counter += 1
            started = False
        
        if letter.isalpha():
            started = True
    return counter


main()

