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

void display_usage(void)
{
	my_putstr("USAGE\n");
	my_putstr("     ./my_sokoban map\n");
	my_putstr("DESCRIPTION\n");
	my_putstr("     map file representing the warehouse map, ");
	my_putstr("containing ‘#’ for walls,\n");
	my_putstr("          ‘P’ for the player, ");
	my_putstr("‘X’ for boxes and ‘O’ for storage locations.\n");
	exit(0);
}

void verify_error(int argc, char **argv)
{
	int file = open(argv[1], O_RDONLY);

	if (argc < 2)
		exit(84);
	if (my_strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'h')
		display_usage();
	if (file < 0)
		exit(84);
}

void init_sokoban(void)
{
	initscr();
	keypad (stdscr, TRUE);
	noecho();
	curs_set(0);
}

void prepare_launch(xbox **b, xbox **box_save, player *p, player *p_save)
{
	copy_box_list(*b, box_save);
	copy_player(*p, p_save);
	init_sokoban();
}

int main(int argc, char *argv[])
{
	map *save = NULL;
	player p;
	player p_save;
	xbox *b = NULL;
	xbox *box_save = NULL;
	place *place = NULL;
	int key;

	prepare_map(argv, argc, &save);
	save = parse_map(save, &p, &b, &place);
	prepare_launch(&b, &box_save, &p, &p_save);
	while (1) {
		display_map(save, p, b, place);
		key = getch();
		move_player(save, &p, key, &b);
		if (key == 32)
			reset_map(&p, p_save, &b, box_save);
		verify_filled_place(b, place, save);
		refresh();
	}
	return (0);
}
