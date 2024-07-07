#pragma once
#include "Const.h"


class Animation
{
public:
	Animation							(const sf::Texture&, sf::Vector2u imageCount, float switchTime);
	~Animation							() = default;
	void update							(const int& row, const float&);
	const sf::IntRect* get_uvRect		() const;
	const sf::Vector2u& getCurrentImage	() const;
	void setCurrentRow					(const unsigned&);
	const sf::Vector2u& getImageCount	() const;
	unsigned getRowOfStandatAni			(const sf::Vector2f& dir) const;

private:

	//-----------private members----------------

	sf::IntRect				m_uvRect;
	sf::Vector2u			m_imageCount;
	sf::Vector2u			m_currentImage;

	float					m_totalTime,
							m_switchTime;
};
