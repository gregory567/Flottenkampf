#ifndef GAMEWORLD_HPP_INCLUDED
#define GAMEWORLD_HPP_INCLUDED

class GameWorld {
    private:
        int height;
        int width;
        // grid of battleship pointers to store the positions of the ships
        std::vector<std::vector<Battleship*>> grid;

    public:
        GameWorld(int worldWidth, int worldHeight, Fleet& fleet1, Fleet& fleet2);
        ~GameWorld();
        int getHeight() const;
        int getWidth() const;
        void moveShip(Battleship* ship, int newX, int newY);
        Battleship* getShipAtPosition(int x, int y) const;
        void removeShip(Battleship* ship);
        void swapShips(Battleship* ship1, Battleship* ship2);
        void displayGameWorld() const;
};


#endif // GAMEWORLD_HPP_INCLUDED
