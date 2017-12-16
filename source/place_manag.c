/*
** EPITECH PROJECT, 2017
** place
** File description:
** place
*/

#include <curses.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
#include "my.h"

place *get_place_from_pos(place *head, int x, int y)
{
	while (head != NULL) {
		if (head->x == x && head->y == y)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void add_place(place **p, int x, int y)
{
	place *new_node = malloc(sizeof(xbox));

	new_node->x = x;
	new_node->y = y;
	new_node->filled = 0;
	new_node->next = (*p);
	(*p) = new_node;
}

void parse_place(map *m, place **p, int x, int y)
{
	if (m->map[y][x] == 'O') {
		m->map[y][x] = ' ';
		add_place(p, x, y);
	}
}

void verify_filled_place(xbox *b, place *pl, map *save)
{
	place *pls = NULL;
	xbox *hb = b;
	place *hpl = pl;

	while (b != NULL) {
		if ((pls = get_place_from_pos(pl, b->x, b->y)) != NULL \
		    && !pls->filled) {
			pls->filled = 1;
		}
		b = b->next;
	}
	b = hb;
	while (pl != NULL) {
		if (get_box_from_pos(b, pl->x, pl->y) == NULL && pl->filled)
			pl->filled = 0;
		pl = pl->next;
	}
	pl = hpl;
	verify_win(pl, save, b);
}
