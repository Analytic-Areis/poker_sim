#ifndef DECK_H
#define DECK_H

#define DECK_SIZE 52

typedef enum {
    HEARTS, DIAMONDS, CLUBS, SPADES
} Suit;

typedef struct {
    int rank; // 2-14 (14 is Ace)
    Suit suit;
} Card;

void init_deck(Card *deck);
void shuffle_deck(Card *deck);

int parse_card(const char* str, Card* card);
int parse_hand(const char* str, Card* hand, int max_cards);
void print_card(const Card* card);

#endif
