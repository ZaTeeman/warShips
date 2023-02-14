
#include <iostream>
#include <string>
#include <random>


#define MIN_SHIP_AMOUNT 2
#define MAX_SHIP_AMOUNT 5 

#define MIN_SHIP_NAME 500
#define MAX_SHIP_NAME 800

#define MIN_WEAPONS_AMOUNT 4
#define MAX_WEAPONS_AMOUNT 15


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
    return "Bs";
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
    return "Cb";  
  }
};


// корабли
class Warship
{
protected:
    string shipType;        // Fregat, cruiser, linkor
    int name;               // The name of the ship is given by the number
    int countOfWeapons;     // Count of weapons
public:
  virtual void shoot(Weapon & weap1, Weapon & weap2, string ammoType)
  {
        if (ammoType == weap1.getType())
            cout << "Ship type " << shipType<< ", name(number): " << name << " make " << weap1.shoot() << "by " << countOfWeapons << " weapon(s)" << endl;
  }
  virtual void getInfo()
  {
      cout << "name(number): " << this->name << " with " << this->countOfWeapons;
  }
};

class Cruiser : public Warship
{
public:
    Cruiser()
    {
        this->shipType = "cruiser";
        this->name = getRandom(MIN_SHIP_NAME, MAX_SHIP_NAME);
        this->countOfWeapons = getRandom(MIN_WEAPONS_AMOUNT, MAX_WEAPONS_AMOUNT); // Buckshot
    }
};

class Fregate: public Warship  
{
public:
    Fregate() 
    {
        this->shipType = "fregat";
        this->name = getRandom(MIN_SHIP_NAME, MAX_SHIP_NAME);
        this->countOfWeapons = getRandom(MIN_WEAPONS_AMOUNT, MAX_WEAPONS_AMOUNT);//Cannonball
    }
};

class Linkor : public Warship
{
private:
    int countOfSecondWeapons;
public:
    Linkor()
    {
        this->shipType = "linkor";
        this->name = getRandom(MIN_SHIP_NAME, MAX_SHIP_NAME);
        this->countOfWeapons = getRandom(MIN_WEAPONS_AMOUNT, MAX_WEAPONS_AMOUNT);//Cannonball
        this->countOfSecondWeapons = getRandom(MIN_WEAPONS_AMOUNT, MAX_WEAPONS_AMOUNT);  // Buckshot
    }
    void shoot(Weapon & weap1, Weapon & weap2, string ammoType) override
    {
        if (ammoType == weap1.getType())
            cout << "Ship type " << shipType<< ", name(number) " << name << " make " << weap1.shoot() << "by " << countOfWeapons << " weapon(s)" << endl;
        else if (ammoType == weap2.getType())
            cout << "Ship type " << shipType<< ", name(number) " << name << " make " << weap2.shoot() << "by " << countOfSecondWeapons << " weapon(s)" << endl;
        else
            cout << "Ship type " << shipType<< ", name(number) " << name << " make " << weap1.shoot() << "by " << countOfWeapons << " and make " << weap2.shoot() << "by " << countOfSecondWeapons << " weapon(s)" << endl;    
    }    
    void getInfo() override
    {
        cout << "name(number): " << this->name << " with " << this->countOfWeapons << " 1st weapons and " << this->countOfSecondWeapons << " 2nd weapons" ;
    }
};

// Cruiser buildCruiser(){
//   return Cruiser();
// }

void shipBuilder()
{
    //build cruisers:
    Cruiser shipsCruiser[getRandom(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT)];
    
    cout << "was builded " << sizeof(shipsCruiser)/sizeof(Cruiser) << " cruisers:" << endl;
    for (int i = 0; i < sizeof(shipsCruiser)/sizeof(Cruiser); i++)
    {
        cout << i+1 << ") "; 
        shipsCruiser[i].getInfo();
        cout << " cannons (buckshots)." << endl;
    }
    
    //build fregats:
    Fregate shipsFregate[getRandom(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT)];
    
    cout << endl << "was builded " << sizeof(shipsFregate)/sizeof(Fregate) << " fregats:" << endl;
    for (int i = 0; i < sizeof(shipsFregate)/sizeof(Fregate); i++)
    {
        cout << i+1 << ") "; 
        shipsFregate[i].getInfo();
        cout << " cannons (cannonballs)." << endl;
    }

    //build linkors:
    Linkor shipsLinkor[getRandom(MIN_SHIP_AMOUNT, MAX_SHIP_AMOUNT)];
    
    cout << endl << "was builded " << sizeof(shipsLinkor)/sizeof(Linkor) << " linkors:" << endl;
    for (int i = 0; i < sizeof(shipsLinkor)/sizeof(Linkor); i++)
    {
        cout << i+1 << ") "; 
        shipsLinkor[i].getInfo();
        cout << endl;
    }
}


int main ()
{
    srand(time(NULL));
    
    // cout << getRandom(500, 900) << endl;
    
    
    shipBuilder();
    // Buckshot buckshots;
    // Cannonball cannonballs;
    
    
    // Cruiser s1("lol", 6);
    // s1.shoot(buckshots, buckshots, "Bs");

    
  return 0;
}
