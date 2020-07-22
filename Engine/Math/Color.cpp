#include "pch.h"
#include "Color.h"


namespace nc
{
	const nc::Color nc::Color::white = { 1, 1, 1 };
	const nc::Color nc::Color::red = { 1, 0, 0 };
	const nc::Color nc::Color::green = { 0, 1, 0 };
	const nc::Color nc::Color::blue = { 0, 0, 1 };

	std::istream& nc::operator>>(std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos)
		{
			// { 1, 0, 1 } r g b
			std::string cr = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			c.r = std::stof(cr);

			line = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);

			std::string cg = line.substr(0, line.find(","));
			c.g = std::stof(cg);

			std::string cb = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
			c.b = std::stof(cb);
		}

		return stream;
	}
}
