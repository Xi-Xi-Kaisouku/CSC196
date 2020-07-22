#include "Player.h"
#include "Math/Math2.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include <fstream>

bool Player::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		Actor::Load(stream);

		stream >> m_thrust;
		stream >> m_rotation;

		stream.close();
	}

	return success;
}

void Player::Update(float dt)
{
	m_fireTimer += dt;
	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0;
		Projectile* projectile = new Projectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);
	}

	//position
	nc::Vector2 force;
	if (Core::Input::IsPressed(Core::Input::KEY_UP))
	{
		force = nc::Vector2::forward * m_thrust;
	}
	force = nc::Vector2::Rotate(force, m_transform.angle);
	//force = force + nc::Vector2{ 0, 200 }; //lunar lander style

	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.99f;
	m_transform.position = m_transform.position + (m_velocity * dt);

	//rotate
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT))
	{
		m_transform.angle = m_transform.angle - (nc::DegreesToRadians(m_rotation) * dt);
	}
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT))
	{
		m_transform.angle = m_transform.angle + (nc::DegreesToRadians(m_rotation) * dt);
	}

	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 800;
	if (m_transform.position.y > 600) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 600;

	if (force.lengthSqr() > 0)
	{
		g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::white, 1, 100, 200);
	}


	m_transform.Update();
}
