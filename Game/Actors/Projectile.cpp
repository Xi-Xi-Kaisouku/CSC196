#include "Projectile.h"
#include "Math/Math2.h"
#include "Graphics/ParticleSystem.h"
#include <fstream>

bool Projectile::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		Actor::Load(stream);

		stream >> m_thrust;

		stream.close();
	}

	return success;
}

void Projectile::Update(float dt)
{
	m_lifetime -= dt;
	m_destroy = (m_lifetime <= 0);

	nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);
	nc::Vector2 velocity = direction * m_thrust;
	m_transform.position = m_transform.position + velocity * dt;
	//m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);

	g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 10, 1, nc::Color::red, 0.5f, 100, 200);

	m_transform.Update();
}

void Projectile::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::ENEMY)
	{
		m_destroy = true;
	}
}