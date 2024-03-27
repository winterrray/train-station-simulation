#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linked list
// structure passenger for all entries
typedef struct passenger {
    char name[50];
    int train_no;
    struct passenger* next;
} Passenger;

Passenger* head = NULL;

void enqueue(char name[], int train_no) {
    Passenger* new_passenger = (Passenger*)malloc(sizeof(Passenger));
    strcpy(new_passenger->name, name);
    new_passenger->train_no = train_no;
    new_passenger->next = NULL;

    if (head == NULL) {
        head = new_passenger;
    } else {
        Passenger* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_passenger;
    }
}

void dequeue() {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    Passenger* temp = head;
    head = head->next;
    free(temp);
}

void insertNode(char name[], int train_no, int position) {
    if (position <= 0) {
        printf("Invalid position\n");
        return;
    }

    Passenger* new_passenger = (Passenger*)malloc(sizeof(Passenger));
    strcpy(new_passenger->name, name);
    new_passenger->train_no = train_no;

    if (position == 1) {
        new_passenger->next = head;
        head = new_passenger;
    } else {
        Passenger* current = head;
        int count = 1;
        while (count < position - 1 && current != NULL) {
            current = current->next;
            count++;
        }
        if (current == NULL) {
            printf("Invalid position\n");
            free(new_passenger);
            return;
        }
        new_passenger->next = current->next;
        current->next = new_passenger;
    }
}

void deleteNode(int position) {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }

    if (position <= 0) {
        printf("Invalid position\n");
        return;
    }

    if (position == 1) {
        Passenger* temp = head;
        head = head->next;
        free(temp);
    } else {
        Passenger* current = head;
        Passenger* prev = NULL;
        int count = 1;
        while (count < position && current != NULL) {
            prev = current;
            current = current->next;
            count++;
        }
        if (current == NULL) {
            printf("Invalid position\n");
            return;
        }
        prev->next = current->next;
        free(current);
    }
}

void display() {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("Passengers waiting for the train:\n");
    Passenger* temp = head;
    while (temp != NULL) {
        printf("%s (Train No. %d)\n", temp->name, temp->train_no);
        temp = temp->next;
    }
}

void status(int train_no) {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    int count = 0;
    Passenger* temp = head;
    while (temp != NULL) {
        if (temp->train_no == train_no) {
            count++;
        }
        temp = temp->next;
    }
    printf("Train No. %d is ready to depart. %d passengers are waiting for this train.\n", train_no, count);
}

int main() {
    int choice, train_no, position;
    char name[50];

    while (1) {
        printf("\n");
        printf("1. Add passenger to the queue\n");
        printf("2. Remove passenger from the queue\n");
        printf("3. Insert passenger at a position\n");
        printf("4. Delete passenger from a position\n");
        printf("5. Display passengers waiting for the train\n");
        printf("6. Check status of a train\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter passenger name: ");
                scanf("%s", name);
                printf("Enter train number: ");
                scanf("%d", &train_no);
                enqueue(name, train_no);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                printf("Enter passenger name: ");
                scanf("%s", name);
                printf("Enter train number: ");
                scanf("%d", &train_no);
                printf("Enter position to insert: ");
                scanf("%d", &position);
                insertNode(name, train_no, position);
                break;

            case 4:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteNode(position);
                break;

            case 5:
                display();
                break;

            case 6:
                printf("Enter train number: ");
                scanf("%d", &train_no);
                status(train_no);
                break;

            case 7:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
