/*
 * File: reservation.c
 *
 * Author: Maria João Rosa
 * Email: maria.j.rosa@tecnico.ulisboa.pt
 *
 * Description: File containing all the code relating to the reservation()
 * function.
 *
 */

#include "manager.h"

/* Lists reservations for the flight specified by the user or adds a new
 * reservation */
void reservation() {
	int i;
	flight input, *f;
	char a;

	a = getchar();

	read_char(input.code, MAX_INPUT, " \t");
	scanf(DATE_INPUT, &input.dep_date.day, &input.dep_date.month,
	      &input.dep_date.year);

	i = search_flight(&input);
	f = flight_list[i];

	if ((a = getchar()) == '\n') {
		if (res_flight_errors(&input)) return;

		if (i != -1) {
			link head = flight_list[i]->passengers;
			while (head != NULL) {
				printf("%s %d\n", head->res->code, head->res->passengers);
				head = head->next;
			}
		} else
			printf(ERROR_NONEXISTENT_FLIGHT, input.code);

	} else {
		char buffer[MAX_INPUT];
		reserv r;
		link newR;

		r = (reserv)malloc(sizeof(struct reservation));

		read_char(buffer, MAX_INPUT, " \t");
		scanf("%d", &r->passengers);

		r->code = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(r->code, buffer);

		if (reservation_errors(&input, f, r)) {
			free(r->code);
			free(r);
			return;
		}

		f->ocupation += r->passengers;
		newR = add_hash(f, r);
		add_reserv(f, newR);
	}
}

/* Adds a reservation to a linked list of flight passengers */
void add_reserv(flight *f, link rNode) {
	link head;

	if (f->passengers == NULL) {
		f->passengers = rNode;
		rNode->next = NULL;
		rNode->prev = NULL;
	} else {
		head = f->passengers;
		while (head != NULL) {
			if (strcmp(head->res->code, rNode->res->code) > 0) {
				if (head->prev == NULL) {
					f->passengers = rNode;
				} else
					head->prev->next = rNode;
				rNode->prev = head->prev;
				head->prev = rNode;
				rNode->next = head;
				return;
			}
			if (head->next == NULL) {
				head->next = rNode;
				rNode->prev = head;
				rNode->next = NULL;
				return;
			}
			head = head->next;
		}
	}
}

/* Checks for errors in the input flight and reservation */
int reservation_errors(flight *input, flight *f, reserv r) {
	if (!valid_rescode(r->code)) return printf(ERROR_RESERV_CODE);
	if (search_flight(input) == -1)
		return printf(ERROR_NONEXISTENT_FLIGHT, input->code);
	if (search_hash(r->code)) return printf(ERROR_RESERV_DUPLICATE, r->code);
	if (f->ocupation + r->passengers > f->capacity)
		return printf(ERROR_RESERV_LIMIT);
	if (compare_date(f->dep_date, current_date) == -1 ||
	    compare_date(f->dep_date, limit_date) == 1)
		return printf(ERROR_DATE);
	if (r->passengers <= 0) return printf(ERROR_PASSENGERS);
	return 0;
}

/* Checks for errors in the input flight */
int res_flight_errors(flight *f) {
	if (search_flight(f) == -1) return printf(ERROR_NONEXISTENT_FLIGHT, f->code);
	if (compare_date(f->dep_date, current_date) == -1 ||
	    compare_date(f->dep_date, limit_date) == 1)
		return printf(ERROR_DATE);
	return 0;
}

/* Checks if the input reservation code is valid */
int valid_rescode(char *code) {
	int i, len = strlen(code);
	if (len < MIN_RESERVATION) {
		return 0;
	}
	for (i = 0; i < len; i++) {
		if ((code[i] > 'Z' || code[i] < 'A') && (code[i] > '9' || code[i] < '0'))
			return 0;
	}
	return 1;
}