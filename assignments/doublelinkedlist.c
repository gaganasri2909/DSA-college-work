#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char page[50];
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;
struct Node *current = NULL;

// Create a new node
struct Node* createNode(char page[])
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->page, page);
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

// Insert a new page at the end
void insertPage(char page[])
{
    struct Node *newNode;
    struct Node *temp;

    newNode = createNode(page);

    if (head == NULL)
    {
        head = newNode;
        current = newNode;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;

        current = newNode;
    }

    printf("Page '%s' inserted successfully.\n", page);
}

// Move forward
void moveForward()
{
    if (current == NULL)
    {
        printf("No pages available.\n");
    }
    else if (current->next == NULL)
    {
        printf("Already at the last page. Cannot move forward.\n");
    }
    else
    {
        current = current->next;
        printf("Moved forward to: %s\n", current->page);
    }
}

// Move backward
void moveBackward()
{
    if (current == NULL)
    {
        printf("No pages available.\n");
    }
    else if (current->prev == NULL)
    {
        printf("Already at the first page. Cannot move backward.\n");
    }
    else
    {
        current = current->prev;
        printf("Moved backward to: %s\n", current->page);
    }
}

// Delete a specified page
void deletePage(char page[])
{
    struct Node *temp = head;

    while (temp != NULL && strcmp(temp->page, page) != 0)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Page '%s' not found.\n", page);
        return;
    }

    // If deleting the first node
    if (temp == head)
    {
        head = temp->next;

        if (head != NULL)
        {
            head->prev = NULL;
        }
    }
    else
    {
        temp->prev->next = temp->next;

        if (temp->next != NULL)
        {
            temp->next->prev = temp->prev;
        }
    }

    // Update current page
    if (temp == current)
    {
        if (temp->next != NULL)
            current = temp->next;
        else
            current = temp->prev;
    }

    free(temp);

    printf("Page '%s' deleted successfully.\n", page);
}

// Display from first to last
void displayForward()
{
    struct Node *temp = head;

    if (head == NULL)
    {
        printf("No pages available.\n");
        return;
    }

    printf("\nPages from First to Last:\n");

    while (temp != NULL)
    {
        printf("%s -> ", temp->page);
        temp = temp->next;
    }

    printf("NULL\n");
}

// Display from last to first
void displayBackward()
{
    struct Node *temp = head;

    if (head == NULL)
    {
        printf("No pages available.\n");
        return;
    }

    // Go to last node
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    printf("\nPages from Last to First:\n");

    while (temp != NULL)
    {
        printf("%s -> ", temp->page);
        temp = temp->prev;
    }

    printf("NULL\n");
}

// Display current page
void displayCurrent()
{
    if (current == NULL)
        printf("No page is currently selected.\n");
    else
        printf("Current Page: %s\n", current->page);
}

int main()
{
    int choice;
    char page[50];

    while (1)
    {
        printf("\n===== WEB PAGE HISTORY =====\n");
        printf("1. Insert New Page\n");
        printf("2. Move Forward\n");
        printf("3. Move Backward\n");
        printf("4. Delete Page\n");
        printf("5. Display First to Last\n");
        printf("6. Display Last to First\n");
        printf("7. Display Current Page\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter page name: ");
                scanf("%s", page);

                insertPage(page);
                displayForward();
                break;

            case 2:
                moveForward();
                displayCurrent();
                break;

            case 3:
                moveBackward();
                displayCurrent();
                break;

            case 4:
                printf("Enter page to delete: ");
                scanf("%s", page);

                deletePage(page);
                displayForward();
                break;

            case 5:
                displayForward();
                break;

            case 6:
                displayBackward();
                break;

            case 7:
                displayCurrent();
                break;

            case 8:
                printf("Program terminated.\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}