
#include "Jaeger.hpp"

Jaeger::Jaeger() : Battleship(75, 4, 30){
    // construction
}

Jaeger::~Jaeger(){
    // destruction
}

void Jaeger::specialAttack(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld){

    // check if targetShip is valid
    if(targetShip == nullptr){
        throw std::invalid_argument("Invalid target ship pointer");
    }

    // roll a 10-sided dice, returns a random number between 1 and 10
    int diceRoll = std::rand() % 10 + 1;

    // Jaegers cause double damage if the result of the dice roll was 9 or 10
    if(diceRoll >= targetShip->getShipSize()){

        // increase experience points by 20 after every successful attack
        this->increaseExperiencePoints(20);

        // calculate the distance between this ship and the target ship using their positions
        int distance = this->calculateDistance(x, y, targetShip->getXPosition(), targetShip->getYPosition());

        // adjust the damage based on the calculated distance
        int adjustedDamage = this->calculateAdjustedDamage(distance);

        if(diceRoll > 8){
            adjustedDamage *= 2;
        }

        int currentShield = targetShip->getShieldValue();
        int newShield = currentShield - adjustedDamage;
        if(newShield < 1){
            std::cout << "Target ship destroyed!\n";
            enemyFleet.destroyTargetShip();
            gameWorld.removeShip(targetShip);
        } else {
            targetShip->setShieldValue(newShield);
            std::cout << "Attack successful! Target ship shield: " << newShield << "\n";
        }

        // Check experience points and use additional abilities if not already used
        if(this->getExperiencePoints() >= 100 && !abilityOneUsed){
            this->abilityOne(friendlyFleet, enemyFleet, targetShip, gameWorld);
            abilityOneUsed = true;
        } else if(this->getExperiencePoints() >= 200 && !abilityTwoUsed){
            this->abilityTwo(friendlyFleet, enemyFleet, targetShip, gameWorld);
            abilityTwoUsed = true;
        }
    } else {
        std::cout << "Attack missed!\n";
    }
}

std::string Jaeger::getType() const {
    return "Jaeger";
}

void Jaeger::abilityOne(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) {
    // Activate an energy shield that absorbs a portion of incoming damage
    int shieldValue = this->getShieldValue();
    // Absorb 50% of the damage dealt by a similar ship
    int absorbedDamage = static_cast<int>(this->getDamage() * 0.5);
    shieldValue += absorbedDamage;
    this->setShieldValue(shieldValue);
    std::cout << "Jaeger used Ability 1: Activated an energy shield that absorbs " << absorbedDamage << " damage." << std::endl;
}

void Jaeger::abilityTwo(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) {
    // Perform a precision strike, targeting a specific module of the target ship
    int targetSize = targetShip->getShipSize();
    // Select a random module to target
    int targetModule = std::rand() % targetSize + 1;
    // Damage based on the targeted module
    int attackDamage = targetModule * 10;
    int remainingShield = targetShip->getShieldValue() - attackDamage;
    if(remainingShield < 1){
        std::cout << "Target ship destroyed!" << std::endl;
        enemyFleet.destroyTargetShip();
        gameWorld.removeShip(targetShip);
    } else {
        targetShip->setShieldValue(remainingShield);
        std::cout << "Attack successful! Target ship shield: " << remainingShield << std::endl;
    }
    std::cout << "Jaeger used Ability 2: Precision strike on module " << targetModule << " dealing " << attackDamage << " damage." << std::endl;
}

