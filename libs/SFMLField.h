#ifndef MINESWEEPER_SFMLFIELD_H
#define MINESWEEPER_SFMLFIELD_H

#include <SFML/Graphics.hpp>

#include "BaseField.h"
#include "Enums.h"

class SFMLField : public BaseField, public sf::Drawable, public sf::Transformable {
private:
	sf::VertexArray m_vertices;
	sf::Texture m_texture;

	virtual void showPlayerTile(const int x, const int y);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// apply the texture
		states.texture = &m_texture;

		// you may also override states.shader or states.blendMode if you want

		// draw the vertex array
		target.draw(m_vertices, states);
	}

public:

	SFMLField(const int height, const int width)
			: BaseField(height, width)
	{

	}

};

#endif
