/*********************************************************************/ 
/*                                                                   */ 
/*             Mathematical Library - (C) TGG 2002                   */ 
/*                                                                   */ 
/*********************************************************************/ 
/*                          Warszawa, 2002                           */ 
/*********************************************************************/ 
/*                                                                   */ 
/* File: itoa.cpp                                                    */
/*                                                                   */
/* Based on "The C Programming Language", 2nd edition,               */
/* by Kernighan and Ritchie                                          */
/* Answers to Exercises maintained by Richard Heathfield             */ 
/*                                                                   */
/* http://users.powernet.co.uk/eton/kandr2/                          */
/*                                                                   */
/*********************************************************************/
/*                                                                   */
/*                                                                   */

#include "itoa.h"

void itoa(int n, char s[])
{
	int i, sign;
	sign = n;
	i = 0;
	do
		{
		s[i++] = abs(n % 10) + '0';
		}
	while ( n /= 10 );
	if (sign < 0) s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/*  Stores a string representation of integer n
    in s[], using a numerical base of b. Will handle
    up to base-36 before we run out of digits to use.  */

#if defined(_LINUX_) || defined(__CYGWIN__)

void itoa(int n, char s[], int b)
{
	static char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i, sign;
	if ( b < 2 || b > 36 ) 
		{
		fprintf(stderr, "EX3_5: Cannot support base %d\n", b);
		exit(EXIT_FAILURE);
		}
	if ((sign = n) < 0) n = -n;
	i = 0;
	do
		{
		s[i++] = digits[n % b];
		}
	while ((n /= b) > 0);
	if (sign < 0) s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

#endif

/*  Reverses string s[] in place  */

void reverse(char s[]) 
{
	int c, i, j;
	for ( i = 0, j = strlen(s)-1; i < j; i++, j--)
		{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		}
}



