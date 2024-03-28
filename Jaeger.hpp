#ifndef JAEGER_HPP_INCLUDED
#define JAEGER_HPP_INCLUDED


class Jaeger : public Battleship {
    private:

    protected:

    public:
        Jaeger();
        virtual ~Jaeger();
        void specialAttack(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) override;
        std::string getType() const override;
        void abilityOne(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) override;
        void abilityTwo(Fleet& friendlyFleet, Fleet& enemyFleet, Battleship* targetShip, GameWorld& gameWorld) override;
};

#endif // JAEGER_HPP_INCLUDED
