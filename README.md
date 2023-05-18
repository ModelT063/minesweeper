# Commnand Line Minesweeper

A renewal of one of my first coding projects (now lost to time) but in C instead of python, and arguably much better in many ways.  
Still working out the kinks and creating better functionality inbetween classes.  
Downloading the .c and .h files and manually compiling is currently the only way to play, hopefully this will be more robust in the future.  

## Game Instructions

1. Choose a difficulty by entering 1, 2 or 3
    * Easy, 9x9 with 10 bombs
    * Medium, 16x16 with 40 bombs
    * Hard, 16x30 with 99 bombs
2. Enter an action
    * r (reveal) - will uncover the selected tile and if a 0, subsequent tiles around it
    * f (flag) - will flag/unflag the selected tile, flagged tiles cannot be revealed unless unflagged
    * q (quit) - exits the game
3. Choose the location
    * Enter in a column number followed by a row number and watch the board update with your selection
4. Play again!
