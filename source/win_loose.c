/*
** EPITECH PROJECT, 2017
** win_loose
** File description:
** win_loose
*/

#include <curses.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
#include "my.h"

void verify_win(place *pl, map *save, xbox *b)
{
	int i = 0;
	int x = 0;

	while (pl != NULL) {
		if (pl->filled)
			i = i + 1;
		x = x + 1;
		pl = pl->next;
	}
	if (x == i) {
		endwin();
		exit(0);
	}
	verify_lose(b, save);
}

void verify_box_stucks(xbox *box, map *m, int *x)
{
	if (m->map[box->y - 1][box->x] == '#' \
	    && m->map[box->y][box->x + 1] == '#')
		*x += 1;
	else if (m->map[box->y - 1][box->x] == '#' \
		 && m->map[box->y][box->x - 1] == '#')
		*x += 1;
	else if (m->map[box->y + 1][box->x] == '#' \
		 && m->map[box->y][box->x + 1] == '#')
		*x += 1;
	else if (m->map[box->y + 1][box->x] == '#' \
		 && m->map[box->y][box->x - 1] == '#')
		*x += 1;
}

void verify_lose(xbox *box, map *m)
{
	int i = 0;
	int x = 0;

	while (box != NULL) {
		verify_box_stucks(box, m, &x);
		i = i + 1;
		box = box->next;
	}
	if (x == i) {
		endwin();
		exit(1);
	}
}
