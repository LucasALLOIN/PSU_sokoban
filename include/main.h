/*
** EPITECH PROJECT, 2017
** Project my_sokoban
** File description:
** Header file
*/

#ifndef MAIN_H_
#define MAIN_H_
#include <stdlib.h>
#include <stdio.h>

typedef struct s_map {
	char **map;
	int width;
	int *len;
} map;

typedef struct s_player {
	int y;
	int x;
} player;

typedef struct s_box {
	int y;
	int x;
	struct s_box *next;
} xbox;

typedef struct s_place {
	int y;
	int x;
	int filled;
	struct s_place *next;
} place;

int get_nbr_line(char *file);
void verify_box_stucks(xbox *box, map *m, int *x);
void parse_player(map *m, player *p, int x, int y);
xbox *get_box_from_pos(xbox *head, int x, int y);
place *get_place_from_pos(place *head, int x, int y);
void add_box(xbox **b, int x, int y);
void free_box(xbox **b);
void copy_box_list(xbox *from, xbox **to);
void verify_map_char(char c);
void verify_map(map *m);
void parse_box(map *m, xbox **b, int x, int y);
void add_place(place **p, int x, int y);
void parse_place(map *m, place **p, int x, int y);
map *parse_map(map *m, player *p, xbox **b, place **place);
void player_pos(char c, player *p, int x, int y);
player get_player_pos(map *map);
map *save_map(char *file, int size);
void display_map(map *map, player p, xbox *b, place *place);
void verify_col_y(map *m, player *p, xbox **b, int val);
void verify_col_x(map *m, player *p, xbox **b, int val);
void move_y(map *m, player *p, xbox **b, int val);
void move_x(map *m, player *p, xbox **b, int val);
void move_player(map *m, player *p, int dir, xbox **b);
void display_list(place *b);
void verify_lose(xbox *box, map *m);
void verify_win(place *pl, map *save, xbox *b);
void verify_filled_place(xbox *b, place *pl, map *save);
void copy_player(player from, player *to);
void reset_map(player *p, player p_save, xbox **b, xbox *box_save);
void verify_error(int argc, char **argv);
void init_sokoban(void);
void prepare_launch(xbox **b, xbox **box_save, player *p, player *p_save);
void prepare_map(char **argv, int argc, map **save);
int main(int argc, char *argv[]);

#endif
