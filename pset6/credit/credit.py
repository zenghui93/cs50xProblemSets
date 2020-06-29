from cs50 import get_int


def main():
    # It promts the user for their card number
    number = get_int("Number: ")
    # length is the length of the number given by the user
    length = len(str(number))
    # Check length
    if length < 13 or length > 16:
        # msg is the output messenge for user
        msg = "INVALID"
    else:
        newNumber = [int(x) for x in str(number)]
        
        # s is the sum of the number
        s = checkSum(newNumber)
        
        # Get the last digit of sum
        last_digit_sum = s % 10
        if last_digit_sum != 0:
            msg = "INVALID"
        else:
            length = len(newNumber)
            if length == 15:
                msg = checkAmex(newNumber[0], newNumber[1])
            
            if length == 13:
                msg = checkVisa(newNumber[0])
            
            if length == 16 and newNumber[0] == 4:
            
                msg = checkVisa(newNumber[0])
            
            if length == 16 and newNumber[0] == 5:
                msg = checkMastercard(newNumber[0], newNumber[1])
            
    print(msg)


# Calculate the sum of the array at index where index % 2 = 1

def get_sum_array(array):
    # s is sum
    s = 0
    
    for arr in array:
        if arr >= 10:
            s += arr // 10
            s += arr % 10
        else:
            s += arr
 
    return s

# Calculate the sum of the array


def checkSum(array):
    # newArray1 contains all the every other digits starting from second-to-last digit
    if len(array) % 2 == 0:
        newArray1 = [array[i] * 2 for i in range(0, len(array), 2)]
        newArray2 = [array[i] for i in range(1, len(array), 2)]
    else:
        newArray1 = [array[i] * 2 for i in range(1, len(array), 2)]
        newArray2 = [array[i] for i in range(0, len(array), 2)]
    
    # s is the sum of all the numbers in newArray1    
    s = get_sum_array(newArray1)
    
    finalsum = s + sum(newArray2)
    return finalsum
    
    
# Check wheather it's an American Express. Return a string AMEX\n if yes, INVALID\n if no.
# It has two parameters : first for the first digit and second for the second digit.


def checkAmex(first, second):
    
    number = first * 10 + second
    cases = {34, 37}
    if number in cases:
        msg = "AMEX"
    else:
        msg = "INVALID"
    return msg
        
    
# Check wheather it's a VISA CARD. Return a string VISA\n if yes, INVALID\n if no.
# It has two parameters : first for the first digit and second for the second digit.

def checkVisa(first):
    
    if first == 4:
        msg = "VISA"
    else:
        msg = "INVALID"
    return msg

# Check whether it's a Mastercard


def checkMastercard(first, second):
    # number is the number composed by the first two digits. eg if my first digit is 1, and second digit is 3, then my number will be 13
    number = first * 10 + second
    cases = {51, 52, 53, 54, 55}
    if number in cases:
        msg = "MASTERCARD"
    else:
        msg = "INVALID"
    return msg
         

main()

