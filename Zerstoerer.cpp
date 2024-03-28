


Zerstoerer::Zerstoerer() : Battleship(150, 6, 60){
    // construction
}

Zerstoerer::~Zerstoerer(){
    // destruction
}

void Zerstoerer::specialAttack(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld){

    // roll a 10-sided dice, returns a random number between 1 and 10
    int diceRoll = std::rand() % 10 + 1;

    // dice rolls are made with a 2-point advantage over the target ship
    if(diceRoll >= targetShip->getShipSize() - 2){

        // increase experience points by 20 after every successful attack
        this->increaseExperiencePoints(20);

        // calculate the distance between this ship and the target ship using their positions
        int distance = this->calculateDistance(x, y, targetShip->getXPosition(), targetShip->getYPosition());

        // adjust the damage based on the calculated distance
        int adjustedDamage = this->calculateAdjustedDamage(distance);

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

std::string Zerstoerer::getType() const {
    return "Zerstoerer";
}

void Zerstoerer::abilityOne(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld){
    // Perform a devastating barrage attack, hitting multiple modules of the target ship
    int targetSize = targetShip->getShipSize();
    int numModules = targetSize / 2; // Attack half of the target ship's modules
    int attackDamage = targetSize; // Damage based on the size of the target ship
    int remainingShield = targetShip->getShieldValue();

    for(int i = 0; i < numModules; i++){
        remainingShield -= attackDamage;
        if (remainingShield < 1) {
            std::cout << "Target ship destroyed!" << std::endl;
            enemyFleet.destroyTargetShip();
            gameWorld.removeShip(targetShip);
            break;
        }
    }

    targetShip->setShieldValue(remainingShield);
    std::cout << "Zerstoerer used Ability 1: Devastating barrage attack, hitting " << numModules << " modules. Target ship shield: " << remainingShield << std::endl;
}

void Zerstoerer::abilityTwo(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) {
    // Increase the damage dealt by the Zerstoerer for the next attack
    int currentDamage = this->getDamage();
    int increasedDamage = currentDamage + 20;
    const int maxDamage = 100;

    if (increasedDamage > maxDamage) {
        increasedDamage = maxDamage;
    }

    this->setDamage(increasedDamage);
    std::cout << "Zerstoerer used Ability 2: Increased damage for the next attack to " << increasedDamage << std::endl;
}

/*
void Zerstoerer::abilityTwo(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) {
    // Launch a barrage of guided missiles at the enemy fleet, damaging multiple ships
    int numShips = enemyFleet.getFleetLength();
    // Number of missiles to launch
    int missileCount = numShips / 2;

    // Inflict damage on multiple enemy ships with guided missiles
    for(int i = 0; i < missileCount; i++){
        // Select a random enemy ship
        int randomIndex = std::rand() % numShips;

        enemyfleet.setTargetShipIndex(randomIndex);
        Battleship* ship = enemyFleet.getTargetShip();

        int currentShield = ship->getShieldValue();
        // Random damage between 30 and 50
        int missileDamage = std::rand() % 21 + 30;
        int newShield = currentShield - missileDamage;

        if (newShield < 1) {
            std::cout << "Target ship destroyed!" << std::endl;
            enemyFleet.destroyTargetShip();
            gameWorld.removeShip(targetShip);
        } else {
            ship->setShieldValue(newShield);
            std::cout << "Missile hit! Target ship shield: " << newShield << std::endl;
        }
    }

    std::cout << "Zerstoerer used Ability 2: Launched a barrage of guided missiles, damaging " << missileCount << " enemy ships." << std::endl;
}
*/
