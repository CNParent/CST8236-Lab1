#include <SFML/Graphics.hpp>
#include "TransformNode.h"
/******************************************************************************
Here begins the spaghetti code
Movement rates have been randomized
Enjoy :)
******************************************************************************/
float getRate();

int main(int argc, char* argv) {
	sf::RenderWindow window(sf::VideoMode(600, 600), "Purple");

	sf::CircleShape head(20.0f, 16);
	sf::RectangleShape neck(sf::Vector2<float>(10.0f, 15.0f));
	sf::RectangleShape body(sf::Vector2<float>(20.0f, 200.0f));
	sf::RectangleShape armLL(sf::Vector2<float>(75.0f, 10.0f));
	sf::RectangleShape armLU(sf::Vector2<float>(75.0f, 10.0f));
	sf::RectangleShape armRL(sf::Vector2<float>(75.0f, 10.0f));
	sf::RectangleShape armRU(sf::Vector2<float>(75.0f, 10.0f));

	head.setFillColor(sf::Color::Blue);
	neck.setFillColor(sf::Color::Blue);
	body.setFillColor(sf::Color::Blue);
	armLL.setFillColor(sf::Color::Blue); //Left-lower
	armLU.setFillColor(sf::Color::Blue); //Left-upper
	armRL.setFillColor(sf::Color::Blue); //Right-lower
	armRU.setFillColor(sf::Color::Blue); //Right-upper

    TransformNode wwiaftm(&body); // Wack-Waving-Inflatable-Arm-Flailing-Tube-Man
    TransformNode neckNode(&neck);
    TransformNode armLNode(&armLL);
    TransformNode armRNode(&armRL);

    wwiaftm.Add(&neckNode);
    wwiaftm.Add(&armLNode);
    wwiaftm.Add(&armRNode);

    neckNode.Add(new TransformNode(&head));
    armLNode.Add(new TransformNode(&armLU));
    armRNode.Add(new TransformNode(&armRU));

    body.setOrigin(10.0f, 200.0f);
    body.move(300.0f, 500.0f);
    
    //Head
    neck.setOrigin(5.0f, 15.0f);
    neck.move(10.0f, -1.0f);
    head.setOrigin(20.0f, 41.0f);
    head.move(5.0f, 0.0f);

    // Left arm
    armLL.setOrigin(76.0f, 5.0f);
    armLL.move(0.0f, 5.0f);
    armLU.setOrigin(76.0f, 5.0f);
    armLU.move(0.0f, 5.0f);

    // Right arm
    armRL.setOrigin(0.0f, 5.0f);
    armRL.move(21.0f, 5.0f);
    armRU.setOrigin(0.0f, 5.0f);
    armRU.move(76.0f, 5.0f);

    srand(time(NULL));

    float armLLRate;
    float armRLRate;
    float armLURate;
    float armRURate;
    float neckRate;
    float headRate;
    float bodyRate;

    sf::Clock deltaTime;
    sf::Clock rngTime;
    sf::Event sfEvent;
	float t = 0.0f;
    float tr = 0.0f;
	while (window.isOpen()) {
		deltaTime.restart();
        while (window.pollEvent(sfEvent)) {
            if (sfEvent.type == sf::Event::Closed) window.close();
        }

        if (rngTime.getElapsedTime().asSeconds() > tr){
            tr = (rand() % 200) / 100.0f;
            armLLRate = getRate();
            armRLRate = getRate();
            armLURate = getRate();
            armRURate = getRate();
            neckRate = getRate();
            headRate = getRate();
            bodyRate = getRate() / 2.0f; // The body was going too fast, had to keep it under control!
            rngTime.restart();
        }

        armLL.rotate(armLLRate * t);
        armRL.rotate(armRLRate * t);
        armRU.rotate(armRURate * t);
        armLU.rotate(armLURate * t);
        neck.rotate(neckRate * t);
        head.rotate(headRate * t);
        body.rotate(bodyRate * t);

        if (bodyRate < 0 && body.getRotation() < 315.0f && body.getRotation() > 270.0f) bodyRate = -bodyRate;
        else if (bodyRate > 0 && body.getRotation() > 45.0f && body.getRotation() < 90.0f) bodyRate = -bodyRate;

		window.clear();
		wwiaftm.Draw(&window);
		window.display();
		t = deltaTime.getElapsedTime().asSeconds();
	}

	return 0;
}

float getRate(){
    return (rand() % 1080) - 540;
}