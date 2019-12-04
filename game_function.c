/*
** EPITECH PROJECT, 2019
** PSU_my_sokoban_2019
** File description:
** game loop
*/

#include "my_sokoban.h"

static int get_width_line(const map_t *map, const int line)
{
    int i_line = 1;
    int len = 0;

    for (int i = 0; map->map[i] != '\0'; i++) {
        if (map->map[i] == '\n' && i_line == line) {
            break;
        } else if (map->map[i] == '\n') {
            i_line++;
        }
        if (i_line == line)
            len++;
    }
    return len;
}

static int get_line(const map_t *map, const int position)
{
    int i_line = 1;

    if (position >= map->size)
        return 0;
    for (int i = 0; i <= position; i++) {
        if (map->map[i] == '\n')
            i_line++;
    }
    return i_line;
}

int get_destination(map_t *map, int pos, int key)
{
    int dest = -1;
    int line_player = get_line(map, pos);

    if (key == K_DOWN)
        dest = pos + get_width_line(map, line_player);
    else if (key == K_UP && line_player > 2)
        dest = pos - get_width_line(map, line_player);
    if (key == K_LEFT)
        dest = pos - 1;
    else if (key == K_RIGHT)
        dest = pos + 1;
    if (dest >= map->size)
        dest = -1;
    return dest;
}

void player_check_and_move(map_t *map, int key)
{
    int dst = get_destination(map, map->player_pos, key);
    int cancel_move = 0;

    if (dst == -1)
        return;
    if (is_object_pos(dst, map->box_pos, map->nb_box))
        cancel_move = box_check_and_move(map, dst, key);
    if (map->map[dst] != '#') {
        if (!cancel_move) {
            map->player_pos = dst;
            printw("m \n");
        }
    }
}
