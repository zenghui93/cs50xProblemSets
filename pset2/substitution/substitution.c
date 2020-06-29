#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int keyValidate(string key);
    char substitute(char character, string key);
    int valid;

    //Check whether the user has inserted more than one command-line argument
    if (argc == 2)
    {
        //Check whether the key is valid
        valid = keyValidate(argv[1]);
        //If the key is valid then prompt the user for the Plaintext.
        if (valid == 0)
        {
            string plaintext = get_string("plaintext: ");
            int length = strlen(plaintext);
            char ciphertext[length + 1];

            for (int i = 0; i < length; i++)
            {
                //Check whether it is an alphabetic letter
                if (isalpha(plaintext[i]))
                {

                    ciphertext[i] = substitute(plaintext[i], argv[1]);
                }//Check whether it is an alphabetic letter
                else
                {
                    ciphertext[i] = plaintext[i];
                }

            }//for ciphertext
            ciphertext[length] = '\0';
            printf("ciphertext: %s\n", ciphertext);
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        valid = 1;
    }
    return valid;
}//main

int keyValidate(string key)
{
    int length = strlen(key);
    int valid = 0;
    //check key length
    if (length != 26)
    {
        printf("Key must contain 26 characters.\n");
        valid = 1;
    }
    //Check for non alphabetic characters
    bool alphabetic = true;
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            alphabetic = false;
        }
    }
    if (!alphabetic)
    {
        printf("Key must only contain alphabetic characters.\n");
        valid = 1;
    }
    //Check for repeated characters
    bool repeated = false;
    for (int i = 0; i < length; i++)
    {
        key[i] = toupper(key[i]);
    }
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (key[i] == key[j])
            {
                repeated = true;

            }
        }
    }
    if (repeated)
    {
        printf("Key must not contain repeated characters.\n");
        valid = 1;
    }

    return valid;
}//keyValidate

//Substitute for the corresponding character in the ciphertext
char substitute(char character, string key)
{
    int map = toupper(character) - 65;
    char coded = key[map];

    //printf("coded is %i %c\n",coded,coded);
    if (islower(character))
    {
        return coded + 32;
    }
    else
    {
        return coded;
    }


}//Substitute












