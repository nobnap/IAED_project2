/* Used for the data type reserv */

#include "manager.h"

void read_reserv() {
	char buffer[MAX_INPUT], *ptr;
	reserv input;
	fgets(buffer, MAX_INPUT, stdin);
	ptr = strtok(buffer, " \t\n");

	input->code = malloc(sizeof(char) * (strlen(buffer) + 1));
}

/* tbm posso, utilizando scanf e strlen, ir adicionando o numero de carateres
 * ate ter MAX_INPUT? */