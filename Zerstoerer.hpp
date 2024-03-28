#ifndef ZERSTOERER_HPP_INCLUDED
#define ZERSTOERER_HPP_INCLUDED


class Zerstoerer : public Battleship {
    private:

    protected:

    public:
        Zerstoerer();
        virtual ~Zerstoerer();
        void specialAttack(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) override;
        std::string getType() const override;
        void abilityOne(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) override;
        void abilityTwo(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) override;
};

#endif // ZERSTOERER_HPP_INCLUDED
