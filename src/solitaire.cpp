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

// Draw Back of Cards
void Solitaire::drawBackOfCards(int x, int y) {
	screenBuffer.writeToScreen(x, y, L"+------------+");
	screenBuffer.writeToScreen(x, y + 1, L"|  / / / / / |");
	screenBuffer.writeToScreen(x, y + 2, L"| / / / / /  |");
	screenBuffer.writeToScreen(x, y + 3, L"| \\ \\ \\ \\ \\  |");
	screenBuffer.writeToScreen(x, y + 4, L"|  \\ \\ \\ \\ \\ |");
	screenBuffer.writeToScreen(x, y + 5, L"|  / / / / / |");
	screenBuffer.writeToScreen(x, y + 6, L"| / / / / /  |");
	screenBuffer.writeToScreen(x, y + 7, L"| \\ \\ \\ \\ \\  |");
	screenBuffer.writeToScreen(x, y + 8, L"|  \\ \\ \\ \\ \\ |");
	screenBuffer.writeToScreen(x, y + 9, L"|  / / / / / |");
	screenBuffer.writeToScreen(x, y + 10, L"+------------+");
}

// Draw a card
void Solitaire::drawCard(int x, int y, Card card) {
	// Set the colour of the card
	WORD colour;
	if (card.colour == Colour::RED) {
		colour = ScreenBuffer::RED;
	}
	else {
		colour = ScreenBuffer::CYAN;
	}

	// Draw the card
	screenBuffer.writeToScreen(x, y, L"+------------+", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 1, L"|            |", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 2, L"|            |", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 3, L"|            |", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 4, L"|            |", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 5, L"|            |", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 6, L"|            |", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 7, L"|            |", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 8, L"|            |", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 9, L"|            |", colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x, y + 10, L"+------------+", colour, ScreenBuffer::BACKGROUND_NORMAL);

	// Draw the value of the card
	screenBuffer.writeToScreen(x + 2, y + 1, valueToString.at(card.value), colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x + 11, y + 9, valueToString.at(card.value), colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x + 10, y + 1, suitToString.at(card.suit), colour, ScreenBuffer::BACKGROUND_NORMAL);
	screenBuffer.writeToScreen(x + 2, y + 9, suitToString.at(card.suit), colour, ScreenBuffer::BACKGROUND_NORMAL);
}

// Draw the game board
void Solitaire::drawBoard() {
	// Draw the stock and waste piles
	drawBackOfCards(0, 0);
	screenBuffer.writeToScreen(6, 11, L"Stock");
	drawCard(15, 0, stock.top());
	screenBuffer.writeToScreen(20, 11, L"Waste");
	screenBuffer.setScreenSize(580, 80);

	// Draw the tableau piles
	for (int i = 0; i < 7; ++i) {
		screenBuffer.writeToScreen(7 + i * 15, 14, std::to_wstring(i));
		
		int size = tableau[i].size();
		int x = i * 15;
		int y = 15;

		for (int j = 0; j < size - 1; ++j) {
			drawBackOfCards(x, y);
			y += 4;
		}
		
		drawCard(x, y, tableau[i].getTopCard());
	}

	// Draw the foundation piles
	std::wstring suits[] = { L"Hearts", L"Diamonds", L"Clubs", L"Spades" };	

	for (int i = 0; i < 4; ++i) {
		// Draw the foundation pile label
		screenBuffer.writeToScreen((14 - static_cast<int>(suits[i].length()))/2 + 45 + i * 15, 6, suits[i]);
	}
}

// Check if the game is won
bool Solitaire::isGameWon() {
	for (int i = 0; i < 4; ++i) {
		if (foundations[i].size() != 13) {
			return false;
		}
	}
	return true;
}

// Run the game
int Solitaire::run() {
	std::string input;
	int pile = 0;
	int fromPile = 0;
	int toPile = 1;

	screenBuffer.clearScreen();
	drawBoard();
	screenBuffer.setActive();
	
	// Display instructions
	screenBuffer.writeToScreen(0, 70, L"Type 'stop' to end game.");
	screenBuffer.writeToScreen(0, 71, L"'W' to reveal new card, 'W0-6' to move card to column, 'W & H,D,C,S' to move card to foundation, '1H or H4' to move card.");
	
	// Main game loop
	while (!isGameWon()) {
		screenBuffer.writeToScreen(0, 72, L"           ");
		screenBuffer.writeToScreen(0, 72, L"Input: ");
		input = screenBuffer.getBlockingInput();

		// Exit the game
		if (input == "stop") {
			return 0;
		}

		if (input == "W") {
			// Check if stock has cards left
			if (!stock.empty()) {
				waste.push(stock.top());
				stock.pop();
			}
			// If stock is empty, move cards back from waste
			else if (stock.empty()) {
				while (!waste.empty()) {
					stock.push(waste.top());
					waste.pop();
				}
			}
		}
		// Move a card to a tableau pile
		if (input[0] == 'W' && (input[1] >= '0' && input[1] <= '6')) {
			pile = input[1] - '0';
			if (waste.size() > 0 && canCardAddToPile(waste.top(), tableau[pile])) {
				tableau[pile].addCard(waste.top());
				waste.pop();
			}
		}

		// Move a card to a foundation pile
		if (input[0] == 'W'  && (input[1] == 'H' || input[1] == 'D' || input[1] == 'C' || input[1] == 'S')) {
			pile = input[1] - 'H';
			if (waste.size() > 0 && canCardAddToFoundation(waste.top(), foundations[pile])) {
				foundations[pile].addCard(waste.top());
				waste.pop();
			}
		}

		// Move a card from a tableau pile to another tableau pile
		if ((input[0] >= '0' && input[0] <= '6') && (input[1] >= '0' && input[1] <= '6')) {
			fromPile = input[0] - '0';
			toPile = input[1] - '0';
			Card topCard = tableau[fromPile].getTopCard();

			if (tableau[fromPile].size() > 0 && canCardAddToPile(topCard, foundations[toPile])) {
				tableau[toPile].addCard(tableau[fromPile].getTopCard());
				tableau[fromPile].removeTopCard();
			}
		}

		// Move a card from a tableau pile to a foundation pile
		if ((input[0] >= '0' && input[0] <= '6') && (input[1] == 'H' || input[1] == 'D' || input[1] == 'C' || input[1] == 'S')) {
			fromPile = input[0] - '0';
			toPile = input[1] - 'H';
			Card topCard = tableau[fromPile].getTopCard();

			if (tableau[fromPile].size() > 0 && canCardAddToFoundation(topCard, foundations[toPile])) {
				foundations[toPile].addCard(tableau[fromPile].getTopCard());
				tableau[fromPile].removeTopCard();
			}
		}

		// Move a card from a foundation pile to a tableau pile
		if ((input[0] == 'H' || input[0] == 'D' || input[0] == 'C' || input[0] == 'S') && (input[1] >= '0' && input[1] <= '6')) {
			fromPile = input[0] - 'H';
			toPile = input[1] - '0';
			Card topCard = foundations[fromPile].getTopCard();

			if (foundations[fromPile].size() > 0 && canCardAddToPile(topCard, tableau[toPile])) {
				tableau[toPile].addCard(foundations[fromPile].getTopCard());
				foundations[fromPile].removeTopCard();
			}
		}

		screenBuffer.clearScreen();
		dealCards();
	}

	return 0;
}

