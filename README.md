# Digital UNO

This is a C++ implementation of the game UNO. It was a project for the course Software Engineering in Spring 2021 at ETHz.
The program is written to work for 2 to 4 players.
The UNO follows the official [UNO rules](https://service.mattel.com/instruction_sheets/42001pr.pdf) except for the following changes, that simplify the implementation:
- a Wild Draw 4 cards can allway be played (assuming it's your turn)
- When you picked up a card because you could not play, your turn is over
- When you have UNO you don't have to do anything, the program will automatically show a popup which says UNO
- When there are only two players in the game, the Reverse card doesn't do anything
- we don't count points 


![UNO-logo](./assets/uno_logo.png?raw=true)

It uses [wxWidgets](https://www.wxwidgets.org/) for the GUI, [sockpp](https://github.com/fpagliughi/sockpp) for the network interface, [the nlohmann json library](https://github.com/nlohmann/json) for object serialization, [spdlog](https://github.com/gabime/spdlog) and [Google test](https://github.com/google/googletest) for testing the server.
Further some of the code and design is copied from the [Lama project](https://gitlab.ethz.ch/hraymond/cse-lama-example-project)

##Download and Compilation




##Download and Compilation
note: Executing the make file will take very long

0. Download the project either with ssh key `git@gitlab.ethz.ch:machart/cerealkillers.git` or with https `https://gitlab.ethz.ch/machart/cerealkillers.git`
1. Create a build folder `mkdir build`
2. navigate into the build folder `cd build`
3. type `cmake ..`
4. type `make`
5. To start a game now first start the server `./ck_server`
6. Then open the build folder in a new terminal window for each client. Start 2 to 4 clients by typing `./ck_client`. (for each client in a separate terminal window)
7. Now you only have to type in a name and press connect to server, then the game can start.  

##Playing the game 
On the game window you can allways see wheter it is your turn or not. If it's your turn, you can play a card by clicking on it. If you don't have a card which you can play you have to click on the draw pile to pick up a card. 
On the right corner you can see a list of all players and how many cards they have at the moment. The player currently playing is highlighted.  

##Code documentation


##____________________________________________________________
## Server-tests Compilation:


0. Clone the server branch with ```git clone -b server https://gitlab.ethz.ch/machart/cerealkillers.git```
1. Create a `build` folder
2. `cd` into `build`
3. cmake .. 
4. make test_game_controller_tests

### Run test
Run with ```./unit-tests/test_game_controller_tests```


#TODO:
TESTS:
Uncomment the right lines in the CMakelists, 
<!-- TODO:
- store Playernames correctly (when they arrive with NewPlayer request
- something is wrong with the number of cards, that get distributed (way to many blue 0) -->


#TODO:

SERVER: 
- somehow there is something strange with the BLUE 0 there are way too many of them and they just disapear all when playing one of them (maybe there is a problem when resizing the list or something I don't know....

- handle the names received

maybe also Client...
- Chosing the color doens't work -> somehow server expects a different color to be played afterwards then client
	also server puts another card on top if player can't play (I would expect the top card stay the same (wild card) but the current color to be adapted

CLIENT:
(somethings might allready be implemented on the crashing branch)

(- handle incorrect behavior of players correctly)
- playerController-> handle the UNO, WON etc responds from the server
	(for the UNO there already is a function in the MainGamePanel but this doesn't work like that)

- MainGamePanel -> add Exit button

NOTE: correct playerID and playerName are stored in the player class
