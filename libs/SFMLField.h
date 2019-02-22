#ifndef MINESWEEPER_SFMLFIELD_H
#define MINESWEEPER_SFMLFIELD_H

#include <SFML/Graphics.hpp>

#include "BaseField.h"
#include "Enums.h"
#include "FieldTexture.h"

class SFMLField : public BaseField, public sf::Drawable, public sf::Transformable {
private:
	sf::Vertex *m_vertices;
	FieldTexture m_texture;

	sf::Color m_defaultBackground = sf::Color(183, 183, 183, 1);

	const int m_vertexPerQuad = 4;

	int m_pixelHeight;
	int m_pixelWidth;

	virtual void showPlayerTile(const int x, const int y);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int getIndex(const int x, const int y, const int vertex);

public:

	SFMLField()
			: BaseField()
	{
		m_vertices = new sf::Vertex[1];
		m_texture.load();
	}

	~SFMLField();

	void setSize(const int height, const int width);

	void setupField(const sf::Vector2f topLeft, const sf::Vector2f bottomRight, const int bombs);

	sf::Color& defaultBackground();

	sf::Vertex& operator()(const int x, const int y, const int vertex);

};

#endif
