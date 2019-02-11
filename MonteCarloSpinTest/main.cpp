#include "Program.h"

int main()

{
	sf::err().rdbuf(NULL);
	Program p(500, 500);
	return p.mainLoop();
}