#include "pch.h"
#include "Actor.h"
#include <fstream>

namespace nc
{
	bool nc::Actor::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

			stream >> m_transform;

			std::string shapename;
			stream >> shapename;
			m_shape.Load(shapename);

			stream.close();
		}

		return success;
	}

	void nc::Actor::Update(float dt)
	{

	}

	void nc::Actor::Draw(Core::Graphics& graphics)
	{

	}
	
	std::istream& operator >> (std::istream& stream, Actor& actor)
	{
		stream >> actor.m_transform;
		stream >> actor.m_shape;
		
		return stream;
	}
}


