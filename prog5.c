/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */




/**
Intro Paragraph
The purpose of this program is to implement the modified version of the Wheel of Fortune which uses the name of the
Star Wars characters. For the function set_seed we used teh srand function to set the seed for the rand function from
user input seed. In the next function, start_game, we used the rand function to generate random integers and put into
solutions[][] array a random assortment of 4 names from pool. This utilized a for loop to generate four different numbers
and use them as index values for pool. For the function, make_guess, we first checked if the user input was valid. We did
this by using the sscanf function and an array, valid [4][10]. If there was an extra input after the four strings the
fucntion would fail and zero would be returned. After these strings were saved to valid [0-3], we used the is_valid
function to check each string indivdually and if one was invalid the function would fail and return 0. Next we created
two arrays to store the matches. In these arrays every element begins as a 0. The next portion utilizes the given
algorithim and our method of marking things as matched is setting their respective element in the char arrays to a 1.
To check for misplaced, we only considered elements that were not marked as matched. At the end of the function we
multiplied the amount of perfect matches by 1000 and the amount of misplaced matches by 100, and the sum was set to the
roundscore. If the roundscore was greater than the max_score, the max_score was replaced by the roundscore. The function
finally returns 2 if 4 perfect matches were found, otherwise returns 1.
Partners:psaboo2, abhyanj2

*/


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below
    int seed;
    char post[2];
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
      // your code here
	printf("set_seed: invalid seed\n");       //prints invalid statement
	return 0;
    }
    // your code here
	srand(seed);                              // sets user input as seed number
	return 1;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    //your code here
	int gen;
	for (int i = 0; i < 4; i++) {               	//loop to get 4 random numbers and set up solutions
		gen = rand() % 8;                       	// makes sure its between 0 and 7
    	strcpy(&solutions[i][0], pool[gen]);    	// one by one, solutions[i] is filled
}
	guess_number = 1;								// init guess_number
	max_score = -1;									// init max_score
}
/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid,
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
  // your code here
  int perfect = 0;
  int misplaced = 0;
  int roundscore = 0;
  char valid[4][10];						// 2D array to hold user input
  char* garbage = "";						// used to check if invalid
	if (sscanf(guess_str, "%s%s%s%s%1s", valid[0], valid[1], valid[2], valid[3], garbage) != 4) {   		// checks if there were only 4 inputs and stores each input into an index of valid
    printf("make_guess: invalid guess\n");						// Invalid Statement
    return 0;
	}
  //now we have to check the strings individually
  for (int i = 0; i < 4; i++) {
    if (is_valid(valid[i]) == 0) {					// calls is_valid() with the argument as each row of valid[][]
      printf("make_guess: invalid guess\n");
      return 0;
    }
  }

  int guess_matched[4];							// init 2 arrays to hold matches
  int solution_matched[4];
  for (int i = 0; i < 4; i++) {					 	// element marked as 1 if matched
      if (strcmp(valid[i], solutions[i]) == 0) { 	// output will be 0 if same
        solution_matched[i] = 1;					// marked element as matched
        guess_matched[i] = 1;						// marked element as matched
        perfect += 1;								// increment perfect counter
      }
  }
  for (int k = 0; k < 4; k++) {						// Loop to count misplaced matches
    if (guess_matched[k] != 1) {					// Makes sure its not a perfect match
      for(int j = 0; j < 4; j++) {
        if (solution_matched[j] != 1) {					// Makes sure solution is not already matched
          if (strcmp(valid[k], solutions[j]) == 0) {	//Output will be 0 if same
            solution_matched[j] = 1;				// marked element as matched
            guess_matched[k] = 1;					// marked element as matched
            misplaced += 1;							// increment misplaced counter
          }
        }
      }
    }
  }
  //need to calculate the score
  roundscore = (perfect*1000) + (misplaced*100);    // Calculates score for each round
  if (roundscore > max_score) {						// if round score is new max, then max_score is set as roundscore
    max_score = roundscore;
  }
	printf("With guess %d, you got %d perfect matches and %d misplaced matches.\nYour score is %d and current max score is %d.\n", guess_number, perfect, misplaced, roundscore, max_score);
  if (perfect == 4) {
    return 2; 				// returns 2 if guess is valid and game should end (all 4 perfect matches)
  }
  else {
    return 1;				// return 1 if guess is valid
  }
}
