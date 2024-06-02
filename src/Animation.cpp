#include "Animation.h"


//------------------------Constructor----------------------------
Animation::Animation(const sf::Texture& texture, sf::Vector2u imageCount, float switchTime)
{
	// Initialize member variables
	m_imageCount = imageCount;
	m_switchTime = switchTime;
	m_totalTime = 0.0f;
	m_currentImage.x = 0;


	// Calculate the size of each image in the texture
	m_uvRect.width = texture.getSize().x / float(m_imageCount.x);
	m_uvRect.height = texture.getSize().y / float(m_imageCount.y);
}
//-----------------------get_uvRect---------------------------
const sf::IntRect* Animation::get_uvRect() const {

	// Return a constant pointer to the uvRect
	return  &m_uvRect;
}

//------------------------update------------------------
void Animation::update(const int& row, const float& deltaTime) {

	// Set the current row of the animation
	m_currentImage.y = row;

	// Update the total time
	m_totalTime += deltaTime;

	// Check if it's time to switch to the next image
	if (m_totalTime >= m_switchTime) 
	{
		m_totalTime -= m_switchTime;
		m_currentImage.x++;

		// Reset to the first image if reached the end of the row
		if (m_currentImage.x >= m_imageCount.x)
		{
			m_currentImage.x = 0;
		}
	}

	// Calculate the texture coordinates for the current image
	m_uvRect.left = m_currentImage.x * m_uvRect.width;
	m_uvRect.top = m_currentImage.y * m_uvRect.height;

}
//----------------------getCurrentImage---------------------
const sf::Vector2u& Animation::getCurrentImage() const {

	// Return a constant reference to the current image
	return m_currentImage;
}
//-----------------------setCurrentRow-----------------------
void Animation::setCurrentRow(const unsigned& newRow) {

	// Set the current row of the animation to the new value
	m_currentImage.y = newRow;
}
//------------------------getImageCount------------------------
const sf::Vector2u& Animation::getImageCount() const {

	// Return a constant reference to the image count
	return m_imageCount;
}
//---------------------getRowOfStandatAni-----------------------
unsigned Animation::getRowOfStandatAni(const sf::Vector2f& dir) const {


	// Check the direction and return the corresponding row index
	if (dir == RIGHT)
		return 2;
	else if (dir == LEFT)
		return 1;
	else if (dir == DOWN)
		return 0;
	else if (dir == UP)
		return 3;

	return 0;// Default to row 0 if direction is not recognized
}