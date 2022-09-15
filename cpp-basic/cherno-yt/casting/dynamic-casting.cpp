#include <array>
#include <iostream>

class Entity
{
public:
    std::string original;
    Entity(/* args */){
        original = "Entity";
    };
    ~Entity(){};
    void show_origin(){
        std::cout << "I was " << original << " originally."<< std::endl;
    };
    void display(){
        show_origin();
        std::cout << "I am Entity.\n" << std::endl;
    };
};

class Player:public Entity
{
public:
    Player(/* args */){
        original = "Player";
    };
    ~Player(){};
    void display(){
        Entity::show_origin();
        std::cout << "I am Player.\n" << std::endl;
    };

    void run(){
        std::cout << "The player is running." << std::endl;
    }
};

class Enemy:public Entity
{
public:
    Enemy(/* args */){
        original = "Enemy";
    };
    ~Enemy(){};
    void display(){
        Entity::show_origin();
        std::cout << "I am Enemy.\n" << std::endl;
    };
};

int main()
{
    Entity* en = new Player();
    en->display();
    // en->run();                   //obviously, we can't do this and we need to cast it to Player* to do that

    auto p1 = static_cast<Player*>(en);
    p1->display();
    p1->run();

    Player* pl = new Player();
    pl->display();
    pl->run();

    Entity* en2 = dynamic_cast<Entity*> (pl);
    en2->display();

}
