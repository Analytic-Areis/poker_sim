# 🎰 Ultimate High-Speed Poker Simulator (C Edition)

Hey there! Welcome to my high-speed Poker Simulator written in C. 
I built this project because I find poker combinatorics fascinating, and I wanted a blazing fast way to calculate complex hand probabilities and Expected Value (EV) on the fly. 
Writing this directly in C gives a huge performance boost, easily processing millions of hands per second!

Here are some of the main things I focused on:
1. **Speed & Efficiency**: By writing it close to the metal, we can run real-time Monte Carlo simulations to find exact odds.
2. **Clean Organization**: I tried to break everything out into clear, modular parts so the code is actually fun to read.
3. **Probability & Expected Value**: Instead of just memorizing poker math, we use brute-force simulation to prove out the numbers logically.

---

## ⚡️ Key Features
- **Blazing Fast**: Evaluates millions of poker hands per second by leveraging C's array allocation speeds.
- **Modularized Structure**: Extremely human-readable split headers (`deck`, `evaluate`, `monte_carlo`).
- **Monte Carlo Validation**: Proves out exact mathematical combinations by running enough randomized trials until the variables align.
- **Expected Value (EV) Calculator**: Beautiful terminal outputs proving if an asymmetric risk is purely profitable or purely a trap.

## 🛠 How to Run it
I wrote a highly standard `Makefile` so building the simulation is completely foolproof. 
Open your terminal inside this folder and type:

```bash
make
./poker_sim
```

## 📂 Code Structure
- **`deck.c` / `deck.h`**: Handles the 52-card digital deck. It uses the `Fisher-Yates` algorithm to shuffle the digital cards. I explicitly use this because it's a famous unbiased shuffling algorithm.
- **`evaluate.c` / `evaluate.h`**: The super simple engine that scans a 5-card hand and immediately figures out what it is (Flush, Pair, etc.). I avoided complex binary bitshifting logic to ensure it's easy to read and explain.
- **`monte_carlo.c` / `monte_carlo.h`**: The simulation loops! It tallies the outcomes, computes the final Expected Values (EV) and maps them cleanly.
- **`simulator.c`**: The main terminal interface that connects everything, using colored terminal configurations!

Enjoy finding your edge! 📈 
