#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define ENTER 13
#define TAB 9
#define BCKSPC 8
#define ADMIN_PASSWORD "admin123"
#define MAX_ITEMS 100

typedef struct {
    char name[50];
    int price;
    int quantity;
    int totalAmount;
} Item;

typedef struct {
    char fullName[50];
    char email[50];
    char password[50];
    char username[50];
    char phone[50];
} User;

void takeInput(char ch[50]) {
    fgets(ch, 50, stdin);
    ch[strlen(ch) - 1] = '\0';
}

void takePassword(char pwd[50]) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == ENTER || ch == TAB) {
            pwd[i] = '\0';
            break;
        } else if (ch == BCKSPC) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            pwd[i++] = ch;
            printf("* \b");
        }
    }
}
int isStrongPassword(const char *pwd) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    int length = strlen(pwd);

    if (length < 8) {
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (isupper(pwd[i])) hasUpper = 1;
        else if (islower(pwd[i])) hasLower = 1;
        else if (isdigit(pwd[i])) hasDigit = 1;
        else if (ispunct(pwd[i])) hasSpecial = 1;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}
void saveItemsToFile(Item items[], int itemCount) {
    FILE *fp = fopen("Menu.dat", "wb");
    fwrite(items, sizeof(Item), itemCount, fp);
    fclose(fp);
}

void loadItemsFromFile(Item items[], int *itemCount) {
    FILE *fp = fopen("Menu.dat", "rb");
    if (fp == NULL) {
        *itemCount = 0;
        return;
    }
    *itemCount = fread(items, sizeof(Item), MAX_ITEMS, fp);
    fclose(fp);
}
    void takeCardDetails(char cardNumber[20], char expiryDate[10], char cvv[5]) {
    printf("Enter card number: ");
     fflush(stdin);
    takeInput(cardNumber);
    printf("Enter expiry date (MM/YY): ");
    takeInput(expiryDate);
    printf("Enter CVV: ");
    takeInput(cvv);
    }
void displayMenu();
void orderPizza(Item items[], int *itemCount);
void orderBiryani(Item items[], int *itemCount);
void orderBurger(Item items[], int *itemCount);
void orderCake(Item items[], int *itemCount);
void orderDrink(Item items[], int *itemCount);
void generateBill(Item items[], int itemCount, const char* customerName, const char* location, int paymentOption);
void adminPanel(Item items[], int *itemCount);

int main() {
    system("color E1");
    int option, choice,add, itemCount = 0;
    char location[200], customerName[100];
    Item items[MAX_ITEMS];
    User currentUser;
    printf("\t\t\t-------------------------------------------------\n");
    printf("\t\t\t|\t\t  CHOOSE AN OPTION\t\t|\n");
    printf("\t\t\t--------------------------------------------------\n");
    printf("1: Admin Panel\n");
    printf("2: User Panel\n\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch(choice){
    case 1:

        loadItemsFromFile(items, &itemCount);
        adminPanel(items, &itemCount);
        break;
    case 2:
    system("cls");
    printf("\t\t\t\t*================================================*\n");
    printf("\t\t\t\t*\t\t\t\t\t\t *\n");
    printf("\t\t\t\t*WELCOME TO  DESHI MAMAR,BIDESHI KHANA RESTURANT *\n");
    printf("\t\t\t\t*\t\t\t\t\t\t *\n");
    printf("\t\t\t\t*================================================*\n");

    int loggedIn = 0;
        do {
            printf("Please choose your operation:\n");
            printf("1. Login\n");
            printf("2. Signup\n");
            printf("3. Exit\n");
            printf("Your choice: ");
            scanf("%d", &option);
            fflush(stdin);

            switch (option) {
                case 1: {
                    printf("\nEnter your username: ");
                    takeInput(currentUser.username);
                    printf("Enter your password: ");
                    takePassword(currentUser.password);

                    FILE *fp = fopen("Users.dat", "rb");
                    int found = 0;
                    User tempUser;
                    while (fread(&tempUser, sizeof(User), 1, fp)) {
                        if (strcmp(tempUser.username, currentUser.username) == 0 &&
                            strcmp(tempUser.password, currentUser.password) == 0) {
                            strcpy(currentUser.fullName, tempUser.fullName);
                            strcpy(currentUser.email, tempUser.email);
                            strcpy(currentUser.phone, tempUser.phone);
                            found = 1;
                            break;
                        }
                    }
                    fclose(fp);

                    if (found) {
                        loggedIn = 1;
                        printf("\nLogin successful!\n");
                    } else {
                        printf("\nInvalid username or password!\n");
                    }
                    break;
                }
                case 2: {
                    printf("\nEnter your full name: ");
                    takeInput(currentUser.fullName);
                    printf("Enter your email: ");
                    takeInput(currentUser.email);
                    printf("Enter your contact number: ");
                    takeInput(currentUser.phone);
                    printf("Create a username: ");
                    takeInput(currentUser.username);

                    do {
                        printf("Create a password: ");
                        takePassword(currentUser.password);
                        if (!isStrongPassword(currentUser.password)) {
                            printf("\nPassword is not strong enough. It must be at least 8 characters long and include an uppercase letter, a lowercase letter, a digit, and a special character.\n");
                        }
                    } while (!isStrongPassword(currentUser.password));

                    FILE *fp = fopen("Users.dat", "ab");
                    fwrite(&currentUser, sizeof(User), 1, fp);
                    fclose(fp);

                    printf("\nSignup successful!\n");
                    loggedIn = 1;
                    break;
                }
                case 3:
                    printf("\nExiting...\n");
                    return 0;
                default:
                    printf("\nInvalid option!\n");
                    break;
            }
        } while (!loggedIn);
    printf("\n\n\n");
    system("cls");
    do {
        displayMenu();
        printf("Please select an option: ");
        scanf("%d", &option);
        fflush(stdin);

        switch (option) {
            case 1:
                orderPizza(items, &itemCount);
                break;
            case 2:
                orderBiryani(items, &itemCount);
                break;
            case 3:
                orderBurger(items, &itemCount);
                break;
            case 4:
                orderCake(items, &itemCount);
                break;
            case 5:
                orderDrink(items, &itemCount);
                break;
            default:
                printf("Invalid option.\n");
                break;
        }

        printf("\nDo you want to order more?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Enter choice: ");
        scanf("%d", &add);
        fflush(stdin);
    } while (add == 1);

    printf("Please select payment method:\n");
    printf("1. Cash On Delivery\n");
    printf("2. Card\n");
    printf("Enter your choice: ");
    int paymentOption;
    scanf("%d", &paymentOption);

    if (paymentOption == 2) {
     system("cls");
     printf("\n\t\t\t\t\t=================================\n");
    printf("\t\t\t\t\t|\tCard Details\t\t|\n");
    printf("\t\t\t\t\t=================================\n");
    char cardNumber[20], expiryDate[10], cvv[5];
    takeCardDetails(cardNumber, expiryDate, cvv);
    printf("Card details received.\n");
    }
    system("cls");
    printf("\nConfirm your location: ");
    scanf("%s", location);
    generateBill(items, itemCount, currentUser.fullName, location, paymentOption);

    printf("Your order is placed\n");
    printf("\t\t\t\t\tThank you for ordering \n");

    return 0;
    break;
    default:
                printf("\nInvalid option!\n");
                break;
    }
}

void displayMenu() {
    printf("\n\t\t\t\t\t=================================\n");
    printf("\t\t\t\t\t|\t\tMENU\t\t|\n");
    printf("\t\t\t\t\t=================================\n");
    printf("------------------------------------------------\n");
    printf("|Delivery:15-30 min\t\t\t\t|\n");
    printf("|10%% off Min order Tk 499.Valid for all items   |\n");
    printf("-------------------------------------------------\n");
    printf("Different cuisines are available here\n");
    printf("1. Pizza\n");
    printf("2. Biryani\n");
    printf("3. Burgers\n");
    printf("4. Cakes\n");
    printf("5. Drinks\n");

}

void orderPizza(Item items[], int *itemCount) {
    int pizzaOption, quantity;
    printf("Pizza Menu:\n");
    printf("1. Margherita   449tk.\n");
    printf("2. Pepperoni   755tk\n");
    printf("3. Hawaiian     1399tk\n");
    printf("Select a pizza: ");
    scanf("%d", &pizzaOption);

    switch (pizzaOption) {
        case 1:
            printf("You ordered a Margherita Pizza.\n");
            strcpy(items[*itemCount].name, "Margherita Pizza");
            items[*itemCount].price = 449;
            break;
        case 2:
            printf("You ordered a Pepperoni Pizza.\n");
            strcpy(items[*itemCount].name, "Pepperoni Pizza");
            items[*itemCount].price = 755;
            break;
        case 3:
            printf("You ordered a Hawaiian Pizza.\n");
            strcpy(items[*itemCount].name, "Hawaiian Pizza");
            items[*itemCount].price = 1399;
            break;
        default:
            printf("Invalid option.\n");
            return;
    }
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    items[*itemCount].quantity = quantity;
    items[*itemCount].totalAmount = items[*itemCount].price * quantity;
    printf("Total %dtk.\n", items[*itemCount].totalAmount);
    (*itemCount)++;
}

void orderBiryani(Item items[], int *itemCount) {
    int biryaniOption, quantity;
    printf("Biryani Menu:\n");
    printf("1. Beef Akhni biryani 140tk.\n");
    printf("2. Chicken biryani     170tk\n");
    printf("3. Mutton kacchi        250tk\n");
    printf("Select a biryani: ");
    scanf("%d", &biryaniOption);

    switch (biryaniOption) {
        case 1:
            printf("You ordered a Beef Akhni biryani.\n");
            strcpy(items[*itemCount].name, "Beef Akhni Biryani");
            items[*itemCount].price = 140;
            break;
        case 2:
            printf("You ordered a Chicken biryani.\n");
            strcpy(items[*itemCount].name, "Chicken Biryani");
            items[*itemCount].price = 170;
            break;
        case 3:
            printf("You ordered a Mutton kacchi.\n");
            strcpy(items[*itemCount].name, "Mutton Kacchi");
            items[*itemCount].price = 250;
            break;
        default:
            printf("Invalid option.\n");
            return;
    }
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    items[*itemCount].quantity = quantity;
    items[*itemCount].totalAmount = items[*itemCount].price * quantity;
    printf("Total %dtk.\n", items[*itemCount].totalAmount);
    (*itemCount)++;
}

void orderBurger(Item items[], int *itemCount) {
    int burgerOption, quantity;
    printf("Burger Menu:\n");
    printf("1. Chesse Burger       200tk.\n");
    printf("2. Chicken Burger      190tk\n");
    printf("3. Veggie Burger       180tk\n");
    printf("Select a Burger: ");
    scanf("%d", &burgerOption);

    switch (burgerOption) {
        case 1:
            printf("You ordered a Beef Burger.\n");
            strcpy(items[*itemCount].name, "Beef Burger");
            items[*itemCount].price = 200;
            break;
        case 2:
            printf("You ordered a Chicken Burger.\n");
            strcpy(items[*itemCount].name, "Chicken Burger");
            items[*itemCount].price = 190;
            break;
        case 3:
            printf("You ordered a Veggie Burger.\n");
            strcpy(items[*itemCount].name, "Veggie Burger");
            items[*itemCount].price = 180;
            break;
        default:
            printf("Invalid option.\n");
            return;
    }
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    items[*itemCount].quantity = quantity;
    items[*itemCount].totalAmount = items[*itemCount].price * quantity;
    printf("Total %dtk.\n", items[*itemCount].totalAmount);
    (*itemCount)++;
}

void orderCake(Item items[], int *itemCount) {
    int cakeOption, quantity;
    printf("Cake Menu:\n");
    printf("1. Black Forest         400tk.\n");
    printf("2. Red Velvet           500tk\n");
    printf("3. Chocolate Truffle    600tk\n");
    printf("Select a Cake: ");
    scanf("%d", &cakeOption);

    switch (cakeOption) {
        case 1:
            printf("You ordered a Black Forest Cake.\n");
            strcpy(items[*itemCount].name, "Black Forest Cake");
            items[*itemCount].price = 400;
            break;
        case 2:
            printf("You ordered a Red Velvet Cake.\n");
            strcpy(items[*itemCount].name, "Red Velvet Cake");
            items[*itemCount].price = 500;
            break;
        case 3:
            printf("You ordered a Chocolate Truffle Cake.\n");
            strcpy(items[*itemCount].name, "Chocolate Truffle Cake");
            items[*itemCount].price = 600;
            break;
        default:
            printf("Invalid option.\n");
            return;
    }
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    items[*itemCount].quantity = quantity;
    items[*itemCount].totalAmount = items[*itemCount].price * quantity;
    printf("Total %dtk.\n", items[*itemCount].totalAmount);
    (*itemCount)++;
}

void orderDrink(Item items[], int *itemCount) {
    int drinkOption, quantity;
    printf("Drink Menu:\n");
    printf("1. Coca-Cola      50tk.\n");
    printf("2. Pepsi              55tk\n");
    printf("3. Sprite              60tk\n");
    printf("Select a drink: ");
    scanf("%d", &drinkOption);

    switch (drinkOption) {
        case 1:
            printf("You ordered a Coca-Cola.\n");
            strcpy(items[*itemCount].name, "Coca-Cola");
            items[*itemCount].price = 50;
            break;
        case 2:
            printf("You ordered a Pepsi.\n");
            strcpy(items[*itemCount].name, "Pepsi");
            items[*itemCount].price = 55;
            break;
        case 3:
            printf("You ordered a Sprite.\n");
            strcpy(items[*itemCount].name, "Sprite");
            items[*itemCount].price = 60;
            break;
        default:
            printf("Invalid option.\n");
            return;
    }
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    items[*itemCount].quantity = quantity;
    items[*itemCount].totalAmount = items[*itemCount].price * quantity;
    printf("Total %dtk.\n", items[*itemCount].totalAmount);
    (*itemCount)++;
}

void generateBill(Item items[], int itemCount, const char* customerName, const char* location, int paymentOption) {
    system("cls");
    char date[50];
    time_t now;
    struct tm *info;
    time(&now);
    info = localtime(&now);
    strftime(date, sizeof(date), "%x - %I:%M%p", info);

    printf("\n\t\t\t\t\t=================================\n");
    printf("\t\t\t\t\t|\t\tBill\t\t|\n");
    printf("\t\t\t\t\t=================================\n");
    printf(" Date&Time: %s\n", date);
    printf(" Customer Name: %s\n", customerName);
    printf(" Location: %s\n\n", location);

    printf(" Items Ordered:\n");
    printf("|----------------------------------------------------------------------|\n");
    printf(" Product\t\tPrice\t\tQuantity\tTotal\n");
    printf("|----------------------------------------------------------------------|\n\n");

    int totalAmount = 0;
    for (int i = 0; i < itemCount; i++) {
        int itemTotal = items[i].price * items[i].quantity;
        printf(" %-20s\t%4d\t\t%4d\t\t%6d\n", items[i].name, items[i].price, items[i].quantity, itemTotal);
        totalAmount += itemTotal;
    }

    printf("|----------------------------------------------------------------------|\n");
    printf(" Total Amount: \t\t\t\t\t\t%dtk\n", totalAmount);
    printf(" Platform bill: \t\t\t\t\t3tk\n");
    printf(" Vat5%: \t\t\t\t\t\t\t%.2lftk\n",totalAmount*0.05);
    double discount=totalAmount>500?totalAmount*0.10:0;
    printf(" Discount: \t\t\t\t\t\t%.2lftk\n",discount);
    printf(" Delivery charge:\t\t\t\t\t50tk\n");
    printf("|----------------------------------------------------------------------|\n");
    double grandtotal= (totalAmount+3+(totalAmount*0.05)+50)-discount;
    printf(" Grand Total: \t\t\t\t\t\t%.2lftk\n\n",grandtotal );
    printf(" Payment Method: %s\n", (paymentOption == 1) ? "Cash" : "Card");
    printf("*==============");
    printf("=========================================*\n\n");
}


void adminPanel(Item items[], int *itemCount) {
    system("cls");
    char adminPassword[50];
    printf("\n\t\t\t\t\t=================================\n");
    printf("\t\t\t\t\t|\t  ADMIN PANEL\t\t|\n");
    printf("\t\t\t\t\t=================================\n");
    printf("\nEnter Admin Password: ");
    takePassword(adminPassword);

    if (strcmp(adminPassword, ADMIN_PASSWORD) != 0) {
        printf("Incorrect Password! Access Denied.\n");
        return;
    }

    int adminOption;
    do {
        printf("\nAdmin Panel\n");
        printf("1. Add Item to Menu\n");
        printf("2. Update Item in Menu\n");
        printf("3. Remove Item from Menu\n");
        printf("4. View Menu\n");
        printf("5. Exit Admin Panel\n");
        printf("Select an option: ");
        scanf("%d", &adminOption);
        fflush(stdin);

        switch (adminOption) {
            case 1: {
                if (*itemCount >= MAX_ITEMS) {
                    printf("Menu is full. Cannot add more items.\n");
                    break;
                }

                Item newItem;
                printf("Enter name of new item: ");
                takeInput(newItem.name);
                printf("Enter price of new item: ");
                scanf("%d", &newItem.price);
                printf("Enter quantity of new item: ");
                scanf("%d", &newItem.quantity);

                items[*itemCount] = newItem;
                (*itemCount)++;
                saveItemsToFile(items, *itemCount);
                printf("Item added to menu successfully.\n");
                break;
            }
            case 2: {
                if (*itemCount == 0) {
                    printf("Menu is empty. Cannot update items.\n");
                    break;
                }

                printf("Current Menu:\n");
                for (int i = 0; i < *itemCount; i++) {
                    printf("%d. %s\n", i + 1, items[i].name);
                }

                int updateIndex;
                printf("Enter the index of item to update: ");
                scanf("%d", &updateIndex);
                updateIndex--;

                if (updateIndex < 0 || updateIndex >= *itemCount) {
                    printf("Invalid index.\n");
                    break;
                }

                printf("Enter updated name (Enter to keep unchanged): ");
                takeInput(items[updateIndex].name);
                printf("Enter updated price (Enter 0 to keep unchanged): ");
                scanf("%d", &items[updateIndex].price);
                printf("Enter updated quantity (Enter 0 to keep unchanged): ");
                scanf("%d", &items[updateIndex].quantity);

                saveItemsToFile(items, *itemCount);
                printf("Item updated successfully.\n");
                break;
            }
            case 3: {
                if (*itemCount == 0) {
                    printf("Menu is empty. Cannot remove items.\n");
                    break;
                }

                printf("Current Menu:\n");
                for (int i = 0; i < *itemCount; i++) {
                    printf("%d. %s\n", i + 1, items[i].name);
                }

                int removeIndex;
                printf("Enter the index of item to remove: ");
                scanf("%d", &removeIndex);
                removeIndex--;

                if (removeIndex < 0 || removeIndex >= *itemCount) {
                    printf("Invalid index.\n");
                    break;
                }

                for (int i = removeIndex; i < *itemCount - 1; i++) {
                    items[i] = items[i + 1];
                }
                (*itemCount)--;
                saveItemsToFile(items, *itemCount);
                printf("Item removed successfully.\n");
                break;
            }
            case 4: {
                if (*itemCount == 0) {
                    printf("Menu is empty.\n");
                } else {
                    printf("\nCurrent Menu:\n");
                    printf("--------------------------------------------------\n");
                    printf("Index\tProduct\t\tPrice\tQuantity\n");
                    printf("--------------------------------------------------\n");
                    for (int i = 0; i < *itemCount; i++) {
                        printf("%d.\t%-15s\t%4d\t%4d\n", i + 1, items[i].name, items[i].price, items[i].quantity);
                    }
                    printf("--------------------------------------------------\n");
                }
                break;
            }
            case 5:
                printf("Exiting Admin Panel.\n");
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    } while (adminOption != 5);
}
