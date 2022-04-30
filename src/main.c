/*
 * File: main.c
 *
 * Author: Maria João Rosa
 * Email: maria.j.rosa@tecnico.ulisboa.pt
 *
 * Description: File containing all the code used in the first Introduction to
 * Algorithms and Data Structures project.
 *
 */

#include "manager.h"

/*
 * Definition of Global Variables
 */

/* Default date at startup */
date current_date = {1, 1, 2022};

/* Date until which new flights can be added */
date limit_date = {1, 1, 2023};

/* List of flights */
flight* flight_list[MAX_FLIGHTS];
/* Number of existing flights */
int num_flights = 0;

/* List of existing airports */
airport airports[MAX_AIRPORT];
/* Number of existing airports */
int num_airport = 0;

/* Hashtable used to save the reservations */
hLink hashtable[1013];

/*
 * Command Related Functions
 */

/* Initializes the hash, calls the input_reader() function and deletes all
 * flights and respective reservations when the program is ended */
int main() {
	initHash();
	while (input_reader());
	del_all();
	return 0;
}

/* Determines which function to run depending on the command */
int input_reader() {
	char command;
	command = getchar();
	switch (command) {
		case 'q':
			return EXIT_SUCCESS;
		case 'a':
			add_airport();
			break;
		case 'l':
			list_airport();
			break;
		case 'v':
			flights();
			break;
		case 'p':
			departures();
			break;
		case 'c':
			arrivals();
			break;
		case 't':
			date_forward();
			break;
		case 'r':
			reservation();
			break;
		case 'e':
			delete();
			break;
	}
	return 1;
}