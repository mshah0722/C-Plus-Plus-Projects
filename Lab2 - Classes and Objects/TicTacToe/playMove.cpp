//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//

#include "tictactoe.h"
#include "gameState.h"

void playMove(gameState& game_state) {
    
    //Sets win code to 0 unless there is a win
    game_state.set_winCode(0);
   
    //Checks if move is valid based on the position on game board
    if (game_state.get_gameBoard(game_state.get_clickedRow(),
        game_state.get_clickedColumn()) == Empty)
    {
        game_state.set_moveValid(true);
    }
   
    //If the spot on the game board is already filled, then move is invalid
    else
    {
        game_state.set_moveValid(false);
    }

    //If the move is valid, fill the spot with the correct turn value
    if (game_state.get_moveValid() == true && game_state.get_turn() == true)
    {
        game_state.set_gameBoard(game_state.get_clickedRow(),
        game_state.get_clickedColumn(),X);
    }
   
    if (game_state.get_moveValid() == true && game_state.get_turn() == false)
    {
        game_state.set_gameBoard(game_state.get_clickedRow(),
        game_state.get_clickedColumn(),O);
    }
    
    //If the move is invalid, ignore the request and try again   
    else if (game_state.get_moveValid() == false)
    {
        return;
    }

    //Sets the different win codes based on the instructions provided
   
    //Row 1 Win
    if (((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(0, 1) +
          game_state.get_gameBoard(0, 2)) == 3) ||
        ((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(0, 1) +
          game_state.get_gameBoard(0, 2)) == -3))
    {
        game_state.set_gameOver(true);
        game_state.set_winCode(1);
        return;
    }

    //Row 2 Win
    else if (((game_state.get_gameBoard(1, 0) + game_state.get_gameBoard(1, 1) +
               game_state.get_gameBoard(1, 2)) == 3) ||
             ((game_state.get_gameBoard(1, 0) + game_state.get_gameBoard(1, 1) +
               game_state.get_gameBoard(1, 2)) == -3))
    {
        game_state.set_gameOver(true);
        game_state.set_winCode(2);
        return;
    }

    //Row 3 Win
    else if (((game_state.get_gameBoard(2, 0) + game_state.get_gameBoard(2, 1) +
               game_state.get_gameBoard(2, 2)) == 3) ||
             ((game_state.get_gameBoard(2, 0) + game_state.get_gameBoard(2, 1) +
               game_state.get_gameBoard(2, 2)) == -3))
    {
        game_state.set_gameOver(true);
        game_state.set_winCode(3);
        return;
    }

    //Col 1 Win
    else if (((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(1, 0) +
               game_state.get_gameBoard(2, 0)) == 3) ||
             ((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(1, 0) +
               game_state.get_gameBoard(2, 0)) == -3))
    {
        game_state.set_gameOver(true);
        game_state.set_winCode(4);
        return;
    }

    //Col 2 Win
    else if (((game_state.get_gameBoard(0, 1) + game_state.get_gameBoard(1, 1) +
               game_state.get_gameBoard(2, 1)) == 3) ||
             ((game_state.get_gameBoard(0, 1) + game_state.get_gameBoard(1, 1) +
               game_state.get_gameBoard(2, 1)) == -3))
    {
        game_state.set_gameOver(true);
        game_state.set_winCode(5);
        return;
    }

    //Col 3 Win
    else if (((game_state.get_gameBoard(0, 2) + game_state.get_gameBoard(1, 2) +
               game_state.get_gameBoard(2, 2)) == 3) ||
             ((game_state.get_gameBoard(0, 2) + game_state.get_gameBoard(1, 2) +
               game_state.get_gameBoard(2, 2)) == -3))
    {
        game_state.set_gameOver(true);
        game_state.set_winCode(6);
        return;
    }

    //Top-left to bottom-right diagonal win
    else if (((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(1, 1) +
               game_state.get_gameBoard(2, 2)) == 3) ||
             ((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(1, 1) +
               game_state.get_gameBoard(2, 2)) == -3))
    {
        game_state.set_gameOver(true);
        game_state.set_winCode(7);
        return;
    }

    //Top-right to bottom-left diagonal win
    else if (((game_state.get_gameBoard(2, 0) + game_state.get_gameBoard(1, 1) +
               game_state.get_gameBoard(0, 2)) == 3) ||
             ((game_state.get_gameBoard(2, 0) + game_state.get_gameBoard(1, 1) +
               game_state.get_gameBoard(0, 2)) == -3))
    {
        game_state.set_gameOver(true);
        game_state.set_winCode(8);
        return;
    }

    //Checks for tie
    else if ((game_state.get_gameBoard(0, 0) != 0) &&
             (game_state.get_gameBoard(0, 1) != 0) &&
             (game_state.get_gameBoard(0, 2) != 0) &&
             (game_state.get_gameBoard(1, 0) != 0) &&
             (game_state.get_gameBoard(1, 1) != 0) &&
             (game_state.get_gameBoard(1, 2) != 0) &&
             (game_state.get_gameBoard(2, 0) != 0) &&
             (game_state.get_gameBoard(2, 1) != 0) &&
             (game_state.get_gameBoard(2, 2) != 0))
    {
        game_state.set_gameOver(true);
        game_state.set_winCode(0);
        return;
    }
   
    //Switches the turn from one to the other at the end of the turn
    game_state.set_turn(!(game_state.get_turn()));
}

