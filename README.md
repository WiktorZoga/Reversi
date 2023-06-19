# Reversi 
Reversi is a strategy board game for two players, played on an 8×8 uncheckered board. 
(Project for object-oriented programming class)

## About Reversi

1. Reversi is played on a square board with 8 rows and 8 columns. Each player starts with two pieces of their color, usually black and white, placed in the center of the board diagonally.

2. Black always moves first.

3. The objective of the game is to have the majority of your pieces of your color on the board at the end of the game.

4. Players take turns placing one piece of their color on the board. A piece must be placed in such a way that it "sandwiches" one or more of the opponent's pieces between two of their own pieces, either horizontally, vertically, or diagonally. All sandwiched pieces are flipped to the current player's color.

5. Players must make a legal move if one is available. If a player cannot make a legal move, their turn is forfeited, and the opponent continues to play until no legal moves are possible.

6. It is mandatory to make a move if one is available. You cannot skip your turn unless you have no legal moves.

7. The game ends when the board is completely filled with pieces, or when no legal moves are possible for either player.

8. The player with the most pieces of their color on the board at the end of the game wins. The pieces are counted and the player with the majority wins. In case of a tie, the game is considered a draw.

9. It is customary to say "pass" if you have no legal moves but your opponent does. This is to signal that you are intentionally passing your turn.

10. Reversi is a strategic game, and it requires careful planning and foresight to outmaneuver your opponent and control the board.

## How to run
Compile with _make main_. Tested on Linux Ubuntu 20.04.5 LTS.\
Standard libraries and _ncurses_ mandatory.

## How to play
You can move the cursor _'@'_ with the w-s-a-d keys and confirm move by _enter_.

