#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string disease;
    string contact;
    Patient* next;

    Patient(int i, string n, int a, string g,
            string d, string c) {
        id = i;
        name = n;
        age = a;
        gender = g;
        disease = d;
        contact = c;
        next = nullptr;
    }
};

struct HashNode {
    int id;
    Patient* patient;
    HashNode* next;

    HashNode(int i, Patient* p) {
        id = i;
        patient = p;
        next = nullptr;
    }
};

class Hospital {
private:
    Patient* head;
    HashNode* table[SIZE];

    int hashFunction(int id) {
        return id % SIZE;
    }

    Patient* search(int id) {
        int index = hashFunction(id);
        HashNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->id == id)
                return temp->patient;

            temp = temp->next;
        }
        return nullptr;
    }

    void insertHash(Patient* p) {
        int index = hashFunction(p->id);

        HashNode* node = new HashNode(p->id, p);
        node->next = table[index];
        table[index] = node;
    }

    void deleteHash(int id) {
        int index = hashFunction(id);

        HashNode* temp = table[index];
        HashNode* prev = nullptr;

        while (temp != nullptr) {
            if (temp->id == id) {
                if (prev == nullptr)
                    table[index] = temp->next;
                else
                    prev->next = temp->next;

                delete temp;
                return;
            }

            prev = temp;
            temp = temp->next;
        }
    }

public:
    Hospital() {
        head = nullptr;

        for (int i = 0; i < SIZE; i++)
            table[i] = nullptr;
    }

    void registerPatient() {
        int id, age;
        string name, gender, disease, contact;

        cout << "Enter Patient ID: ";
        cin >> id;

        if (search(id) != nullptr) {
            cout << "Patient ID already exists!\n";
            return;
        }

        cout << "Enter Name: ";
        getline(cin >> ws, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Gender: ";
        cin >> gender;

        cout << "Enter Disease: ";
        getline(cin >> ws, disease);

        cout << "Enter Contact: ";
        cin >> contact;

        Patient* p = new Patient(
            id, name, age, gender, disease, contact
        );

        p->next = head;
        head = p;

        insertHash(p);

        cout << "Patient registered successfully!\n";
    }

    void searchPatient() {
        int id;
        cout << "Enter Patient ID: ";
        cin >> id;

        Patient* p = search(id);

        if (p == nullptr) {
            cout << "Patient not found!\n";
            return;
        }

        cout << "\nPatient Details\n";
        cout << "ID: " << p->id << endl;
        cout << "Name: " << p->name << endl;
        cout << "Age: " << p->age << endl;
        cout << "Gender: " << p->gender << endl;
        cout << "Disease: " << p->disease << endl;
        cout << "Contact: " << p->contact << endl;
    }

    void updatePatient() {
        int id;
        cout << "Enter Patient ID: ";
        cin >> id;

        Patient* p = search(id);

        if (p == nullptr) {
            cout << "Patient not found!\n";
            return;
        }

        cout << "Enter New Name: ";
        getline(cin >> ws, p->name);

        cout << "Enter New Age: ";
        cin >> p->age;

        cout << "Enter New Gender: ";
        cin >> p->gender;

        cout << "Enter New Disease: ";
        getline(cin >> ws, p->disease);

        cout << "Enter New Contact: ";
        cin >> p->contact;

        cout << "Patient updated successfully!\n";
    }

    void dischargePatient() {
        int id;
        cout << "Enter Patient ID: ";
        cin >> id;

        Patient* temp = head;
        Patient* prev = nullptr;

        while (temp != nullptr && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Patient not found!\n";
            return;
        }

        if (prev == nullptr)
            head = temp->next;
        else
            prev->next = temp->next;

        deleteHash(id);
        delete temp;

        cout << "Patient discharged successfully!\n";
    }

    void displayPatients() {
        Patient* temp = head;

        if (temp == nullptr) {
            cout << "No patient records available!\n";
            return;
        }

        cout << "\n===== PATIENT RECORDS =====\n";

        while (temp != nullptr) {
            cout << "\nPatient ID: " << temp->id;
            cout << "\nName: " << temp->name;
            cout << "\nAge: " << temp->age;
            cout << "\nGender: " << temp->gender;
            cout << "\nDisease: " << temp->disease;
            cout << "\nContact: " << temp->contact;
            cout << "\n--------------------------\n";

            temp = temp->next;
        }
    }

    ~Hospital() {
        while (head != nullptr) {
            Patient* temp = head;
            head = head->next;
            delete temp;
        }

        for (int i = 0; i < SIZE; i++) {
            while (table[i] != nullptr) {
                HashNode* temp = table[i];
                table[i] = table[i]->next;
                delete temp;
            }
        }
    }
};

int main() {
    Hospital h;
    int choice;

    do {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====\n";
        cout << "1. Register Patient\n";
        cout << "2. Update Patient\n";
        cout << "3. Discharge Patient\n";
        cout << "4. Display All Patients\n";
        cout << "5. Search Patient\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                h.registerPatient();
                break;

            case 2:
                h.updatePatient();
                break;

            case 3:
                h.dischargePatient();
                break;

            case 4:
                h.displayPatients();
                break;

            case 5:
                h.searchPatient();
                break;

            case 6:
                cout << "Exiting Hospital System...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
