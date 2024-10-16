Game: GameMaster.cpp
	g++ GameMaster.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
	./game

GameTest: GameMaster_copy.cpp
	g++ -Wall -Wextra GameMaster_copy.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
	./game

ActionTest: GameMasterFinal.cpp
	g++ -Wall -Wextra GameMasterFinal.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
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