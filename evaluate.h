#ifndef EVALUATE_H
#define EVALUATE_H

#include "deck.h"

typedef enum {
    HIGH_CARD, PAIR, TWO_PAIR, THREE_OF_A_KIND,
    STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND,
    STRAIGHT_FLUSH, ROYAL_FLUSH, HAND_TYPE_COUNT
} HandType;

HandType evaluate_hand(Card *hand);
const char* get_hand_name(HandType type);

#endif
