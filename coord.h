// Note : ne pas oublier la garde pour le header
#ifndef COORD_H
#define COORD_H

typedef struct {
    int x;
    int y;
} coord_t;

coord_t creer_coord(int x, int y);

int get_x(coord_t coord);

int get_y(coord_t coord);

void set_x(coord_t* coord, int x);

void set_y(coord_t* coord, int y);

coord_t translation(coord_t coord, int dx, int dy);

float distance_euclidienne(coord_t coord_a, coord_t coord_b);

int memes_coord(coord_t a, coord_t b);

#endif