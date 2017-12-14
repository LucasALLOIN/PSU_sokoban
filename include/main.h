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

#endif
