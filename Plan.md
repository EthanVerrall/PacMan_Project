![Basic Diagram of pacman](image.png)

# Pacman

## Description of the Ghosts
There are four ghosts, each of the ghosts have different behaviours. 
- Red - Follows pacman
- Pink - Goes 4 steps ahead of pacman
- 

## Ghost Algorithm


## The Board


## Pacman

## Sections
There are four sections, 
- Home Screen
- Gameplay
- Score Board
- Options
- Pause Menu
- Create User

## Responsibilities
- Joshua
1) Make the ghost struct? (You can make one that is the same for all 4 OR they can each have their own unique struct)
2) Algorithms for the ghost, You will get pacmans postion through my point/pacman struct and then you will do as needed.
3) Get assets for us to use and draw

- Ethan
1) Finish Point
2) Finish board/grid
3) -Make the board static and singleton since it's always the same.
4) Make the PacMan and movement

- Illa
1) Create basic home screen that matches the image.
2) We dont need a fancy background yet, just get the text to display and highlight current selected text.
3) If you can, consider making the text flash between white and another colour while its highlighted to make it appear alive. - No need to priotise this at the start.
4) If you want after this you can try make the background like look something a home screen pacman would use.

PS: Try to group your menus in structs, that point to other structs that will describe what the current screen looks like and what state must be drawn.
    I might provide you with a basic struct state. 