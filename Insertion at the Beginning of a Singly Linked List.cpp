#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

void insertAtBeginning(Node *&head, int value)
{
   
    Node *newNode = new Node;

    newNode->data = value;

    if (head == NULL)
    {
        newNode->next = NULL;
        head = newNode;
    }
    else
    {
      
        newNode->next = head;

        head = newNode;
    }

    cout << "Node inserted successfully.\n";
}

void display(Node *head)
{
    Node *temp = head;

    cout << "Linked List: ";

    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }

    cout << "NULL\n";
}

int main()
{
    Node *head = NULL;
    int value, choice;

    do
    {
        cout << "\n1. Insert at Beginning";
        cout << "\n2. Display Linked List";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter data: ";
                cin >> value;
                insertAtBeginning(head, value);
                break;

            case 2:
                display(head);
                break;

            case 3:
                cout << "Program terminated.\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);

    return 0;
}
