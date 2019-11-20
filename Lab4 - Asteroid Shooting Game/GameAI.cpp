#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

//Global variables to set initial ship turn to Clockwise 
bool turnClockwise = true; // Controls Clockwise Turn
bool turnCounterClockwise = false; // Controls CounterClockwise Turn

//bool aimStraight = false;
//bool switchsides = true;

//Global variables set the max and min angle the ship should fire
int maxAngleToFire = 35000; //35 degrees (Max Angle)
int minAngleToFire = -35000; //-35 degrees (Min Angle)

GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
	this->debug_rt = debug_rt;
	this->game_info = game_info;
	this->asteroid_observer = AsteroidsObserver(this);
	this->my_game_ai = new MyAIData();

	// customState().debug_on = false;
}

GameAI::~GameAI() {
	delete my_game_ai;
}

SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
	debug_rt->clear(sf::Color::Transparent);

	if (customState().debug_on) {
		if (not asteroidsObserver().asteroids().isEmpty()) {
			const sf::IntRect first_ast_hb = asteroidsObserver().asteroids().front().getCurrentHitbox();
			sf::RectangleShape ast_rect(sf::Vector2f(first_ast_hb.width, first_ast_hb.height));
			ast_rect.setPosition(first_ast_hb.left, first_ast_hb.top);
			ast_rect.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect.setOutlineColor(sf::Color::Yellow);
			ast_rect.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect);
		}
	}
        
        //If the ship angle exceeds 30 degrees while going clockwise 
        //Both boolean values switch
        if (turnClockwise && ship_state.millidegree_rotation > maxAngleToFire) {
            turnClockwise = !turnClockwise;
            turnCounterClockwise = !turnCounterClockwise;
        }
        
//        if (turnClockwise && ship_state.millidegree_rotation == 0) {
//            turnClockwise = !turnClockwise;
//            aimStraight = !aimStraight;
//        }
//        
//        if(aimStraight && switchsides) {
//            aimStraight = !aimStraight;
//            turnCounterClockwise = !turnCounterClockwise;
//        }
        
        //If the ship angle falls below -30 degrees while going clockwise 
        //Both boolean values switch
        if (turnCounterClockwise && ship_state.millidegree_rotation < minAngleToFire) {
            turnCounterClockwise = !turnCounterClockwise;
            turnClockwise = !turnClockwise;
        }
        
//        if (turnCounterClockwise && ship_state.millidegree_rotation == 0) {
//            turnCounterClockwise = !turnCounterClockwise;
//            aimStraight = !aimStraight;
//        }
//        
//        if(aimStraight && !switchsides) {
//            aimStraight = !aimStraight;
//            turnClockwise = !turnClockwise;
//        }
        
        //If turnClockwise is true, the ship turns clockwise and shoots
        if (turnClockwise) {
            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
        }
        
//        if (aimStraight) {
//            return SimpleActions::STOP_YAWING_AND_FIRE;
//        }
        
        ////If turnCounterClockwise is true, the ship turns counter clockwise and shoots
        if (turnCounterClockwise) {
            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
        }
        
        //Factors such as proximity of asteroids to the ship
        //The time until the phaser bank charges
        //The mass of an asteroid as well as its remaining health
        //The larger the asteroids that are destroyed, the higher the score
        
	return SimpleActions::NO_CHANGE;
	// return SimpleActions::START_YAWING_CW;
	// return SimpleActions::START_YAWING_ACW;
	// return SimpleActions::STOP_YAWING_AND_FIRE;
	// return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
}
