/* HASHTABLES */

#include "manager.h"

void innitHash() {
	int i;
	for (i = 0; i < 0; i++) hashtable[i] = NULL;
}

int hash(char *code) {
	int i, h = 0, a = 127, M = 1013;
	for (i=0;code[i] != '\0';i++) {
		h = (a * h + code[i]) % M;
	}
	return h;
}

link add_hash(flight *f, reserv r) {
	int h;
	link newNode;
	hLink newHash, head;

	newNode = (link)malloc(sizeof(struct node));
	newNode->res = r;

	newHash = (hLink)malloc(sizeof(struct hNode));
	newHash->rNode = newNode;
	newHash->dep = f;

	h = hash(r->code);
	head = hashtable[h];
	if (head == NULL) {
		hashtable[h] = newHash;
		newHash->next = NULL;
	} else {
		newHash->next = head;
		hashtable[h] = newHash;
	}

	return newNode;
}

hLink search_hash(char *code) {
	int h = hash(code);
	hLink head = hashtable[h];
	while (head) {
		if (!strcmp(head->rNode->res->code, code)) {
			return head;
		}
		head = head->next;
	}
	return NULL;
}

void del_hash(char *code) {
	int h = hash(code);
	hLink head = NULL, todel = hashtable[h];
	link node;
	while (todel) {
		if (!strcmp(todel->rNode->res->code, code)) {
			if (head) head->next = todel->next;
			else hashtable[h] = NULL;
			break;
		}
		head = todel;
		todel = todel->next;
	}

	node = todel->rNode;
	if (node->next) node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	else
		todel->dep->passengers = node->next;
	
	todel->dep->ocupation -= todel->rNode->res->passengers;

	free(todel->rNode->res->code);
	free(todel->rNode->res);
	free(todel->rNode);
	free(todel);
}