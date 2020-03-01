#include <iostream>
#include <string>
#include "gambler.h"
#include <fstream>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

gambler::gambler(int file_num){
  //read in values of counts given a file name
  ifstream genetics;
  string file_name = "gambler" + to_string(file_num) + ".txt";
  genetics.open(file_name);
  for(int i = 0; i < 10; i++){
    genetics >> mycounts[i];
  }
  current_count = 0;
  bet_amount = 100;
  bet_choice = -1;
  moneyleft = 5000.0;
  total_money_over_10_shoes = 0.0;
  genetics.close();
}

void gambler::reset_money(){
  moneyleft = 5000.0;
}

void gambler::reset_count(){
  current_count = 0;
}

int gambler::choose_bet(float cards_left){
  if(moneyleft - bet_amount < 0){
    bet_amount = moneyleft;
  }
  //if the true count is above 0 bet banker
  if(((float)current_count)/(cards_left/52.0) > 0){
    bet_choice = 1;
  }
  //if the true count is below -0 bet player
  else if(((float)current_count)/(cards_left/52.0) < 0){
    bet_choice = 0;
  }
  else{
    bet_choice = -1;
    //moneyleft -= 7.5;
  }
  return bet_choice;
}

void gambler::payout(int winner){
  if(bet_choice == winner){
    if(winner == 1){
      moneyleft += 0.95 * bet_amount;
    }
    else if(winner == 0){
      moneyleft += bet_amount;
    }
  }
  else if(winner == 2){
    moneyleft += 0;
  }
  else{
    if(moneyleft - bet_amount <= 0){
        moneyleft = 0;
    }
    else{
        moneyleft -= bet_amount;
    }
  }
}

void gambler::add_to_total_10_shoes(){
  total_money_over_10_shoes += moneyleft;
}

float gambler::get_average_over_10_shoes(){
  return total_money_over_10_shoes/10;
}

void gambler::adjust_count(int card){
  current_count += mycounts[card];
}

void gambler::adjust_count(int num_banker_cards_drawn, int banker_cards[], int num_player_cards_drawn, int player_cards[]){
  for(int i = 0; i < num_banker_cards_drawn; i++){
    current_count += mycounts[banker_cards[i]];
  }
  for(int i = 0; i < num_player_cards_drawn; i++){
    current_count += mycounts[player_cards[i]];
  }
}

void gambler::crossbreed(gambler bottom, int file_num){
  int newbreed[10];
  vector<int> positions;
  //srand(time(NULL));

  for(int i = 0; i < 5; i++){
    newbreed[i] = mycounts[i];
  }
  for(int i = 5; i < 10; i++){
    newbreed[i] = bottom.mycounts[i];
  }
  while(positions.size() != 4){
    int mutation_pos = rand()%10;
    if(find(positions.begin(), positions.end(), mutation_pos) == positions.end()){
      positions.push_back(mutation_pos);
    }
  }
  sort(positions.begin(), positions.end());
  for(int i = 0; i < positions.size(); i++){
    int mutated_val = newbreed[positions[i]];
    if(rand()%2 == 0){
        mutated_val = rand()%500+1;
    }
    else{
      mutated_val = -rand()%500-1;
    }
    newbreed[positions[i]] = mutated_val;
  }
  ofstream output_mutation;
  string file_name = "gambler" + to_string(file_num) + ".txt";
  output_mutation.open(file_name);
  for(int i = 0; i < 10; i++){
    output_mutation << newbreed[i] << endl;
  }
}

void gambler::carryover(int file_num){
  ofstream output_parent;
  string file_name = "gambler" + to_string(file_num) + ".txt";
  output_parent.open(file_name);
  for(int i = 0; i < 10; i++){
    output_parent << mycounts[i] << endl;
  }
}
