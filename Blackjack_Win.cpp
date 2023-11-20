#include <iostream>  
#include <random>
#include <windows.h>
#include <vector>

bool stand = false;

int playerPoints, dealerPoints;

std::vector<int> player;
std::vector<int> dealer;

std::string cardP1, cardP2, cardP3, cardP4, cardP5, cardP6, carda = " _____  |A .  || /.\\ ||(_._)||  |  ||____A|", card2 = " _____  |2    ||  ^  ||     ||  ^  ||___ 2|", card3 = " _____  |3    || ^ ^ ||     ||  ^  ||___ 3|", card4 = " _____  |4    || ^ ^ ||     || ^ ^ ||____4|", card5 = " _____  |5    || ^ ^ ||  ^  || ^ ^ ||____5|", card6 = " _____  |6    || ^ ^ || ^ ^ || ^ ^ ||____6|", card7 = " _____  |7    || ^ ^ ||^ ^ ^|| ^ ^ ||____7|", card8 = " _____  |8    ||^ ^ ^|| ^ ^ ||^ ^ ^||____8|", card9 = " _____  |9    ||^ ^ ^||^ ^ ^||^ ^ ^||____9|", card10 = " _____  |10^  ||^ ^ ^||^ ^ ^||^ ^ ^||___10|", cardj = " _____  |J  ww|| ^ {)||(.)%%|| | % ||__%%J|", cardq = " _____  |Q  ww|| ^ {(||(.)%%|| |%%%||_%%%Q|", cardk = " _____  |K  WW|| ^ {)||(.)%%|| |%%%||_%%%K|", cardque = " _____  |?    ||     ||     ||     ||____?|";

char input1;

enum winCase 
{
    playerWin,
    dealerWin,
    playerBust,
    dealerBust,
    playerBlackjack,
    dealerBlackjack,
    standoff,
    nothing
};

// Draws one random card for the player, and add the card to the players total card value and array of cards

void drawCard(std::vector<int> &target, int &points){

    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> card(1,13);

    int cardNumber = card(rng);

        switch (cardNumber) 
        {
            case 1:
                target.push_back(1);
                if (points <= 10) {
                    points += 11;
                } 
                else {
                    points += 1;
                }
                break;
            case 11:
                target.push_back(11);
                points += 10;
                break;
            case 12:
                target.push_back(12);
                points += 10;
                break;
            case 13: 
                target.push_back(13);
                points += 10;
                break;
            default:
                target.push_back(cardNumber);
                points += cardNumber;
                break;
        };
}

// Checks if the player or dealer has busted, depending on the input

bool bust(int points) 
{
    if (points > 21) 
    {
        return true;
    } 
    else 
    {
        return false;
    }
    return false;
}

// Checks if target has a blackjack

bool blackjack(std::vector<int> target) 
{
        if (target[0] == 1 && target[1] >= 10) 
        {
            return true;
        }
        else if (target[0] >= 10 && target[1] == 1) 
        {
            return true;
        }
        return false;
}

// Checks if the game has ended

winCase returnHowSomebodyWon() {
    if (blackjack(player) == true) 
    {   
        drawCard(dealer, dealerPoints);
        if (blackjack(dealer) == false)
        {
            return playerBlackjack;
        } else 
        {
            return standoff;
        }
    }
    if (blackjack(player) == false && blackjack(dealer) == true) 
    {
        return dealerBlackjack;
    }
    else if (bust(dealerPoints) == true) 
    {
        return dealerBust;
    }
    else if (bust(playerPoints) == true) 
    {
        return playerBust ;
    }
    else if (bust(playerPoints) == false && dealerPoints < playerPoints && dealerPoints >= 17) 
    {
        return playerWin;
    }
    else if (playerPoints < dealerPoints && stand == true and dealerPoints >= 17 and bust(dealerPoints) == false) 
    {
        return dealerWin;
    }
    else if (playerPoints == dealerPoints && stand == true && dealerPoints >= 17) 
    {
        return standoff;
    }
    return nothing;
}

// Checks if Somebody has won

bool somebodyHasWon()
{
    if (returnHowSomebodyWon() != nothing)
    {
        return true;
    } 
    else
    {
        return false;
    }
}

// Resets print queue

void resetPrintQueue()
{
    cardP1 = "";
    cardP2 = "";
    cardP3 = "";
    cardP4 = "";
    cardP5 = "";
    cardP6 = "";
}

// Adds card to print queue

void addCard(std::string card) {
    cardP1 += card.substr(0, 7);
    cardP2 += card.substr(8, 7);
    cardP3 += card.substr(15, 7);
    cardP4 += card.substr(22, 7);
    cardP5 += card.substr(29, 7);
    cardP6 += card.substr(36, 7);
}

// Prints a card

void displayCard(std::vector<int> inputCard, int inputNum) {
    resetPrintQueue();

    for (int i = 0; i < inputNum; i++) {
        switch (inputCard[i]) 
        {
            case 0:
                addCard(cardque);
                break;
            case 1:
                addCard(carda);
                break;
            case 2:
                addCard(card2);
                break;
            case 3:
                addCard(card3);
                break;
            case 4:
                addCard(card4);
                break;
            case 5:
                addCard(card5);
                break;
            case 6:
                addCard(card6);
                break;
            case 7:
                addCard(card7);
                break;
            case 8:
                addCard(card8);
                break;
            case 9:
                addCard(card9);
                break;
            case 10:
                addCard(card10);
                break;
            case 11:
                addCard(cardj);
                break;
            case 12:
                addCard(cardq);
                break;
            case 13:
                addCard(cardk);
                break;
            default:
                break;
        }
    }
    std::cout << cardP1 << '\n' << cardP2 << '\n' <<  cardP3 << '\n' << cardP4 << '\n' <<  cardP5 << '\n' << cardP6 << '\n';
}

// Prints the game

void displayGame() 
{
    std::cout << "-----------------------" << '\n' << dealerPoints << '\n';
    displayCard(dealer, dealer.size());
    std::cout << "-----------------------" << '\n' << playerPoints << '\n';
    displayCard(player, player.size());
    std::cout << "-----------------------" << '\n';
}

// Prints game result

void printResult(winCase result)
{
    switch (result)
    {
        case nothing:
            break;
        case playerWin:
            std::cout << "-----------------------" << '\n' << "You won with " << playerPoints << " points!" << '\n' << "-----------------------" << '\n';
            break;
        case dealerWin:
            std::cout << "-----------------------" << '\n' << "Dealer won with " << dealerPoints << " points!" << '\n' << "-----------------------" << '\n';
            break;
        case playerBust:
            std::cout << "-----------------------" << '\n' << "Player went bust!" << '\n' << "-----------------------" << '\n';
            break;
        case dealerBust:
            std::cout << "-----------------------" << '\n' << "Dealer went bust!" << '\n' << "-----------------------" << '\n';
            break;
        case playerBlackjack:
            std::cout << "-----------------------" << '\n' << "Player won with blackjack!" << '\n' << "-----------------------" << '\n';
            break;
        case dealerBlackjack:
            std::cout << "-----------------------" << '\n' << "Dealer won with blackjack!" << '\n' << "-----------------------" << '\n';
            break;
        case standoff:
            std::cout << "-----------------------" << '\n' << "Standoff!" << '\n' << "-----------------------" << '\n';
            break;
        default:
            break;
    }
}

// displays the game

void clearAndDisplayGame()
{
    system("cls");
    displayGame();
}
// Resets values of the game

void resetGame()
{
    stand = false;
    player.clear();
    dealer.clear();
    dealerPoints = 0;
    playerPoints = 0;
}

// Sets up the game by giving out cards

void setup()
{
    drawCard(dealer, dealerPoints);
    drawCard(player, playerPoints);
    drawCard(player, playerPoints);
    dealer.push_back(0);
    clearAndDisplayGame();
}

// Makes the player draw cards until they stand

void playerHitOrStandLoop()
{
    while (true)
    {
        if (somebodyHasWon() == true)
        {
            Sleep(1000);
            break;
        }

        std::cout << "(S)tand or (H)it: ";
        std::cin >> input1;

        if (input1 == 's' || input1 == 'S')
        {
            stand = true;
            break;
        } 
        else if (input1 == 'h' || input1 == 'H')
        {
            drawCard(player, playerPoints);
            system("cls");
            displayGame();
        }
    }
}

// Makes the dealer draw cards

void dealerDrawCardsLoop() 
{
    dealer.erase(std::next(dealer.begin()));

    int i = 0;

    while (i <= 16 && somebodyHasWon() == false)
    {
        drawCard(dealer, dealerPoints);
        clearAndDisplayGame();
        Sleep(1000);
    }
}

// Finishes the game and resets it

void endgame()
{  
    system("cls");
    printResult(returnHowSomebodyWon());
    Sleep(1000);
    resetGame();
}

int main () 
{
    while (true)
    {
        setup();

        playerHitOrStandLoop();

        if (somebodyHasWon() == true)
        {
            goto endGame;
        }

        dealerDrawCardsLoop();

        endGame: 
            endgame();
    }
}
