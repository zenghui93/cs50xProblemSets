#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{

    //Calculate how many digits(length) of the number that the user has typed in
    int get_length(long n);

    //Return the digit of the number at index index
    int get_digit(long number, int index);
    //Return an inverted array
    int *get_inverted(int number[], int length);

    //Return the sum of an array
    int sum_array(int array[], int length);

    //Calculate the sum of the array
    int checkSum(int array[], int l);
    
    //Check whether it's an American Express Card
    string checkAmex(int first, int second);
    
    //Check whether it's a Visa Card
    string checkVisa(int first);
    
    //Check whether it's a Mastercard
    string checkMastercard(int first, int second);

    // It promts the user for their number
    unsigned long number = get_long("Number: ");

    int length = get_length(number);
    string msg;
    //printf("length of the number is %i\n", length);
    //Check length
    if (length < 13 || length > 16)
    {
        msg = "INVALID";
    }
    else
    {
        int newNumber[length];
        int i = 0;
        long divider = 10;
        do
        {
            newNumber[i] = get_digit(number, i);
            i++;
        }
        while (i < length);
        int sum = checkSum(newNumber, length);
        //printf("The sum is %i\n",sum);
    
        //Get the last digit of sum
        int last_digit_sum = get_digit(sum, 0);
        if (last_digit_sum != 0)
        {
            msg = "INVALID";
        }
        else
        {
            int *inverted_array;
            inverted_array = get_inverted(newNumber, length);
     
            if (length == 15)
            {
                msg = checkAmex(inverted_array[0], inverted_array[1]);
            }
            
            if (length == 13)
            {
                msg = checkVisa(inverted_array[0]);
            }
            if (length == 16 && inverted_array[0] == 4)
            {
                msg = checkVisa(inverted_array[0]);
            }
            if (length == 16 && inverted_array[0] == 5)
            {
                msg = checkMastercard(inverted_array[0], inverted_array[1]);
                
            }
                
            
            
        }
        
        
        
    }
    
    
    printf("%s\n", msg);


}



//get the digit of a number at index index
int get_digit(long number, int index)
{
    long divider = pow(10, index + 1);
    long remainder = number % divider;
    int digit = (int)round(remainder / (divider / 10));
    return digit;
}
// Calculate and return the length of the number n passed as a parameter
int get_length(long n)
{
    int length = 0;
    do
    {
        length++;
        n = n / 10;
    }
    while ((int)n);
    return length;
}//get_length

//Calculate the sum of the array at index where index % 2 = 1
int get_sum_array(int array[], int length)
{
    int sum = 0;

    for (int ii = 0; ii < length / 2; ii++)
    {
        if (array[ii] >= 10)
        {
            sum += get_digit(array[ii], 0);
            sum += get_digit(array[ii], 1);
        }
        else
        {
            sum += array[ii];
        }
    }
    return sum;
}
//Calculate the sum of the array
int checkSum(int array[], int l)
{
    int newArray[l / 2];
    int i_array = 1;
    for (int ii = 0; ii < l / 2; ii++)
    {
        newArray[ii] = array[i_array] * 2;
        //printf("length is %i\n",l/2);
        i_array += 2;
    }//End for

    int sum = get_sum_array(newArray, l);
    int finalsum = array[0] + sum;
    for (int ii = 2; ii < l; ii++)
    {
        if (ii % 2 == 0)
        {
            finalsum += array[ii];
        }
    }
    return finalsum;
}//checkSum

//Invert the position of an array. For example the last item become the first.
int *get_inverted(int *number, int length)
{
    int w = length - 1;
    int temp[w];
    for (int ii = 0; ii <= length - 1; ii++)
    {
        temp[ii] = number[w];
        w--;
    }
    //Create the final array
    for (int ii = 0; ii <= length - 1; ii++)
    {
        number[ii] = temp[ii];
        //printf("arrayNumber is %i\n", number[ii]);
    }
    return number;
}//get_inverted
    
//Check wheather it's an American Express. Return a string AMEX\n if yes, INVALID\n if no.
//It has two parameters : first for the first digit and second for the second digit.
string checkAmex(int first, int second)
{
    int number = first * 10 + second;
    string msg;
    switch (number)
    {
        case 34 :
            msg = "AMEX";
            break;
        
        case 37 :
            msg = "AMEX";
            break;
        
        default :
            msg = "INVALID";
    }
    return msg;
}

//Check wheather it's a VISA CARD. Return a string VISA\n if yes, INVALID\n if no.
//It has two parameters : first for the first digit and second for the second digit.
string checkVisa(int first)
{
    
    string msg;
    switch (first)
    {
        case 4 :
            msg = "VISA";
            break;
       
        default :
            msg = "INVALID";
    }
    return msg;
}//checkVisa

//Check whether it's a Mastercard
//It has two parameters : first for the first digit and second for the second digit.
string checkMastercard(int first, int second)
{
    int number = first * 10 + second;
    string msg;
    switch (number)
    {
        case 51 :
            msg = "MASTERCARD";
            break;
        
        case 52 :
            msg = "MASTERCARD";
            break;
        
        case 53 :
            msg = "MASTERCARD";
            break;
        
        case 54 :
            msg = "MASTERCARD";
            break;
        
        case 55 :
            msg = "MASTERCARD";
            break;
       
        default :
            msg = "INVALID";
    }
    
    return msg;
    
}




