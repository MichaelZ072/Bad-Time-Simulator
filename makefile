Game: GameMaster.cpp
	g++ -Wall -Wextra GameMaster.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
	./game

BoardTest: BulletBoard_test.cpp
	g++ -Wall -Wextra BulletBoard_test.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
	./game

SoulTest: Soul_test.cpp
	g++ -Wall -Wextra Soul_test.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
	./game

BlasterTest: GasterBlaster_test.cpp
	g++ -Wall -Wextra GasterBlaster_test.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
	./game