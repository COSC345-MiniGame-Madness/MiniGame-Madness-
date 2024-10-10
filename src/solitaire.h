#ifndef SOLITAIRE_H
#define SOLITAIRE_H

/*!
* @file solitaire.h
* @brief Contains the declaration of the Solitaire class and its member functions.
* @author Angus Martin
*/

#include "ScreenBuffer.h"
#include <stack>
#include <map>
#include <algorithm>
#include <random>
#include <windows.h>

// Forward declaration of the test class
namespace SolitaireTests {
	class SolitaireTests;
}


/*!
* @enum Suit
* @brief An enum that represents the suit of a card.
*/
enum Suit {
	HEARTS, /*!< The hearts suit */
	DIAMONDS, /*!< The diamonds suit */
	CLUBS, /*!< The clubs suit */
	SPADES /*!< The spades suit */
};

/*!
* @enum Colour
* @brief An enum that represents the colour of a card.
*/
enum Colour {
	RED, /*!< The red colour */
	BLACK /*!< The black colour */
};

/*!
* @enum Value
* @brief An enum that represents the value of a card.
*/
enum Value {
	ACE, /*!< The ace card */
	TWO, /*!< The two card */
	THREE, /*!< The three card */
	FOUR, /*!< The four card */
	FIVE, /*!< The five card */
	SIX, /*!< The six card */
	SEVEN, /*!< The seven card */
	EIGHT, /*!< The eight card */
	NINE, /*!< The nine card */
	TEN, /*!< The ten card */
	JACK, /*!< The jack card */
	QUEEN, /*!< The queen card */
	KING /*!< The king card */
};

/*!
* @struct Card
* @brief A struct that represents a card in the deck.
*/
struct Card {
	Value value; /*!< The value of the card */
	Suit suit; /*!< The suit of the card */
	Colour colour; /*!< The colour of the card */
	bool faceUp; /*!< Whether the card is face up or not */

	/*!
   * @brief Constructor for Card.
   * @param value The value of the card.
   * @param suit The suit of the card.
   * @param colour The colour of the card.
   * @param faceUp Whether the card is face up or not.
   */
	Card(Value value, Suit suit, Colour colour, bool faceUp)
		: value(value), suit(suit), colour(colour), faceUp(faceUp) {}

};

/*!
* @struct Pile
* @brief A struct that represents a pile of cards.
* @details The pile is built up in descending order of alternating colours.
*/
struct Pile {
	std::stack<Card> pile; /*!< The pile of cards */
	
	/*!
	* @brief Function to add a card to the pile.
	* @param card The card to add to the pile.
	*/
	void addCard(Card card) {
		pile.push(card);
	}

	/*!
	* @brief Function to remove a card from the pile.
	* @return The card that was removed from the pile.
	*/
    Card removeTopCard() {
        Card topCard = pile.top();
        pile.pop();
        return topCard;
    }
	
	/*!
	* @brief Function to get the top card of the pile.
	* @return The top card of the pile.
	*/
	Card getTopCard() {
		return pile.top();
	}

	/*!
	* @brief Function to get the colour of the top card of the pile.
	*/
	Colour getTopCardColour() {
		return pile.top().colour;
	}

	/*!
	* @brief Function to check if the top card of the pile is face up.
	* @return true if the top card of the pile is face up, false otherwise.
	*/
	bool isTopCardFaceUp() {
		return pile.top().faceUp;
	}

	/*!
	* @brief Function to change the top card of the pile to face up or down.
	*/
	void flipTopCard() {
		pile.top().faceUp = !pile.top().faceUp;
	}

	/*!
	* @brief Function to get a reference to the stack in the Pile struct.
	* @return A reference to the stack in the Pile struct.
	*/
	std::stack<Card>& getStack() {
		return pile;
	}

	/*!
	* @brief Function to check if the pile is empty.
	* @return true if the pile is empty, false otherwise.
	*/
	bool isEmpty() {
		return pile.empty();
	}

	/*!
	* @brief Function to get the size of the pile.
	* @return The size of the pile.
	*/
	int size() {
		return static_cast<int>(pile.size());
	}
};

/*!
* @struct foundationPile
* @brief A struct that represents a foundation pile of cards.
* @details The foundation pile is where the player will move the cards to in order to win the game.
* @details The foundation pile is built up in ascending order of the same suit.
* @see Pile
*/
struct FoundationPile : Pile {
	Suit foundationSuit; /*!< The suit of the foundation */

	/*!
	* @brief Constructor to initialize the foundation suit.
	* @param suit The suit of the foundation.
	*/
	FoundationPile(Suit suit) : foundationSuit(suit) {}
};

/*!
* @class Solitaire
* @brief A class that represents the solitaire game.
*/
class Solitaire {
private:
	// Declare the test class as a friend
	friend class SolitaireTests::SolitaireTests;

	const std::map<Value, std::wstring> valueToString = {
	{ACE, L"A"},
	{TWO, L"2"},
	{THREE, L"3"},
	{FOUR, L"4"},
	{FIVE, L"5"},
	{SIX, L"6"},
	{SEVEN, L"7"},
	{EIGHT, L"8"},
	{NINE, L"9"},
	{TEN, L"T"},
	{JACK, L"J"},
	{QUEEN, L"Q"},
	{KING, L"K"}
	};/*!< Map to convert card value to string. */
	
	const std::map<Suit, std::wstring> suitToString = {
	{HEARTS, L"\u2665"},
	{DIAMONDS, L"\u2666"},
	{CLUBS, L"\u2663"},
	{SPADES, L"\u2660"}
	};/*!< Map to convert card suit to string. */
	
	ScreenBuffer screenBuffer; /*!< The screen buffer for displaying the game. */

	std::vector<Card> deck; /*!< The deck of cards. */
	std::stack<Card> stock; /*!< The stock pile of cards. */
	std::stack<Card> waste; /*!< The waste pile of cards. */

	Pile tableau[7]; /*!< The tableau piles of cards. */
	FoundationPile foundations[4] = { FoundationPile(HEARTS), FoundationPile(DIAMONDS), FoundationPile(CLUBS), FoundationPile(SPADES) }; /*!< The foundation piles of cards. */

	/*!
	* @brief Function to create a stockpile of cards and randomly suffle them.
	*/
	void createStock();

	/*!
	* @brief Function to deal the cards from the stockpile to the tableau piles.
	* @details The first tableau pile will have 1 card, the second will have 2 cards, and so on.
	*/
	void dealCards();

	/*!
	* @brief Function to check if card can be added to a pile.
	* @param card The card to add to the pile.
	* @param pile The pile to add the card to.
	* @return true if the card can be added to the pile, false otherwise.
	*/
	bool canCardAddToPile(Card& card, Pile& pile);

	/*!
	* @brief Function to check if a card can be added to a foundation pile.
	* @param card The card to add to the pile.
	* @param foundationPile The foundation pile to add the card to.
	* @return true if the card can be added to the foundation pile, false otherwise.
	*/
	bool canCardAddToFoundation(Card& card, FoundationPile& foundationPile);


	/*!
	* @brief Function to draw the game board.
	* @details The game board consists of the stock, waste, tableau, and foundations.
	*/
	void drawBoard();

	/*!
	* @brief Function to draw back of cards
	* @param x The x coordinate to draw the card
	* @param y The y coordinate to draw the card
	*/
	void drawBackOfCards(int x, int y);

	/*!
	* @brief Function to draw a card
	* @param x The x coordinate to draw the card
	* @param y The y coordinate to draw the card
	* @param card The card to draw
	*/
	void drawCard(int x, int y, Card card);

	/*!
	* @brief Function to check if the player has won the game.
	* @return true if the player has won the game, false otherwise.
	*/
	bool isGameWon();

	/*!
	* @brief Function to check player input is vaild for tableau index.
	* @param input The input to check.
	* @return true if the input is valid, false otherwise.
	*/
	bool isValidTableauInput(char input);

	/*!
	* @brief Function to check player input is vaild for foundation index.
	* @param input The input to check.
	* @return true if the input is valid, false otherwise.
	*/
	bool isValidFoundationInput(char input);

	/*!
	* @brief Function to flip new card into waste pile and redraw.
	*/
	void flipNewCard();

	/*!
	* @brief Function to draw foundation pile.
	* @param i The index of the foundation pile.
	*/
	void drawFoundationPile(int i);

	/*!
	* @brief Function to draw tableau pile.
	* @param i The index of the tableau pile.
	*/
	void drawTableauPile(int i);

public:
	/*!
	* @brief Default constructor for Solitaire.
	*/
	Solitaire();

	/*!
	* @brief Function to run the game of solitaire.
	* @return 0 to return to main menu or 1 to exit app.
	*/
	int run();
};

#endif // SOLITAIRE_H
