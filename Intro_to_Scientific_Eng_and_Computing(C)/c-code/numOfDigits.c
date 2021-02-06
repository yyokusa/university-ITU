//Efficient way to determine number of digits in an integer

int numDigits(T number)
{
    int digits = 0;
    if (number < 0) digits = 1; // remove this line if '-' counts as a digit
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}



// Recursive C program to count number of 
// digits in a number 
  
int countDigit(long long n) 
{ 
    if (n == 0) 
        return 0; 
    return 1 + countDigit(n / 10); 
} 
  

unsigned GetNumberOfDigits (unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}