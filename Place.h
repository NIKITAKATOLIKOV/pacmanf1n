#pragma once
#include <vector>

enum class Direction { Stop = 0, Right, Left, Up, Down };

class Place
{
public: short x, y, dis;
    Direction dir;
    Place(short x, short y, Direction dir, short dis);
};
std::vector<Direction> Find_Path(const std::vector<std::vector<bool>> &dec_arr, const std::vector<std::vector<short>> &dis_arr,
                                 short wX, short wY, short fwX, short fwY, Direction dir_now);
