#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "deck.h"
#include "monte_carlo.h"

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    srand(time(NULL));
    
    printf("\n\033[1;34m====================================================\033[0m\n");
    printf("\033[1;34m      ULTIMATE HIGH-SPEED POKER SIMULATOR           \033[0m\n");
    printf("\033[1;34m====================================================\033[0m\n");
    printf("Hey there! Welcome to my custom Monte Carlo simulation engine.\n");
    printf("I built this to play around with poker odds and quickly prove out hand probabilities.\n\n");
    
    int choice;
    do {
        printf("\n\033[1mSelect a mode:\033[0m\n");
        printf("1. Simulate 2 Million Random Hands\n");
        printf("2. Calculate Expected Value (EV)\n");
        printf("3. Interactive Input Mode (Predict Hand Outcomes)\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            flush_input();
            continue;
        }
        flush_input(); // clear the newline
        
        if (choice == 1) {
            run_monte_carlo_hands(2000000);
        } else if (choice == 2) {
            calculate_expected_value(10.0, 40.0, 1000000);
        } else if (choice == 3) {
            printf("\nEnter your known cards separated by spaces (e.g., 'Ah Kd' or 'Qs Jc 9h'): ");
            char input[256];
            if (fgets(input, sizeof(input), stdin) != NULL) {
                // remove trailing newline
                input[strcspn(input, "\n")] = 0;
                
                Card known_cards[5];
                int num_known = parse_hand(input, known_cards, 5);
                
                if (num_known == 0) {
                    printf("Could not parse any valid cards. Did you format them correctly? (e.g., 'As Ks')\n");
                } else {
                    run_monte_carlo_for_hand(known_cards, num_known, 2000000);
                }
            }
        } else if (choice != 4) {
            printf("Invalid choice. Please pick 1-4.\n");
        }
        
    } while (choice != 4);
    
    printf("\n\033[1;34m====================================================\033[0m\n\n");
    return 0;
}