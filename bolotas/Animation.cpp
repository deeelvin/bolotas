#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	//Time elapsed used to control which texture frame to use
	totalTime = 0.0f;
	//Current texture frame
	currentImage.x = 0;

	//Create a "rect" with the normalized size of the texture so we can iterate through the frames
	uvRect.size.x = texture->getSize().x / float(imageCount.x);
	uvRect.size.y = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation() {

}

void Animation::Update(int row, float deltaTime, bool faceRight) {
	
	currentImage.y = row;
	totalTime += deltaTime;

	//Checks if the elapsed time is greater than the defined time for each frame
	//If it is, go to the next frame and rests the timer
	//Also, if the animation got to the last frame, resets to the first
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.position.y = currentImage.y * uvRect.size.y;

	if (faceRight) {
		uvRect.position.x = currentImage.x * uvRect.size.x;
		uvRect.size.x = abs(uvRect.size.x);
	}
	else {
		uvRect.position.x = (currentImage.x + 1) * abs(uvRect.size.x);
		uvRect.size.x = -abs(uvRect.size.x);
	}
}
