#include "solitaire.h"

// Default constructor
Solitaire::Solitaire() {
	createStock();
	dealCards();
}

// Create the stock of cards
void Solitaire::createStock() {
  
    for (int suit = Suit::HEARTS; suit <= Suit::SPADES; ++suit) {
        for (int value = Value::ACE; value <= Value::KING; ++value) {
            // Determine the color based on the suit
            Colour color = (suit == Suit::HEARTS || suit == Suit::DIAMONDS) ? Colour::RED : Colour::BLACK;

            // Assign the card to the deck
            deck.push_back(Card(static_cast<Value>(value), static_cast<Suit>(suit), color, false));
        }
    }

	// Shuffle the deck
	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(deck.begin(), deck.end(), generator);

	// Add the shuffled deck to the stock
	for (Card card : deck) {
		stock.push(card);
	}
}

// Deal the cards to the tableau
void Solitaire::dealCards() {
	// Deal the cards to the tableau
	for (int i = 0; i < 7; ++i) {
		std::stack<Card>& cards = tableau[i].getStack(); 
		for (int j = 0; j < i + 1; ++j) {
			Card card = stock.top();
			stock.pop();
			cards.push(card);
		}
	}

	// Flip the last card in each tableau
	for (int i = 0; i < 7; ++i) {
		tableau[i].flipTopCard();
	}
}

// Check if a card can be added to a pile
bool Solitaire::canCardAddToPile(Card& card, Pile& pile) {
	if (pile.isEmpty() && card.value == Value::KING) {
		return true;
	}
	else if (!pile.isEmpty() && pile.getTopCard().value == card.value - 1 && pile.getTopCard().suit != card.suit) {
		return true;
	}
	return false;
}

// Check if a card can be added to a foundation pile
bool Solitaire::canCardAddToFoundation(Card& card, FoundationPile& pile) {
	if (pile.isEmpty() && card.value == Value::ACE) {
		return true;
	}
	else if (!pile.isEmpty() && pile.getTopCard().value == card.value + 1 && pile.getTopCard().suit == card.suit) {
		return true;
	}
	return false;
}



