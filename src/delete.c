#include "manager.h"

void delete () {
	int i, len, notfound = 1;
	char code[MAX_INPUT];
	scanf("%s", code);
	len = strlen(code)+1;
	if (len < MIN_RESERVATION) {
		for (i = 0; i < num_flights; i++) {
			if (!strcmp(flight_list[i].code, code)) {
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


void del_allres(int i) {
	link tmp, todel = flight_list[i].passengers;
	while (todel != NULL) {
		tmp = todel->next;
		del_hash(todel->res->code);
		todel = tmp;
	}
}

void del_flight(int n) {
	int i;

	del_allres(n);
	for (i = n + 1; i < num_flights; i++) flight_list[i - 1] = flight_list[i];
	num_flights--;
}

void del_all() {
	int i;
	for (i = 0; i < num_flights; i++) del_allres(i);
}