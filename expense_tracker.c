#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPENSES 100

// Function declarations
void addExpense();
void viewExpenses();
void calculateSummary();
void clearExpenses();

int main() {
    int choice;

    do {
        printf("\n===========  EXPENSE TRACKER SYSTEM  ===========\n");
        printf("1. Add New Expense\n");
        printf("2. View All Expenses\n");
        printf("3. View Expense Summary (Total, Average, Highest, Lowest)\n");
        printf("4. Clear All Expenses\n");
        printf("5. Exit\n");
        printf("====================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                calculateSummary();
                break;
            case 4:
                clearExpenses();
                break;
            case 5:
                printf("\n Exiting Expense Tracker. Thank you!\n");
                break;
            default:
                printf("\n Invalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}

//------------------------------------------------------
// Function to add an expense and save it to file
//------------------------------------------------------
void addExpense() {
    FILE *fp;
    float amount;
    char category[30];

    fp = fopen("expenses.txt", "a");  // append mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter expense amount (₹): ");
    scanf("%f", &amount);
    printf("Enter category (e.g., Food, Travel, Bills): ");
    scanf("%s", category);

    fprintf(fp, "%.2f %s\n", amount, category);
    fclose(fp);

    printf(" Expense added successfully!\n");
}

//------------------------------------------------------
// Function to view all expenses from file
//------------------------------------------------------
void viewExpenses() {
    FILE *fp;
    float amount;
    char category[30];
    int count = 0;

    fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("\n No expenses recorded yet.\n");
        return;
    }

    printf("\n-------------  Expense Records -------------\n");
    printf("%-10s %-15s\n", "Amount(₹)", "Category");
    printf("---------------------------------------------\n");

    while (fscanf(fp, "%f %s", &amount, category) != EOF) {
        printf("%-10.2f %-15s\n", amount, category);
        count++;
    }

    if (count == 0)
        printf("No data available.\n");

    fclose(fp);
}

//------------------------------------------------------
// Function to calculate total, average, max, and min
//------------------------------------------------------
void calculateSummary() {
    FILE *fp;
    float expenses[MAX_EXPENSES];
    char category[30];
    int count = 0;
    float total = 0, avg, max, min;

    fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("\n No data available to calculate summary.\n");
        return;
    }

    // Read data into array
    while (fscanf(fp, "%f %s", &expenses[count], category) != EOF && count < MAX_EXPENSES)
        count++;

    fclose(fp);

    if (count == 0) {
        printf("\n No data found.\n");
        return;
    }

    // Calculate total, average, max, min
    total = 0;
    max = min = expenses[0];
    for (int i = 0; i < count; i++) {
        total += expenses[i];
        if (expenses[i] > max) max = expenses[i];
        if (expenses[i] < min) min = expenses[i];
    }
    avg = total / count;

    printf("\n-----------  Expense Summary -----------\n");
    printf("Total Expenses   : ₹%.2f\n", total);
    printf("Average Expense  : ₹%.2f\n", avg);
    printf("Highest Expense  : ₹%.2f\n", max);
    printf("Lowest Expense   : ₹%.2f\n", min);
    printf("------------------------------------------\n");
}

//------------------------------------------------------
// Function to clear all records
//------------------------------------------------------
void clearExpenses() {
    FILE *fp = fopen("expenses.txt", "w"); // overwrite file
    if (fp == NULL) {
        printf("Error clearing file!\n");
        return;
    }
    fclose(fp);
    printf("\n All expense records cleared successfully!\n");
}