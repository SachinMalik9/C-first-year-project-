#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Product Structure (NOW WITH STOCK)
typedef struct {
    char name[50];
    int price;
    int stock;
} Item;

// Luhn Algorithm for card validation
int get_card_type(long long num) {
    long long n = num;
    int evenSum = 0, oddSum = 0;
    int pos = 1, digits = 0;

    while (n > 0) {
        int d = n % 10;
        if (pos % 2 == 0) {
            int x = d * 2;
            evenSum += (x / 10) + (x % 10);
        } else {
            oddSum += d;
        }
        n /= 10;
        pos++;
        digits++;
    }

    if ((evenSum + oddSum) % 10 != 0)
        return 0;

    long long prefix = num;
    while (prefix >= 100)
        prefix /= 10;

    long long first = prefix / 10;

    if ((prefix == 34 || prefix == 37) && digits == 15) return 1;
    if ((prefix >= 51 && prefix <= 55) && digits == 16) return 2;
    if (first == 4 && (digits == 13 || digits == 16)) return 3;
    if ((prefix == 60 || prefix == 65) && digits == 16) return 4;

    return 0;
}

int main() {

    // ENTRY SCREEN
    printf("=====================================\n");
    printf("           STUDENT DETAILS           \n");
    printf("=====================================\n");
    printf("Name          : Sachin Kumar\n");
    printf("SAP ID        : 590025633\n");
    printf("Batch         : 10\n");
    printf("Faculty Name  : Prof. Pankaj Bhadoni\n");
    printf("=====================================\n");
    printf("Press ENTER to continue...\n");
    getchar();

    // INVENTORY (new stock added)
    Item store[3] = {
        {"Gaming Laptop", 80000, 10},
        {"Mechanical Keyboard", 5000, 20},
        {"Wireless Mouse", 2000, 50}
    };

    char again = 'y';

    while (again == 'y' || again == 'Y') {

        char name[50];
        int total = 0;

        // NAME INPUT
        while (1) {
            printf("\nEnter your name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            if (strlen(name) == 0) {
                printf("Invalid case. Blank name not allowed.\n");
                continue;
            }

            int valid = 1;
            for (int i = 0; name[i]; i++) {
                if (!isalpha(name[i])) valid = 0;
            }

            if (!valid) {
                printf("Invalid case. Name should have only letters.\n");
                continue;
            }

            break;
        }

        printf("\nWelcome %s, let's start your shopping.\n", name);

        char more = 'y';

        while (more == 'y' || more == 'Y') {

            // DISPLAY INVENTORY
            printf("\nAvailable Products:\n");

            for (int i = 0; i < 3; i++) {
                if (store[i].stock == 0)
                    printf("%d. %s - Rs. %d (OUT OF STOCK)\n", i + 1, store[i].name, store[i].price);
                else
                    printf("%d. %s - Rs. %d (Available: %d)\n",
                           i + 1, store[i].name, store[i].price, store[i].stock);
            }

            char choiceStr[20];
            int choice;

            // PRODUCT CHOICE INPUT
            while (1) {
                printf("\nChoose product (1-3): ");
                fgets(choiceStr, sizeof(choiceStr), stdin);
                choiceStr[strcspn(choiceStr, "\n")] = '\0';

                if (strlen(choiceStr) == 0) {
                    printf("Invalid case. Blank input not allowed.\n");
                    continue;
                }

                int valid = 1;
                for (int i = 0; choiceStr[i]; i++) {
                    if (!isdigit(choiceStr[i])) valid = 0;
                }

                if (!valid) {
                    printf("Invalid case. Only digits allowed.\n");
                    continue;
                }

                choice = atoi(choiceStr);

                if (choice >= 1 && choice <= 3) {

                    // Check if product is out of stock
                    if (store[choice - 1].stock == 0) {
                        printf("This product is OUT OF STOCK. Choose another item.\n");
                        continue;
                    }

                    break;
                }

                printf("Invalid choice. Please pick 1, 2, or 3.\n");
            }

            // QUANTITY INPUT WITH INVENTORY CHECK
            char qtyStr[20];
            int qty;

            while (1) {
                printf("Enter quantity: ");
                fgets(qtyStr, sizeof(qtyStr), stdin);
                qtyStr[strcspn(qtyStr, "\n")] = '\0';

                if (strlen(qtyStr) == 0) {
                    printf("Invalid case. Blank quantity not allowed.\n");
                    continue;
                }

                int valid = 1;
                for (int i = 0; qtyStr[i]; i++) {
                    if (!isdigit(qtyStr[i])) valid = 0;
                }

                if (!valid) {
                    printf("Invalid case. Only digits allowed.\n");
                    continue;
                }

                qty = atoi(qtyStr);

                if (qty <= 0) {
                    printf("Invalid input. Quantity must be greater than zero.\n");
                    continue;
                }

                if (qty > store[choice - 1].stock) {
                    printf("Invalid input. Only %d pieces available.\n",
                           store[choice - 1].stock);
                    continue;
                }

                break;
            }

            // UPDATE TOTAL AND INVENTORY
            total += store[choice - 1].price * qty;
            store[choice - 1].stock -= qty;

            printf("%d x %s added to cart.\n",
                   qty, store[choice - 1].name);

            // Add more items?
            while (1) {
                printf("Add more items? (y/n): ");
                scanf(" %c", &more);
                getchar();

                if (more == 'y' || more == 'Y' || more == 'n' || more == 'N')
                    break;

                printf("Invalid case. Please enter only y or n.\n");
            }
        }

        printf("\nYour total before discount is: Rs. %d\n", total);

        // CARD VALIDATION
        int tries = 5;
        int cardType = 0;
        long long cardNum;
        char cardStr[50];

        while (tries > 0) {

            printf("\nEnter card number: ");
            fgets(cardStr, sizeof(cardStr), stdin);
            cardStr[strcspn(cardStr, "\n")] = '\0';

            if (strlen(cardStr) == 0) {
                printf("Invalid case. Blank card number not allowed.\n");
                tries--;
                printf("Attempts left: %d\n", tries);
                continue;
            }

            int valid = 1;
            for (int i = 0; cardStr[i]; i++) {
                if (!isdigit(cardStr[i])) valid = 0;
            }

            if (!valid) {
                printf("Invalid case. Card must contain only digits.\n");
                tries--;
                printf("Attempts left: %d\n", tries);
                continue;
            }

            cardNum = atoll(cardStr);

            printf("Checking card...\n");
            cardType = get_card_type(cardNum);

            if (cardType != 0) break;

            tries--;
            printf("Invalid card number. Attempts left: %d\n", tries);
        }

        if (cardType == 0) {
            printf("\nYour card has been blocked due to invalid attempts.\n");
        } 
        else {

            // DISCOUNT
            if (cardType == 1) total = total * 0.80;
            if (cardType == 4) total = total * 0.85;
            if (cardType == 2 || cardType == 3) total = total * 0.95;

            printf("\nFinal amount after discount: Rs. %d\n", total);

            // ===== TERMINAL RECEIPT =====
            printf("\n------------------------------\n");
            printf("        TECH STORE RECEIPT     \n");
            printf("------------------------------\n");
            printf("Customer Name : %s\n", name);
            printf("Final Amount  : Rs. %d\n", total);

            if (cardType == 1) printf("Payment Method: AMEX\n");
            else if (cardType == 2) printf("Payment Method: MasterCard\n");
            else if (cardType == 3) printf("Payment Method: VISA\n");
            else if (cardType == 4) printf("Payment Method: RuPay\n");

            printf("------------------------------\n");
            printf("Thank you for shopping!\n");
            printf("------------------------------\n");

            // SAVE RECEIPT?
            char wantReceipt;

            while (1) {
                printf("\nDo you want a receipt saved? (y/n): ");
                scanf(" %c", &wantReceipt);
                getchar();

                if (wantReceipt == 'y' || wantReceipt == 'Y' ||
                    wantReceipt == 'n' || wantReceipt == 'N')
                    break;

                printf("Invalid case. Please enter only y or n.\n");
            }

            if (wantReceipt == 'y' || wantReceipt == 'Y') {
                FILE *f = fopen("receipts.txt", "a");
                if (f) {
                    fprintf(f, "Customer: %s | Paid: %d\n", name, total);
                    fclose(f);
                    printf("Receipt saved successfully.\n");
                }
            }
        }

        // SHOP AGAIN?
        while (1) {
            printf("\nDo you want to shop again? (y/n): ");
            scanf(" %c", &again);
            getchar();

            if (again == 'y' || again == 'Y' || again == 'n' || again == 'N')
                break;

            printf("Invalid case. Please enter only y or n.\n");
        }
    }

    printf("\nThank you for visiting the Tech Store!\n");
    return 0;
}
