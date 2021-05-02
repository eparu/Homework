#include "visualizer.hpp"

void Visualizer::initialize(){

    for (auto i = 0U; i < squares_in_column; i++)
    {
        for (auto j = 0U; j < squares_in_line; j++){
            field[i][j] = 0;
        }
    }
    m_particles.reserve(m_particles_num);
    std::mt19937_64 mt;
    std::uniform_int_distribution uid_x(0, static_cast<int>(width) - 1);
    std::uniform_int_distribution uid_y(0, static_cast<int>(height) - 1);
    std::uniform_int_distribution<> uid_dir(0, 3);
    for (auto i = 0; i < m_particles_num; ++i)
    {
        auto x = uid_x(mt);
        auto y = uid_y(mt);
        auto dir = static_cast<Direction>(uid_dir(mt));
        ++field[x/squares_size][y/squares_size];
        m_particles.insert(std::end(m_particles), Particle(x, y, dir));
    }
}


void Visualizer::run(){
    while (m_window.isOpen())
    {
        Event event;

        while (m_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                m_window.close();
            }
        }
        update();
        m_window.clear();
        draw();
    }
}


void Visualizer::update(){
    for (auto & particle : m_particles)
    {
        move(particle);
    }
}


void Visualizer::move(Particle& particle)
{
    switch (particle.direction)
    {
        case Direction::Down:
            if (particle.y == height - 1 )
                particle.direction = Direction::Up;
            else
                particle.y++;
            break;
        case Direction::Up:
            if (particle.y == 0)
                particle.direction = Direction::Down;
            else
                particle.y--;
            break;
        case Direction::Left:
            if (particle.x == 0)
                particle.direction = Direction::Right;
            else
                particle.x--;
            break;
        case Direction::Right:
            if (particle.x == width - 1)
                particle.direction = Direction::Left;
            else
                particle.x++;
            break;
        default:
            break;
    }
}


void Visualizer::draw()
{
    for (auto i = 0U; i < squares_in_column; i++)
    {
        for (auto j = 0U; j < squares_in_line; j++){
            field[i][j] = 0;
        }
    }
    for (const auto & particle : m_particles){
         ++field[particle.x / squares_size][particle.y / squares_size];
    }

    RectangleShape Rect(Vector2f(squares_size, squares_size));
    for (auto i = 0U; i < squares_in_column; ++i)
    {
        for (auto j = 0U; j < squares_in_line; ++j)
        {
            Color color;
            const std::size_t particles_num = field[i][j];

            auto color_num  = particles_num / particles_per_color;
            color_num = (color_num > m_colors_num - 1 ? color_num - 1 : color_num);
            color = m_colors[color_num];

            Rect.setPosition(static_cast <float> (i * squares_size), static_cast <float> (j * squares_size));
            Rect.setFillColor(color);
            m_window.draw(Rect);
        }
    }

    m_window.display();
    }
