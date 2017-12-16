/*
** EPITECH PROJECT, 2017
** map
** File description:
** map
*/

#include <curses.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
#include "my.h"

int get_nbr_line(char *file)
{
	FILE *fd = fopen(file, "r");
	char *line = NULL;
	size_t len = 0;
	int i = 0;

	while ((getline(&line, &len, fd)) != -1)
		i = i + 1;
	fclose(fd);
	return (i);
}

map *save_map(char *file, int size)
{
	FILE *fd = fopen(file, "r");
	char *line = NULL;
	size_t len = 0;
	map *res = malloc(sizeof(map));
	ssize_t read;
	int i = 0;

	res->map = malloc(sizeof(char *) * size + 1);
	res->len = malloc(sizeof(int) * size + 1);
	while ((read = getline(&line, &len, fd)) != -1) {
		res->map[i] = malloc(read + 1);
		res->len[i] = read;
		for (int y = 0; line[y]; y = y + 1)
			res->map[i][y] = line[y];
		i = i + 1;
	}
	res->width = size;
	fclose(fd);
	return (res);
}

void display_map(map *map, player p, xbox *b, place *place)
{
	for (int i = 0; i != map->width; i = i + 1)
		mvprintw(i, 0, "%s", map->map[i]);
	for (; place != NULL; place = place->next)
		mvprintw(place->y, place->x, "%c", 'O');
	mvprintw(p.y, p.x, "%c", 'P');
	for (; b != NULL; b = b->next)
		mvprintw(b->y, b->x, "%c", 'X');
}

void reset_map(player *p, player p_save, xbox **b, xbox *box_save)
{
	copy_player(p_save, p);
	copy_box_list(box_save, b);
}
