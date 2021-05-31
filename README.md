# CerealKillers

## Server-tests Compilation:


0. Clone the server branch with ```git clone -b server https://gitlab.ethz.ch/machart/cerealkillers.git```
1. Create a `build` folder
2. `cd` into `build`
3. cmake .. 
4. make test_game_controller_tests

### Run test
Run with ```./unit-tests/test_game_controller_tests```


TODO:
- store Playernames correctly (when they arrive with NewPlayer request
- something is wrong with the number of cards, that get distributed (way to many blue 0)
