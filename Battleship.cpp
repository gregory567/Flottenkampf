


Battleship::Battleship(int shield, int shipsize, int damage){

    // input validation for constructor parameters
    if (shield < 0) {
        throw std::invalid_argument("Shield value cannot be negative.");
    }
    if (shipsize < 0) {
        throw std::invalid_argument("Ship size cannot be negative.");
    }
    if (damage < 0) {
        throw std::invalid_argument("Damage value cannot be negative.");
    }

    this->shield = shield;
    this->shipsize = shipsize;
    this->damage = damage;
    x = std::rand() % 10; // random x-coordinate between 0 and 9
    y = std::rand() % 10; // random y-coordinate between 0 and 9
    experiencePoints = 0;
    abilityOneUsed = false;
    abilityTwoUsed = false;
}

Battleship::~Battleship(){
    // destruction
}

int Battleship::getShieldValue() const{
    return shield;
}

int Battleship::getShipSize() const{
    return shipsize;
}

int Battleship::getDamage() const{
    return damage;
}

void Battleship::setShieldValue(int newShield){
    if(newShield >= 0){
        shield = newShield;
    } else {
        throw std::invalid_argument("Shield value cannot be negative.");
    }
}

void Battleship::setDamage(int newDamage){
    if (newDamage >= 0) {
        damage = newDamage;
    } else {
        throw std::invalid_argument("Damage value cannot be negative.");
    }
}

void Battleship::setPosition(int xPos, int yPos){
    // Boundary checking for xPos and yPos
    if (xPos < 0 || xPos >= 10 || yPos < 0 || yPos >= 10) {
        throw std::invalid_argument("Invalid position coordinates.");
    }
    x = xPos;
    y = yPos;
}

int Battleship::getXPosition() const{
    return x;
}

int Battleship::getYPosition() const{
    return y;
}

int Battleship::calculateDistance(int x1, int y1, int x2, int y2) const{
    // calculate and return the distance between two ships using distance formula
    int dx = x2 - x1;
    int dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

int Battleship::calculateAdjustedDamage(int distance) const{
    // logic for damage adjustment based on distance:
    // decrease the damage linearly as the distance increases
    // the average distance between two points on a 10 by 10 map is: 6.20484
    int maxDistance = 7; // maximum distance for full damage
    int damage = this->getDamage();
    return distance <= maxDistance ? damage : damage * (maxDistance / distance);
}

int Battleship::getExperiencePoints() const{
    return experiencePoints;
}

void Battleship::setExperiencePoints(int xp){
    experiencePoints = xp;
}

void Battleship::increaseExperiencePoints(int amount){
    experiencePoints += amount;
}
