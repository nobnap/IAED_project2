#include "manager.h"

void reservation() {
	int i;
	flight input;
	char a;

	a = getchar();

	read_char(input.code, MAX_INPUT, " \t");
	scanf(DATE_INPUT, &input.dep_date.day, &input.dep_date.month, &input.dep_date.year);

	i = search_flight(input);

	if ((a = getchar()) == '\n') {
		if (i != -1) {
			link head = flight_list[i].passengers;
			while (head != NULL) {
				printf("%s %d\n", head->res->code, head->res->passengers);
				head = head->next;
			}
		} else
			printf(ERROR_NONEXISTENT_FLIGHT, input.code);

	} else {
		reserv r;
		char buffer[MAX_INPUT];
		flight *f = &flight_list[i];

		r = (reserv)malloc(sizeof(struct reservation));

		read_char(buffer, MAX_INPUT, " \t");
		scanf("%d", &r->passengers);

		r->code = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(r->code, buffer);

		if (reservation_errors(f, r)) {
			free(r->code);
			free(r);
			return;
		}

		f->ocupation += r->passengers;
		/* adicionar a reserva de forma ordenada */
		/* lembrar de adicionar tambem à HASHTABLE */
		add_reserv(f, r);
		/* add_hash(r); */
	}
}

void add_reserv(flight *f, reserv r) {
	link head, newNode;

	head = f->passengers;

	newNode = (link)malloc(sizeof(struct node));
	newNode->res = r;

	if (head == NULL) {
		f->passengers = newNode;
		newNode->next = NULL;
		return;
	} else {
		while (head->next != NULL) {
			if (strcmp(head->next->res->code, r->code) > 0) {
				newNode->next = head->next;
				head->next = newNode;
				return;
			}
			head = head->next;
		}
	}

	newNode->next = NULL;
	head->next = newNode;
}

/* void add_hash(reserv r) {

} */

int reservation_errors(flight *f, reserv r) {
	if (!valid_rescode(r->code)) return printf(ERROR_RESERV_CODE);
	if (search_flight(*f) == -1) return printf(ERROR_NONEXISTENT_FLIGHT, f->code);
	/* procurar a reserva, if already exists -> error (HASHTABLES) */
	if (f->ocupation + r->passengers > f->capacity) return printf(ERROR_RESERV_LIMIT);
	if (compare_date(f->dep_date, current_date) == -1 ||
	    compare_date(f->dep_date, limit_date) == 1)
		return printf(ERROR_DATE);
	if (r->passengers <= 0) return printf(ERROR_PASSENGERS);
	return 0;
}

int valid_rescode(char *code) {
	int i, len = strlen(code);
	if (len < MIN_RESERVATION) {
		printf("HERE %s\n%d\n", code, len);
		return 0;
	}
	for (i = 0; i < len; i++) {
		if ((code[i] > 'Z' || code[i] < 'A') && (code[i] > '9' || code[i] < '0'))
			return 0;
	}
	return 1;
}