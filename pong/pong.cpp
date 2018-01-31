#include <SFML/Graphics.hpp>



using namespace sf;
using namespace std;

Vector2f ballVelocity;
bool server = false;

const Keyboard::Key controls[4] = {
	Keyboard::A,	//P1 up
	Keyboard::Z,	//P1 down
	Keyboard::Up,	//P2 up
	Keyboard::Down	//P2 down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];

void reset() {
	// reset ball velocity
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition((gameWidth - 10) - paddleSize.x / 2, gameHeight / 2);
	//reset ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);
}

void Load() {
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
	// set size and origin of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	// set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	reset();
}

void ai() {

	float direction = 0.0f;
	static Clock clock;
	float dt = clock.restart().asSeconds();
	const float ballPosition = ball.getPosition().y;
	const float paddlePosition = paddles[1].getPosition().y;
	if (ballPosition > paddlePosition) {
		direction++;
	}
	else if (ballPosition < paddlePosition) {
		direction--;
	}
	paddles[1].move(0, direction * paddleSpeed * dt);
}

void Update(RenderWindow &window) {
	
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	ball.move(ballVelocity * dt);
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	
	// Quit via ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
	
	// handle paddle movement for P1
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		if ((paddles[0].getPosition().y - (paddleSize.y * 0.5)) > 0) {
			direction--;
		}
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		if ((paddles[0].getPosition().y + (paddleSize.y * 0.5)) < gameHeight) {
			direction++;
		}
	}
	paddles[0].move(0, direction * paddleSpeed * dt);

	

	// handle paddle movement for P2
	float direction2 = 0.0f;
	if (Keyboard::isKeyPressed(controls[2])) {
		if ((paddles[1].getPosition().y - (paddleSize.y * 0.5)) > 0) {
			direction2--;
		}
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		if ((paddles[1].getPosition().y + (paddleSize.y * 0.5)) < gameHeight) {
			direction2++;
		}
	}
	paddles[1].move(0, direction2 * paddleSpeed * dt);

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if(by > gameHeight) {
		// bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	} else if (by < 0) {
		// top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	} else if (bx > gameWidth) {
		// right wall
		reset();
	} else if (bx < 0) {
		// left wall
		reset();
	} else if (
		// ball is inline or behind paddle
		bx < (paddleSize.x + 10) && 
		// AND ball is above bottom edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is below top edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
	) {
			ballVelocity.x *= -1.1f;
			ballVelocity.y *= 1.1f;
			ball.move(10, 0);
	} else if (
		// ball is inline or behind paddle
		bx > (gameWidth - paddleSize.x - 10) &&
		// AND ball is above bottom edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is below top edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
	) {
			ballVelocity.x *= -1.1f;
			ballVelocity.y *= 1.1f;
			ball.move(-10, 0);
	}
}



void Render(RenderWindow &window) {
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		ai();
		Render(window);
		window.display();
	}
	return 0;
}




















