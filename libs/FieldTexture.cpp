#include "FieldTexture.h"

bool FieldTexture::load() {
	return loadFromFile("../assets/field_textures.png");
}

FieldTexture::~FieldTexture() {
	delete[] m_texCoords;
	delete[] m_index;
}

sf::Vector2f *FieldTexture::operator[](const int index) {
	for(int i = 0; i < m_fieldTypes; i++){
		if(m_index[i] == index){
			return m_texCoords[i];
		}
	}

	return nullptr;
}
