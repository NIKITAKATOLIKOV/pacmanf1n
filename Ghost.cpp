#include "Ghost.h"

Ghost::Ghost(Pacman& pacman, GhostType name, int x, int y) : name(name), x(x), y(y)

{// конструктор
    Px = pacman.getX();
    Py = pacman.getY();
    mapX = x * DISTANCE + 62.5f;
    mapY = y * DISTANCE + 64.f;
    distance = DISTANCE;
    wasEaten = wasScare = revived = false;
    state = GhostState::Normal;
    speed = 1.25f;
    side = 30;
}

void  Ghost::draw(sf::RenderWindow& win, const std::vector<std::vector<bool>> &dec_arr,
                  const std::vector<std::vector<short>> &dis_arr,
                  sf::Texture& TGhostE, sf::Texture& TGhostN_0,
                  sf::Texture& TGhostN_1, sf::Texture& TGhostS_0,
                  sf::Texture& TGhostS_1, short& time_passed, signed char& second_scared, signed char& killed_count)
{// рисовка приведения
    short randAngle = rand() % 4;
    sf::Sprite sprite;
    sprite.setPosition(mapX, mapY);
    sprite.setOrigin(side / 2.f, side / 2.f);
    if (state != GhostState::Eaten && second_scared == char(0) && wasScare) // изменение состояния на нормальное при истечении срока действия энергетика
    {
        distance == DISTANCE ? dir_vec = Find_Path(dec_arr, dis_arr, x, y, Px, Py,
                                                   dir_vec.size() > 0 ? dir_vec.back() : Direction::Stop), wasScare = false
                             : NULL, killed_count = char(0), revived = false, state = GhostState::Normal;
    }
    if (state != GhostState::Eaten && !revived && second_scared != 0 && (!wasScare || dir_vec.size() == 0)) // изменение состояния на испуганное во время действия энергетика
    {
        distance == DISTANCE ? (dir_vec = Find_Path(dec_arr, dis_arr, x, y, randAngle % 2 == 0 ? 1 : 26,
                                                    randAngle > 1 ? 28 : 0, Direction::Stop), wasScare = true)
                             : NULL, state = GhostState::Scared;
    }
    switch (state)
    {// анимация движения
        case GhostState::Normal:
            time_passed < 250 || (time_passed > 500 && time_passed < 750) ? sprite.setTexture(TGhostN_0) : sprite.setTexture(TGhostN_1);
            break;
        case GhostState::Scared:
            time_passed <= 500 && second_scared < 3 ? sprite.setTexture(TGhostN_0) : time_passed > 500 && second_scared < 3 ? sprite.setTexture(TGhostS_1) : time_passed < 250 || (time_passed > 500 && time_passed < 750) ? sprite.setTexture(TGhostS_0) : sprite.setTexture(TGhostS_1);
            break;
        case GhostState::Eaten:
            sprite.setTexture(TGhostE);
            break;
    }
    switch (name)
    {// характерный имени цвет
        case GhostType::Blue:
            if (state != GhostState::Scared)
            {
                sprite.setColor(sf::Color(128, 255, 255));
            }
            break;
        case GhostType::Red:
            if (state != GhostState::Scared)
            {
                sprite.setColor(sf::Color::Red);
            }
            break;
        case GhostType::Orange:
            if (state != GhostState::Scared)
            {
                sprite.setColor(sf::Color(255, 128, 0));
            }
            break;
        case GhostType::Pink:
            if (state != GhostState::Scared)
            {
                sprite.setColor(sf::Color(255, 128, 255));
            }
            break;
    }
    win.draw(sprite);
}

void  Ghost::move(Pacman& pacman, const std::vector<std::vector<bool>> &dec_arr,
                  const std::vector<std::vector<short>> &dis_arr, const std::array<std::array<short, 28>, 29>& map,
                  unsigned int& score, unsigned int lenght, signed char& killed_count,
                  signed char second_scared, signed char level, short& GRedX, short& GRedY, Direction Plast_dir, bool& gameOver, bool& deathPacman)
{// логика приведения
    short Nspeed = short(speed / STEP), i = 0, j = 0;
    Direction dir_now = dir_vec.size() > 0 ? dir_vec.back() : Direction::Stop;
    if (dir_vec.size() > 0)
        switch (dir_now)
        {// движение по карте
            case Direction::Right:
                if (x == 27)
                {
                    if (distance < DISTANCE / 2)
                    {
                        mapX = 62.5f + -1 * distance;
                    }
                    for (; j < Nspeed; ++j)
                    {
                        distance != 0 ? (mapX += STEP, distance -= STEP) : (dir_vec.pop_back(), distance = DISTANCE, x = 0, j = Nspeed);
                    }
                }
                else
                    for (; j < Nspeed; ++j)
                    {
                        distance != 0 ? (mapX += STEP, distance -= STEP) : (dir_vec.pop_back(), distance = DISTANCE, ++x, j = Nspeed);
                    }
                break;
            case Direction::Left:
                if (x == 0)
                {
                    if (distance < DISTANCE / 2)
                    {
                        mapX = lenght - 62.5f + distance;
                    }
                    for (; j < Nspeed; ++j)
                    {
                        distance != 0 ? (mapX -= STEP, distance -= STEP) : (dir_vec.pop_back(), distance = DISTANCE, x = 27, j = Nspeed);
                    }
                }
                else
                    for (; j < Nspeed; ++j)
                    {
                        distance != 0 ? (mapX -= STEP, distance -= STEP) : (dir_vec.pop_back(), distance = DISTANCE, --x, j = Nspeed);
                    }
                break;
            case Direction::Down:
                for (; j < Nspeed; ++j)
                {
                    distance != 0 ? (mapY += STEP, distance -= STEP) : (dir_vec.pop_back(), distance = DISTANCE, ++y, j = Nspeed);
                }
                break;
            case Direction::Up:
                for (; j < Nspeed; ++j)
                {
                    distance != 0 ? (mapY -= STEP, distance -= STEP) : (dir_vec.pop_back(), distance = DISTANCE, --y, j = Nspeed);
                }
                break;
        }// изменение состояния на нормальное при достижении точки возрождения
    if ((x == 14 || x == 13) && y == 12 && distance == DISTANCE && state == GhostState::Eaten)
    {
        state = GhostState::Normal, revived = true, wasScare = false, Px = Py = -1;
    }
    if (revived && (second_scared == char(0) || second_scared == char(9 - ((level + 1) / 7 > 2 ? 6 : (level + 1) / 7 * 2))))
    {
        revived = false;
    }
    if (name == GhostType::Red && x != GRedX && y != GRedY)
    {
        GRedX = x, GRedY = y;
    }
    if (distance == DISTANCE && state == GhostState::Normal) {// характерный имени логика при нормальном состоянии
        short randAngle = rand() % 4;
        if (pacman.getX() != Px || pacman.getY() != Py) {
            short fwX = Px = pacman.getX(), fwY = Py = pacman.getY();
            switch (name) {
                case GhostType::Blue: // строит вектор до первой возможной дороги от координат Red до Pacman и дальше
                    if (2 * Px - GRedX >= 0 && 2 * Px - GRedX < 28 && 2 * Py - GRedY >= 0 && 2 * Py - GRedY < 29 &&
                        map[2 * Py - GRedY][2 * Px - GRedX] != 0) {
                        fwX = 2 * Px - GRedX, fwY = 2 * Py - GRedY;
                        break;
                    }
                case GhostType::Red: // всегда идет на Pacman
                    break;
                case GhostType::Orange: // идет на Pacman, когда не находится в круге радиусом 5 единиц, потом идет в один из углов
                    if (abs(x - Px) <= 5 && abs(y - Py) <= 5) {
                        fwX = randAngle % 2 == 0 ? 1 : 26, fwY = randAngle > 1 ? 28 : 0;
                        break;
                    }
                case GhostType::Pink: // идет через 4 единицы от Pacman
                    switch (Plast_dir) {
                        case Direction::Right:
                            if (fwX <= 23 && map[fwY][fwX + 4] != 0) {
                                fwX += 4;
                                break;
                            }
                        case Direction::Left:
                            if (fwX >= 4 && map[fwY][fwX - 4] != 0) {
                                fwX -= 4;
                                break;
                            }
                        case Direction::Down:
                            if (fwY <= 24 && map[fwY + 4][fwX] != 0) {
                                fwY += 4;
                                break;
                            }
                        case Direction::Up:
                            if (fwY >= 4 && map[fwY - 4][fwX] != 0) {
                                fwY -= 4;
                                break;
                            }
                    }
                    break;
            }
            dir_vec = Find_Path(dec_arr, dis_arr, x, y, fwX, fwY, dir_now);
        }
        else if (name == GhostType::Orange) {
            abs(x - Px) <= 5 && abs(y - Py) <= 5 ? dir_vec = Find_Path(dec_arr, dis_arr, x, y,
                                                                       randAngle % 2 == 0 ? 1 : 26,
                                                                       randAngle > 1 ? 28 : 0, dir_now)
                                                 : dir_vec = Find_Path(dec_arr, dis_arr, x, y, Px, Py, dir_now);

        }
    }
    if (abs(pacman.getMapX() - mapX) <= 15 && abs(pacman.getMapY() - mapY) <= 15 && state != GhostState::Eaten)
    {// соприкасание с пакманом
        if (state == GhostState::Normal)
        {
            gameOver = deathPacman = true;
        }
        else
        {
            state = GhostState::Eaten, wasEaten = true, score += 200 << (killed_count + 1 < char(5) ? killed_count++ : killed_count = char(0));
        }
    }// нахождение пути до точки возрождения
    if (state == GhostState::Eaten && wasEaten && distance == DISTANCE)
    {
        dir_vec = Find_Path(dec_arr, dis_arr, x, y, 14, 13, dir_now), wasEaten = false;
    }
}

void  Ghost::setState(GhostState state) { this->state = state; }

void  Ghost::setSpeed(float speed) { this->speed = speed; }

void  Ghost::setDir_Vec(const std::vector<Direction> &dir_vec) { this->dir_vec = dir_vec; }

short Ghost::getX() { return x; }

short Ghost::getY() { return y; }

float Ghost::getSpeed() { return speed; }