/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */

#include <galaxy-explorer/AsteroidsObserver.hpp>

//Function is called whenever a new asteroid appears on the field
//Function pushes the asteroid to the front of asteroid list
void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    asteroid_list.pushFront(asteroid);
}

//Function is called when an asteroid has moved
//Function uses Asteroid ID to find the asteroid that needs to be replaced
//Then it creates a new list item with the updated asteroid information
//It then deletes the older list = item
void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    AsteroidListItem *temp = asteroid_list.beforeBegin();
    while (temp != asteroid_list.beforeEnd()) {
        if (temp->getNext()->getData().getID() == asteroid.getID()) {
            asteroid_list.insertAfter(temp->getNext(), asteroid);
            asteroid_list.eraseAfter(temp);
            return;
        }
        temp = temp->getNext();
    }
}

//Called when an asteroid leaves the field without being destroyed
//Functions finds the Asteroid and deletes it from the linked list
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem *temp = asteroid_list.beforeBegin();
    while (temp != asteroid_list.beforeEnd()) {
        if (temp->getNext()->getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(temp);
            return;
        }
        temp = temp->getNext();
    }  
}

//Called when an asteroid is destroyed by a phaser shot
//Functions finds the Asteroid and deletes it from the linked list
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    AsteroidListItem *temp = asteroid_list.beforeBegin();
    while (temp != asteroid_list.beforeEnd()) {
        if (temp->getNext()->getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(temp);
            return;
        }
        temp = temp->getNext();
    }  
}
