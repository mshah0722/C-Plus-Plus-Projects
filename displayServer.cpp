//
//  displayServer.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Copyright © 2019 Tarek Abdelrahman. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;

#include "tictactoe.h"
#include "gameState.h"

// Function prototype for playMove
void playMove(gameState&);

// The display server function
int displayServer() {

    /************************************************************************************************************/
    /* Insert code that loads the various images used by the game and creates the sprites                       */
    /* ECE244 Student: The loading of the X image is shown. Repeat for the rest of the images                  */
    /************************************************************************************************************/

    // Get the X image
    sf::Texture X_texture;
    if (!X_texture.loadFromFile("/share/copy/ece244f/lab2/data/X.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite X_sprite(X_texture);
    
    // Get the O image
    sf::Texture O_texture;
    if (!O_texture.loadFromFile("/share/copy/ece244f/lab2/data/O.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite O_sprite(O_texture);
    
    // Get the blank image
    sf::Texture Blank_texture;
    if (!Blank_texture.loadFromFile("/share/copy/ece244f/lab2/data/B.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite Blank_sprite(Blank_texture);
    
    // First, we find the sizes of the images so we can determine the size of the window we must create
    // The images (X, O and Black) are assumed to be square are are all of the same size
    // Thus, we just find the size of one of them
    
    // The tile size is the size of the images
    const int tileSize = O_texture.getSize().x;
    
    // The cell borders (thick lines) are rectangles
    // The size of these rectangles is 1/20th of the size of the tile by 3 
    const int barWidth = tileSize/20;
    const int barHeight = boardSize*tileSize + (boardSize-1)*barWidth;
    
    // The size of the window in pixels can now be calculated
    const int windowSize = boardSize*tileSize + (boardSize-1)*barWidth;
    
    // Create the main window: it has a title bar and a close button, but is not resizable
    // ECE244 Student: you should replace ECE244 in the title of the window by your login ID
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Tic-Tac_Toe (shahmal5 Display Server)", sf::Style::Titlebar | sf::Style::Close);
    
    // Set the Icon that appears in the task bar when the window is minimized
    // ECE244 Student: add your code here
    sf::Image windowIcon;
    if (!windowIcon.loadFromFile("/share/copy/ece244f/lab2/data/icon.jpg")) {
        return EXIT_FAILURE;
    }
    
    window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y,
                   windowIcon.getPixelsPtr());
    
    // Create the horizonal (vertical) borders as rectangles of sizes barWidth and barHeight (berHeight and barWidth)
    // ECE244 Student: insert your code here
    sf::RectangleShape horizontalBorder(sf::Vector2f(barWidth, barHeight));
    horizontalBorder.setFillColor(sf::Color::Black);

    sf::RectangleShape verticalBorder(sf::Vector2f(barWidth, barHeight));
    verticalBorder.setFillColor(sf::Color::Black);
    /************************************************************************************************************/
    /* Create and initialize the game state object                                                              */
    /************************************************************************************************************/
    gameState game_state;

    game_state.set_clickedRow(0);
    game_state.set_clickedColumn(0);
    game_state.set_moveValid(true); // This must start out as true
    game_state.set_gameOver(false);
    game_state.set_winCode(0);
    game_state.set_turn(true);  // X always plays first
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            game_state.set_gameBoard(i,j,Empty);
        }
    }
    
    /************************************************************************************************************/
    /* This is the main event loop of the code                                                                  */
    /************************************************************************************************************/
    
    // Start the game loop that runs as long as the window is open
    while (window.isOpen()) {
        // The event
        sf::Event event;
        
        // Process the events
        while (window.pollEvent(event)) {
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            // Left mouse button pressed: get the click position and update the game
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !game_state.get_gameOver()) {
                // left mouse button is pressed: get the coordinates in pixels
                // ECE244 Student: Insert your code to get the coordinates here
                sf::Vector2i localPosition = Mouse::getPosition(window);
                
                int xPosition = localPosition.x;
                int yPosition = localPosition.y;
                
                // Convert the pixel coordinates into game board rows and columns
                // Just divide by tileSize
                // Observe that the x axis is the rows and the y axis is the columns
                // Also make sure that row and column values are valid
                // ECE244 Student: Insert your code below
                int rowClicked = xPosition/tileSize;
                int columnClicked = yPosition/tileSize;
                if (game_state.get_gameBoard(rowClicked, columnClicked) == Empty)
                {
                    game_state.set_moveValid(true);
                }
                
                else
                {
                    game_state.set_moveValid(false);
                }
                
                // Update the game state object with the coordinates
                // ECE244 Student: insert code to update the object game_state here
                if (game_state.get_moveValid() == true)
                {
                    game_state.set_clickedRow(rowClicked);
                    game_state.set_clickedColumn(columnClicked);
                }
                
                else
                {
                    ;
                }
                // Update the game with the new move
                // ECE244 Student: invoke the playMove function here
                if (game_state.get_moveValid() == true)
                {
                    playMove(game_state);
                }
                
                else
                {
                    ;
                }
            }
        }

        // If the move is invalid, go to next event
        if (!game_state.get_moveValid()) continue;
                
        // Insert code to draw the tiles using the sprites created earlier
        // You must determine the position of each cell on the grid, taking into account the width of
        // the border and then position the sprite there and draw it.
        // Draw the entire board, cell borders included,
        // reflecting any move that has just happened (check the gameBoard array)
        // Further, if the game is over and one player wins, you must create and draw a rectangle of
        // windowSize width and 10 pixels height to indicate the winning marks
        // The fill of this rectangle should be white

        // ECE244 Student: insert your code here
        //First, draw the Blank background
        Blank_sprite.setPosition(0,0);
        window.draw(Blank_sprite);
        Blank_sprite.setPosition(0, tileSize + barWidth);
        window.draw(Blank_sprite);
        Blank_sprite.setPosition(0, 2*tileSize + 2*barWidth);
        window.draw(Blank_sprite);
        Blank_sprite.setPosition(tileSize + barWidth,0);
        window.draw(Blank_sprite);
        Blank_sprite.setPosition(tileSize + barWidth, tileSize+ barWidth);
        window.draw(Blank_sprite);
        Blank_sprite.setPosition(tileSize + barWidth, 2*tileSize+ 2*barWidth);
        window.draw(Blank_sprite);
        Blank_sprite.setPosition(tileSize*2 + barWidth*2,0);
        window.draw(Blank_sprite);
        Blank_sprite.setPosition(2*tileSize+ 2*barWidth, tileSize+ barWidth);
        window.draw(Blank_sprite);
        Blank_sprite.setPosition(2*tileSize+ 2*barWidth, 2*tileSize+ 2*barWidth);
        window.draw(Blank_sprite);
        
        //Next, draw the horizontal borders
        horizontalBorder.setPosition(0, tileSize);
        horizontalBorder.setRotation(90);
        window.draw(horizontalBorder);
        horizontalBorder.setPosition(0, tileSize*2 + barWidth);
        horizontalBorder.setRotation(90);
        window.draw(horizontalBorder);
        
        //lNext, draw vertical borders
        verticalBorder.setPosition(tileSize, 0);
        window.draw(verticalBorder);
        verticalBorder.setPosition(tileSize*2 + barWidth, 0);
        window.draw(verticalBorder);
        
        for (int i = 0; i < boardSize; ++i) {
           for (int j = 0; j < boardSize; ++j) {
               int value = game_state.get_gameBoard(i,j);
               if (value == X)
               {
                   X_sprite.setPosition(i*tileSize + i*barWidth, j*tileSize + j*barWidth);
                   window.draw(X_sprite);
               }
               else if (value == O)
               {
                   O_sprite.setPosition(i*tileSize + i*barWidth, j*tileSize + j*barWidth);
                   window.draw(O_sprite);
               }
           }
        }
        
        //Next, we need to draw a line for a win
        sf::RectangleShape winningLine(sf::Vector2f(windowSize, 10));
        winningLine.setFillColor(sf::Color::White);

        sf::RectangleShape winningDiagonal(sf::Vector2f(sqrt(2*windowSize*windowSize), 10));
        winningDiagonal.setFillColor(sf::Color::White);
        
        //Implement the winning lines
        if(game_state.get_gameOver() == true && game_state.get_winCode() != 0)
        {
            if (game_state.get_winCode() == 4)
            {
                winningLine.setPosition(0, tileSize/2);
                window.draw(winningLine);
            }
            
            else if (game_state.get_winCode() == 5)
            {
                winningLine.setPosition(0, (tileSize*2 + barWidth) - tileSize/2 - barWidth/2);
                window.draw(winningLine);
            }
            
            else if (game_state.get_winCode() == 6)
            {
                winningLine.setPosition(0, (tileSize*3 + barWidth*2) - tileSize/2 - barWidth/2);
                window.draw(winningLine);
            }
            
            else if (game_state.get_winCode() == 1)
            {
                winningLine.rotate(90);
                winningLine.setPosition(tileSize/2, 0);
                window.draw(winningLine);
            }
            
            else if (game_state.get_winCode() == 2)
            {
                winningLine.rotate(90);
                winningLine.setPosition((tileSize*2 + barWidth) - tileSize/2 - barWidth/2, 0);
                window.draw(winningLine);
            }
            
            else if (game_state.get_winCode() == 3)
            {
                winningLine.rotate(90);
                winningLine.setPosition((tileSize*3 + barWidth*2) - tileSize/2 - barWidth/2, 0);
                window.draw(winningLine);
            }
            
            else if (game_state.get_winCode() == 7)
            {
                winningDiagonal.rotate(45);
                winningDiagonal.setPosition(0,0);
                window.draw(winningDiagonal);
            }
            
            else if (game_state.get_winCode() == 8)
            {
                winningDiagonal.rotate(-45);
                winningDiagonal.setPosition(0,windowSize);
                window.draw(winningDiagonal);
            }
        }
        
        // Display to the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}

