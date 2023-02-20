
#include <iostream>
#include <string>
#include <random>


#define MIN_SHIP_AMOUNT 2  // минимальное количество кораблей каждого типа
#define MAX_SHIP_AMOUNT 5  // максимальное количество кораблей каждого типа

#define MIN_SHIP_NAME 500  // минимальное значение имени корабля
#define MAX_SHIP_NAME 800  // максимальное значение имени корабля

#define MIN_WEAPONS_AMOUNT 3    //минимальное количество вооружений каждого типа
#define MAX_WEAPONS_AMOUNT 10   //максимальное количество вооружений каждого типа


using namespace std;

int getRandom (int minVal, int maxVal)
{    
    static int callCounter = 0;
    callCounter ++;
    int i = minVal + (rand() / callCounter) % (maxVal - minVal + 1);
    srand(i);
    return i;
}

// Вооружение
class Weapon
{
public:
  virtual string shoot () = 0;
  virtual string getType () = 0;
};

class Buckshot : public Weapon // картечь
{
public:
  string shoot () override
  {
    return "buckshot shot ";
  }
  string getType () override
  {
    return "buckshots";
  }
};

class Cannonball : public Weapon // ядра
{
public:
  string shoot () override
  {
    return "cannonball shot ";
  }
  string getType () override
  {
    return "cannonballs";  
  }
};

// корабли
class Warship
{
protected:
    Cannonball cannonball;
    Buckshot buckshot;
    string shipType;        // Fregat, cruiser, linkor
    int name;               // именем корабля будет номер
    int countOfCannonball;
    int countOfBuckshot;
public:
    virtual void shoot(string ammoType)
    {        
        if (ammoType == this->cannonball.getType() && countOfCannonball != 0)
            cout << "Ship type: " << shipType<< ", name(number): " << name << " make " << this->cannonball.shoot() << "by " << this->countOfCannonball << " " << this->cannonball.getType() << endl;
        if (ammoType == this->buckshot.getType() && countOfBuckshot != 0)
            cout << "Ship type: " << shipType<< ", name(number): " << name << " make " << this->buckshot.shoot() << "by " << this->countOfBuckshot << " " << this->buckshot.getType() << endl;
    }
    virtual void shootAll()
    {
        if (countOfCannonball != 0)
            cout <<" make " << this->cannonball.shoot() <<" by " << this->countOfCannonball << " " << this->cannonball.getType() << endl;
        else if (countOfBuckshot != 0)
            cout <<" make " << this->buckshot.shoot() << " by " << this->countOfBuckshot << " " << this->buckshot.getType() <<endl;
    }
        
    virtual void getInfo()
    {
        cout << this->shipType << " name(number): " << this->name << " with " << this->countOfCannonball+this->countOfBuckshot << " weapons ";
    }  
};

class Cruiser : public Warship
{
public:
    Cruiser(){}
    Cruiser(Buckshot buckshot)
    {
        this->buckshot = buckshot;
        this->shipType = "cruiser";
        this->name = getRandom(MIN_SHIP_NAME, MAX_SHIP_NAME);
        this->countOfCannonball = 0;
        this->countOfBuckshot = getRandom(MIN_WEAPONS_AMOUNT, MAX_WEAPONS_AMOUNT);  // Buckshot
    }
};

class Fregate: public Warship  
{

  
public:
    Fregate(){}
    Fregate(Cannonball cannonball) 
    {
        this->cannonball = cannonball;
        this->shipType = "fregat";
        this->name = getRandom(MIN_SHIP_NAME, MAX_SHIP_NAME);
        this->countOfCannonball = getRandom(MIN_WEAPONS_AMOUNT, MAX_WEAPONS_AMOUNT);//Cannonball
        this->countOfBuckshot = 0;
    }
};

class Linkor : public Warship
{
  
public:
    Linkor(){}
    Linkor(Buckshot buckshot, Cannonball cannonball)
    {
        this->buckshot = buckshot;
        this->cannonball = cannonball;
        this->shipType = "linkor";
        this->name = getRandom(MIN_SHIP_NAME, MAX_SHIP_NAME);
        this->countOfCannonball = getRandom(MIN_WEAPONS_AMOUNT, MAX_WEAPONS_AMOUNT);//Cannonball
        this->countOfBuckshot = getRandom(MIN_WEAPONS_AMOUNT, MAX_WEAPONS_AMOUNT);  // Buckshot
    }
    void shoot(string ammoType) override
    {
        if (ammoType == cannonball.getType())
            cout << "Ship type: " << this->shipType<< ", name(number): " << this->name << " make " << this->cannonball.shoot() << "by " << this->countOfCannonball << " " << this->cannonball.getType() << endl;
        else if (ammoType == buckshot.getType())
            cout << "Ship type: " << this->shipType<< ", name(number): " << this->name << " make " << this->buckshot.shoot() << "by " << this->countOfBuckshot << " " << this->buckshot.getType() << endl;
        else
            cout << "Ship type: " << this->shipType<< ", name(number): " << this->name << " make " << this->cannonball.shoot() << "by " << this->countOfCannonball << " and make " << this->buckshot.shoot() << "by " << this->countOfBuckshot << " weapon(s)" << endl;    
    }
    void shootAll() override
    {
        cout <<" make " << cannonball.shoot() <<" by " << countOfCannonball << " " << this->cannonball.getType() <<" and " << this->buckshot.shoot() << " by " << countOfBuckshot << " " << this->buckshot.getType() <<endl;
    }
};


int main ()
{
    srand(time(NULL));
    
    // создаём вооружение
    Cannonball cannonballs; 
    Buckshot buckshots;
    
    // строим флотилию
    int shipsCruiserAmount = getRandom(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT);
    Cruiser shipsCruiser[shipsCruiserAmount];
    for (int i = 0; i < shipsCruiserAmount; i++)
        shipsCruiser[i] = Cruiser(buckshots);

    int shipsFregateAmount = getRandom(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT);
    Fregate shipsFregate[shipsFregateAmount];
    for (int i = 0; i < shipsFregateAmount; i++)
        shipsFregate[i] = Fregate(cannonballs);
    
    int shipsLinkorAmount = getRandom(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT);
    Linkor shipsLinkor[shipsLinkorAmount];
     for (int i = 0; i < shipsLinkorAmount; i++)
        shipsLinkor[i] = Linkor(buckshots, cannonballs);
    
    // выводим информацию о флотилии и доступные команды
    cout << "was builded " << shipsCruiserAmount << " cruisers:" << endl;
    cout << "was builded " << shipsFregateAmount << " fregats:" << endl;
    cout << "was builded " << shipsLinkorAmount << " linkors:" << endl << endl;
    
    cout << "Available commands:" << "\n";
    cout << "fireAll" << "\n";
    cout << "fireCruisers, fireFregates, fireLinkors" << "\n";
    cout << "fireCannonballs, fireBuckshots" << "\n";
    cout << "- - - - -" << "\n";
    
    
    // запускаем контроллер
    while (1)
    {
        cout << "\n" << "print command:" << "\n";
        string command;
        cin >> command;
        cout<< "> > > > >" << "\n";
        
        if (command == "fireAll")
        {
            for (int i = 0; i < shipsCruiserAmount; i++)
            {
                shipsCruiser[i].getInfo(); 
                shipsCruiser[i].shootAll();
            }
            
            for (int i = 0; i < shipsFregateAmount; i++)
            {
                shipsFregate[i].getInfo();
                shipsFregate[i].shootAll();
            }
            
            for (int i = 0;i < shipsLinkorAmount; i++)
            {
                shipsLinkor[i].getInfo();
                shipsLinkor[i].shootAll();
            }
        }
        
        else if (command == "fireCannonballs" || command == "fireBuckshots")
        {
            string weaponType = "buckshots";
            if (command == "fireCannonballs")
                weaponType = "cannonballs";
            for (int i = 0; i < shipsCruiserAmount; i++)
                shipsCruiser[i].shoot(weaponType);
            
            for (int i = 0; i < shipsFregateAmount; i++)
                shipsFregate[i].shoot(weaponType);
            
            for (int i = 0;i < shipsLinkorAmount; i++)
                shipsLinkor[i].shoot(weaponType);
            
        }
        else if (command == "fireCruisers")
            for (int i = 0; i < shipsCruiserAmount; i++)
                {
                    shipsCruiser[i].getInfo(); 
                    shipsCruiser[i].shootAll();
                }
            
        else if (command == "fireFregates")
            for (int i = 0; i < shipsFregateAmount; i++)
                {
                    shipsFregate[i].getInfo();
                    shipsFregate[i].shootAll();
                }
        else if (command == "fireLinkors")
            for (int i = 0;i < shipsLinkorAmount; i++)
                {
                    shipsLinkor[i].getInfo();
                    shipsLinkor[i].shootAll();
                }
            
        else
            cout << "invalid command" << endl;
        
    }
    
  return 0;
}

