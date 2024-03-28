

GameController::GameController(){
    round_counter = 1;
}

GameController::~GameController(){
    // destruction
}

int GameController::getRoundCounter() const{
    return round_counter;
}

void GameController::incrementRoundCounter(){
    round_counter++;
}

void GameController::buildFleet(Fleet& fleet, const std::string& fleetName){
    std::cout << "\nBuilding " << fleetName << ":" << std::endl;
    int numShips = 0;
    std::cout << "Enter the number of ships for " << fleetName << " (1-9): ";
    std::cin >> numShips;

    for (int i = 0; i < numShips; ++i) {
        std::cout << "Ship " << i + 1 << " for " << fleetName << ":" << std::endl;
        std::cout << "Choose ship type (J for Jaeger, K for Kreuzer, Z for Zerstoerer): ";
        char shipType;
        std::cin >> shipType;

        Battleship* newShip = nullptr;

        switch (shipType) {
            case 'J':
                newShip = new Jaeger();
                break;
            case 'K':
                newShip = new Kreuzer();
                break;
            case 'Z':
                newShip = new Zerstoerer();
                break;
            default:
                throw std::invalid_argument("Invalid ship type. Ship not added to " + fleetName + ".");
        }
        fleet.addShip(newShip);
    }
}


void GameController::fleetAttacksFleet(Fleet& attackingFleet, Fleet& targetFleet, GameWorld& gameWorld, const std::string& attackingFleetName, const std::string& targetFleetName) {
    // Fleet attacks
    std::cout << "\n" << attackingFleetName << " attacks " << targetFleetName << std::endl;

    // Display the updated state of the game world
    gameWorld.displayGameWorld();

    // Display attacking fleet information
    std::cout << std::endl;
    std::cout << attackingFleetName << " currently has the following ships: " << std::endl;
    attackingFleet.displayFleetInformation();

    // Choose an attacking ship
    std::cout << "Choose the number of the ship to attack with between 1 and " << attackingFleet.getFleetLength() << ":";
    int attackingShipIndex;
    std::cin >> attackingShipIndex;
    attackingFleet.setAttackingShipIndex(attackingShipIndex - 1);
    Battleship* attackingShip = attackingFleet.getAttackingShip();

    // Display target fleet information
    std::cout << std::endl;
    std::cout << targetFleetName << " currently has the following ships: " << std::endl;
    targetFleet.displayFleetInformation();

    // Choose a target ship
    std::cout << "Choose the number of the ship to attack in " << targetFleetName << " between 1 and " << targetFleet.getFleetLength() << ":";
    int targetShipIndex;
    std::cin >> targetShipIndex;
    targetFleet.setTargetShipIndex(targetShipIndex - 1);
    Battleship* targetShip = targetFleet.getTargetShip();

    // Get the attacking ship's position
    int attackingX = attackingShip->getXPosition();
    int attackingY = attackingShip->getYPosition();

    // Move the attacking ship to a new position
    int newX;
    int LeftOrRight = std::rand() % 2 + 1;
    int XDistance = std::rand() % 3 + 1;
    if (LeftOrRight == 1) {
        // Move left
        newX = attackingX - XDistance;
    } else {
        // Move right
        newX = attackingX + XDistance;
    }

    int newY;
    int UpOrDown = std::rand() % 2 + 1;
    int YDistance = std::rand() % 3 + 1;
    if (UpOrDown == 1) {
        // Move down
        newY = attackingY - YDistance;
    } else {
        // Move up
        newY = attackingY + YDistance;
    }

    // Move the attacking ship to the new position in the game world
    gameWorld.moveShip(attackingShip, newX, newY);

    // Perform attack
    attackingShip->specialAttack(attackingFleet, targetFleet, targetShip, gameWorld);
}
