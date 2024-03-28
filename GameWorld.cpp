


GameWorld::GameWorld(int worldWidth, int worldHeight, Fleet& fleet1, Fleet& fleet2){
    width = worldWidth;
    height = worldHeight;
    // initialize the grid with nullptrs to represent empty positions
    grid.resize(height, std::vector<Battleship*>(width, nullptr));

    // this is the same as:
    /*
    grid.resize(height);
    for(int y = 0; y < height; y++){
        grid[y].resize(width, nullptr);
    }
    */

    // iterate through the ships of Fleet 1 and store them in the grid
    for(Battleship* ship : fleet1.getFleet()){
        int x = ship->getXPosition();
        int y = ship->getYPosition();
        grid[y][x] = ship;
    }

    // iterate through the ships of Fleet 2 and store them in the grid
    for(Battleship* ship : fleet2.getFleet()){
        int x = ship->getXPosition();
        int y = ship->getYPosition();
        grid[y][x] = ship;
    }
}

GameWorld::~GameWorld(){
    // destruction
}

int GameWorld::getHeight() const{
    return height;
}

int GameWorld::getWidth() const{
    return width;
}

void GameWorld::moveShip(Battleship* ship, int newX, int newY) {
    // check if the ship pointer is valid
    if (ship == nullptr) {
        throw std::invalid_argument("Invalid ship pointer");
    }

    // check if the new position is within the boundaries of the game world
    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
        // get the current position of the ship
        int oldX = ship->getXPosition();
        int oldY = ship->getYPosition();

        // update the ship's position in the grid
        grid[oldY][oldX] = nullptr;
        grid[newY][newX] = ship;

        // update the ship's position in the Battleship object
        ship->setPosition(newX, newY);
    } else {
        throw std::out_of_range("Ship position out of bounds");
    }
}

Battleship* GameWorld::getShipAtPosition(int x, int y) const {
    // check if the position is within the boundaries of the game world
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return grid[y][x];
    } else {
        throw std::out_of_range("Invalid position");
    }
}

void GameWorld::removeShip(Battleship* ship) {
    // check if the ship pointer is valid
    if (ship == nullptr) {
        throw std::invalid_argument("Invalid ship pointer");
    }

    int x = ship->getXPosition();
    int y = ship->getYPosition();

    // remove the ship from the grid by setting its position to nullptr
    grid[y][x] = nullptr;
}

void GameWorld::swapShips(Battleship* ship1, Battleship* ship2) {
    // check if the ship pointers are valid
    if (ship1 == nullptr || ship2 == nullptr) {
        throw std::invalid_argument("Invalid ship pointers");
    }

    // Get the positions of the two ships
    int ship1X = ship1->getXPosition();
    int ship1Y = ship1->getYPosition();
    int ship2X = ship2->getXPosition();
    int ship2Y = ship2->getYPosition();

    // Update the ships' positions in the grid
    grid[ship1Y][ship1X] = ship2;
    grid[ship2Y][ship2X] = ship1;

    // Update the ships' positions in the Battleship objects
    ship1->setPosition(ship2X, ship2Y);
    ship2->setPosition(ship1X, ship1Y);
}


void GameWorld::displayGameWorld() const{
    // display the state of the game world with ship positions
    for(int y = 0; y < this->getHeight(); y++){
        for(int x = 0; x < this->getWidth(); x++){
            Battleship* ship = this->getShipAtPosition(x, y);
            if(ship != nullptr){
                if(ship->getType() == "Jaeger"){
                    std::cout << "J ";
                } else if(ship->getType() == "Kreuzer"){
                    std::cout << "K ";
                } else if(ship->getType() == "Zerstoerer"){
                    std::cout << "Z ";
                } else {
                    // this should never happen
                    throw std::runtime_error("Invalid ship type");
                }
            } else {
                // the "." represents the sea
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}


