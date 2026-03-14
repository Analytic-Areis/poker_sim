#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

void run_monte_carlo_hands(int num_trials);
void calculate_expected_value(double bet_cost, double pot_size, int num_trials);
void run_monte_carlo_for_hand(Card* known_cards, int num_known, int num_trials);

#endif
