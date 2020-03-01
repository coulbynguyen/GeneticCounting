#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <bits/stdc++.h>
#include <omp.h>
#include "gambler.h"
#include <vector>
using namespace std;


int comparehands(int player_total, int banker_total){

    //0 represents that a player has won
    if(player_total > banker_total){
        // cout << player_total << " > " << banker_total << endl;
        return 0;

    }
    //1 represents that a banker has won
    else if(player_total < banker_total){
        // cout << player_total << " < " << banker_total << endl;
        return 1;
    }
    //this represents that a tie has occured and should be considered a player win since banker charges a 5% tax
    //changed my mind. 2 represents that a tie has occured
    else{
        // cout << player_total << " = " << banker_total << endl;
        return 2;
    }
}

int playhand(int &top_of_deck, int shoe[], int card_count[], int &num_player_cards_drawn, int &num_banker_cards_drawn, int player_cards[], int banker_cards[]){
    //this value doesn't need to be initialized
    //as its value will always be set when drawn
    int third_card_value;
    int player_total = 0;
    int banker_total = 0;

    num_player_cards_drawn = 0;
    num_banker_cards_drawn = 0;

    //Both players draw their first card
    player_total += shoe[top_of_deck];
    player_cards[num_player_cards_drawn] = shoe[top_of_deck];
    num_player_cards_drawn++;
    // getcount(shoe[top_of_deck], card_count);
    top_of_deck++;

    banker_total += shoe[top_of_deck];
    banker_cards[num_banker_cards_drawn] = shoe[top_of_deck];
    num_banker_cards_drawn++;
    // getcount(shoe[top_of_deck], card_count);
    top_of_deck++;

    //Both players draw their second card
    player_total += shoe[top_of_deck];
    player_cards[num_player_cards_drawn] = shoe[top_of_deck];
    num_player_cards_drawn++;
    // getcount(shoe[top_of_deck], card_count);
    top_of_deck++;

    banker_total += shoe[top_of_deck];
    banker_cards[num_banker_cards_drawn] = shoe[top_of_deck];
    num_banker_cards_drawn++;
    // getcount(shoe[top_of_deck], card_count);
    top_of_deck++;

    //in baccarat you only care abou the right digit
    player_total = player_total%10;
    banker_total = banker_total%10;

    //since 4 cards have been drawn the top of deck has been moved by plus 4

    //If either player has a 8 or 9 then they have a natural and it is over
    if(player_total == 8 || player_total == 9 || banker_total == 8 || banker_total == 9){
        //no need for a third card for either hand and the hands need to be compared
        //no need to mod 10 here because there was no change in card totals
        return comparehands(player_total, banker_total);
    }

    //player does not draw a card when their total is 6 or 7
    if(player_total > 5){
        //banker does not draw for 6 or 7 when the player stands with 6 or 7
        if(banker_total > 5){
            //no need for a third card for either hand and the cards need to be compared
            //no need to mod 10 here because there was no change in card totals
            return comparehands(player_total, banker_total);
        }
        else{
            //since we already incremented top_of_deck before here
            //we simply just need to take the card off the top
            banker_total += shoe[top_of_deck];
            banker_cards[num_banker_cards_drawn] = shoe[top_of_deck];
            num_banker_cards_drawn++;
            //and increment it for the number of cards drawn which will be 1
            // getcount(shoe[top_of_deck], card_count);
            top_of_deck += 1;
            //here we need to get the new total because it could have exceeded 10 and we only care about the right digit
            banker_total = banker_total%10;
            //then once the final totals are added and modded it is sent to see who won that hand
            return comparehands(player_total, banker_total);
        }
    }
    //if the players first two cards add up and mod 10 below 5 then they must draw another card
    else{

        //since we already incremented top_of_deck before here
        //we simply just need to take the card off the top
        player_total += shoe[top_of_deck];
        player_cards[num_player_cards_drawn] = shoe[top_of_deck];
        num_player_cards_drawn++;
        third_card_value = shoe[top_of_deck];
        //and increment it for the number of cards drawn which will be 1
        // getcount(shoe[top_of_deck], card_count);
        top_of_deck += 1;
        //here we need to get the new total because it could have exceeded 10 and we only care about the right digit
        player_total = player_total%10;

        //however the banker can draw a third card based one what they currently have AND the third card drawn by player

        //The banker will never draw a card when their total is 7 and a third card is drawn by the player
        if(banker_total == 7){
            //we don't need to recalculate the banker_total or draw a card
            //so we just compare hands
            return comparehands(player_total, banker_total);
        }
        //if the banker hand totals to 6 with the first 2 cards, then they might have to draw
        else if(banker_total == 6){
            //if the third card value is either 6 or 7 then the banker needs to draw
            if(third_card_value == 6 || third_card_value == 7){
                //since we already incremented top_of_deck before here
                //we simply just need to take the card off the top
                banker_total += shoe[top_of_deck];
                banker_cards[num_banker_cards_drawn] = shoe[top_of_deck];
                num_banker_cards_drawn++;
                //and increment it for the number of cards drawn which will be 1
                // getcount(shoe[top_of_deck], card_count);
                top_of_deck += 1;
                //here we need to get the new total because it could have exceeded 10 and we only care about the right digit
                banker_total = banker_total%10;
                //now the totals are tallied and there will not be a card drawn for either hands
                //so they just need to compare hands and determine a winner
                return comparehands(player_total, banker_total);
            }
            else{
                //since the third card wasn't a 6 or 7 then the banker doesn't need to draw and the hands
                //just need to be compared
                return comparehands(player_total, banker_total);
            }

        }
        //if the banker hand totals to 5 with the first 2 cards then they might have to draw
        else if(banker_total == 5){
            //if the third card value is either 4,5,6,or 7 then the banker has to draw
            if(third_card_value == 4 || third_card_value == 5 || third_card_value == 6 || third_card_value == 7){
                //since we already incremented top_of_deck before here
                //we simply just need to take the card off the top
                banker_total += shoe[top_of_deck];
                banker_cards[num_banker_cards_drawn] = shoe[top_of_deck];
                num_banker_cards_drawn++;
                //and increment it for the number of cards drawn which will be 1
                // getcount(shoe[top_of_deck], card_count);
                top_of_deck += 1;
                //here we need to get the new total because it could have exceeded 10 and we only care about the right digit
                banker_total = banker_total%10;
                //now the totals are tallied and there will not be a card drawn for either hands
                //so they just need to compare hands and determine a winner
                return comparehands(player_total, banker_total);
            }
            else{
                //since the third card wasn't a 4,5,6 or 7 then the banker doesn't need to draw and the hands
                //just need to be compared
                return comparehands(player_total, banker_total);
            }

        }
        // if the banker hand totals to 4, with the first 2 cards then they might have to draw
        else if(banker_total == 4){
            //if the third card value is either 2,3,4,5,6, or 7 then the banker has to draw
            if(third_card_value == 2 || third_card_value == 3 || third_card_value == 4 || third_card_value == 5 || third_card_value == 6 || third_card_value == 7){
                //since we already incremented top_of_deck before here
                //we simply just need to take the card off the top
                banker_total += shoe[top_of_deck];
                banker_cards[num_banker_cards_drawn] = shoe[top_of_deck];
                num_banker_cards_drawn++;
                //and increment it for the number of cards drawn which will be 1
                // getcount(shoe[top_of_deck], card_count);
                top_of_deck += 1;
                //here we need to get the new total because it could have exceeded 10 and we only care about the right digit
                banker_total = banker_total%10;
                //now the totals are tallied and there will not be a card drawn for either hands
                //so they just need to compare hands and determine a winner
                return comparehands(player_total, banker_total);
            }
            else{
                //since the third card wasn't a 2,3,4,5,6 or 7 then the banker doesn't need to draw and the hands
                //just need to be compared
                return comparehands(player_total, banker_total);
            }

        }
        //if the banker hand totals to 3 in the first 2 cards they might have to draw
        else if(banker_total == 3){
            //the banker does not draw when the third card for the player is an 8
            if(third_card_value != 8){
                //since we already incremented top_of_deck before here
                //we simply just need to take the card off the top
                banker_total += shoe[top_of_deck];
                banker_cards[num_banker_cards_drawn] = shoe[top_of_deck];
                num_banker_cards_drawn++;
                //and increment it for the number of cards drawn which will be 1
                // getcount(shoe[top_of_deck], card_count);
                top_of_deck += 1;
                //here we need to get the new total because it could have exceeded 10 and we only care about the right digit
                banker_total = banker_total%10;
                //now the totals are tallied and there will not be a card drawn for either hands
                //so they just need to compare hands and determine a winner
                return comparehands(player_total, banker_total);
            }
            else{
                //since the third card was an 8 then the banker doesn't need to draw and the hands
                //just need to be compared
                return comparehands(player_total, banker_total);
            }
        }
        //if the bankers first 2 card totals are either 0,1,2 then the banker HAS TO DRAW regardless of what the third card was
        else{
            //since we already incremented top_of_deck before here
            //we simply just need to take the card off the top
            banker_total += shoe[top_of_deck];
            banker_cards[num_banker_cards_drawn] = shoe[top_of_deck];
            num_banker_cards_drawn++;
            //and increment it for the number of cards drawn which will be 1
            // getcount(shoe[top_of_deck], card_count);
            top_of_deck += 1;
            //here we need to get the new total because it could have exceeded 10 and we only care about the right digit
            banker_total = banker_total%10;
            //now the totals are tallied and there will not be a card drawn for either hands
            //so they just need to compare hands and determine a winner
            return comparehands(player_total, banker_total);

        }
    }

}

int sumofarray(int *myarray, int size, int type){
    int total = 0;
    for(int i = 0; i < size; i++){
        if(myarray[i] == type){
            total += 1;
        }
    }
    return total;
}

bool tumsort(gambler a, gambler b){
  return a.get_average_over_10_shoes() > b.get_average_over_10_shoes();
}

int main(){
    ifstream deck_file[10];
    deck_file[0].open("deck_file0");
    deck_file[1].open("deck_file1");
    deck_file[2].open("deck_file2");
    deck_file[3].open("deck_file3");
    deck_file[4].open("deck_file4");
    deck_file[5].open("deck_file5");
    deck_file[6].open("deck_file6");
    deck_file[7].open("deck_file7");
    deck_file[8].open("deck_file8");
    deck_file[9].open("deck_file9");


    vector<gambler> my_gamblers;
    for(int i = 0; i < 16; i++){
      gambler temp_gambler(i);
      my_gamblers.push_back(temp_gambler);
    }
    for(int iloop = 0; iloop < 10; iloop++){
      for(int i = 0; i < 16; i++){
        my_gamblers[i].reset_count();
        my_gamblers[i].reset_money();
      }

      srand(time(NULL));


      int *cards_in_deck = new int[10];
      for(int i = 0; i < 10; i++){
        cards_in_deck[i] = 0;
      }
      // cards_in_deck[0] = 128;
      int *shoe = new int[416];

      int red_card;
      int top_of_deck;
      int card_count[10] = {0};

      int num_banker_cards_drawn = 0;
      int num_player_cards_drawn = 0;
      int banker_cards[3];
      int player_cards[3];


      //Get the shoe information from the deck file
      for(int i = 0; i < 416; i++){
          deck_file[iloop] >> shoe[i];
      }

      //Randomize when the red card will occur it should occur around one deck from the end of the game
      red_card = rand()%52+52;

      //The way casinos work is that they reveal the very first card and burn that many cards AND the card drawn
      if(shoe[0] == 0){
        top_of_deck = 11;
      }
      else{
        top_of_deck = shoe[0] + 1;
      }
      for(int i = 0; i < 16; i++){
        my_gamblers[i].adjust_count(shoe[0]);
      }
      cards_in_deck[shoe[0]]++;
      // int count = 0;

      while(top_of_deck < 416-red_card){

          for(int i = 0; i < 16; i++){
            my_gamblers[i].choose_bet(float(416-top_of_deck));
          }
          int result = playhand(top_of_deck, shoe, card_count, num_player_cards_drawn, num_banker_cards_drawn, player_cards, banker_cards);
          // if(result != 2){
          //   for(int i = 0; i < 10; i++){
          //     arr_train[loop] << cards_in_deck[i] << " ";
          //   }
          //   arr_train[loop] << result << endl;
          // }
          for(int i = 0; i < num_player_cards_drawn; i++){
            cards_in_deck[player_cards[i]]++;
          }
          for(int i = 0; i < num_banker_cards_drawn; i++){
            cards_in_deck[banker_cards[i]]++;
          }
          for(int i = 0; i < 16; i++){
            my_gamblers[i].adjust_count(num_banker_cards_drawn, banker_cards, num_player_cards_drawn, player_cards);
            my_gamblers[i].payout(result);
          }


      }
      // cout << "********************" << endl;
      for(int i = 0; i < 16; i++){
        // cout << my_gamblers[i].moneyleft << endl;
        my_gamblers[i].add_to_total_10_shoes();
      }

    }
  // cout << "===============" << endl;
  // for(int i = 0; i < 16; i++){
  //   cout << my_gamblers[i].get_average_over_10_shoes() << endl;
  // }
  // }
  sort(my_gamblers.begin(), my_gamblers.end(), tumsort);
  cout << "#################" << endl;
  for(int i = 0; i < 16; i++){
    cout << my_gamblers[i].get_average_over_10_shoes() << endl;
  }
  int file_counter = 0;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(i != j){
        my_gamblers[i].crossbreed(my_gamblers[j], file_counter);
        file_counter++;
      }
    }
  }
  my_gamblers[0].carryover(12);
  my_gamblers[1].carryover(13);
  my_gamblers[2].carryover(14);
  my_gamblers[3].carryover(15);
  return 0;
}
