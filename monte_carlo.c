#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "evaluate.h"
#include "monte_carlo.h"

void run_monte_carlo_hands(int num_trials) {
    Card deck[DECK_SIZE];
    init_deck(deck);
    
    int results[HAND_TYPE_COUNT] = {0};
    
    printf("\n\033[1;36m--- 🎰 SIMULATING %d POKER HANDS ---\033[0m\n", num_trials);
    clock_t start = clock();
    
    for (int i = 0; i < num_trials; i++) {
        shuffle_deck(deck);
        
        // We implicitly evaluate the first 5 cards of the freshly shuffled deck.
        HandType type = evaluate_hand(deck);
        results[type]++;
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\033[1;32mSimulation Speed:\033[0m %.0f hands/second.\n\n", num_trials / time_spent);
    
    // Theoretical probabilities for 5-card hands out of 2,598,960 total configurations
    // I added these standard combinatorial odds here as a baseline to verify the simulation accuracy!
    double theoretical[HAND_TYPE_COUNT] = {
        1302540.0 / 2598960.0, // High Card
        1098240.0 / 2598960.0, // Pair
        123552.0  / 2598960.0, // Two Pair
        54912.0   / 2598960.0, // 3 of a Kind
        10200.0   / 2598960.0, // Straight
        5108.0    / 2598960.0, // Flush
        3744.0    / 2598960.0, // Full House
        624.0     / 2598960.0, // 4 of a Kind
        36.0      / 2598960.0, // Straight Flush
        4.0       / 2598960.0  // Royal Flush
    };
    
    printf("\033[1m%-18s | %-16s | %-16s | %s\033[0m\n", "Hand Type", "Simulated Prob", "Theoretical Prob", "Difference");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = HAND_TYPE_COUNT - 1; i >= 0; i--) { 
        double sim_prob = (double)results[i] / num_trials;
        double theo_prob = theoretical[i];
        double diff = sim_prob - theo_prob;
        printf("%-18s | %8.5f%%       | %8.5f%%       | \033[1;%dm%+8.5f%%\033[0m\n", 
               get_hand_name(i), sim_prob * 100.0, theo_prob * 100.0, 
               (diff >= 0 ? 32 : 31), diff * 100.0); 
    }
}

void calculate_expected_value(double bet_cost, double pot_size, int num_trials) {
    printf("\n\033[1;35m--- 💰 EXPECTED VALUE (EV) CALCULATION ---\033[0m\n");
    printf("Scenario: Chasing a flush draw on the River.\n");
    printf("Pot: \033[1;32m$%.2f\033[0m, Cost to Call: \033[1;31m$%.2f\033[0m\n", pot_size, bet_cost);
    
    // We have 4 cards of one suit. 9 winning cards left, 37 losing cards left (46 total unknown)
    int wins = 0;
    
    for (int i = 0; i < num_trials; i++) {
        // Fast random choice out of the 46 unknown cards
        int draw = rand() % 46;
        if (draw < 9) {
            wins++;
        }
    }
    
    double win_probability = (double)wins / num_trials;
    double lose_probability = 1.0 - win_probability;
    
    // EV = (Win Rate * Win Amount) - (Loss Rate * Loss Amount)
    double expected_value = (win_probability * pot_size) - (lose_probability * bet_cost);
    
    printf("  => Simulated Win Probability: \033[1m%.2f%%\033[0m\n", win_probability * 100.0);
    printf("  => Expected Value (EV): \033[1;%dm$%.2f per hand\033[0m\n", (expected_value > 0 ? 32 : 31), expected_value);
    
    if (expected_value > 0) {
        printf("  => \033[1;32mConclusion: PROFITABLE purely rational bet. Call!\033[0m\n");
    } else {
        printf("  => \033[1;31mConclusion: LOSING bet mathematically. Fold!\033[0m\n");
    }
}

void run_monte_carlo_for_hand(Card* known_cards, int num_known, int num_trials) {
    if (num_known < 1 || num_known > 5) {
        printf("Invalid number of known cards (must be 1-5).\n");
        return;
    }
    
    printf("\n\033[1;36m--- 🎰 PREDICTING WITH %d KNOWN CARDS ---\033[0m\n", num_known);
    printf("Known cards: ");
    for (int i = 0; i < num_known; i++) {
        print_card(&known_cards[i]);
        printf(" ");
    }
    printf("\n");
    
    Card clean_remaining_deck[DECK_SIZE];
    int remaining_count = 0;
    
    Card full_deck[DECK_SIZE];
    init_deck(full_deck);
    
    for (int j = 0; j < DECK_SIZE; j++) {
        int is_known = 0;
        for (int k = 0; k < num_known; k++) {
            if (full_deck[j].rank == known_cards[k].rank && full_deck[j].suit == known_cards[k].suit) {
                is_known = 1;
                break;
            }
        }
        if (!is_known) {
            clean_remaining_deck[remaining_count++] = full_deck[j];
        }
    }
    
    if (remaining_count != DECK_SIZE - num_known) {
        printf("Error: Invalid known cards (maybe duplicates).\n");
        return;
    }

    int results[HAND_TYPE_COUNT] = {0};
    clock_t start = clock();

    for (int i = 0; i < num_trials; i++) {
        Card test_deck[DECK_SIZE];
        for (int j = 0; j < remaining_count; j++) {
            test_deck[j] = clean_remaining_deck[j];
        }
        
        // shuffle only the remaining deck
        for (int j = remaining_count - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            Card temp = test_deck[j];
            test_deck[j] = test_deck[k];
            test_deck[k] = temp;
        }
        
        Card hand[5];
        for (int j = 0; j < num_known; j++) {
            hand[j] = known_cards[j];
        }
        for (int j = 0; j < 5 - num_known; j++) {
            hand[num_known + j] = test_deck[j];
        }
        
        HandType type = evaluate_hand(hand);
        results[type]++;
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\033[1;32mSimulation Speed:\033[0m %.0f hands/second.\n\n", num_trials / time_spent);
    
    printf("\033[1m%-18s | %-16s\033[0m\n", "Hand Type", "Simulated Prob");
    printf("--------------------------------------\n");
    
    for (int i = HAND_TYPE_COUNT - 1; i >= 0; i--) { 
        double sim_prob = (double)results[i] / num_trials;
        double display_prob = sim_prob * 100.0;
        if (display_prob > 0.0 || i == HIGH_CARD) { // Always show high card or anything that hit
            printf("%-18s | %8.5f%%\n", get_hand_name(i), display_prob); 
        }
    }
}
