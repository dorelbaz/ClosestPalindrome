#include <stdio.h>
#include <stdbool.h>

/* Check to see if the input is a palindrome. */
bool isPalin(char *k)                    
{
    int cnt_equals = 0;
    int median = 0;
    if (strlen(k)%2 == 1) {median++;}
    int i = 0;
    int j = strlen(k)-1;
     
    while (i < strlen(k)/2)
    {
        if (k[i] == k[j]) {cnt_equals += 2;}
        i++;
        j--;
    }
    if (cnt_equals + median == strlen(k)) 
    {
        return true;
    }
    return false;
}

/* The special cases follow these patterns 99 100 101
999 1000 1001... To deal with these cases, we add 2, subtract 1, subtract 2 respectively. */

char * Special_cases(char *k)           
{
   char *t = malloc(strlen(k)+2);
   t[strlen(k)+1] = '\0';

   if (atoi(k)%10 == 9) 
   {     
       int n = atoi(k) + 2;
       sprintf(t, "%d", n);
       if (isPalin(t) == true) {return t;}
       free(t);
       t = NULL;       
   }

    if (atoi(k)%10 == 1) 
    { 
       int n = atoi(k) - 2;
       sprintf(t, "%d", n);
       if (isPalin(t) == true) {return t;}
       free(t); 
       t = NULL;
    }

    if (atoi(k)%10 == 0) 
    { 
       int n = atoi(k) - 1;
       sprintf(t, "%d", n);
       if (isPalin(t) == true) {return t;}
       free(t);
       t = NULL;
     }
   return NULL;
}

/*
If the input is a palindrome, what matters to us is whether its length is even or not, for then 2 special mathmatical laws can be invoked.

If the length is not even, we take the median and add to it 1 * 10^n, check if the result is a palindrome if not we subtract 1 * 10^n, n depends how far the median is from the input's beginning (or end, it doesn't really matter).
For example, 12221 we subtract 100 (1 * 10^2), for 11011 we add 100.

If the length is even, we take the 2 middle numbers and add or subtract to them 11 * 10^n, n also being dependant on how far each number is from the input's beginning or end, repectively. For example, 1221 we subtract 110 (11 * 10^1).

And these is what I do with the next 2 methods.
*/

char * palin_with_median(char *k)
{
    long num = atol(k);    
    char *t = malloc(strlen(k)+1);
    t[strlen(k)] = '\0';
    char temp[strlen(k)/2+2];
    temp[strlen(k)/2+1] = '\0';
    int i = 1;
    temp[0] = '1';
    while (i < strlen(k)/2+1)
    {
        temp[i] = '0';
        i++;
    }
    long t_num = atol(temp);
    sprintf(t, "%ld", num - t_num);
    if (isPalin(t) == true)
    {
        return t;
    }
    free(t);
    t = malloc(strlen(k)+1);
    t[strlen(k)] = '\0';
    sprintf(t, "%ld", num + t_num);
    return t;
}

char * palin_without_median(char *k)
{
    long num = atol(k);
    char *t = malloc(strlen(k)+1);
    t[strlen(k)] = '\0';
    char temp[strlen(k)/2+2];
    temp[strlen(k)/2+1] = '\0';
    int i = 2;
    temp[0] = '1';
    temp[1] = '1';
    while (i < strlen(k)/2 + 1)
    {  
        temp[i] = '0';
        i++;
    }
    long t_num = atol(temp);
    sprintf(t, "%ld", num - t_num);
    if (isPalin(t) == true)
    {               
        return t;
    }
    free(t);
    t = malloc(strlen(k)+1);
    t[strlen(k)] = '\0';
    sprintf(t, "%ld", num + t_num);
    return t;
}

char * nearestPalindromic(char * n)

{

if (strlen(n) == 1)   /* This is another special case if the input is smaller than 10.*/
{
    int res = atoi(n) - 1;
    char *p = malloc(2);
    p[0] = res + '0';
    p[1] = '\0';
    return p;
}
 
char *p = NULL;
p = Special_cases(n);                                                            
if (p != NULL) {return p;}    
if (strlen(n)%2 == 1 && isPalin(n) == true)  
{
    p =  palin_with_median(n);
    return p;
}
if (strlen(n)%2 == 0 && isPalin(n) == true) 
{
    p =  palin_without_median(n);
    return p;
}

/*
    Now if the input isn't a special case or a palindrome.
	
    I copy the left half of the input into the right half, set an offset to 1, and if the        
	result is bigger than the input I set the offset to -1, and add it to the median of           
	the input or the middle number that is closer to the beginning and copy again.
	
    So this guarantees that I get 2 strings that represent the closest palindromes               
	(could check but it is pointless), one bigger than the input the other smaller.
	
    I than check for the differences between the strings and the input and return the            
	smallest, if the diffrences are the same I return the string that represents the             
	smaller palindrome.       
*/

long l_n = atol(n);
int len = strlen(n);
int i = 0;
int j = len-1;
int median = 0;
if (len%2 == 1) {median++;}

char *temp = malloc(len+1);
temp[len] = '\0';

while (i < len/2 + median)
{
    temp[i] = n[i];
    temp[j] = n[i];
    i++;
    j--;
}

int offset = 1;
long l_temp = atol(temp);

if (l_n < l_temp)
{
    offset = -1;
}

i = 0;
j = len-1;
if (len%2 == 1) 
{
    n[len/2] += offset;
}
else {n[len/2 - 1] += offset;}

char *temp2 = malloc(len+1);
temp2[len] = '\0';

while (i < len/2 + median)
{
    temp2[i] = n[i];
    temp2[j] = n[i];
    i++;
    j--;
}
long l_temp2 = atol(temp2);

long diff = l_n - l_temp;
if (diff < 0) {diff *= -1;}
long diff2 = l_n - l_temp2;
if (diff2 < 0) {diff2 *= -1;}

if (diff < diff2)
{
    free(temp2);
    temp2 = NULL;
    return temp;
}
if (diff == diff2)
{
    if (l_temp < l_temp2)
    {
        free(temp2);
        temp2 = NULL;
        return temp;
    }
    free(temp);
    temp = NULL;
    return temp2;
}

free(temp);
temp = NULL;
return temp2;

/*
    0 ms and 6 MB
    Side notes: I use long because we can't know the size of the number the input                
	represents and I constantly transfer the results to long, using atol, and                    
	vice versa, using sprintf, for convenience. 
*/   

}