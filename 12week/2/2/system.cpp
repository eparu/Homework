#include "system.hpp"

void System::initialize(std::size_t n_lines, std::size_t n_columns)
{
	const auto size = std::size(m_particles);
	const auto stiffness = 0.5f;


	for (auto i = 0U; i < n_lines; i++)
	{
		for (auto j = 0U; j < n_columns; j++)
		{
			if (i > 0)
			{
				m_links.push_back(Link(particle(i*n_columns + j ), particle((i-1)*n_columns + j), stiffness));
				if (j > 0)
				{
					m_links.push_back(Link(particle(i * n_columns + j), particle((i - 1) * n_columns + j - 1), stiffness));
				}
				if (j + 1 < n_columns)
				{
					m_links.push_back(Link(particle(i * n_columns + j), particle((i - 1) * n_columns + j + 1), stiffness));
				}
			}
			if (j > 0)
			{
				m_links.push_back(Link(particle(i * n_columns + j), particle(i * n_columns + j -1), stiffness));

			}
		}
	}
}

void System::push(const sf::Vector2f force) const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(force);
	}
}

void System::update() const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(0.20f);

		if (m_particles[i]->position().y + m_particles[i]->radius() > m_max_point.y)
		{
			m_particles[i]->set_y(m_max_point.y - m_particles[i]->radius());
		}

		if (m_particles[i]->position().y - m_particles[i]->radius() < m_min_point.y)
		{
			m_particles[i]->set_y(m_min_point.y + m_particles[i]->radius());
		}

		if (m_particles[i]->position().x + m_particles[i]->radius() > m_max_point.x)
		{
			m_particles[i]->set_x(m_max_point.x - m_particles[i]->radius());
		}

		if (m_particles[i]->position().x - m_particles[i]->radius() < m_min_point.x)
		{
			m_particles[i]->set_x(m_min_point.x + m_particles[i]->radius());
		}
	}

	for (auto i = 0U; i < std::size(m_links); ++i)
	{
		m_links[i].update();
	}


}