/*
I wrote this code myself with the help of L.S.Fosters "C By Discovery" and the inout2.c file.  
This program parses through the input stream and extracts out each individual word, and designated special characters,
returning the size of the word as well as pushing the characters onto the input buffer for display. 
 
Eric Spengler
09/04/19
Dr. John Carroll
CS570
*/

#include "getword.h"

int getword(char *word)
{
	//counter for the number of chars in the word
	int numChars = 0;
	//stdin input variable
	int input;
	//looping through the input stream until EOF or a break from inside the loop
	while (numChars < 254 && (input = getchar()) != EOF)
	{
		//ignoring spaces from the input or exiting the loop if the word is finished due to a space
		if (numChars > 0 && input == ' ')
		{
			break;
		}
		else if (input == ' ')
		{
			continue;
		}
		//pushing newline back on the input stream if at the end of a word so that it can be read by itself
		if (numChars > 0 && input == '\n')
		{
			ungetc('\n', stdin);
			break;
		}
		//dealing with newline if it's the first char from the input stream
		else if (input == '\n')
		{
			word[numChars] = '\0';	
			return 0;
		}
		//dealing with the input of '\' displaying the char that follows it except newline
		if (input == '\\')
		{
			if ((input = getchar()) != EOF)
			{
				if (input == '\n')
				{
					ungetc(input, stdin);
					break;
				}	
				word[numChars] = input;
				numChars++;
				continue;
			}
			else
			{
				break;
			}
			continue;
		}
		//putting the designated special chars back on the input stream if attached to a word so that it cant be read by itself
		else if (numChars > 0 && (input == '<' || input == '>' || input == '|' || input == '#' || input == '&'))
		{
			ungetc(input, stdin);
			break;
		}
		//handling the special chars '<' '|' '#' '&' if they are the first chars on the input stream
		else if (input == '<' || input == '|' || input == '#' || input == '&')
		{
			word[numChars] = input;
			numChars++;
			break;
		}
		//handling the special chars '>' '>>' '>&' '>>&' if they are the first chars on the input stream 
		//'>'
		else if (input == '>')
		{
			word[numChars] = input;
			numChars++;
			if ((input = getchar()) != EOF)
			{
				//'>>'
				if (input == '>')
				{		
					word[numChars] = input;
					numChars++;
					if ((input = getchar()) != EOF)
					{
						//'>>&'
						if (input == '&')
						{
							word[numChars] = input;
							numChars++;
							break;
						}
						else
						{
							ungetc(input, stdin);
							break;
						}
					}
					else
					{
						break;
					}
				}
				//'>&'
				else if (input == '&')
				{
					word[numChars] = input;
					numChars++;
					break;
				}
				else
				{
					ungetc(input, stdin);
					break;
				}
			}
			else
			{
				break;
			}
		}
		word[numChars] = input;
		numChars++;
	}
        //adding null terminator to input buffer 
        word[numChars] = '\0';	
	//handling EOF
	if (numChars == 0 && input == EOF)
	{
		return -1;
	}
	//handling 'done' to return -1
	if (word[0] == 'd' && word[1] == 'o' && word[2] == 'n' && word[3] == 'e' && word[4] == '\0')
	{
		return -1;
	}	
	//returning the number of chars
	return numChars;
}
