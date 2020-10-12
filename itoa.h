/*********************************************************************/ 
/*                                                                   */ 
/*             Mathematical Library - (C) TGG 2002                   */ 
/*                                                                   */ 
/*********************************************************************/ 
/*                          Warszawa, 2002                           */ 
/*********************************************************************/ 
/*                                                                   */ 
/* File: itoa.h                                                      */
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


#ifndef _ITOA_H_
#define _ITOA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itoa(int n, char s[]);
#if defined(_LINUX_) || defined(__CYGWIN__)
void itoa(int n, char s[], int b);
#endif
void reverse(char s[]);


#endif /*_ITOA_H_*/
