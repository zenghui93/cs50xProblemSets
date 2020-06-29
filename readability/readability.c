#include<cs50.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>

  
int main(void)
{
    
    //Count the number of letters in a phrase
    int conta(string t, int length);
    //Count the number of words in a phrase
    int count_words(string t, int length);
    //Count the number of sentences in a phrase
    int count_sentences(string t, int length);
    string text = get_string("Text: ");
    int size = strlen(text);
    //printf(" Hello my Darling! The length of the text is %i.\n", size);
  
    int total_letter = conta(text, size);
    //printf("%i letter(s)\n", total_letter);
    int total_words = count_words(text, size);
    //printf("%i word(s)\n", total_words);
    int total_sentences = count_sentences(text, size);
    //printf("%i sentence(s)\n", total_sentences);
    
    float L = (total_letter * 100) / (float)total_words;
    float S = (total_sentences * 100) / (float)total_words;
    float index = round((0.0588 * L) - (0.296 * S) - 15.8);
    //printf("index is %i\n",(int)index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
        
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)index);
    }
   
        
 
     
}

//Count the number of letters 
int conta(string t, int length)
{
    int count_letter = 0;
    
    for (int i = 0; i < length; i++)
    {
        
        if (islower(t[i]) || isupper(t[i]))
        {
            count_letter++;
        }
    }
    return count_letter;

}


//Count the number of words in a phrase
int count_words(string t, int length)
{
    int counter = 0;
    bool started = true;
    for (int i = 0; i < length; i++)
    {
        
        if (started && isalpha(t[i]))
        {
            counter++;
            started = false;
        }
        if ((int)t[i] == 32)
        {
            started = true;
        }
    }   
    return counter;
    
}//count_words

//Count the number of sentences in a phrase
int count_sentences(string t, int length)
{
    int counter = 0;
    bool started = true;
    for (int i = 0; i < length; i++)
    {
        if (started && ((int)t[i] == 46 || (int)t[i] == 33 || (int)t[i] == 63))
        {
            counter++;
            started = false;
        }
        if (isalpha(t[i]))
        {
            started = true;
        }
    }
    
    return counter;
}//count_sentences


