#include <iostream>
#include <string>

using namespace std;

// -------------------------------------------------------------
// CLASS 1: Song
// Holds metadata for a single track.
// -------------------------------------------------------------
class Song {
private:
    string title;
    string genre;      // pop, rock, jazz, classical, electronic
    int duration;      // in seconds
    bool explicitContent;

public:
    Song() : title(""), genre(""), duration(0), explicitContent(false) {}

    Song(string t, string g, int d, bool exp)
        : title(t), genre(g), duration(d), explicitContent(exp) {}

    // Getters and Setters
    string getTitle() const { return title; }
    string getGenre() const { return genre; }
    int getDuration() const { return duration; }
    bool isExplicit() const { return explicitContent; }

    void setExplicit(bool exp) { explicitContent = exp; }

    void display() const {
        cout << "Title: " << title 
             << " | Genre: " << genre 
             << " | Duration: " << duration << "s"
             << " | Explicit: " << (explicitContent ? "Yes" : "No") << endl;
    }
};

// -------------------------------------------------------------
// CLASS 2: Node
// Represents a single node in the Singly Linked List.
// -------------------------------------------------------------
class Node {
private:
    Song song;
    Node* next;

public:
    Node(Song s) : song(s), next(nullptr) {}

    // Non-const getter (used when editing song data directly)
    Song& getSong() { return song; }

    // Const getter (read-only access for const functions)
    const Song& getSong() const { return song; }

    Node* getNext() const { return next; }
    void setNext(Node* n) { next = n; }

    // Grants Playlist direct access to private members
    friend class Playlist;
};

// -------------------------------------------------------------
// CLASS 3: Playlist
// Manages the Singly Linked List and handles constraints.
// -------------------------------------------------------------
class Playlist {
private:
    Node* head;
    int opCount;

    // Helper: Counts total songs in the linked list
    int getLength() const {
        int len = 0;
        Node* temp = head;
        while (temp != nullptr) {
            len++;
            temp = temp->getNext();
        }
        return len;
    }

    // Helper: Validates if inserting 'newSong' at 'pos' maintains constraints
    bool isValidPosition(const Song& newSong, int pos) const {
        int total = getLength();
        if (pos < 1 || pos > total + 1) return false;

        // Traverse to find adjacent nodes around the target insertion index:
        // p2 (pos-2), p1 (pos-1) ---> [NEW SONG at pos] ---> n1 (pos), n2 (pos+1)
        Node* p2 = nullptr;
        Node* p1 = nullptr;
        Node* n1 = nullptr;
        Node* n2 = nullptr;

        Node* curr = head;
        int idx = 1;
        while (curr != nullptr) {
            if (idx == pos - 2) p2 = curr;
            if (idx == pos - 1) p1 = curr;
            if (idx == pos)     n1 = curr;
            if (idx == pos + 1) n2 = curr;
            curr = curr->getNext();
            idx++;
        }

        // Constraint A: Genre Check (No adjacent identical genres)
        if (p1 != nullptr && p1->getSong().getGenre() == newSong.getGenre()) {
            return false;
        }
        if (n1 != nullptr && n1->getSong().getGenre() == newSong.getGenre()) {
            return false;
        }

        // Constraint B: Duration Check (Sum of any 3 consecutive songs <= 600s)
        // Window 1: (p2, p1, newSong)
        if (p2 != nullptr && p1 != nullptr) {
            int sum = p2->getSong().getDuration() + p1->getSong().getDuration() + newSong.getDuration();
            if (sum > 600) return false;
        }

        // Window 2: (p1, newSong, n1)
        if (p1 != nullptr && n1 != nullptr) {
            int sum = p1->getSong().getDuration() + newSong.getDuration() + n1->getSong().getDuration();
            if (sum > 600) return false;
        }

        // Window 3: (newSong, n1, n2)
        if (n1 != nullptr && n2 != nullptr) {
            int sum = newSong.getDuration() + n1->getSong().getDuration() + n2->getSong().getDuration();
            if (sum > 600) return false;
        }

        return true;
    }

    // Operation counter & periodic constraint validator
    void incrementAndCheckOps() {
        opCount++;
        cout << "[System] Operation Count: " << opCount << endl;

        if (opCount % 3 == 0) {
            cout << "-> [3-Operation Threshold Reached] Running playlist constraint verification...\n";
            if (validatePlaylist()) {
                cout << "   STATUS: PASSED. All genre and duration rules are intact.\n";
            } else {
                cout << "   STATUS: FAILED. Playlist violates constraints!\n";
            }
        }
    }

public:
    Playlist() : head(nullptr), opCount(0) {}

    // Destructor to clean up dynamic memory
    ~Playlist() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* nextNode = curr->getNext();
            delete curr;
            curr = nextNode;
        }
    }

    // Validates whole playlist from start to finish
    bool validatePlaylist() const {
        if (head == nullptr) return true;

        // Check 1: Adjacent genres
        Node* curr = head;
        while (curr != nullptr && curr->getNext() != nullptr) {
            if (curr->getSong().getGenre() == curr->getNext()->getSong().getGenre()) {
                return false;
            }
            curr = curr->getNext();
        }

        // Check 2: 3-consecutive duration sum <= 600s
        curr = head;
        while (curr != nullptr && curr->getNext() != nullptr && curr->getNext()->getNext() != nullptr) {
            int sum = curr->getSong().getDuration() +
                      curr->getNext()->getSong().getDuration() +
                      curr->getNext()->getNext()->getSong().getDuration();
            if (sum > 600) return false;
            curr = curr->getNext();
        }

        return true;
    }

    // 1. Insert Song with Auto-Relocation
    void insertSong(Song newSong, int reqPos) {
        int total = getLength();
        if (reqPos < 1) reqPos = 1;

        int targetPos = reqPos;
        bool found = false;

        // Search for the next valid position starting from reqPos
        while (targetPos <= total + 1) {
            if (isValidPosition(newSong, targetPos)) {
                found = true;
                break;
            }
            targetPos++;
        }

        if (!found) {
            cout << "Error: Could not insert '" << newSong.getTitle() 
                 << "'. No valid position available without violating rules.\n";
            incrementAndCheckOps();
            return;
        }

        if (targetPos != reqPos) {
            cout << "Notice: Requested position " << reqPos << " violated rules. "
                 << "Auto-adjusting insertion to position " << targetPos << ".\n";
        }

        Node* newNode = new Node(newSong);

        if (targetPos == 1) {
            newNode->setNext(head);
            head = newNode;
        } else {
            Node* prev = head;
            for (int i = 1; i < targetPos - 1; i++) {
                prev = prev->getNext();
            }
            newNode->setNext(prev->getNext());
            prev->setNext(newNode);
        }

        cout << "Inserted '" << newSong.getTitle() << "' at position " << targetPos << ".\n";
        incrementAndCheckOps();
    }

    // 2. Delete Song (with Explicit Check)
    void deleteSong(int pos) {
        int total = getLength();
        if (pos < 1 || pos > total) {
            cout << "Error: Invalid position " << pos << ".\n";
            incrementAndCheckOps();
            return;
        }

        Node* curr = head;
        Node* prev = nullptr;

        for (int i = 1; i < pos; i++) {
            prev = curr;
            curr = curr->getNext();
        }

        // Block deletion if song is explicit
        if (curr->getSong().isExplicit()) {
            cout << "Error: Cannot delete '" << curr->getSong().getTitle() 
                 << "' because it is marked EXPLICIT! Remove explicit status first.\n";
            incrementAndCheckOps();
            return;
        }

        if (pos == 1) {
            head = head->getNext();
        } else {
            prev->setNext(curr->getNext());
        }

        cout << "Deleted '" << curr->getSong().getTitle() << "' from position " << pos << ".\n";
        delete curr;
        incrementAndCheckOps();
    }

    // Method to toggle/unmark explicit status
    void setExplicitStatus(int pos, bool status) {
        int total = getLength();
        if (pos < 1 || pos > total) {
            cout << "Error: Invalid position " << pos << ".\n";
            return;
        }

        Node* curr = head;
        for (int i = 1; i < pos; i++) {
            curr = curr->getNext();
        }

        curr->getSong().setExplicit(status);
        cout << "Updated explicit status of '" << curr->getSong().getTitle() 
             << "' to " << (status ? "Explicit" : "Non-Explicit") << ".\n";
    }

    // 3. Search Song by Title
    void searchSong(string title) {
        Node* curr = head;
        int pos = 1;
        bool found = false;

        while (curr != nullptr) {
            if (curr->getSong().getTitle() == title) {
                cout << "Found '" << title << "' at position " << pos << ":\n  ";
                curr->getSong().display();
                found = true;
                break;
            }
            curr = curr->getNext();
            pos++;
        }

        if (!found) {
            cout << "Song '" << title << "' not found in playlist.\n";
        }

        incrementAndCheckOps();
    }

    // Display entire playlist
    void displayPlaylist() const {
        if (head == nullptr) {
            cout << "\nPlaylist is empty.\n";
            return;
        }

        cout << "\n================ CURRENT PLAYLIST ================\n";
        Node* curr = head;
        int pos = 1;
        while (curr != nullptr) {
            cout << pos << ". ";
            curr->getSong().display();
            curr = curr->getNext();
            pos++;
        }
        cout << "==================================================\n\n";
    }
};

// -------------------------------------------------------------
// MAIN FUNCTION
// -------------------------------------------------------------
int main() {
    Playlist myPlaylist;

    cout << "--- Populating Playlist ---\n";

    // Operation 1: Insert Pop song
    myPlaylist.insertSong(Song("Shape of You", "pop", 180, false), 1);

    // Operation 2: Insert Rock song (marked explicit)
    myPlaylist.insertSong(Song("Believer", "rock", 200, true), 2);

    // Operation 3: Insert another Pop song at Pos 2
    // Conflict: Genre matches 'Shape of You' -> Moves to Position 3
    // Triggers 3-operation check
    myPlaylist.insertSong(Song("As It Was", "pop", 170, false), 2);

    myPlaylist.displayPlaylist();

    // Operation 4: Search
    myPlaylist.searchSong("Believer");

    // Operation 5: Attempt to delete explicit song at Position 2 -> Blocked!
    myPlaylist.deleteSong(2);

    // Unmark explicit flag so it can be deleted
    myPlaylist.setExplicitStatus(2, false);

    // Operation 6: Delete after unmarking explicit flag
    // Triggers 6th operation check
    myPlaylist.deleteSong(2);

    myPlaylist.displayPlaylist();

    return 0;
}
