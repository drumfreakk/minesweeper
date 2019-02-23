#include "SFMLField.h"

#include <iostream>

SFMLField::~SFMLField() {
	delete[] m_vertices;
}

void SFMLField::showPlayerTile(const int x, const int y) {
	for(int z = 0; z < m_vertexPerQuad; z++) {
		m_vertices[getIndex(x, y, z)].texCoords = m_texture[m_visibleField[y][x]][z];
	}
}

void SFMLField::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vertices, m_height * m_width * m_vertexPerQuad, sf::Quads, states);
}

sf::Vertex &SFMLField::operator()(const int x, const int y, const int vertex) {
	return m_vertices[getIndex(x, y, vertex)];
}

int SFMLField::getIndex(const int x, const int y, const int vertex) {
	return (y * (m_width * m_vertexPerQuad)) + (x * m_vertexPerQuad) + vertex;
}

sf::Color &SFMLField::defaultBackground() {
	return m_defaultBackground;
}

void SFMLField::setSize(const int height, const int width) {
	BaseField::setSize(height, width);

	delete[] m_vertices;
	m_vertices = new sf::Vertex[m_height * m_width * m_vertexPerQuad];
}

bool SFMLField::setupField(const sf::Vector2f topLeft, const sf::Vector2f bottomRight, const int bombs) {
	if(!BaseField::setupField(bombs))
		return false;

	m_topLeft = topLeft;
	m_bottomRight = bottomRight;

	m_pixelHeight = bottomRight.y - topLeft.y;
	m_pixelWidth = bottomRight.x - topLeft.x;

	float heightPerTile = m_pixelHeight / m_height;
	float widthPerTile = m_pixelWidth / m_width;

	sf::Vector2f add(0.f, 0.f);

	for(int x = 0; x < m_width; x++){
		for(int y = 0; y < m_height; y++){
			for(int z = 0; z < m_vertexPerQuad; z++){
				add = sf::Vector2f(0.f, 0.f);

				if(z == 1 || z == 2){
					add.x = widthPerTile;
				}
				if(z == 2 || z == 3){
					add.y = heightPerTile;
				}

				m_vertices[getIndex(x, y, z)].position = sf::Vector2f((x * widthPerTile) + topLeft.x + add.x, (y * heightPerTile) + topLeft.y + add.y);
				showPlayerTile(x, y);
			}
		}
	}

	return true;
}

Return SFMLField::click(const int localX, const int localY, const Click type) {
	float heightPerTile = m_pixelHeight / m_height;
	float widthPerTile = m_pixelWidth / m_width;

	int normX = localX - m_topLeft.x;
	int normY = localY - m_topLeft.y;

	int x = normX / widthPerTile;
	int y = normY / heightPerTile;
	if(x >= 0 && x < m_width && y >= 0 && y < m_height){
//		std::cout << x << " " << y;
		return BaseField::click(x, y, type);
	}



	return RETURN_FALSE_CLICK;
}

