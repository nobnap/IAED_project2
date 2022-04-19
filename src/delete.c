#include "manager.h"

/* maybe make voos (single) linked lists?????????? */

void delete() {
	int i, len;
	char input[MAX_INPUT], *code;
	scanf("%s", input);
	len = strlen(input);
	code = malloc(sizeof(char) * (len + 1)); /* is the alloc even necessary????????? can't i just use the string as is??? */
	if (len < MIN_RESERVATION) {
		for (i = 0; i < num_flights; i++) {
			if (!strcmp(flight_list[i].code, code)) {
				del_flight(i);
				i--;
			}
		}
	} else {
		for (i = 0; i < num_flights; i++) {
			while (head != NULL) {
				if (!strcmp(head->code, code)) {
					
					return;
				}
			}
		}
	}
	printf(ERROR_NOT_FOUND);
}

void del_flight(int n) {
	int i;
	reserv tmp, todel = flight_list[i].passengers;
	while (todel != NULL) {
		tmp = todel->next;
		free(todel);
		todel = tmp;
	}
	for (i = n + 1; i < num_flights; i++) {
		flight_list[i - 1] = flight_list[i];
	}
	num_flights--;
}