#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Friend {
    char name[50];
    struct Friend *next;
};

struct Friend *head = NULL;
void addFriend() {
    struct Friend *newNode, *temp;

    newNode = (struct Friend *)malloc(sizeof(struct Friend));

    printf("Enter friend's name: ");
    scanf("%s", newNode->name);

    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    }
    else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("Friend added successfully!\n");
}
void removeFriend() {
    struct Friend *temp, *prev;
    char name[50];

    if (head == NULL) {
        printf("Friend list is empty!\n");
        return;
    }

    printf("Enter name to remove: ");
    scanf("%s", name);

    temp = head;
    prev = NULL;
    if (strcmp(temp->name, name) == 0) {
        head = temp->next;
        free(temp);
        printf("Friend removed successfully!\n");
        return;
    }
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;}
        
    if (temp == NULL) {
        printf("Friend not found!\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Friend removed successfully!\n");
}
void displayFriends() {
    struct Friend *temp;

    if (head == NULL) {
        printf("Friend list is empty!\n");
        return;
    }
    temp = head;
    printf("\nYour Friends:\n");
    while (temp != NULL) {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }}
int main() {
    int choice;

    while (1) {
        printf("\n--- Social Media Friend List ---\n");
        printf("1. Add Friend\n");
        printf("2. Remove Friend\n");
        printf("3. Display Friends\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addFriend();
            break;
        case 2:
            removeFriend();
            break;
        case 3:
            displayFriends();
            break;
        case 4:
            printf("Exiting program...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }}
    return 0;
}