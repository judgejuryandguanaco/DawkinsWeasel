/**
 * @author Mitchell Smith <mitchell.smith317@gmail.com>
 * @brief Randomly mutate a string into a user specified one.
 *
 * Use a hill cimbing searching algorithm and random mutation
 * to match a string full of 'A''s to a user specified one.
 * 
 * The program takes three arguments from the command line:
 * 1. The string
 * 2. The probability of each char in each string mutating,
 *      this value must be expressed as a pu value, less than one
 * 3. The number of strings to create, and to mutate.
 * eg
 *      weasel "METHINKS IT IS LIKE A WEASEL" 0.05 100
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h> // can this be replaced?

int initstr(char **str, int *len);
int randstr(char *str0, const float *prob);
void randchar(char *ch);
int compstr(const char *str0, const char *str1);
int chartbl(const char *ch);
int compchar(const char *ch0, const char *ch1);
int binprob(const float *prob, bool *res);
int cumprob();
int initstrs(char **strs, int *size, int *len);
void randstrs(char **strs, int *size, float *prob);
int compstrs(char **strs, int *size, char *input);
int cpywin(char **strs, int *size, int *win);
int freestrs(char **strs, int *size);

/**
 * @brief Implementation of Dawkin's Weasel. Use genetic algorithm to
 *          evolve a random string towards specified target strings.
 * @param argc Number of arguments passed to main by terminal
 * @param argv Arguments passed to main
 * @return 0 if OK
 */
int main(int argc, char **argv)
{
    int numstrs = atoi(argv[3]);
    char **strs = malloc(sizeof(*strs)*numstrs);
    float prob = atof(argv[2]);
    int i = 0;
    bool end = false;
    int t = clock();
    int len = strlen(argv[1]);
    srand(time(NULL));
    
    initstrs(strs, &numstrs, &len);
    do {
        int win;
        randstrs(strs, &numstrs, &prob);
        win = compstrs(strs, &numstrs, argv[1]);
        if(win != 0) {
            printf("%i: %s\n", i, strs[win]);
            if (compstr(strs[win], argv[1]) == strlen(argv[1]))
                end = true;
        }
        cpywin(strs, &numstrs, &win);
        i++;
        if(kbhit()) {
            printf("User escape\n");
            end = true;
        }
    } while(!end);
    t = clock() - t;
    printf("It took %d clicks (%f seconds).\n", t, (float)t/CLOCKS_PER_SEC);
    freestrs(strs, &numstrs);
    return 0;
}

/**
 * @brief Initialise strings in array, with size based on input
 * @param input 
 * @param strs
 * @param size
 * @return 
 */
int initstrs(char **strs, int *size, int *len)
{
	for (int i = 0; i < *size; i++) {
		initstr(&strs[i], len);
	}
	return 0;
}

/**
 * @brief Randomly change chars in strings contained within array
 * @param strs The array of strings
 * @param size The size of the array
 * @param prob The probability that any character will change
 */
void randstrs(char **strs, int *size, float *prob)
{
	for (int i = 1; i < *size; i++) {
		randstr(strs[i], prob);
	}	
}

/**
 * @brief Compare elements of array of strings to a string
 * @param strs The array of strings
 * @param size The size of strs
 * @param input The string to compare to
 * @return The position of the closest matching element
 */
int compstrs(char **strs, int *size, char *input)
{
	int max = 0;
	int num;
	for (int i = 0; i < *size; i++) {
		int tmp = compstr(strs[i], input);
		if (tmp > max) {
			max = tmp;
			num = i;
		}
	}
	return num;
}

/**
 * @brief Copy the winning string into each string
 * @param strs Array of strings
 * @param size Size of array
 * @param win Position of winning string
 * @return 0 if OK
 */
int cpywin(char **strs, int *size, int *win)
{
	int ret = 0;
	for (int i = 0; i < *size; i++) {
		strcpy(strs[i], strs[*win]);
	}
	return ret;
}

/**
 * @brief Allocate memory for str1 based on len of str0
 * @param str0 Initialised string
 * @param str1 Uninitialised string
 * @return 0 if OK
 */
int initstr(char **str, int *len)
{
    int ret = 0;
    
    *str = malloc(sizeof(**str) * *len+1);
    if (*str == NULL)
        ret = -1;
    
    for (int i = 0; i < *len; i++) {
        (*str)[i] = 'A';
    }
    (*str)[*len] = '\0';
    return ret;
}

/**
 * @brief Randomly change characters in a string
 * @param str0 The string to change
 * @param prob The probability any charater will change
 * @return 0 if OK
 */
int randstr(char *str0, const float *prob)
{
    int ret = 0;
    int len = strlen(str0);
       
    for (int i = 0; i < len; i++) {
        bool res;
        binprob(prob, &res);
        if (res)
            randchar(&str0[i]);
    }
    return ret;
}

/**
 * @brief Count number of identical chars
 * @param str0 First string
 * @param str1 Second string
 * @return 
 */
int compstr(const char *str0, const char *str1)
{
    int ret = 0;
    int len = strlen(str0);
    
    for (int i = 0; i < len; i++) {
        if (str0[i] == str1[i])
            ret++;
    }
    return ret;
}

/**
 * @brief Assign new letter of alphabet to char * based on probability
 * @param ch Pointer to the char
 */
void randchar(char *ch)
{
    int letter = cumprob();
    
    switch(letter) {
    case 1:
        *ch = 'A';
        break;
    case 2:
        *ch = 'B';
        break;
    case 3:
        *ch = 'C';
        break;
    case 4:
        *ch = 'D';
        break;
    case 5:
        *ch = 'E';
        break;
    case 6:
        *ch = 'F';
        break;
    case 7:
        *ch = 'G';
        break;
    case 8:
        *ch = 'H';
        break;
    case 9:
        *ch = 'I';
        break;
    case 10:
        *ch = 'J';
        break;
    case 11:
        *ch = 'K';
        break;
    case 12:
        *ch = 'L';
        break;
    case 13:
        *ch = 'M';
        break;
    case 14:
        *ch = 'N';
        break;
    case 15:
        *ch = 'O';
        break;
    case 16:
        *ch = 'P';
        break;
    case 17:
        *ch = 'Q';
        break;
    case 18:
        *ch = 'R';
        break;
    case 19:
        *ch = 'S';
        break;
    case 20:
        *ch = 'T';
        break;
    case 21:
        *ch = 'U';
        break;
    case 22:
        *ch = 'V';
        break;
    case 23:
        *ch = 'W';
        break;
    case 24:
        *ch = 'X';
        break;
    case 25:
        *ch = 'Y';
        break;
    case 26:
        *ch = 'Z';
        break;
    case 27:
        *ch = ' ';
    default:
        break;
    }
}

/**
 * @brief Compare prob to random value to make bool decision
 * @param prob The probability of returnung true as a pu value
 * @param res Variable that the result is copied into
 * @return 
 */
int binprob(const float *prob, bool *res)
{
    float test = (float)rand() / (float)RAND_MAX;
    
    if (*prob >= test)
        *res = true;
    else
        *res = false;
    return 0;
}

/**
 * @brief Use cumulative probability to choose a letter of the
 *          alphabet
 * @return Number of letter of the alphabet
 */
int cumprob(void)
{
    const int alphabet = 26;
    float test = (float)rand() / (float)RAND_MAX;
    float inc = 1.0 / (float)alphabet;
    float cum = 0.0;
    int i = 1;
    bool end = false;
    do {
        cum += inc;
        i++;
        if (cum >= test)
            end = true;
    } while (!end);
    return i;
}

/**
 * @brief Free elements of char * array and then the array itself
 * @param strs Array of char * elements
 * @param size Size of array
 * @return 0 if OK
 */
int freestrs(char **strs, int *size)
{
    for(int i = 0; i < *size; i++) {
        free(strs[i]);
    }
    free(strs);
    return 0;
}