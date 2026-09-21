#include <iostream>
#include <cctype>

using namespace std;

// -------------------------------------------------------------
// CLASS 1: StackNode
// Class implementation with public members for direct access.
// -------------------------------------------------------------
class StackNode {
public:
    char command;
    int prevPosition;
    StackNode* next;

    StackNode(char cmd, int pos) : command(cmd), prevPosition(pos), next(nullptr) {}
};

// -------------------------------------------------------------
// CLASS 2: LinkedStack
// Custom LIFO Stack implemented using a Singly Linked List.
// -------------------------------------------------------------
class LinkedStack {
private:
    StackNode* topNode;

public:
    LinkedStack() : topNode(nullptr) {}

    ~LinkedStack() {
        while (!isEmpty()) {
            popDummy();
        }
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    // Pushes valid movement and pre-movement position onto stack
    void push(char cmd, int pos) {
        StackNode* newNode = new StackNode(cmd, pos);
        newNode->next = topNode;
        topNode = newNode;
    }

    // Pops top movement and retrieves saved position directly
    bool pop(int& restoredPos) {
        if (isEmpty()) return false;

        StackNode* temp = topNode;
        restoredPos = temp->prevPosition;
        topNode = topNode->next;
        delete temp;
        return true;
    }

    // Helper pop for destructor cleanup
    void popDummy() {
        if (isEmpty()) return;
        StackNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    // Displays un-popped commands in stack order (Top to Bottom)
    void displayStack() const {
        if (isEmpty()) {
            cout << "Empty";
            return;
        }

        StackNode* curr = topNode;
        while (curr != nullptr) {
            cout << curr->command;
            if (curr->next != nullptr) cout << " -> ";
            curr = curr->next;
        }
    }
};

// -------------------------------------------------------------
// CLASS 3: UndoBattleGame
// Encapsulates player state, command evaluation, and game loop.
// -------------------------------------------------------------
class UndoBattleGame {
private:
    LinkedStack moveStack;
    int currentPosition;
    int successfulMovements;
    int successfulUndos;

public:
    UndoBattleGame() 
        : currentPosition(0), successfulMovements(0), successfulUndos(0) {}

    // Evaluates a single command character against game rules
    void processCommand(char cmd) {
        cmd = toupper(cmd);

        if (cmd == 'R') {
            // Move 1 step Right
            moveStack.push('R', currentPosition);
            currentPosition += 1;
            successfulMovements++;
        } 
        else if (cmd == 'L') {
            // Move 1 step Left (Invalid if target position < 0)
            if (currentPosition - 1 < 0) {
                cout << "Invalid Movement ('L')! Position cannot fall below 0. Ignored.\n";
            } else {
                moveStack.push('L', currentPosition);
                currentPosition -= 1;
                successfulMovements++;
            }
        } 
        else if (cmd == 'J') {
            // Jump 2 steps Right
            moveStack.push('J', currentPosition);
            currentPosition += 2;
            successfulMovements++;
        } 
        else if (cmd == 'B') {
            // Undo operation: restore previous position from top of stack
            int restoredPos;
            if (moveStack.pop(restoredPos)) {
                currentPosition = restoredPos;
                successfulUndos++;
            } else {
                cout << "Undo ('B') ignored! Stack is empty.\n";
            }
        } 
        else {
            cout << "Unrecognized command '" << cmd << "' ignored.\n";
        }
    }

    // Runs main game loop for 'n' commands
    void play() {
        int n;
        cout << "Enter total number of commands: ";
        cin >> n;

        cout << "Enter " << n << " commands (R = Right, L = Left, J = Jump +2, B = Undo):\n";
        for (int i = 0; i < n; i++) {
            char cmd;
            cin >> cmd;
            processCommand(cmd);
        }

        displayResults();
    }

    // Prints final metrics and remaining stack items
    void displayResults() const {
        cout << "\n====================================================\n";
        cout << "                 GAME RESULTS                       \n";
        cout << "====================================================\n";
        cout << "Player's Final Position:          " << currentPosition << "\n";
        cout << "Total Successful Movements:       " << successfulMovements << "\n";
        cout << "Total Successful Undo Operations: " << successfulUndos << "\n";
        cout << "Remaining Stack (Top to Bottom):  ";
        moveStack.displayStack();
        cout << "\n====================================================\n";
    }
};

// -------------------------------------------------------------
// MAIN FUNCTION
// -------------------------------------------------------------
int main() {
    UndoBattleGame game;
    game.play();
    return 0;
}
