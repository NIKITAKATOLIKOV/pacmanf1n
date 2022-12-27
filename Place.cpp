#include "Place.h"

Place::Place(short x, short y, Direction dir, short dis) :
        x(x), y(y), dis(dis), dir(dir) {
}

std::vector<Direction>
Find_Path(const std::vector<std::vector<bool>> &dec_arr, const std::vector<std::vector<short>> &dis_arr,
          short wX, short wY, short fwX, short fwY,
          Direction dir_now) {// алгоритм Дейкстры (нахождение кратчайшего пути)
    short i, x_left = fwX, y_left = fwY, Pdis, dis_left;
    std::vector<std::vector<bool>> dec_arrV;
    std::vector<std::vector<short>> dis_arrV;
    std::vector<Direction> dir_vec;
    std::vector<Place> arr;
    arr.push_back(Place(wX, wY, dir_now, 0));
    dec_arrV = dec_arr;
    dis_arrV = dis_arr;
    dis_arrV[wY][wX] = 0;
    for (i = 0; i < short(arr.size()); ++i) {
        Place value = arr[i];
        if (value.dir != Direction::Left && value.x <= 27) {
            if (value.x == 27) {
                if (!dec_arrV[value.y][0]) {
                    arr.push_back(Place(0, value.y, Direction::Right, value.dis + 1));
                    if (dis_arrV[value.y][0] > dis_arrV[value.y][27] + 1) {
                        dis_arrV[value.y][0] = dis_arrV[value.y][27] + 1;
                    }
                }
            } else if (!dec_arrV[value.y][value.x + 1]) {
                arr.push_back(Place(value.x + 1, value.y, Direction::Right, value.dis + 1));
                if (dis_arrV[value.y][value.x + 1] > dis_arrV[value.y][value.x] + 1) {
                    dis_arrV[value.y][value.x + 1] = dis_arrV[value.y][value.x] + 1;
                }
            }
        }
        if (value.dir != Direction::Right && value.x >= 0) {
            if (value.x == 0) {
                if (!dec_arrV[value.y][27]) {
                    arr.push_back(Place(27, value.y, Direction::Left, value.dis + 1));
                    if (dis_arrV[value.y][27] > dis_arrV[value.y][0] + 1)
                        dis_arrV[value.y][27] = dis_arrV[value.y][0] + 1;
                }
            } else if (!dec_arrV[value.y][value.x - 1]) {
                arr.push_back(Place(value.x - 1, value.y, Direction::Left, value.dis + 1));
                if (dis_arrV[value.y][value.x - 1] > dis_arrV[value.y][value.x] + 1)
                    dis_arrV[value.y][value.x - 1] = dis_arrV[value.y][value.x] + 1;
            }
        }
        if (value.dir != Direction::Up && value.y < 28)
            if (!dec_arrV[value.y + 1][value.x]) {
                arr.push_back(Place(value.x, value.y + 1, Direction::Down, value.dis + 1));
                if (dis_arrV[value.y + 1][value.x] > dis_arrV[value.y][value.x] + 1)
                    dis_arrV[value.y + 1][value.x] = dis_arrV[value.y][value.x] + 1;
            }
        if (value.dir != Direction::Down && value.y > 0) {
            if (!dec_arrV[value.y - 1][value.x]) {
                arr.push_back(Place(value.x, value.y - 1, Direction::Up, value.dis + 1));
                if (dis_arrV[value.y - 1][value.x] > dis_arrV[value.y][value.x] + 1) {
                    dis_arrV[value.y - 1][value.x] = dis_arrV[value.y][value.x] + 1;
                }
            }
            dec_arrV[value.y][value.x] = true;
        }
    }
    Pdis = dis_left = dis_arrV[y_left][x_left];
    for (i = 0; i < Pdis; ++i) {
        if (x_left + 1 < 28 && dis_left == dis_arrV[y_left][x_left + 1] + 1) {
            dir_vec.push_back(Direction::Left), --dis_left, ++x_left;
        } else if (x_left == 27 && dis_left == dis_arrV[y_left][0] + 1) {
            dir_vec.push_back(Direction::Left), --dis_left, x_left = 0;
        } else if (x_left - 1 >= 0 && dis_left == dis_arrV[y_left][x_left - 1] + 1) {
            dir_vec.push_back(Direction::Right), --dis_left, --x_left;
        } else if (x_left == 0 && dis_left == dis_arrV[y_left][27] + 1) {
            dir_vec.push_back(Direction::Right), --dis_left, x_left = 27;
        } else if (y_left + 1 < 29 && dis_left == dis_arrV[y_left + 1][x_left] + 1) {
            dir_vec.push_back(Direction::Up), --dis_left, ++y_left;
        } else if (y_left - 1 >= 0 && dis_left == dis_arrV[y_left - 1][x_left] + 1) {
            dir_vec.push_back(Direction::Down), --dis_left, --y_left;
        }
    }
    return dir_vec;
}