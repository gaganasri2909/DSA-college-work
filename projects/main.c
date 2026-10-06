#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================= FUNCTION DECLARATIONS ================= */

void insertBid(int bidderID, int itemID, float amount);
void processAutoBid(int itemID, float currentBid, int currentBidderID);
void endAuction();

/* ================= BIDDER ================= */

struct Bidder
{
    int id;
    char name[50];
    float maxBid;
    int autoBidEnabled;
    struct Bidder *next;
};

struct Bidder *head = NULL;


/* ================= AUCTION ITEM ================= */

struct Item
{
    int id;
    char name[50];
    float startingPrice;
    float currentBid;
    struct Item *next;
};

struct Item *itemHead = NULL;


/* ================= BID / PRIORITY QUEUE ================= */

struct Bid
{
    int bidderID;
    int itemID;
    float amount;
};

struct Bid bidQueue[100];
int bidCount = 0;


/* ================= BIDDER FUNCTIONS ================= */

void addBidder()
{
    struct Bidder *newNode;

    newNode = (struct Bidder *)malloc(sizeof(struct Bidder));

    printf("\nEnter Bidder ID: ");
    scanf("%d", &newNode->id);

    printf("Enter Bidder Name: ");
    scanf("%s", newNode->name);

    printf("Enter Maximum Bid: ");
    scanf("%f", &newNode->maxBid);

    printf("Enable Auto-Bidding? (1-Yes / 0-No): ");
    scanf("%d", &newNode->autoBidEnabled);

    newNode->next = head;
    head = newNode;

    printf("\nBidder registered successfully!\n");
}


void displayBidders()
{
    struct Bidder *temp;

    if (head == NULL)
    {
        printf("\nNo bidders registered.\n");
        return;
    }

    temp = head;

    printf("\n========== BIDDERS ==========\n");

    while (temp != NULL)
    {
        printf("ID          : %d\n", temp->id);
        printf("Name        : %s\n", temp->name);
        printf("Maximum Bid : %.2f\n", temp->maxBid);

        if (temp->autoBidEnabled == 1)
            printf("Auto-Bid    : ON\n");
        else
            printf("Auto-Bid    : OFF\n");

        printf("-----------------------------\n");

        temp = temp->next;
    }
}


void searchBidder()
{
    int id;
    struct Bidder *temp;

    printf("\nEnter Bidder ID to search: ");
    scanf("%d", &id);

    temp = head;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("\nBidder Found!\n");
            printf("ID          : %d\n", temp->id);
            printf("Name        : %s\n", temp->name);
            printf("Maximum Bid : %.2f\n", temp->maxBid);

            if (temp->autoBidEnabled == 1)
                printf("Auto-Bid    : ON\n");
            else
                printf("Auto-Bid    : OFF\n");

            return;
        }

        temp = temp->next;
    }

    printf("\nBidder not found.\n");
}


/* ================= ITEM FUNCTIONS ================= */

void addItem()
{
    struct Item *newNode;

    newNode = (struct Item *)malloc(sizeof(struct Item));

    printf("\nEnter Item ID: ");
    scanf("%d", &newNode->id);

    printf("Enter Item Name: ");
    scanf("%s", newNode->name);

    printf("Enter Starting Price: ");
    scanf("%f", &newNode->startingPrice);

    newNode->currentBid = newNode->startingPrice;

    newNode->next = itemHead;
    itemHead = newNode;

    printf("\nAuction item added successfully!\n");
}


void displayItems()
{
    struct Item *temp;

    if (itemHead == NULL)
    {
        printf("\nNo auction items available.\n");
        return;
    }

    temp = itemHead;

    printf("\n======= AUCTION ITEMS =======\n");

    while (temp != NULL)
    {
        printf("Item ID        : %d\n", temp->id);
        printf("Item Name      : %s\n", temp->name);
        printf("Starting Price : %.2f\n", temp->startingPrice);
        printf("Current Bid    : %.2f\n", temp->currentBid);
        printf("-----------------------------\n");

        temp = temp->next;
    }
}


void searchItem()
{
    int id;
    struct Item *temp;

    printf("\nEnter Item ID to search: ");
    scanf("%d", &id);

    temp = itemHead;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("\nItem Found!\n");
            printf("Item ID        : %d\n", temp->id);
            printf("Item Name      : %s\n", temp->name);
            printf("Starting Price : %.2f\n", temp->startingPrice);
            printf("Current Bid    : %.2f\n", temp->currentBid);

            return;
        }

        temp = temp->next;
    }

    printf("\nItem not found.\n");
}


/* ================= PRIORITY QUEUE ================= */

void insertBid(int bidderID, int itemID, float amount)
{
    int i;
    struct Bid newBid;

    if (bidCount == 100)
    {
        printf("\nPriority Queue is full!\n");
        return;
    }

    newBid.bidderID = bidderID;
    newBid.itemID = itemID;
    newBid.amount = amount;

    i = bidCount - 1;

    while (i >= 0 && bidQueue[i].amount < amount)
    {
        bidQueue[i + 1] = bidQueue[i];
        i--;
    }

    bidQueue[i + 1] = newBid;
    bidCount++;

    printf("\nBid added to Priority Queue.\n");
}


void displayBids()
{
    int i;

    if (bidCount == 0)
    {
        printf("\nNo bids available.\n");
        return;
    }

    printf("\n======= PRIORITY QUEUE =======\n");

    for (i = 0; i < bidCount; i++)
    {
        printf("Bidder ID : %d\n", bidQueue[i].bidderID);
        printf("Item ID   : %d\n", bidQueue[i].itemID);
        printf("Bid       : %.2f\n", bidQueue[i].amount);
        printf("-----------------------------\n");
    }
}


void showHighestBid()
{
    if (bidCount == 0)
    {
        printf("\nNo bids available.\n");
        return;
    }

    printf("\n======= HIGHEST BID =======\n");

    printf("Bidder ID : %d\n", bidQueue[0].bidderID);
    printf("Item ID   : %d\n", bidQueue[0].itemID);
    printf("Bid       : %.2f\n", bidQueue[0].amount);
}


/* ================= AUTO BIDDING ================= */

void processAutoBid(int itemID, float currentBid, int currentBidderID)
{
    struct Bidder *temp;
    float nextBid;

    temp = head;

    while (temp != NULL)
    {
        if (temp->id != currentBidderID &&
            temp->autoBidEnabled == 1 &&
            temp->maxBid > currentBid)
        {
            nextBid = currentBid + 500;

            if (nextBid <= temp->maxBid)
            {
                printf("\nAuto-Bid Activated!");
                printf("\nBidder : %s", temp->name);
                printf("\nAuto Bid Amount : %.2f\n", nextBid);

                insertBid(temp->id, itemID, nextBid);
            }
        }

        temp = temp->next;
    }
}


/* ================= PLACE BID ================= */

void placeBid()
{
    int bidderID;
    int itemID;
    float bidAmount;

    struct Bidder *bidder;
    struct Item *item;

    bidder = head;
    item = itemHead;

    printf("\nEnter Bidder ID: ");
    scanf("%d", &bidderID);

    while (bidder != NULL)
    {
        if (bidder->id == bidderID)
        {
            break;
        }

        bidder = bidder->next;
    }

    if (bidder == NULL)
    {
        printf("\nBidder not found!\n");
        return;
    }

    printf("Enter Item ID: ");
    scanf("%d", &itemID);

    while (item != NULL)
    {
        if (item->id == itemID)
        {
            break;
        }

        item = item->next;
    }

    if (item == NULL)
    {
        printf("\nItem not found!\n");
        return;
    }

    printf("Enter Bid Amount: ");
    scanf("%f", &bidAmount);

    if (bidAmount <= item->currentBid)
    {
        printf("\nBid rejected!\n");
        printf("Bid must be greater than current bid %.2f\n",
               item->currentBid);
        return;
    }

    if (bidAmount > bidder->maxBid)
    {
        printf("\nBid rejected!\n");
        printf("Bid exceeds bidder's maximum limit.\n");
        return;
    }

    item->currentBid = bidAmount;

    insertBid(bidderID, itemID, bidAmount);

    printf("\nBid placed successfully!\n");
    printf("Item        : %s\n", item->name);
    printf("Bidder      : %s\n", bidder->name);
    printf("Current Bid : %.2f\n", item->currentBid);

    processAutoBid(itemID, bidAmount, bidderID);
}


/* ================= END AUCTION ================= */

void endAuction()
{
    if (bidCount == 0)
    {
        printf("\nNo bids available. Auction cannot be ended.\n");
        return;
    }

    printf("\n====================================\n");
    printf("          AUCTION ENDED\n");
    printf("====================================\n");

    printf("Winner Bidder ID : %d\n", bidQueue[0].bidderID);
    printf("Item ID          : %d\n", bidQueue[0].itemID);
    printf("Winning Bid      : %.2f\n", bidQueue[0].amount);

    printf("\nCongratulations to the highest bidder!\n");
}


/* ================= MAIN ================= */

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("       REAL-TIME AUCTION SYSTEM\n");
        printf("====================================\n");

        printf("1. Register Bidder\n");
        printf("2. Display Bidders\n");
        printf("3. Search Bidder\n");
        printf("4. Add Auction Item\n");
        printf("5. Display Auction Items\n");
        printf("6. Search Auction Item\n");
        printf("7. Place Bid\n");
        printf("8. Display Bids\n");
        printf("9. Show Highest Bid\n");
        printf("10. End Auction\n");
        printf("11. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addBidder();
                break;

            case 2:
                displayBidders();
                break;

            case 3:
                searchBidder();
                break;

            case 4:
                addItem();
                break;

            case 5:
                displayItems();
                break;

            case 6:
                searchItem();
                break;

            case 7:
                placeBid();
                break;

            case 8:
                displayBids();
                break;

            case 9:
                showHighestBid();
                break;

            case 10:
                endAuction();
                break;

            case 11:
                printf("\nThank you!\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}