#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "deck.h"

// Fills an empty deck array with the 52 standard cards
void init_deck(Card *deck) {
    int index = 0;
    for (int suit = HEARTS; suit <= SPADES; suit++) {
        for (int rank = 2; rank <= 14; rank++) {
            deck[index].rank = rank;
            deck[index].suit = suit;
            index++;
        }
    }
}

// Fisher-Yates shuffle algorithm: beautifully simple and mathematically unbiased
void shuffle_deck(Card *deck) {
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

int parse_card(const char* str, Card* card) {
    if (str == NULL || strlen(str) < 2) return 0;
    
    char rank_char = toupper(str[0]);
    char suit_char = tolower(str[1]);
    
    if (rank_char == '1' && str[1] == '0' && strlen(str) >= 3) {
        card->rank = 10;
        suit_char = tolower(str[2]);
    } else {
        switch (rank_char) {
            case '2': card->rank = 2; break;
            case '3': card->rank = 3; break;
            case '4': card->rank = 4; break;
            case '5': card->rank = 5; break;
            case '6': card->rank = 6; break;
            case '7': card->rank = 7; break;
            case '8': card->rank = 8; break;
            case '9': card->rank = 9; break;
            case 'T': card->rank = 10; break;
            case 'J': card->rank = 11; break;
            case 'Q': card->rank = 12; break;
            case 'K': card->rank = 13; break;
            case 'A': card->rank = 14; break;
            default: return 0;
        }
    }
    
    switch (suit_char) {
        case 'H': case 'h': card->suit = HEARTS; break;
        case 'D': case 'd': card->suit = DIAMONDS; break;
        case 'C': case 'c': card->suit = CLUBS; break;
        case 'S': case 's': card->suit = SPADES; break;
        default: return 0;
    }
    
    return 1;
}

int parse_hand(const char* str, Card* hand, int max_cards) {
    int count = 0;
    char buffer[256];
    strncpy(buffer, str, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    char* token = strtok(buffer, " \t\n");
    while (token != NULL && count < max_cards) {
        if (parse_card(token, &hand[count])) {
            count++;
        }
        token = strtok(NULL, " \t\n");
    }
    return count;
}

void print_card(const Card* card) {
    char r;
    if (card->rank >= 2 && card->rank <= 9) r = '0' + card->rank;
    else if (card->rank == 10) r = 'T';
    else if (card->rank == 11) r = 'J';
    else if (card->rank == 12) r = 'Q';
    else if (card->rank == 13) r = 'K';
    else if (card->rank == 14) r = 'A';
    else r = '?';
    
    char s;
    switch (card->suit) {
        case HEARTS: s = 'h'; break;
        case DIAMONDS: s = 'd'; break;
        case CLUBS: s = 'c'; break;
        case SPADES: s = 's'; break;
        default: s = '?';
    }
    printf("%c%c", r, s);
}
