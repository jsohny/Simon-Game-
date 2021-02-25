/* 
 * Name: Justin Sohnne
 * Subject: APSC160 LAB 8 SIMON GAME
 * Date: Dec. 1, 2017
 * Lab Section: L1A
 * UBC Alumni e-mail address: justin.sohn08@alumni.ubc.ca
 * Purpose of code: Implements the Simon game
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <DAQlib.h>
#include <Windows.h>

#define MAX_LENGTH 5
#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define GREEN 0
#define RED 1
#define YELLOW 2
#define BLUE 3
#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0
#define ONE_SECOND 1000

/* List of all functions used (More detail about each function below the main function */
int randInt(int lower, int upper);
void generateSequence(int length, int data[], int lower, int upper);
void flashLEDS(int level, int LED_Sequence[]);
int checkUserResponse(int level, int LED_Sequence[]);
void startGame(void);
void game_over(int LEDtoFlash);
void won_game(int LEDtoFlash);
void runSimon(void);

int main(void) {
	int setupNum;

	srand((unsigned)time(NULL));

	printf("Enter 0 to use hardware or 6 to use simulator: ");
	scanf("%d", &setupNum);

	if (setupDAQ(setupNum)) {
		printf("\n\nSIMON GAME\n\n");
		runSimon();
	}

	else {
		printf("ERROR: cannot initialize.\n ");
	}

	system("PAUSE");
	return 0;
}


/* 
 * Purpose: Returns a random integer between the specified upper and lower bounds.
 */
int randInt(int lower, int upper) {
	return rand() % (upper - lower + 1) + lower;
}


/*
 * Purpose: Generates a random sequence of integers given a specified length, the array to 
            generate integers into, as well as the upper and lower bounds.
 */
void generateSequence(int length, int data[], int lower, int upper) {
	int index;

	for (index = 0; index < length; index++)
		data[index] = randInt(lower, upper);
}


/*
 * Purpose: Given the specified level within the game, displays the sequence of lights in which 
            the user must repeat back. 
 */
void flashLEDS(int level, int LED_Sequence[]) {
	int count;
	//flashes the sequence of LEDs for the user to repeat back using a for loop for the array containing the generated sequence.
	for (count = 0; count <= level; count++) {
		digitalWrite(LED_Sequence[count], ON);
		Sleep(ONE_SECOND/2);
		digitalWrite(LED_Sequence[count], OFF);
		Sleep(ONE_SECOND/3);

		if (!continueSuperLoop())
			return;
	}
}


/*
 * Purpose: Within a given level, checks each button pressed by the user with the sequence of 
            lights which were required to repeat back. If the user is successful, the function 
			returns 1 to indicate the user passed the level. If the user makes a mistake, the 
			function returns 0, indiciating the end of the game. If the user has closed the
			window, the function returns -1 indicating the program to quit running.
 */
int checkUserResponse(int level, int LED_Sequence[]) {
	int getUserResponse;
	int flag = 1;
	int count;

	for (count = 0; count <= level; count++) {
		//System stays inside while TRUE loop until user presses one of the buttons. Program then checks if the pressed button is the correct button to press. 
		while (TRUE) {
			if (digitalRead(LED0) == ON) {
				digitalWrite(LED0, ON);
				getUserResponse = LED0;
				if (getUserResponse == LED_Sequence[count]) {
					while (digitalRead(LED0) == ON) {
						Sleep(ONE_SECOND / 20);
					}
					digitalWrite(LED0, OFF);
					break;
				}
				else {
					digitalWrite(LED0, ON);
					flag = 0;
					while (digitalRead(LED0) == ON) {
						Sleep(ONE_SECOND / 20);
					}
					digitalWrite(LED0, OFF);
					return flag;
				}
			}

			else if (digitalRead(LED1) == ON) {
				digitalWrite(LED1, ON);
				getUserResponse = LED1;
				if (getUserResponse == LED_Sequence[count]) {
					while (digitalRead(LED1) == ON) {
						Sleep(ONE_SECOND / 20);
					}
					digitalWrite(LED1, OFF);
					break;
				}
				else {
					flag = 0;
					while (digitalRead(LED1) == ON) {
						Sleep(ONE_SECOND / 20);
					}
					digitalWrite(LED1, OFF);
					return flag;
				}
			}

			else if (digitalRead(LED2) == ON) {
				digitalWrite(LED2, ON);
				getUserResponse = LED2;
				if (getUserResponse == LED_Sequence[count]) {
					while (digitalRead(LED2) == ON) {
						Sleep(ONE_SECOND / 20);
					}
					digitalWrite(LED2, OFF);
					break;
				}
				else {
					digitalWrite(LED2, ON);
					flag = 0;
					while (digitalRead(LED2) == ON) {
						Sleep(ONE_SECOND / 20);
					}
					digitalWrite(LED2, OFF);
					return flag;
				}
			}

			else if (digitalRead(LED3) == ON) {
				digitalWrite(LED3, ON);
				getUserResponse = LED3;
				if (getUserResponse == LED_Sequence[count]) {
					while (digitalRead(LED3) == ON) {
						Sleep(ONE_SECOND / 20);
					}
					digitalWrite(LED3, OFF);
					break;
				}
				else {
					digitalWrite(LED3, ON);
					flag = 0;
					while (digitalRead(LED3) == ON) {
						Sleep(ONE_SECOND / 20);
					}
					digitalWrite(LED3, OFF);
					return flag;
				}
			}

			if (!continueSuperLoop()) {
				flag = -1;
				return flag;
			}
		}
	}
	return flag;
}


/* 
 * Purpose: Flashes all LEDs in quick succession to indicate the start of a new game.
 */
void startGame(void) {
	int LED;
	int count;

	for (count = 0; count < 3; count++) {
		for (LED = LED0; LED <= LED3; LED++) {
			digitalWrite(LED, ON);
			Sleep(ONE_SECOND/20);
			digitalWrite(LED, OFF);
			Sleep(ONE_SECOND/20);
		}
	}
	Sleep(ONE_SECOND);
}


/* 
 * Purpose: Flashes the red LED 3 times in quick succession to indicate game over.
 */
void game_over(int LEDtoFlash) {
	int count;

	for (count = 0; count < 3; count++) {
		digitalWrite(LEDtoFlash, ON);
		Sleep(ONE_SECOND/10);
		digitalWrite(LEDtoFlash, OFF);
		Sleep(ONE_SECOND/10);
	}
	Sleep(ONE_SECOND);
}


/*
 * Purpose: Flahses the green LED 6 times in quick succession to indiciate the user has passed 
            all levels.
 */
void won_game(int LEDtoFlash) {
	int count;

	for (count = 0; count < 3; count++) {
		digitalWrite(LEDtoFlash, ON);
		Sleep(ONE_SECOND/10);
		digitalWrite(LEDtoFlash, OFF);
		Sleep(ONE_SECOND/10);
	}

	Sleep(ONE_SECOND / 3);

	for (count = 0; count < 3; count++) {
		digitalWrite(LEDtoFlash, ON);
		Sleep(ONE_SECOND / 10);
		digitalWrite(LEDtoFlash, OFF);
		Sleep(ONE_SECOND / 10);
	}

	Sleep(ONE_SECOND);
}


/*
 * Purpose: Work function of the program. Runs the Simon game. Indicates the current level, high 
            score, and is able to start new games.
 */
void runSimon(void) {
	int level;
	int highScore = 0;
	int userProgress;
	int LED_Sequence[MAX_LENGTH];

	while (continueSuperLoop()) {
		//Initializes a new game and generates a sequence 
		printf("\nA new game is starting now...\n");
		startGame(LED_Sequence);
		generateSequence(MAX_LENGTH, LED_Sequence, LED0, LED3);
		//for each level, flashes LED's and checks user progress
		for (level = 0; level < MAX_LENGTH; level++) {
			printf("Level %i\n", level + 1);
			flashLEDS(level, LED_Sequence);
			userProgress = checkUserResponse(level, LED_Sequence);
			//if checkUserResponse returns 0, it means game over
			if (userProgress == 0) {
				game_over(RED);
				printf("\nGame Over...\n");
				if (level > highScore) {
					highScore = level;
				}
				printf("High Score: %i\n\n", highScore);
				break;
			}
			//if checkUserResponse returned -1, the user closed the window, thus the program will stop running
			else if (userProgress == -1) {
				return;
			}
			//if checkUserResponse returned 1, the user passes the level and moves on to the next
			else {
				Sleep(ONE_SECOND/3);
			}
		}
		//if userprogress maintained at 1 throughout all levels, user wins game.
		if (userProgress == 1) {
			printf("\nCongratulations! You passed all 5 levels!\n");
			highScore = MAX_LENGTH;
			printf("High score: %i\n\n", highScore);
			won_game(GREEN);
		}

		Sleep(ONE_SECOND);
	}
}