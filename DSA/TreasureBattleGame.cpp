#include <iostream>
using namespace std;

// Class 1: Player Entity & Personal Action Stack
class Player {
private:
    int id;
    int energy;
    char historyStack[100];
    int top;

public:
    Player() {
        id = -1;
        energy = 100;
        top = -1;
    }

    Player(int pId) {
        id = pId;
        energy = 100;
        top = -1;
    }

    int getId() const { 
        return id; 
    }

    int getEnergy() const { 
        return energy; 
    }

    void modifyEnergy(int delta) { 
        energy += delta; 
    }

    void pushHistory(char action) {
        if (top < 99) {
            top++;
            historyStack[top] = action;
        }
    }

    bool popHistory(char &action) {
        if (top >= 0) {
            action = historyStack[top];
            top--;
            return true;
        }
        return false;
    }

    int getUndoableCount() const {
        return top + 1;
    }
};

// Class 2: Queue for Waiting Players
class PlayerQueue {
private:
    Player arr[100];
    int frontIndex;
    int rearIndex;
    int count;

public:
    PlayerQueue() {
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count >= 100;
    }

    void enqueue(Player p) {
        if (isFull()) return;
        rearIndex = (rearIndex + 1) % 100;
        arr[rearIndex] = p;
        count++;
    }

    Player dequeue() {
        Player p = arr[frontIndex];
        frontIndex = (frontIndex + 1) % 100;
        count--;
        return p;
    }

    int size() const {
        return count;
    }
};

// Class 3: Game Controller (Encapsulates Game Logic & Execution)
class TreasureBattleGame {
private:
    PlayerQueue waitingQueue;
    int eliminatedIDs[100];
    int eliminatedCount;

public:
    TreasureBattleGame() {
        eliminatedCount = 0;
    }

    void addPlayer(int id) {
        waitingQueue.enqueue(Player(id));
    }

    bool hasActivePlayers() const {
        return !waitingQueue.isEmpty();
    }

    // Process a single turn for the player at the front of the queue
    void processTurn(char cmd) {
        if (waitingQueue.isEmpty()) return;

        Player currentPlayer = waitingQueue.dequeue();

        if (cmd == 'F' || cmd == 'f') {
            currentPlayer.modifyEnergy(-10);
            currentPlayer.pushHistory('F');
        } 
        else if (cmd == 'B' || cmd == 'b') {
            currentPlayer.pushHistory('B');
        } 
        else if (cmd == 'T' || cmd == 't') {
            currentPlayer.modifyEnergy(20);
            currentPlayer.pushHistory('T');
        } 
        else if (cmd == 'U' || cmd == 'u') {
            char lastAction;
            if (currentPlayer.popHistory(lastAction)) {
                if (lastAction == 'F') {
                    currentPlayer.modifyEnergy(10);
                } else if (lastAction == 'T') {
                    currentPlayer.modifyEnergy(-20);
                }
            }
        }

        // Check survival
        if (currentPlayer.getEnergy() <= 0) {
            eliminatedIDs[eliminatedCount++] = currentPlayer.getId();
        } else {
            waitingQueue.enqueue(currentPlayer);
        }
    }

    // Display final statistics and remaining players
    void displaySummary() {
        cout << "\n==========================================\n";
        cout << "         TREASURE BATTLE RESULTS          \n";
        cout << "==========================================\n";

        // 1. Elimination Order
        cout << "Elimination Order: ";
        if (eliminatedCount == 0) {
            cout << "None (No players were eliminated)";
        } else {
            for (int i = 0; i < eliminatedCount; i++) {
                cout << "Player " << eliminatedIDs[i] << (i == eliminatedCount - 1 ? "" : " -> ");
            }
        }
        cout << "\n\n";

        // 2. Active Players Status
        cout << "Active Players in Waiting Line:\n";
        if (waitingQueue.isEmpty()) {
            cout << "  No active players remaining.\n";
        } else {
            int activeSize = waitingQueue.size();
            for (int i = 0; i < activeSize; i++) {
                Player p = waitingQueue.dequeue();
                cout << "  - Player ID: " << p.getId() 
                     << " | Remaining Energy: " << p.getEnergy() 
                     << " | Undoable Actions: " << p.getUndoableCount() << "\n";
            }
        }
        cout << "==========================================\n";
    }
};

// Main Driver Function
int main() {
    TreasureBattleGame game;

    int numPlayers;
    cout << "Enter total number of players: ";
    cin >> numPlayers;

    cout << "Enter Player IDs in arrival order: ";
    for (int i = 0; i < numPlayers; i++) {
        int id;
        cin >> id;
        game.addPlayer(id);
    }

    int numCommands;
    cout << "Enter total number of commands to execute: ";
    cin >> numCommands;

    cout << "Enter " << numCommands << " commands (F, B, T, U) separated by space:\n";
    for (int i = 0; i < numCommands; i++) {
        if (!game.hasActivePlayers()) {
            cout << "\nAll players have been eliminated before processing all commands!\n";
            break;
        }
        char cmd;
        cin >> cmd;
        game.processTurn(cmd);
    }

    game.displaySummary();

    return 0;
}
