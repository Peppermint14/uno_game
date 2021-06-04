# Digital UNO

This is a C++ implementation of the game UNO. It was a project for the course Software Engineering in Spring 2021 at ETHz.
The program is written to work for 2 to 4 players.


The UNO follows the official [UNO rules](https://service.mattel.com/instruction_sheets/42001pr.pdf) except for the following changes, that simplify the implementation:
- a Wild Draw 4 cards can allway be played (assuming it's your turn)
- When you picked up a card because you could not play, your turn is over
- When you have UNO you don't have to do anything, the program will automatically show a popup which says UNO
- When there are only two players in the game, the Reverse card doesn't do anything
- we don't count points 
 
While playing the game you can allways see wheter it is your turn or not on the game window. If it's your turn, you can play a card by clicking on it. If you don't have a card which you can play you have to click on the draw pile to pick up a card. 
On the right corner you can see a list of all players and how many cards they have at the moment. The player currently playing is highlighted.  


![UNO-logo](./assets/uno_logo.png?raw=true)

It uses [wxWidgets](https://www.wxwidgets.org/) for the GUI, [sockpp](https://github.com/fpagliughi/sockpp) for the network interface, [the nlohmann json library](https://github.com/nlohmann/json) for object serialization, [spdlog](https://github.com/gabime/spdlog) and [Google test](https://github.com/google/googletest) for testing the server.
Further some of the code and design is copied from the [Lama project](https://gitlab.ethz.ch/hraymond/cse-lama-example-project)


## Download and Compilation
Compiling the program will create two executables for running the program. One for running the server and one for running the client. 
# Da no gnauer schriebe oder ev alles im nechste kapitel was s teste betrifft??
Further it will create two?? executables in the folder unit-tests for testing the server (........??????????????????? for testing?????????????)

note: Executing the make file will take very long

0. Download the project either with ssh key `git@gitlab.ethz.ch:machart/cerealkillers.git` or with https `https://gitlab.ethz.ch/machart/cerealkillers.git`
1. Create a build folder `mkdir build`
2. navigate into the build folder `cd build`
3. type `cmake ..`
4. type `make`
5. To start a game now first start the server `./ck_server`
6. Then open the build folder in a new terminal window for each client. Start 2 to 4 clients by typing `./ck_client`. (for each client in a separate terminal window)
7. Now you only have to type in a name and press connect to server, then the game can start.  

## Server-tests 
.....
# Da no e churzi zemefassig zude tests -> was testets etc oder was au immer 

### Compiling and running the tests 

For the following steps we are assuming, you allready downloaded the whole project, using git clone, as it is described above and you created the build folder. 
0. If you are not yet in the build folder, go into the build folder `cd build`
1. If you didn't run the cmake file yet, type in `cmake ..` (if allready done you can skip it) 
2. type in `make test_game_controller_tests`
3. Run the tests with `./unit-tests/test_game_controller_tests`


##Code documentation

The code consits of three different parts: Server, Client and Common. 
All server files are only used by the server side. The client files are only used by the client and the common files are used by both the client and the server. 

The following two files show the originally planed Software Requirements Specifications and Software Design Specifications. During the programming some changes were made ........

[Software Requirements Specifications](./doc/srs_digitalUno.pdf)

[Software Design Specifications](./doc/sds_digitalUno.pdf)







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


