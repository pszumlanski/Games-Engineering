#include <SFML/Graphics.hpp>



using namespace sf;
using namespace std;

void Render(RenderWindow &window) {
	// Draw Everything

}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	while (window.isOpen()) {
		window.clear();
		Render(window);
		window.display();
	}
	return 0;
}