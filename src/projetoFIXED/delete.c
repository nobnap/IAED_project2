/*
 * File: delete.c
 *
 * Author: Maria João Rosa
 * Email: maria.j.rosa@tecnico.ulisboa.pt
 *
 * Description: File containing all the code relating to the delete() function.
 *
 */

#include "manager.h"

/* Deletes either a flight or a reservation */
void delete () {
	int i, len, notfound = 1;
	char code[MAX_INPUT];
	scanf("%s", code);
	len = strlen(code) + 1;
	if (len < MIN_RESERVATION) {
		for (i = 0; i < num_flights; i++) {
			if (!strcmp(flight_list[i]->code, code)) {
				del_flight(i);
				i--;
				notfound = 0;
			}
		}
	} else {
		if (search_hash(code)) {
			notfound = 0;
			del_hash(code);
		}
	}
	if (notfound) printf(ERROR_NOT_FOUND);
}

/* Deletes all reservations from the flight with index i on the flight_list */
void del_allres(int i) {
	link tmp, todel = flight_list[i]->passengers;
	while (todel != NULL) {
		tmp = todel->next;
		if (search_hash(todel->res->code)) del_hash(todel->res->code);
		todel = tmp;
	}
}

/* Deletes a flight and its respective reservations */
void del_flight(int n) {
	int i;

	del_allres(n);
	free(flight_list[n]);
	for (i = n + 1; i < num_flights; i++) flight_list[i - 1] = flight_list[i];
	num_flights--;
	flight_list[num_flights] = NULL;
}

/* Deletes all flights and respective reservations */
void del_all() {
	while (flight_list[0]) del_flight(0);
}