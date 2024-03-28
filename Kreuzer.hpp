#ifndef KREUZER_HPP_INCLUDED
#define KREUZER_HPP_INCLUDED


class Kreuzer : public Battleship {
    private:

    protected:

    public:
        Kreuzer();
        virtual ~Kreuzer();
        void specialAttack(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) override;
        std::string getType() const override;
        void abilityOne(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) override;
        void abilityTwo(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) override;
};

#endif // KREUZER_HPP_INCLUDED
