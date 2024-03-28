#ifndef BATTLESHIP_HPP_INCLUDED
#define BATTLESHIP_HPP_INCLUDED

// forward declaration of class Fleet and GameWorld
class Fleet;
class GameWorld;

class Battleship{
    private:

    protected:
        int shield;
        int shipsize;
        int damage;
        int x; // x-coordinate of the ship's position
        int y; // y-coordinate of the ship's position
        int experiencePoints;
        bool abilityOneUsed;    // Flag indicating if ability one has been used
        bool abilityTwoUsed;    // Flag indicating if ability two has been used

    public:
        Battleship(int shield, int shipsize, int damage);
        virtual ~Battleship();
        virtual void specialAttack(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) = 0;
        int getShieldValue() const;
        int getShipSize() const;
        int getDamage() const;
        virtual std::string getType() const = 0;
        void setShieldValue(int newShield);
        void setDamage(int newDamage);
        void setPosition(int xPos, int yPos);
        int getXPosition() const;
        int getYPosition() const;
        int calculateDistance(int x1, int y1, int x2, int y2) const;
        int calculateAdjustedDamage(int distance) const;
        int getExperiencePoints() const;
        void setExperiencePoints(int xp);
        void increaseExperiencePoints(int amount);
        virtual void abilityOne(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) = 0;
        virtual void abilityTwo(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) = 0;

};

#endif // BATTLESHIP_HPP_INCLUDED
