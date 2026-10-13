#ifndef ROOM_H
#define ROOM_H

struct Room {
    int x, y;           // top-left corner
    int width, height;

    int getCenterX() const { return x + width / 2; }
    int getCenterY() const { return y + height / 2; }

    // AABB overlap test with a padding buffer so rooms don't end up wall-to-wall.
    bool intersects(const Room& other, int padding = 1) const {
        return x - padding < other.x + other.width &&
               x + width + padding > other.x &&
               y - padding < other.y + other.height &&
               y + height + padding > other.y;
    }
};

#endif //ROOM_H
