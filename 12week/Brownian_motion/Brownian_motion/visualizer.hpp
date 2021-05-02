#pragma once

#include <algorithm>
#include <array>
#include <thread>
#include <vector>
#include <random>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace sf;


enum class Direction
{
    Down,
    Up,
    Left,
    Right,
};

struct Particle
{
    Particle() = default;
    Particle(int x_value, int y_value, Direction dir) : x(x_value), y(y_value), direction(dir) {}

    int x;
    int y;
    Direction direction;
};



class Visualizer
{

public:
    Visualizer() :
    m_window(VideoMode(width, height), "Brownian motion")
    {
        initialize();
    };

    ~Visualizer() noexcept = default;

    void run();

private:
    void initialize();

    void draw();
    void move(Particle& particle);
    void update();


private:
    static const std::size_t width = 1000;
    static const std::size_t height = 1000;
    static const std::size_t squares_in_column = 10;
    static const std::size_t squares_in_line = squares_in_column;
    static const std::size_t squares_size = height / squares_in_column;

    static const std::size_t m_particles_num = 1000;

    static const std::size_t m_colors_num = 5;
    static const std::size_t particles_per_color = 5;
    const std::array<Color, m_colors_num> m_colors =
    {Color( 202,225,250), Color(152,200,250), Color(102,174,250), Color(52,148,250), Color(2,122,250)};

    std::size_t field[squares_in_column][squares_in_line];
    RenderWindow m_window;
    std::vector<Particle> m_particles;
};
