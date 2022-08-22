***DISCLAIMER:*** *THIS WAS A GROUP PROJECT AT ETHZ. TO PREVENT LEAKING OF PERSONAL INFORMATION I DELETED ALL REFERENCES TO OTHER PEOPLE INCLUDING COMMIT HISTORY*

# Digital UNO

This is a C++ implementation of the game UNO. It was a project for the course Software Engineering in Spring 2021 at ETHZ.
The program is written to work for 2 to 4 players.


The UNO follows the official [UNO rules](https://service.mattel.com/instruction_sheets/42001pr.pdf) except for the following changes, that simplify the implementation:
- a Wild Draw 4 cards can allway be played (assuming it's your turn)
- When you picked up a card because you could not play, your turn is over
- When you have UNO you don't have to do anything, the program will automatically show a popup which says UNO
- When there are only two players in the game, the Reverse card doesn't do anything
- we don't count points 
 
While playing the game you can allways see wheter it is your turn or not on the game window. If it's your turn, you can play a card by clicking on it. If you don't have a card which you can play you have to click on the draw pile to pick up a card. Cards you get due to an opponent playing a draw card, are give to you by the server automatically, which means you don't have to do anything.
On the right corner you can see a list of all players and how many cards they have at the moment. The player currently playing is highlighted.  


![UNO-logo](./assets/uno_logo.png?raw=true)

It uses [wxWidgets](https://www.wxwidgets.org/) for the GUI, [sockpp](https://github.com/fpagliughi/sockpp) for the network interface, [the nlohmann json library](https://github.com/nlohmann/json) for object serialization, [spdlog](https://github.com/gabime/spdlog) and [Google test](https://github.com/google/googletest) for testing the server.
Further some of the code and design is copied from the [Lama project](https://gitlab.ethz.ch/hraymond/cse-lama-example-project)

## Downloading, Compiling and running Code

### Make and Run
```bash
git clone https://gitlab.ethz.ch/machart/cerealkillers.git
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
```
### Build Server
```bash
make ck_server
./ck_server
```
### Build Client
```bash
make ck_client
./ck_client 
```

### Build Tests
Important: Tests need to be run in release mode. Googletest adds -Werror to the compile flags and will not compile without -fsanitize= which leads to plenty of error messages.
```bash
make tcp_server_client_connection_tests
./unit-tests/tcp_server_client_connection_tests
```
or
```bash
make test_game_controller_tests
./unit-tests/test_game_controller_tests
```

## Code documentation

The code consits of three different parts: Server, Client and Common. 
All server files are only used by the server side. The client files are only used by the client and the common files are used by both the client and the server.
The folders include and src both hold three folders, one for each of the parts. The include folder holds all the header files and the src all the corrsponding cpp files. In the src folders one can also find the "main.cpp" files.
 
Next to the include and the src folder, there is an asset folder which holds all the card pictures and a unit-test folder which holds all the server and common tests. 

### Server
The server is responsible for exchanging all the information between the clients. It updates the hand of all the players and evaluates wheter the players requested moves are valid

* __[GameController](./include/server/game_controlller.hpp)__
* __[GameState](./include/server/game_state.hpp)__
* __[Player](./include/server/player.hpp)__
* __[TCP Server](./include/server/tcp_server.hpp)__ :builds a connections to the tcp_clients and sends and receives json messages

### Client
* __[digital UNO](./include/client/digital_UNO.hpp)__
* __[Player_controller](./include/client/player_controller.hpp)__ : Handles all the responses from the server and holds functions for sending requests to the server. 
* __[player_state](./include/client/player_state.hpp)__ : Stores all the information about the current state of the game 
* __[player](./include/client/player.hpp)__ : stores player name and id
* __[Tcp Client](./include/client/tcp_client.hpp)__ : builds a connection to the tcp_server and sends and receives json messages

##### UI
The files in here are used for the graphical interface of the Client
* __[Connection Panel](./include/client/UI/ConnectionPanel.hpp)__ : Panel to type in Name, Port and Address when connecting to the game 
* __[GameWindow](./include/client/UI/GameWindow.hpp)__
* __[ImagePanel](./include/client/UI/ImagePanel.hpp)__ 
* __[InputField](./include/client/UI/InputField.hpp)__  
* __[MainGamePanel](./include/client/UI/MainGamePanel.hpp)__ : Panel used for graphical interface during the game.  

### Common
Holds all the enums for the used types
* __[cards](./include/common/cards.hpp)__ :holds the card enum and different enums for the card color, type etc. and a type for the card Piles/Hand
* __[common](./include/common/common.hpp)__ : holds enums for request and response types, Player_id etc.  
* __[logger](./include/common/logger.hpp)__
* __[utils](./include/common/logger.hpp)__

### Unit-Tests
* __[Common Tests](./unit-tests/commontest)__
* __[Server Tests](./unit-tests/servertest)__

## Software Specifications

Before starting to code the [Software Requirements Specifications](./doc/srs_digitalUno.pdf) and the [Software Design Specifications](./doc/sds_digitalUno.pdf) were determined. During the programming process some adaptions in the code were made.

## Shortcomings

When a game is over, there is no implementation allowing to start a second round.
