#pragma once
#include <SFML/Graphics.hpp>
#include "Place.h"

const float DISTANCE = 21.5f;
const float STEP = 0.25f;

class Pacman                                 // пакман (класс)
{
protected:
    float mapX, mapY;                        // координата в пикселях в приложении
    float speed;                             // скорость
    float distance;                          // оставшееся расстояние до следующей координаты массива map
    short side;                              // длина текстуры
    short x, y;                              // координата в массиве map
    Direction dir;                            // текущее направление
    Direction next_dir;                       // следующее напраление
public:
    Pacman(int x = 0, int y = 0);
    void draw(sf::RenderWindow& win, sf::Sprite& SPacman, sf::Texture& TPacman_0, sf::Texture& TPacman_1,
              sf::Texture& TPacman_2, sf::Texture& TPacman_3, sf::Texture& TDeathP_0,
              sf::Texture& TDeathP_1, sf::Texture& TDeathP_2, sf::Texture& TDeathP_3,
              sf::Texture& TDeathP_4, sf::Texture& TDeathP_5, sf::Texture& TDeathP_6,
              sf::Texture& TDeathP_7, short time_passed, signed short second_deathP, signed char& lifes,
              bool& deathPacman, bool& gameOver, bool isPause);
    void move(sf::Sprite& SFruit, Direction Plast_dir, const std::array<std::array<short, 28>, 29>& map, std::array<std::array<short, 28>, 29>& energy, unsigned int lenght,
              unsigned int& score, unsigned int& lifes_vertex, signed char& lifes_add,
              short& energy_count, signed char& second_fruit, signed char& lifes, signed char number_fruit,
              signed char& second_scared, signed char& level, bool& gameOver);
    // перезадание направления
    void setDirection(Direction next_dir);
    // перезадание дистанции
    void setDistance(float distance);
    // получение текущего напраления
    Direction getDirection() const;
    // получение расстояния до следующей координаты массива map
    float getDistance() const;
    // получение координаты абциссы приведения
    short getX() const;
    // получение координаты ординаты приведения
    short getY() const;
    // получение кол-во пикселей абсциссы приведения
    float getMapX() const;
    // получение кол-во пикселей ординаты приведения
    float getMapY() const;

};