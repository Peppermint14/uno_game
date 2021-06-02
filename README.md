# CerealKillers





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

