#include "manager.h"

void reservation() {
	int i, size = MAX_INPUT;
	flight f;
	date d;
	read_char(f.code, size, " \t");
	scanf(DATE_INPUT, &d.day, &d.month, &d.year);
	if (getchar() == '\n') {
		i = search_flight(f);
		if (i != -1) {
			reserv head = flight_list[i].passengers;
			while (head != NULL) {
				printf("%s %d", head->code, head->passengers);
				head = head->next;
			}
		}
	} else {
		reserv r; /* maybe usar char e int para n ter de alocar o espaço?? */
		char buffer[size];
		int people;

		r = (reserv)malloc(sizeof(struct reservation));

		read_char(buffer, size, " \t");
		scanf("%d", r->passengers);

		r->code = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(r->code, buffer);

		r->pFlight = &f;

		if (reservation_errors(f, r)) {
			free(r->code);
			free(r);
			return;
		}

		f.ocupation += r->passengers;
		/* adicionar a reserva de forma ordenada */
		/* lembrar de adicionar tambem à HASHTABLE */
		add_reserv(f, r);
	}
}

void add_reserv(flight f, reserv r) { /* pretty sure this method doesnt make any goddamn sense */
	int i = search_flight(f);
	reserv head;
	head = flight_list[i].passengers;
	while (head != NULL) {
		if (strcmp(head->code, r->code) < 0) {
			r->next = head;
			head = r;
			return;
		}
		head = head->next;
	}
	r->next = NULL;
	head = r;
}

int reservation_errors(flight f, reserv r) {
	if (!valid_rescode(r->code)) return printf(ERROR_RESERV_CODE);
	if (search_flight(f) == -1) return printf(ERROR_NONEXISTENT_FLIGHT, f.code);
	/* procurar a reserva, if already exists -> error (HASHTABLES) */
	if (f.ocupation + r->passengers >= f.capacity)
		return printf(ERROR_RESERV_LIMIT);
	if (compare_date(f.dep_date, current_date) == -1 ||
	    compare_date(f.dep_date, limit_date) == 1)
		return printf(ERROR_DATE);
	if (r->passengers <= 0) return printf(ERROR_PASSENGERS);
	return 0;
}

int valid_rescode(char *code) {
	int i, len = strlen(code);
	if (len < MIN_RESERVATION) return 0;
	for (i = 0; i < len; i++) {
		if ((code[i] > 'Z' || code[i] < 'A') && (code[i] > '9' || code[i] < '0'))
			return 0;
	}
	return 1;
}