#ifndef MINESWEEPER_FIELDTEXTURE_H
#define MINESWEEPER_FIELDTEXTURE_H

#include <SFML/Graphics.hpp>
#include "Enums.h"


class FieldTexture : public sf::Texture {
private:
	sf::Vector2f **m_texCoords;
	int *m_index;

	const int m_fieldTypes = 15;
	const int m_vertexPerQuad = 4;

public:
	FieldTexture()
		: sf::Texture()
	{
		m_texCoords = new sf::Vector2f*[m_fieldTypes];
		m_index = new int[m_fieldTypes];

		for(int i = 0; i < m_fieldTypes; i++)
			m_texCoords[i] = new sf::Vector2f[m_vertexPerQuad];

		m_index[0] = 0;
		m_index[1] = 1;
		m_index[2] = 2;
		m_index[3] = 3;
		m_index[4] = 4;
		m_index[5] = 5;
		m_index[6] = 6;
		m_index[7] = 7;
		m_index[8] = 8;
		m_index[9] = CODE_LINE;
		m_index[10] = CODE_FLAG;
		m_index[11] = CODE_POSSIBLE_FLAG;
		m_index[12] = CODE_WRONG_FLAG;
		m_index[13] = CODE_MINE;
		m_index[14] = CODE_EXPLODED_MINE;

		sf::Vector2f add;
		float curPos = 0;

		for(int i = 0; i < m_fieldTypes; i++){
			for(int v = 0; v < m_vertexPerQuad; v++){
				add.x = 0;
				add.y = 0;

				if(v == 1 || v == 2){
					add.x = 256;
				}
				if(v == 2 || v == 3){
					add.y = 256;
				}

				m_texCoords[i][v] = sf::Vector2f(curPos + add.x, add.y);

			}

			curPos += 256;
		}
	}

	~FieldTexture();

	bool load();

	sf::Vector2f* operator[](int index);

};


#endif