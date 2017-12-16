/*
** EPITECH PROJECT, 2017
** player
** File description:
** player
*/

#include <curses.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
#include "my.h"

void parse_player(map *m, player *p, int x, int y)
{
	if (m->map[y][x] == 'P') {
		m->map[y][x] = ' ';
		(*p).x = x;
		(*p).y = y;
	}
}

void player_pos(char c, player *p, int x, int y)
{
	if (c == 'P') {
		p->x = x;
		p->y = y;
	}
}

player get_player_pos(map *map)
{
	int x = 0;
	int y = 0;
	player res;

	for (; y < map->width; y = y + 1) {
		for (x = 0; x < map->len[y]; x = x + 1) {
			player_pos(map->map[y][x], &res, y, x);
		}
	}
	return (res);
}

void copy_player(player from, player *to)
{
	(*to).x = from.x;
	(*to).y = from.y;
}
