/*
** EPITECH PROJECT, 2017
** box
** File description:
** box
*/

#include <curses.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
#include "my.h"

xbox *get_box_from_pos(xbox *head, int x, int y)
{
	while (head != NULL) {
		if (head->x == x && head->y == y)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void add_box(xbox **b, int x, int y)
{
	xbox *new_node = malloc(sizeof(xbox));

	new_node->x = x;
	new_node->y = y;
	new_node->next = (*b);
	(*b) = new_node;
}

void free_box(xbox **b)
{
	xbox *prev = *b;

	while (*b != NULL) {
		prev = (*b);
		free(prev);
		(*b) = (*b)->next;
	}
	free(*b);
}

void copy_box_list(xbox *from, xbox **to)
{
	free_box(to);
	while (from != NULL) {
		add_box(to, from->x, from->y);
		from = from->next;
	}
}

void parse_box(map *m, xbox **b, int x, int y)
{
	if (m->map[y][x] == 'X') {
		m->map[y][x] = ' ';
		add_box(b, x, y);
	}
}
