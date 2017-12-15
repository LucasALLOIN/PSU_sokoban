/*
** EPITECH PROJECT, 2017
** Project my_sokoban
** File description:
** Main file.
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

void parse_player(map *m, player *p, int x, int y)
{
	if (m->map[y][x] == 'P') {
		m->map[y][x] = ' ';
		(*p).x = x;
		(*p).y = y;
	}
}

xbox *get_box_from_pos(xbox *head, int x, int y)
{	
	while (head != NULL) {
		if (head->x == x && head->y == y)
			return (head);
		head = head->next;
	}
	return (NULL);
}

place *get_place_from_pos(place *head, int x, int y)
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
        return (m);
}

player get_player_pos(map *map)
{
        int x = 0;
        int y = 0;
        player res;

        for (; y < map->width; y = y + 1) {
                for (x = 0; x < map->len[y]; x = x + 1) {
                        res.x = (map->map[y][x] == 'P') ? x : res.x;
                        res.y = (map->map[y][x] == 'P') ? y : res.y;
                }
        }
        return (res);
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

void move_player(map *m, player *p, int dir, xbox **b)
{
	xbox *box = NULL;
	
	if (dir == KEY_UP) {
		if (m->map[(*p).y - 1][(*p).x] != '#') {
			if ((box = get_box_from_pos(*b, (*p).x, (*p).y - 1)) != NULL) {
				if (m->map[(*p).y - 2][(*p).x] != '#' && get_box_from_pos(*b, (*p).x, (*p).y - 2) == NULL) {
					box->y -= 1;
					(*p).y = (*p).y - 1;
				}
			} else
				(*p).y = (*p).y - 1;
		}
	} else if (dir == KEY_LEFT) {
		if (m->map[(*p).y][(*p).x - 1] != '#') {
			if ((box = get_box_from_pos(*b, (*p).x - 1, (*p).y)) != NULL) {
				if (m->map[(*p).y][(*p).x - 2] != '#' && get_box_from_pos(*b, (*p).x - 2, (*p).y) == NULL) {
                                        box->x -= 1;
					(*p).x = (*p).x - 1;
                                }
                        } else
				(*p).x = (*p).x - 1;
		}
	} else if (dir == KEY_RIGHT) {
		if (m->map[(*p).y][(*p).x + 1] != '#') {
                        if ((box = get_box_from_pos(*b, (*p).x + 1, (*p).y)) != NULL) {
				if (m->map[(*p).y][(*p).x + 2] != '#' && get_box_from_pos(*b, (*p).x + 2, (*p).y) == NULL) {
                                        box->x += 1;
					(*p).x = (*p).x + 1;
                                }
                        } else
				(*p).x = (*p).x + 1;
		}
	} else if (dir == KEY_DOWN) {
		if (m->map[(*p).y + 1][(*p).x] != '#') {
                        if ((box = get_box_from_pos(*b, (*p).x, (*p).y + 1)) != NULL) {
				if (m->map[(*p).y + 2][(*p).x] != '#' && get_box_from_pos(*b, (*p).x, (*p).y + 2) == NULL) {
                                        box->y += 1;
					(*p).y = (*p).y + 1;
                                }
                        } else
				(*p).y = (*p).y + 1;
		}
	}
}

void display_list(place *b)
{
	while (b != NULL) {
		my_put_nbr(b->x);
		my_putchar(' ');
		my_put_nbr(b->filled);
		my_putchar('\n');
		b = b->next;
	}
}

void verify_win(place *pl)
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
}

void verify_filled_place(xbox *b, place *pl)
{
	place *pls = NULL;
	xbox *hb = b;
	place *hpl = pl;

	while (b != NULL) {
		if ((pls = get_place_from_pos(pl, b->x, b->y)) != NULL && !pls->filled) {
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
	verify_win(pl);
}

void copy_player(player from, player *to)
{
	(*to).x = from.x;
	(*to).y = from.y;
}

void reset_map(player *p, player p_save, xbox **b, xbox *box_save)
{
	copy_player(p_save, p);
	copy_box_list(box_save, b);
}

void verify_lose(xbox *box, map *m)
{
	int i = 0;
	int x = 0;
	
	while (box != NULL) {
		if (m->map[box->y - 1][box->x] == '#' && m->map[box->y][box->x + 1] == '#')
			x = x + 1;
		if (m->map[box->y - 1][box->x] == '#' && m->map[box->y][box->x - 1] == '#')
			x = x +	1;
		if (m->map[box->y + 1][box->x] == '#' && m->map[box->y][box->x + 1] == '#')
			x = x +	1;
		if (m->map[box->y + 1][box->x] == '#' && m->map[box->y][box->x - 1] == '#')
			x = x +	1;
		i = i + 1;
		box = box->next;
	}
	if (x == i) {
		endwin();
		exit(0);
	}	
}
	       
int main(int argc, char *argv[])
{
	map *save = NULL;
	int size = get_nbr_line(argv[1]);
	player p;
	player p_save;
	xbox *b = NULL;
	xbox *box_save = NULL;
	place *place = NULL;
	int key;

	(void) argc;
	save = save_map(argv[1], size);
	save = parse_map(save, &p, &b, &place);
	copy_box_list(b, &box_save);
	copy_player(p, &p_save);
        initscr();
	keypad (stdscr, TRUE);
	noecho();
	curs_set(0);
	while (1) {
		display_map(save, p, b, place);
		key = getch();
		move_player(save, &p, key, &b);
		if (key == 32)
			reset_map(&p, p_save, &b, box_save);
		verify_filled_place(b, place);
		verify_lose(b, save);
		refresh();
	}
        endwin();
	return (0);
}
