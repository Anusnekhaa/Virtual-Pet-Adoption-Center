#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class Pet {
protected:
    string name;
    int age;
    string type;
    int health;
    int happiness;

public:
 static int totalPetsAdopted;

    Pet(string n, int a, string t) {
        name = n;
        age = a;
        type = t;
        health = 100;
        happiness = 100;
    }
    Pet(const Pet& other) {
        name = other.name;
        age = other.age;
        type = other.type;
        health = other.health;

        happiness = other.happiness;
    }

    virtual ~Pet() {
        cout << name << " is being destroyed." << endl;
    }

    virtual void feed() {
        health = 100;
        happiness = 100;
        cout << name << " has been fed. Health restored to " << health << "." << endl;
    }

    string getName() const { return name; }
    int getHealth() const { return health; }
    int getHappiness() const { return happiness; }

    void increaseHappiness(int amount) {
        happiness += amount;
        if (happiness > 100) {
            happiness = 100;
        }
    }

    virtual void decreaseHealth(int amount) {
        health -= amount;
        happiness -= amount;
        if (health < 0) {
            health = 0;
        }
        if (happiness < 0) {

            happiness = 0;
        }
    }

    virtual void display() const {
        cout << "Pet Name: " << name << ", Age: " << age << ", Type: " << type
             << ", Health: " << health << ", Happiness: " << happiness << endl;
    }

    bool isAlive() const {
        return health > 0;
    }

    friend void showPetDetails(const Pet& pet);

};

int Pet::totalPetsAdopted = 0;

class MythicalPet : public Pet {
private:
    string mythicalType;

public:
    MythicalPet(string n, int a, string t, string mType) : Pet(n, a, t), mythicalType(mType) {}

    void feed() override {
        health = 120;
        happiness = 120;
        cout << name << " (Mythical) has been fed. Health restored to " << health << "." << endl;
    }

    void display() const override {
        cout << "Mythical Pet Name: " << name << ", Age: " << age << ", Type: " << type
             << ", Mythical Type: " << mythicalType << ", Health: " << health
             << ", Happiness: " << happiness << endl;
    }

    void decreaseHealth(int amount) override {
        health -= (amount / 2);
        happiness -= amount;
        if (health < 0) {
            health = 0;
        }
        if (happiness < 0) {
            happiness = 0;
        }
    }
};

void showPetDetails(const Pet& pet) {
    cout << "Friend Function - Pet Details: " << pet.name << ", " << pet.age << ", " << pet.type << endl;
}

void playWithPet(Pet* pet) {
    pet->increaseHappiness(10);
    pet->decreaseHealth(5);
    cout << pet->getName() << " played and is now happier, but a little tired!" << endl;
}

class PetAdoption {
private:
    vector<Pet*> adoptedPets;

    vector<string> deadPets;

public:
    void adoptPet(Pet* pet) {
        if (adoptedPets.size() >= 4) {
            cout << "Cannot adopt " << pet->getName() << ". You can only have a maximum of 4 pets. Please un-adopt one." << endl;
            delete pet;
            return;
        }

        for (auto& adoptedPet : adoptedPets) {
            char feedChoice;
            cout << "Do you want to feed " << adoptedPet->getName() << "? (y/n): ";
            cin >> feedChoice;

            if (feedChoice == 'y' || feedChoice == 'Y') {
                adoptedPet->feed();
            } else {
                adoptedPet->decreaseHealth(25);
                cout << adoptedPet->getName() << " has not been fed and its health decreased by 25." << endl;
            }

            if (adoptedPet->getHealth() < 25) {
                cout << "Warning: " << adoptedPet->getName() << "'s health is critically low!" << endl;
            }
        }

        adoptedPets.push_back(pet);
        Pet::totalPetsAdopted++;

        cout << pet->getName() << " has been adopted!" << endl;
    }

    void unadoptPet(string name) {
        for (auto it = adoptedPets.begin(); it != adoptedPets.end(); ++it) {
            if ((*it)->getName() == name) {
                cout << name << " has been unadopted!" << endl;
                deadPets.push_back(name);
                delete *it;
                adoptedPets.erase(it);
                Pet::totalPetsAdopted--;
                return;
            }
        }

        throw invalid_argument("Error: Pet not found with the given name!");
    }


    void displayAdoptedPets() const {
        if (adoptedPets.empty()) {
            cout << "No pets adopted yet!" << endl;
            return;
        }
        cout << "Adopted Pets:" << endl;
        for (const auto& pet : adoptedPets) {
            pet->display();
        }
        cout << "Total Pets Adopted: " << Pet::totalPetsAdopted << endl;
    }

    void increaseHealthOfAdoptedPets() {
        for (auto& pet : adoptedPets) {

            pet->feed();
        }
    }

    void checkForDeadPets() {
        for (auto it = adoptedPets.begin(); it != adoptedPets.end();) {
            if (!(*it)->isAlive()) {
                cout << (*it)->getName() << " has died." << endl;
                deadPets.push_back((*it)->getName());
                delete *it;
                it = adoptedPets.erase(it);
            } else {
                ++it;
            }
        }
    }

    void displayDeadPets() const {
        if (deadPets.empty()) {
            cout << "No pets dead or unadopted. You are doing a good job" << endl;
        } else {
            cout << "Previously dead and un-adopted pets:" << endl;
            for (const auto& deadPet : deadPets) {
                cout << deadPet << endl;
            }
        }
    }

    void playWithSpecificPet(const string& name) {
        for (auto& pet : adoptedPets) {
            if (pet->getName() == name) {

                playWithPet(pet);
                return;
            }
        }
        throw invalid_argument("Error: Pet not found with the given name!");
    }

    void saveAdoptedPetsToFile(const string& filename) const {
        ofstream outFile(filename, ios::out);
        if (!outFile) {
            cerr << "Error: Could not open file for saving!" << endl;
            return;
        }
        outFile << "Adopted Pets:\n";
        for (const auto& pet : adoptedPets) {
            outFile << "Name: " << pet->getName()
                    << ", Health: " << pet->getHealth()
                    << ", Happiness: " << pet->getHappiness()
                    << "\n";
        }
        outFile.close();
        cout << "Adopted pet details saved to " << filename << "." << endl;
    }

    // Save dead pets to a file
    void saveDeadPetsToFile(const string& filename) const {
        ofstream outFile(filename, ios::out);
        if (!outFile) {
            cerr << "Error: Could not open file for saving!" << endl;
            return;
        }
        outFile << "Previously Dead and Unadopted Pets:\n";
        for (const auto& deadPet : deadPets) {
            outFile << "Name: " << deadPet << "\n";
        }
        outFile.close();
        cout << "Dead pet details saved to " << filename << "." << endl;
    }
};

int main() {
    PetAdoption adoptionSystem;

    int choice;
    do {
        cout << "\nVirtual Pet Adoption System\n";
        cout << "1. Adopt Pet\n";
        cout << "2. Display Adopted Pets\n";
        cout << "3. Unadopt Pet\n";
        cout << "4. Increase Health of Adopted Pets\n";
        cout << "5. Display Previously Dead and Un-adopted Pets\n";
        cout << "6. Play with a Pet\n";
        cout << "7. Save Pet Details to File\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, type, mythicalType;
                int age;
                cout << "Enter the name of the pet: ";
                cin >> name;
                cout << "Enter the age of the pet: ";
                cin >> age;
                cout << "Enter the type of pet (Dog/Cat/Fish/Bird/Mythical): ";
                cin >> type;

                Pet* pet;
                if (type == "Dog" || type == "Cat" || type == "Fish" || type == "Bird") {
                    pet = new Pet(name, age, type);
                } else if (type == "Mythical") {
                    cout << "Enter the type of mythical pet: ";
                    cin >> mythicalType;
                    pet = new MythicalPet(name, age, type, mythicalType);
                } else {
                    cout << "Invalid pet type!" << endl;
                    continue;
                }

                adoptionSystem.adoptPet(pet);
                adoptionSystem.checkForDeadPets();
                break;
            }
            case 2:
                adoptionSystem.displayAdoptedPets();
                break;
            case 3: {
                string name;
                try {
                    cout << "Enter the name of the pet to unadopt: ";
                    cin >> name;
                    adoptionSystem.unadoptPet(name);
                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 4:
                adoptionSystem.increaseHealthOfAdoptedPets();
                cout << "Health increased for all adopted pets." << endl;
                break;
            case 5:
                adoptionSystem.displayDeadPets();
                break;
            case 6: {
                string name;
                try {
                    cout << "Enter the name of the pet you want to play with: ";
                    cin >> name;
                    adoptionSystem.playWithSpecificPet(name);
                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 7:
                adoptionSystem.saveAdoptedPetsToFile("adopted_pets.txt");
                adoptionSystem.saveDeadPetsToFile("dead_pets.txt");
                break;
            case 8:
                cout << "Thank you for entering the Virtual Pet Adoption Center! Saving pet details and exiting...\n";
                adoptionSystem.saveAdoptedPetsToFile("adopted_pets.txt");
                adoptionSystem.saveDeadPetsToFile("dead_pets.txt");
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
