


void Fleet::addShip(Battleship* ship){
    if(ship != nullptr){
        ships.push_back(ship);
    } else {
        throw std::invalid_argument("Invalid ship pointer.");
    }
}

void Fleet::displayFleetInformation() const {
    int shipNumber = 1;
    for (const auto& ship : ships) {
        std::cout << "Ship " << shipNumber << " - Type: " << ship->getType()
                  << ", Shield: " << ship->getShieldValue()
                  << ", Size: " << ship->getShipSize()
                  << ", Damage: " << ship->getDamage()
                  << ", X-Coordinate: " << ship->getXPosition() + 1
                  << ", Y-Coordinate: " << ship->getYPosition() + 1 << std::endl;
        shipNumber++;
    }
}

std::vector<Battleship*>& Fleet::getFleet() {
    return ships;
}

bool Fleet::isDestroyed() const{
    return ships.empty();
}

int Fleet::getFleetLength() const{
    return ships.size();
}

void Fleet::setAttackingShipIndex(int attackingShip){
    if (attackingShip >= 0 && attackingShip < static_cast<int>(ships.size())) {
        attackingShipIndex = attackingShip;
    } else {
        throw std::out_of_range("Invalid attacking ship index.");
    }
}

Battleship* Fleet::getAttackingShip() const{
    if(attackingShipIndex >= 0 && attackingShipIndex < static_cast<int>(ships.size())){
        return ships[attackingShipIndex];
    } else {
        throw std::out_of_range("Attacking ship index out of range.");
    }
}

void Fleet::setTargetShipIndex(int targetShip){
    if (targetShip >= 0 && targetShip < static_cast<int>(ships.size())) {
        targetShipIndex = targetShip;
    } else {
        throw std::out_of_range("Invalid target ship index.");
    }
}

Battleship* Fleet::getTargetShip() const{
    if(targetShipIndex >= 0 && targetShipIndex < static_cast<int>(ships.size())){
        return ships[targetShipIndex];
    } else {
        throw std::out_of_range("Target ship index out of range.");
    }
}

void Fleet::destroyTargetShip(){
    if (targetShipIndex >= 0 && targetShipIndex < static_cast<int>(ships.size())) {
        ships.erase(ships.begin() + targetShipIndex);
    } else {
        throw std::out_of_range("Target ship index out of range.");
    }
}

void Fleet::clearFleet(){
    // deallocate the dynamically allocated memory for each ship
    for(auto ship : ships){
        delete ship;
    }
    // clear the vector of ship pointers
    ships.clear();
    // reset the attacking ship index
    attackingShipIndex = -1;
    // reset the target ship index
    targetShipIndex = -1;
}

Battleship* Fleet::getRandomShip() const{
    if(ships.empty()){
        return nullptr;
    }

    // Get a random index
    int randomIndex = rand() % this->getFleetLength();

    // Return the random ship
    return ships[randomIndex];
}


