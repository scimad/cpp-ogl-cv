#include <iostream>

class Player
{
private:
    std::string name;
    std::string club_name;
    int age;
    float salary;
public:
    Player();
    std::string GetName() const
    {
        return name;
    }

    Player(std::string n, int age);
};

Player::Player(std::string n, int age):name(n),age(age)
{
}

std::ostream& operator<<(std::ostream& stream, const Player& p)
{
    stream << p.GetName();
    return stream;

}

int main(int argc, char const *argv[])
{
    std::cout << Player("Messi",34) << std::endl;
}
