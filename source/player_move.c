/*
** EPITECH PROJECT, 2017
** player_move
** File description:
** player_move
*/

#include <curses.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
#include "my.h"

void verify_col_y(map *m, player *p, xbox **b, int val)
{
	xbox *box = NULL;
	int x = 0;

	x = (val < 0) ? -1 : 1;
	if ((box = get_box_from_pos(*b, (*p).x, (*p).y + val)) != NULL) {
		if (m->map[(*p).y + val + x][(*p).x] != '#' \
		    && get_box_from_pos(*b, (*p).x, (*p).y + val + x) == NULL) {
			box->y += val;
			(*p).y = (*p).y + val;
		}
	} else
		(*p).y = (*p).y + val;
}

void verify_col_x(map *m, player *p, xbox **b, int val)
{
	xbox *box = NULL;
	int x = 0;

	x = (val < 0) ? -1 : 1;
	if ((box = get_box_from_pos(*b, (*p).x + val, (*p).y)) != NULL) {
		if (m->map[(*p).y][(*p).x + val + x] != '#' \
		    && get_box_from_pos(*b, (*p).x + val + x, (*p).y) == NULL) {
			box->x += val;
			(*p).x = (*p).x + val;
		}
	} else
		(*p).x = (*p).x + val;
}

void move_y(map *m, player *p, xbox **b, int val)
{
	if (m->map[(*p).y + val][(*p).x] != '#') {
		verify_col_y(m, p, b, val);
	}
}

void move_x(map *m, player *p, xbox **b, int val)
{
	if (m->map[(*p).y][(*p).x + val] != '#') {
		verify_col_x(m, p, b, val);
	}
}

void move_player(map *m, player *p, int dir, xbox **b)
{
	switch (dir) {
	case KEY_UP:
		move_y(m, p, b, -1);
		break;
	case KEY_DOWN:
		move_y(m, p, b, 1);
		break;
	case KEY_LEFT:
		move_x(m, p, b, -1);
		break;
	case KEY_RIGHT:
		move_x(m, p, b, 1);
	}
}
