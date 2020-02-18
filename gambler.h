#include <iostream>
#include <string>

using namespace std;

#ifndef GAMBLER
#define GAMBLER

class gambler{
  public:
    int mycounts[10];
    int current_count;
    int bet_amount;
    int bet_choice;
    float moneyleft;
    float total_money_over_10_shoes;

    gambler(int);
    void reset_money();
    void reset_count();
    int choose_bet();
    void payout(int);
    void add_to_total_10_shoes();
    float get_average_over_10_shoes();
    void adjust_count(int);
    void adjust_count(int, int[], int, int[]);
    void crossbreed(gambler, int);
    void carryover(int);


};

#endif
