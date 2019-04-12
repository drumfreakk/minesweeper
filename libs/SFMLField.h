#ifndef MINESWEEPER_SFMLFIELD_H
#define MINESWEEPER_SFMLFIELD_H

#include <SFML/Graphics.hpp>

#include "BaseField.h"
#include "Enums.h"
#include "FieldTexture.h"

class SFMLField : public BaseField, public sf::Drawable, public sf::Transformable {
private:
	sf::Vertex *m_vertices;

	sf::Color m_defaultBackground = sf::Color(183, 183, 183, 1);

	const int m_vertexPerQuad = 4;

	int m_pixelHeight;
	int m_pixelWidth;

	sf::Vector2f m_topLeft;
	sf::Vector2f m_bottomRight;

	virtual void showPlayerTile(int x, int y);

	int getIndex(int x, int y, int vertex);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	FieldTexture m_texture;

public:

	friend std::ostream& operator<<(std::ostream& out, SFMLField &field);

	SFMLField()
			: BaseField()
	{
		m_vertices = new sf::Vertex[1];
		m_texture.load();
	}

	SFMLField(const int height, const int width)
		: BaseField(height, width)
	{
		m_texture.load();
		m_vertices = new sf::Vertex[m_height * m_width * m_vertexPerQuad];
	}

	~SFMLField();

	void setSize(int height, int width);

	void setWindowSize(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	Return click(int localX, int localY, Click type);

	sf::Color& defaultBackground();

	sf::Vertex& operator()(int x, int y, int vertex);

};

#endif
