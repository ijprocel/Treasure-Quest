# Treasure-Quest
A text-based adventure!

In this game, the protagonist’s grandfather is on his deathbed and has revealed the location of a vault
filled with treasure. However, the vault requires four keys to open, which the protagonist
must obtain by defeating the four bandits who’ve stolen them.

To play, run the executable file 'final' in a terminal window. Alternatively, use 'make final' to recompile the source code.

### Game Overview:
The game is played on a board with 36 spaces, arranged 6x6. The player moves around the
board and can move from their current space to any adjacent space, whether diagonally,
vertically, or horizontally adjacent (a non-edge space will have 8 adjacent spaces). The
board is written to the terminal after each turn, with each space represented by a single
character.
There are 5 different types of spaces, each of which is a derived subclass of a master **Space** clas:
* **Mountains** – The only type of space that the player cannot occupy. They’re just there
as obstacles. They are represented by the character ‘A’ when the board is written to
the terminal. There are 8-10 on the board.
* **Portals** - The board has 2 of these, represented by ‘O’. If the player moves onto one
Portal, they are instantly transported to the other
* **The Vault** – The board has 1 of these, represented by an exclamation point (‘!’). After
the player defeats 4 enemies and acquires 4 keys, they must get to this space to win
the game.
* **Enemies** – When the player moves onto one of these spaces, they must battle an
enemy to win a key. They’re represented with ‘.’ (a period).
* **Blanks** – Nothing happens when these are occupied. They are also represented with
a period, meaning that the locations of enemies are hidden from the player.
Also, any space currently occupied by the player is represented with ‘x’, regardless of its
type.

The player starts the game with a certain number of strength points. Each time they move
to a different space, they lose a point. Battling enemies also causes a loss of strength points.
If the player runs out of strength points before accomplishing their goal (get to The Vault
with 4 keys), they lose the game.

### Battle:
To win the game, the player must battle and defeat opponents. Each enemy has a randomly
generated maximum attack power [6, 10]. The enemy will launch a random attack in the
range [1, maximum].
The player wagers some of their strength points for their own attack, losing them in the
process. If the amount wagered is greater than or equal to the enemy’s attack, they win the
battle, gain a key, and recover half the points wagered (rounded down for odd wagers).
For example, say a player with 19 strength points encounters an enemy with a maximum
power of 8, and wagers 7 of their strength points. Following the wager, they have 12
strength points left.

If the enemy’s attack is 6, the player wins and recovers 3 strength points, finishing the
battle with 15.

If the enemy’s attack is 7, the player wins and recovers 3 strength points, finishing the
battle with 15.

If the enemy’s attack is 8, the player loses and recovers no strength points, finishing the
battle with 12.

Upon winning a battle, the player gains a key.
After a battle takes place on a given space, that space will be empty for the rest of the game.
The player will encounter no more enemies after winning 4 battles.

### Classes:
* **Space** – An abstract class with 5 derived classes, one for each space type described
above. Has 8 Space pointers as data members pointing to each adjacent Space. Has a
“move_player()” function which takes a parameter indicating which way the player
wants to move next and performs all necessary movement actions.
* **Board** – Creates a 2D vector of Space pointers representing the game board.
Randomly selects 1 of 10 templates from a text file to build the board from. Returns
the player’s starting position to the main function and then has no more
involvement.
* **Player** – Keeps track of the player’s keys and strength points.

main.cpp Functions:
* **getMove()** - Gets player’s move and returns a char representing it
* **map_keys()** - The game is intended to be played with a number pad, so the default
control keys are all numbers. However, the user is prompted before the game to
designate new keys or play with the default ones.
