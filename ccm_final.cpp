#include <iostream>
#include <string>
using namespace std;

const int SIZE = 101;

// ---------------- LINKED LIST ----------------
class snode {
public:
    int id;
    snode *next;
    snode(int val) {
        id = val;
        next = NULL;
    }
};

class ll {
public:
    snode *start, *last;
    int count;

    ll() {
        start = last = NULL;
        count = 0;
    }

    ll(const ll&) = delete;
    ll& operator=(const ll&) = delete;

    ~ll() { clear(); }

    // O(1) insertion using tail pointer
    void insertEnd(int id) {
        snode *n = new snode(id);
        if (start == NULL)
            start = last = n;
        else {
            last->next = n;
            last = n;
        }
        count++;
    }

    bool remove(int id) {
        snode *temp = start, *prev = NULL;
        while (temp != NULL) {
            if (temp->id == id) {
                if (prev == NULL)
                    start = temp->next;
                else
                    prev->next = temp->next;

                if (last == temp)
                    last = prev;

                delete temp;
                count--;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    void display() {
        if (start == NULL) {
            cout << "None";
            return;
        }
        snode *temp = start;
        while (temp != NULL) {
            cout << temp->id;
            if (temp->next != NULL) cout << " -> ";
            temp = temp->next;
        }
    }

    void clear() {
        snode *temp = start;
        while (temp != NULL) {
            snode *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        start = last = NULL;
        count = 0;
    }
};

// ---------------- MANUAL HASH TABLE ----------------
// Separate chaining is used to handle collisions.

int hashFunction(int id) {
    int index = id % SIZE;
    if (index < 0) index += SIZE;
    return index;
}

void initHash(snode *table[]) {
    for (int i = 0; i < SIZE; i++)
        table[i] = NULL;
}

bool hashSearch(snode *table[], int id) {
    snode *temp = table[hashFunction(id)];
    while (temp != NULL) {
        if (temp->id == id) return true;
        temp = temp->next;
    }
    return false;
}

void hashInsert(snode *table[], int id) {
    if (hashSearch(table, id)) return;

    int index = hashFunction(id);
    snode *n = new snode(id);
    n->next = table[index];
    table[index] = n;
}

bool hashDelete(snode *table[], int id) {
    int index = hashFunction(id);
    snode *temp = table[index], *prev = NULL;

    while (temp != NULL) {
        if (temp->id == id) {
            if (prev == NULL)
                table[index] = temp->next;
            else
                prev->next = temp->next;
            delete temp;
            return true;
        }
        prev = temp;
        temp = temp->next;
    }
    return false;
}

void clearHash(snode *table[]) {
    for (int i = 0; i < SIZE; i++) {
        snode *temp = table[i];
        while (temp != NULL) {
            snode *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        table[i] = NULL;
    }
}

// ---------------- CLUB ----------------
class Club {
public:
    int clubId;
    string name;
    ll members;
    snode *memberTable[SIZE];
    Club *next;

    Club(int id, string clubName) {
        clubId = id;
        name = clubName;
        next = NULL;
        initHash(memberTable);
    }

    Club(const Club&) = delete;
    Club& operator=(const Club&) = delete;

    ~Club() {
        clearHash(memberTable);
    }

    bool addMember(int id) {
        if (hashSearch(memberTable, id)) return false;
        members.insertEnd(id);
        hashInsert(memberTable, id);
        return true;
    }

    bool removeMember(int id) {
        if (!hashSearch(memberTable, id)) return false;
        members.remove(id);
        hashDelete(memberTable, id);
        return true;
    }
};

// ---------------- CLUB MANAGEMENT ----------------
class ClubManager {
    Club *start, *last;
    int nextId;

public:
    ClubManager() {
        start = last = NULL;
        nextId = 1;
    }

    ClubManager(const ClubManager&) = delete;
    ClubManager& operator=(const ClubManager&) = delete;

    ~ClubManager() {
        Club *temp = start;
        while (temp != NULL) {
            Club *nextClub = temp->next;
            delete temp;
            temp = nextClub;
        }
    }

    Club* findClub(int id) {
        Club *temp = start;
        while (temp != NULL) {
            if (temp->clubId == id) return temp;
            temp = temp->next;
        }
        return NULL;
    }

    bool nameExists(string name) {
        Club *temp = start;
        while (temp != NULL) {
            if (temp->name == name) return true;
            temp = temp->next;
        }
        return false;
    }

    void createClub() {
        string name;
        cout << "Enter club name: ";
        getline(cin >> ws, name);

        if (nameExists(name)) {
            cout << "Club already exists.\n";
            return;
        }

        Club *n = new Club(nextId, name);
        nextId++;

        if (start == NULL)
            start = last = n;
        else {
            last->next = n;
            last = n;
        }
        cout << "Club created. Club ID: " << n->clubId << "\n";
    }

    void displayClubs() {
        if (start == NULL) {
            cout << "No clubs created.\n";
            return;
        }

        cout << "\n--- COLLEGE CLUBS ---\n";
        Club *temp = start;
        while (temp != NULL) {
            cout << "ID: " << temp->clubId
                 << " | Name: " << temp->name
                 << " | Members: " << temp->members.count << "\n";
            temp = temp->next;
        }
    }

    void addMember() {
        int cid, mid;
        cout << "Enter club ID: ";
        cin >> cid;
        Club *c = findClub(cid);

        if (c == NULL) {
            cout << "Club not found.\n";
            return;
        }

        cout << "Enter student/member ID: ";
        cin >> mid;
        if (mid <= 0) {
            cout << "Member ID must be positive.\n";
            return;
        }

        if (c->addMember(mid))
            cout << "Member added successfully.\n";
        else
            cout << "Member already exists in this club.\n";
    }

    void removeMember() {
        int cid, mid;
        cout << "Enter club ID: ";
        cin >> cid;
        Club *c = findClub(cid);

        if (c == NULL) {
            cout << "Club not found.\n";
            return;
        }

        cout << "Enter member ID to remove: ";
        cin >> mid;

        if (c->removeMember(mid))
            cout << "Membership removed successfully.\n";
        else
            cout << "Member not found in this club.\n";
    }

    void searchMember() {
        int cid, mid;
        cout << "Enter club ID: ";
        cin >> cid;
        Club *c = findClub(cid);

        if (c == NULL) {
            cout << "Club not found.\n";
            return;
        }

        cout << "Enter member ID to search: ";
        cin >> mid;

        if (hashSearch(c->memberTable, mid))
            cout << "Member is registered in " << c->name << ".\n";
        else
            cout << "Member not found in this club.\n";
    }

    void displayMembers() {
        int cid;
        cout << "Enter club ID: ";
        cin >> cid;
        Club *c = findClub(cid);

        if (c == NULL) {
            cout << "Club not found.\n";
            return;
        }

        cout << "\nMembers of " << c->name << ": ";
        c->members.display();
        cout << "\nTotal members: " << c->members.count << "\n";
    }

    // One approach only: manual hashing.
    void compareClubs() {
        int idA, idB;
        cout << "Enter first club ID: ";
        cin >> idA;
        Club *A = findClub(idA);

        if (A == NULL) {
            cout << "First club not found.\n";
            return;
        }

        cout << "Enter second club ID: ";
        cin >> idB;
        Club *B = findClub(idB);

        if (B == NULL) {
            cout << "Second club not found.\n";
            return;
        }

        if (A == B) {
            cout << "Choose two different clubs.\n";
            return;
        }

        ll uni, inter, onlyA, onlyB;
        snode *seen[SIZE], *processedA[SIZE], *processedB[SIZE];
        initHash(seen);
        initHash(processedA);
        initHash(processedB);

        // UNION: unique members of A followed by new members of B.
        snode *temp = A->members.start;
        while (temp != NULL) {
            if (!hashSearch(seen, temp->id)) {
                uni.insertEnd(temp->id);
                hashInsert(seen, temp->id);
            }
            temp = temp->next;
        }

        temp = B->members.start;
        while (temp != NULL) {
            if (!hashSearch(seen, temp->id)) {
                uni.insertEnd(temp->id);
                hashInsert(seen, temp->id);
            }
            temp = temp->next;
        }

        // INTERSECTION and members only in Club A.
        temp = A->members.start;
        while (temp != NULL) {
            if (!hashSearch(processedA, temp->id)) {
                hashInsert(processedA, temp->id);
                if (hashSearch(B->memberTable, temp->id))
                    inter.insertEnd(temp->id);
                else
                    onlyA.insertEnd(temp->id);
            }
            temp = temp->next;
        }

        // Members only in Club B.
        temp = B->members.start;
        while (temp != NULL) {
            if (!hashSearch(processedB, temp->id)) {
                hashInsert(processedB, temp->id);
                if (!hashSearch(A->memberTable, temp->id))
                    onlyB.insertEnd(temp->id);
            }
            temp = temp->next;
        }

        cout << "\n===== MEMBERSHIP REPORT =====\n";
        cout << "Club A: " << A->name << "\n";
        cout << "Club B: " << B->name << "\n";
        cout << "Union: ";
        uni.display();
        cout << "\nIntersection: ";
        inter.display();
        cout << "\nOnly in " << A->name << ": ";
        onlyA.display();
        cout << "\nOnly in " << B->name << ": ";
        onlyB.display();
        cout << "\n";

        clearHash(seen);
        clearHash(processedA);
        clearHash(processedB);
    }

    void statistics() {
        int clubs = 0, memberships = 0;
        Club *largest = NULL;
        Club *temp = start;

        while (temp != NULL) {
            clubs++;
            memberships += temp->members.count;
            if (largest == NULL ||
                temp->members.count > largest->members.count)
                largest = temp;
            temp = temp->next;
        }

        cout << "\n--- MEMBERSHIP STATISTICS ---\n";
        cout << "Total clubs: " << clubs << "\n";
        cout << "Total memberships: " << memberships << "\n";
        if (largest != NULL)
            cout << "Largest club: " << largest->name
                 << " (" << largest->members.count << " members)\n";
        else
            cout << "No clubs available.\n";
    }
};

// ---------------- MAIN MENU ----------------
int main() {
    ClubManager manager;
    int choice;

    do {
        cout << "\n============================================\n";
        cout << " COLLEGE CLUB MEMBERSHIP MANAGEMENT SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Create Club\n";
        cout << "2. Display All Clubs\n";
        cout << "3. Add Member to Club\n";
        cout << "4. Remove Member from Club\n";
        cout << "5. Search Member in Club\n";
        cout << "6. Display Club Members\n";
        cout << "7. Compare Two Clubs (Union and Intersection)\n";
        cout << "8. Display Membership Statistics\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.createClub(); break;
            case 2: manager.displayClubs(); break;
            case 3: manager.addMember(); break;
            case 4: manager.removeMember(); break;
            case 5: manager.searchMember(); break;
            case 6: manager.displayMembers(); break;
            case 7: manager.compareClubs(); break;
            case 8: manager.statistics(); break;
            case 0: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
