from cs50 import get_int


def main():
    while True:
        # height is the height of the pyramid 
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break
        
    get_pyramid(height)
    
    
def get_pyramid(n):
    for i in range(n):
        j = n - i - 1
        print(" " * j + "#" * (i + 1) + "  " + "#" * (i + 1), end="\n")
       
        
main()