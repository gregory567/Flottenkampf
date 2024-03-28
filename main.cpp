

// libraries
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>
#include <random>
#include <ctime>
#include <stdexcept>
#include <cmath>

// classes
#include "Fleet.hpp"
#include "Battleship.hpp"
#include "Jaeger.hpp"
#include "Kreuzer.hpp"
#include "Zerstoerer.hpp"
#include "GameController.hpp"
#include "GameWorld.hpp"


#include "Fleet.cpp"
#include "Battleship.cpp"
#include "Jaeger.cpp"
#include "Kreuzer.cpp"
#include "Zerstoerer.cpp"
#include "GameController.cpp"
#include "GameWorld.cpp"


int main(){

    try{
        // seed the random number generator with the current time
        std::srand(std::time(nullptr));

        // initialize fleets and the game controller
        Fleet fleet1;
        Fleet fleet2;
        GameController game;

        // build up Fleet 1
        game.buildFleet(fleet1, "Fleet 1");

        // build up Fleet 2
        game.buildFleet(fleet2, "Fleet 2");

        // initialize 2-dimensional game world with the fleets
        GameWorld gameWorld(10, 10, fleet1, fleet2);

        // while-loop for the battle (until one of the fleets gets destroyed)
        while(!fleet1.isDestroyed() && !fleet2.isDestroyed()){

            // display the round counter:
            std::cout << std::endl;
            std::cout << "Round: " << game.getRoundCounter() << std::endl;

            // Fleet 1 attacks Fleet 2
            try{
                game.fleetAttacksFleet(fleet1, fleet2, gameWorld, "Fleet 1", "Fleet 2");
            } catch(const std::exception& except){
                std::cout << "Error: " << except.what() << std::endl;
            }

            // Fleet 2 attacks Fleet 1
            // it can happen that Fleet 1 already destroyed the last ship of Fleet 2 in the previous step
            if (!fleet2.isDestroyed()){
                try{
                    game.fleetAttacksFleet(fleet2, fleet1, gameWorld, "Fleet 2", "Fleet 1");
                } catch(const std::exception& except){
                    std::cout << "Error: " << except.what() << std::endl;
                }
            } else{
                continue;
            }

            // display end of current round
            std::cout << std::endl << "End of round: " << game.getRoundCounter() << std::endl;
            // increment round counter for the next round
            game.incrementRoundCounter();
        }

        // determine the winner based on remaining ships at the end of the game
        if(fleet2.isDestroyed()){
            std::cout << std::endl;
            std::cout << "Fleet 1 has won the game!\n";
        } else{
            std::cout << std::endl;
            std::cout << "Fleet 2 has won the game!\n";
        }
        // display the final state of the game world
        gameWorld.displayGameWorld();

        // clean up the dynamically allocated memory
        fleet1.clearFleet();
        fleet2.clearFleet();
    } catch(const std::exception& except){
        std::cout << "Unhandled exception: " << except.what() << std::endl;
    }

    return 0;
}

