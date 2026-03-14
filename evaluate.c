#include "evaluate.h"

// A simple and intuitive evaluator array approach without getting bogged down in bitwise math
HandType evaluate_hand(Card *hand) {
    int rank_counts[15] = {0}; // Track counts of ranks 2 through 14
    int suit_counts[4] = {0};  // Track counts of the 4 suits
    
    for (int i = 0; i < 5; i++) {
        rank_counts[hand[i].rank]++;
        suit_counts[hand[i].suit]++;
    }
    
    int is_flush = 0;
    for (int i = 0; i < 4; i++) {
        if (suit_counts[i] == 5) {
            is_flush = 1;
            break;
        }
    }
    
    int consecutive = 0;
    int is_straight = 0;
    int high_straight_rank = 0;
    
    for (int i = 2; i <= 14; i++) {
        if (rank_counts[i] == 1) {
            consecutive++;
            if (consecutive == 5) {
                is_straight = 1;
                high_straight_rank = i;
            }
        } else {
            consecutive = 0; // Break consecutive streak
        }
    }
    
    // Check for "Wheel" straight: Ace, 2, 3, 4, 5
    if (rank_counts[14] == 1 && rank_counts[2] == 1 && rank_counts[3] == 1 && 
        rank_counts[4] == 1 && rank_counts[5] == 1) {
        is_straight = 1;
        high_straight_rank = 5;
    }
    
    int pairs = 0, three_of_a_kind = 0, four_of_a_kind = 0;
    for (int i = 2; i <= 14; i++) {
        if (rank_counts[i] == 2) pairs++;
        else if (rank_counts[i] == 3) three_of_a_kind++;
        else if (rank_counts[i] == 4) four_of_a_kind++;
    }
    
    // Determine strongest hand type first (Top-Down execution flow)
    if (is_straight && is_flush) {
        if (high_straight_rank == 14) return ROYAL_FLUSH;
        else return STRAIGHT_FLUSH;
    }
    if (four_of_a_kind) return FOUR_OF_A_KIND;
    if (three_of_a_kind && pairs == 1) return FULL_HOUSE;
    if (is_flush) return FLUSH;
    if (is_straight) return STRAIGHT;
    if (three_of_a_kind) return THREE_OF_A_KIND;
    if (pairs == 2) return TWO_PAIR;
    if (pairs == 1) return PAIR;
    
    return HIGH_CARD;
}

const char* get_hand_name(HandType type) {
    switch (type) {
        case HIGH_CARD: return "High Card";
        case PAIR: return "Pair";
        case TWO_PAIR: return "Two Pair";
        case THREE_OF_A_KIND: return "Three of a Kind";
        case STRAIGHT: return "Straight";
        case FLUSH: return "Flush";
        case FULL_HOUSE: return "Full House";
        case FOUR_OF_A_KIND: return "Four of a Kind";
        case STRAIGHT_FLUSH: return "Straight Flush";
        case ROYAL_FLUSH: return "Royal Flush";
        default: return "Unknown";
    }
}
