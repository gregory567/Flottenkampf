#ifndef FLEET_HPP_INCLUDED
#define FLEET_HPP_INCLUDED

// forward declaration of class Battleship
class Battleship;

class Fleet {
    private:
        std::vector<Battleship*> ships;
        int attackingShipIndex;
        int targetShipIndex;

    public:
        void addShip(Battleship* ship);
        void displayFleetInformation() const;
        std::vector<Battleship*>& getFleet();
        bool isDestroyed() const;
        int getFleetLength() const;

        void setAttackingShipIndex(int attackingShip);
        Battleship* getAttackingShip() const;

        void setTargetShipIndex(int targetShip);
        Battleship* getTargetShip() const;

        void destroyTargetShip();
        void clearFleet();
        Battleship* getRandomShip() const;
};


#endif // FLEET_HPP_INCLUDED
