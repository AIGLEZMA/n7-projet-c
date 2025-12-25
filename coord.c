#include "coord.h"
#include "math.h"

coord_t creer_coord(int x, int y) {
    coord_t coord;

    coord.x = x;
    coord.y = y;

    return coord;
}

int get_x(coord_t coord) {
    return coord.x;
}

int get_y(coord_t coord) {
    return coord.y;
}

void set_x(coord_t *coord, int x) {
    coord->x = x;
}

void set_y(coord_t *coord, int y) {
    coord->y = y;
}

coord_t translation(coord_t coord, int dx, int dy) {
    int x = dx + coord.x;
    int y = dy + coord.y;
    
    return creer_coord(x, y);
}

float distance_euclidienne(coord_t coord_a, coord_t coord_b) {
    float dx = coord_b.x - coord_a.x;
    float dy = coord_b.y - coord_a.y;

    return sqrtf(dx * dx + dy * dy);
}

int memes_coord(coord_t a, coord_t b) {
    return a.x == b.x && a.y == b.y;
}