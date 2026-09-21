#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

// -------------------------------------------------------------
// CLASS 1: Combatant
// Encapsulates stats for a single hero or enemy.
// -------------------------------------------------------------
class Combatant {
private:
    string name;
    int health;
    int attackPower;

public:
    Combatant() : name(""), health(0), attackPower(0) {}
    
    Combatant(string n, int hp, int ap) : name(n), health(hp), attackPower(ap) {
        if (health < 1) health = 1;
        if (health > 70) health = 70;
        if (attackPower < 1) attackPower = 1;
        if (attackPower > 5) attackPower = 5;
    }

    string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttackPower() const { return attackPower; }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    bool isAlive() const { return health > 0; }

    void displayFullStats() const {
        cout << "  Name: " << name 
             << " | HP: " << health 
             << " | Attack Power: " << attackPower << endl;
    }
};

// -------------------------------------------------------------
// CLASS 2: DLLNode
// Represents a single node in a Doubly Linked List.
// -------------------------------------------------------------
class DLLNode {
private:
    Combatant data;
    DLLNode* prev;
    DLLNode* next;

public:
    DLLNode(Combatant c) : data(c), prev(nullptr), next(nullptr) {}

    Combatant& getData() { return data; }
    const Combatant& getData() const { return data; }

    DLLNode* getPrev() const { return prev; }
    DLLNode* getNext() const { return next; }

    void setPrev(DLLNode* p) { prev = p; }
    void setNext(DLLNode* n) { next = n; }

    friend class TeamList;
};

// -------------------------------------------------------------
// CLASS 3: TeamList
// Doubly Linked List managing a team of Combatants.
// -------------------------------------------------------------
class TeamList {
private:
    DLLNode* head;
    DLLNode* tail;
    int size;

public:
    TeamList() : head(nullptr), tail(nullptr), size(0) {}

    ~TeamList() {
        DLLNode* curr = head;
        while (curr != nullptr) {
            DLLNode* nextNode = curr->getNext();
            delete curr;
            curr = nextNode;
        }
    }

    int getSize() const { return size; }
    bool isEmpty() const { return head == nullptr; }

    void addCombatant(Combatant c) {
        DLLNode* newNode = new DLLNode(c);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        size++;
    }

    void removeNode(DLLNode* node) {
        if (node == nullptr) return;

        if (node == head) {
            head = head->getNext();
            if (head != nullptr) head->setPrev(nullptr);
            else tail = nullptr;
        } else if (node == tail) {
            tail = tail->getPrev();
            if (tail != nullptr) tail->setNext(nullptr);
            else head = nullptr;
        } else {
            node->getPrev()->setNext(node->getNext());
            node->getNext()->setPrev(node->getPrev());
        }

        delete node;
        size--;
    }

    DLLNode* findCombatant(const string& query) const {
        if (head == nullptr) return nullptr;

        bool isNumber = true;
        for (char c : query) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (isNumber) {
            int pos = stoi(query);
            if (pos < 1 || pos > size) return nullptr;
            
            DLLNode* curr = head;
            for (int i = 1; i < pos; i++) {
                curr = curr->getNext();
            }
            return curr;
        } else {
            DLLNode* curr = head;
            while (curr != nullptr) {
                if (curr->getData().getName() == query) {
                    return curr;
                }
                curr = curr->getNext();
            }
        }
        return nullptr;
    }

    DLLNode* getNodeAt(int pos) const {
        if (pos < 1 || pos > size) return nullptr;
        DLLNode* curr = head;
        for (int i = 1; i < pos; i++) {
            curr = curr->getNext();
        }
        return curr;
    }

    void displayNamesOnly() const {
        if (head == nullptr) {
            cout << "[Eliminated]";
            return;
        }
        DLLNode* curr = head;
        int pos = 1;
        while (curr != nullptr) {
            cout << pos << ". " << curr->getData().getName();
            if (curr->getNext() != nullptr) cout << " | ";
            curr = curr->getNext();
            pos++;
        }
    }

    void displayFullTeam() const {
        if (head == nullptr) {
            cout << "  None (Team Eliminated)\n";
            return;
        }
        DLLNode* curr = head;
        while (curr != nullptr) {
            curr->getData().displayFullStats();
            curr = curr->getNext();
        }
    }

    int getTotalHealth() const {
        int total = 0;
        DLLNode* curr = head;
        while (curr != nullptr) {
            total += curr->getData().getHealth();
            curr = curr->getNext();
        }
        return total;
    }
};

// -------------------------------------------------------------
// CLASS 4: BattleSimulator
// Game Controller that handles game loops, turns, and outcome rules.
// -------------------------------------------------------------
class BattleSimulator {
private:
    TeamList heroTeam;
    TeamList enemyTeam;
    int maxRounds;
    int currentRound;

    // Populates teams with initial 5 heroes and 5 enemies
    void setupTeams() {
        heroTeam.addCombatant(Combatant("Aron", 55, 4));
        heroTeam.addCombatant(Combatant("Valerie", 45, 5));
        heroTeam.addCombatant(Combatant("Cedric", 65, 3));
        heroTeam.addCombatant(Combatant("Lyra", 40, 5));
        heroTeam.addCombatant(Combatant("Gideon", 70, 2));

        enemyTeam.addCombatant(Combatant("Goblin", 35, 3));
        enemyTeam.addCombatant(Combatant("Orc", 60, 4));
        enemyTeam.addCombatant(Combatant("Skeleton", 30, 5));
        enemyTeam.addCombatant(Combatant("Troll", 70, 3));
        enemyTeam.addCombatant(Combatant("Shadow", 45, 4));
    }

    void displayRoster() const {
        cout << "Heroes:  "; heroTeam.displayNamesOnly(); cout << "\n";
        cout << "Enemies: "; enemyTeam.displayNamesOnly(); cout << "\n";
    }

    void displayRoundHeader() const {
        cout << "\n----------------------------------------------------\n";
        cout << "                    ROUND " << currentRound << "                    \n";
        cout << "----------------------------------------------------\n";
        displayRoster();
        cout << "\n";
    }

    // Handles user input, validation, damage generation, and node removal
    void executeHeroTurn() {
        DLLNode* attackerNode = nullptr;
        DLLNode* targetNode = nullptr;
        string attackerChoice, targetChoice;

        while (attackerNode == nullptr) {
            cout << "Select Attacker Hero (Name or Position): ";
            cin >> attackerChoice;
            attackerNode = heroTeam.findCombatant(attackerChoice);
            if (attackerNode == nullptr) {
                cout << "Invalid selection! Choose a valid hero.\n";
            }
        }

        while (targetNode == nullptr) {
            cout << "Select Target Enemy (Name or Position): ";
            cin >> targetChoice;
            targetNode = enemyTeam.findCombatant(targetChoice);
            if (targetNode == nullptr) {
                cout << "Invalid selection! Choose a valid enemy.\n";
            }
        }

        int randMultiplier = (rand() % 3) + 1;
        int damage = attackerNode->getData().getAttackPower() * randMultiplier;

        cout << "\n>>> " << attackerNode->getData().getName() << " attacks " 
             << targetNode->getData().getName() << " for " << damage << " damage!\n";

        targetNode->getData().takeDamage(damage);

        if (!targetNode->getData().isAlive()) {
            cout << ">>> " << targetNode->getData().getName() << " was defeated and removed from battle!\n";
            enemyTeam.removeNode(targetNode);
        }
    }

    // Handles AI counterattack turn
    void executeEnemyTurn() {
        if (enemyTeam.isEmpty()) return;

        cout << "\n--- Enemy Counterattack ---\n";
        int randomEnemyIdx = (rand() % enemyTeam.getSize()) + 1;
        int randomHeroIdx = (rand() % heroTeam.getSize()) + 1;

        DLLNode* enemyAttacker = enemyTeam.getNodeAt(randomEnemyIdx);
        DLLNode* heroTarget = heroTeam.getNodeAt(randomHeroIdx);

        int randMultiplier = (rand() % 3) + 1;
        int damage = enemyAttacker->getData().getAttackPower() * randMultiplier;

        cout << ">>> Enemy " << enemyAttacker->getData().getName() << " counterattacks " 
             << heroTarget->getData().getName() << " for " << damage << " damage!\n";

        heroTarget->getData().takeDamage(damage);

        if (!heroTarget->getData().isAlive()) {
            cout << ">>> Hero " << heroTarget->getData().getName() << " was fallen and removed from battle!\n";
            heroTeam.removeNode(heroTarget);
        }
    }

    // Evaluates victory/draw conditions at battle conclusion
    void displayGameSummary() const {
        cout << "\n====================================================\n";
        cout << "                    GAME OVER                       \n";
        cout << "====================================================\n";

        if (enemyTeam.isEmpty()) {
            cout << "VICTORY: Hero Team has completely eliminated the Enemy Team!\n\n";
            cout << "Surviving Members of Winning Team (Heroes):\n";
            heroTeam.displayFullTeam();
        } else if (heroTeam.isEmpty()) {
            cout << "DEFEAT: Enemy Team has completely eliminated the Hero Team!\n\n";
            cout << "Surviving Members of Winning Team (Enemies):\n";
            enemyTeam.displayFullTeam();
        } else {
            int totalHeroHP = heroTeam.getTotalHealth();
            int totalEnemyHP = enemyTeam.getTotalHealth();

            cout << "Battle ended after " << maxRounds << " rounds!\n";
            cout << "Total Hero Team HP: " << totalHeroHP << "\n";
            cout << "Total Enemy Team HP: " << totalEnemyHP << "\n\n";

            if (totalHeroHP > totalEnemyHP) {
                cout << "VICTORY: Hero Team wins by higher remaining Health Points!\n\n";
                cout << "Surviving Members of Winning Team (Heroes):\n";
                heroTeam.displayFullTeam();
            } else if (totalEnemyHP > totalHeroHP) {
                cout << "DEFEAT: Enemy Team wins by higher remaining Health Points!\n\n";
                cout << "Surviving Members of Winning Team (Enemies):\n";
                enemyTeam.displayFullTeam();
            } else {
                cout << "MATCH DRAW: Both teams have identical total Health Points!\n\n";
                cout << "Remaining Members of Hero Team:\n";
                heroTeam.displayFullTeam();
                cout << "\nRemaining Members of Enemy Team:\n";
                enemyTeam.displayFullTeam();
            }
        }
    }

public:
    BattleSimulator(int rounds = 10) : maxRounds(rounds), currentRound(1) {
        setupTeams();
    }

    // Main Game Loop Method
    void startBattle() {
        cout << "====================================================\n";
        cout << "       TURN-BASED BATTLE SIMULATOR (DLL)            \n";
        cout << "====================================================\n";

        while (currentRound <= maxRounds && !heroTeam.isEmpty() && !enemyTeam.isEmpty()) {
            displayRoundHeader();
            
            // Player Turn
            executeHeroTurn();
            if (enemyTeam.isEmpty()) {
                cout << "\nAll enemies have been defeated!\n";
                break;
            }

            // Enemy Turn
            executeEnemyTurn();

            // Display remaining roster
            cout << "\nRemaining Team Roster:\n";
            displayRoster();

            currentRound++;
        }

        displayGameSummary();
    }
};

// -------------------------------------------------------------
// MAIN FUNCTION (Clean & Minimal)
// -------------------------------------------------------------
int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Initialize game engine with 10 rounds max and start
    BattleSimulator game(10);
    game.startBattle();

    return 0;
}
