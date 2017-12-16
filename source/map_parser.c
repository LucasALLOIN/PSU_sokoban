/*
** EPITECH PROJECT, 2017
** map_parser
** File description:
** map_parser
*/

#include <curses.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
#include "my.h"

void verify_map_char(char c)
{
	if (c != '\n' && c != ' ' && c != '#')
		exit(84);
}

void verify_map(map *m)
{
	int x = 0;
	int y = 0;

	for (; y < m->width; y = y + 1)
		for (x = 0; x < m->len[y]; x = x + 1)
			verify_map_char(m->map[y][x]);
}

map *parse_map(map *m, player *p, xbox **b, place **place)
{
	int y = 0;
	int x = 0;

	for (; y < m->width; y = y + 1) {
		for (x = 0; x < m->len[y]; x = x + 1) {
			parse_player(m, p, x, y);
			parse_box(m, b, x, y);
			parse_place(m, place, x, y);
		}
	}
	verify_map(m);
	return (m);
}

void prepare_map(char **argv, int argc, map **save)
{
	int size = 0;

	verify_error(argc, argv);
	size = get_nbr_line(argv[1]);
	*save = save_map(argv[1], size);
}
