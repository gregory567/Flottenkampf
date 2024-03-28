#ifndef GAMECONTROLLER_HPP_INCLUDED
#define GAMECONTROLLER_HPP_INCLUDED

// forward declaration of class GameWorld
//class GameWorld;

class GameController{
    private:
        int round_counter;

    public:
        GameController();
        ~GameController();
        int getRoundCounter() const;
        void incrementRoundCounter();
        void buildFleet(Fleet& fleet, const std::string& fleetName);
        void fleetAttacksFleet(Fleet& attackingFleet, Fleet& targetFleet, GameWorld& gameWorld, const std::string& attackingFleetName, const std::string& targetFleetName);

};

#endif // GAMECONTROLLER_HPP_INCLUDED
