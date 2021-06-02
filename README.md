# CerealKillers

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
