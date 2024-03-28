

Kreuzer::Kreuzer() : Battleship(250, 8, 50){
    // construction
}

Kreuzer::~Kreuzer(){
    // destruction
}

void Kreuzer::specialAttack(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld){

    int success_counter = 0;
    int failure_counter = 0;
    // Kreuzers are allowed to make an additional attack against the same ship if the first one was successful
    do{
        // roll a 10-sided dice, returns a random number between 1 and 10
        int diceRoll = std::rand() % 10 + 1;

        if(diceRoll >= targetShip->getShipSize()){

            success_counter++;
            // increase experience points by 20 after every successful attack
            this->increaseExperiencePoints(20);
            // calculate the distance between this ship and the target ship using their positions
            int distance = this->calculateDistance(x, y, targetShip->getXPosition(), targetShip->getYPosition());

            // adjust the damage based on the calculated distance
            int adjustedDamage = this->calculateAdjustedDamage(distance);

            int currentShield = targetShip->getShieldValue();
            int newShield = currentShield - adjustedDamage;
            if(newShield < 1){
                // we need to set the success counter equal to 2 here,
                // otherwise the next ship of the enemy fleet can be destroyed instantly as well
                success_counter = 2;
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
            failure_counter++;
            std::cout << "Attack missed!\n";
        }
    }while(success_counter < 2 && failure_counter < 1);
}

std::string Kreuzer::getType() const {
    return "Kreuzer";
}

void Kreuzer::abilityOne(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) {
    // create a protective force field around friendly ships in the fleet
    std::vector<Battleship*>& fleetShips = friendlyFleet.getFleet();
    int numShips = fleetShips.size();
    int forceFieldStrength = numShips * 3;

    // increase the shield value of each friendly ship in the fleet
    for (Battleship* ship : fleetShips) {
        int currentShield = ship->getShieldValue();
        int newShield = currentShield + forceFieldStrength;
        int maxShieldValue = 0;

        if (ship->getType() == "Jaeger") {
            maxShieldValue = 75;
        } else if (ship->getType() == "Kreuzer") {
            maxShieldValue = 250;
        } else if (ship->getType() == "Zerstoerer") {
            maxShieldValue = 150;
        } else {
            throw std::runtime_error("Invalid ship type.");
        }

        newShield = std::min(newShield, maxShieldValue);
        ship->setShieldValue(newShield);
    }

    std::cout << "Kreuzer used Ability 1: Created a protective force field around friendly ships. Increased shield value by " << forceFieldStrength << " for each ship." << std::endl;
}

void Kreuzer::abilityTwo(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) {
    // swap positions with another friendly ship
    // choose a random friendly ship in the friendly fleet
    Battleship* friendlyShip = friendlyFleet.getRandomShip();
    if(friendlyShip){
        gameWorld.swapShips(this, friendlyShip);
        std::cout << "Kreuzer used Ability 2: Swapped positions with a friendly ship" << std::endl;
    } else {
        throw std::runtime_error("No friendly ship available for position swap.");
    }
}
