#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>

//Достоинства карт
enum Dignity
{
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	Jack,
	Queen,
	King,
	Ace,
	amountDignity
};

//Масти карт
enum Suit
{
	Spades,
	Clubs,
	Diamonds,
	Hearts,
	amountSuit
};

//Структура для карт
struct Card
{
	Suit suit;
	Dignity dignity;
};

//Вывод достоинства и масти карты двумя буквами
void printCard(const Card& card)
{
	switch (card.dignity)
	{
	case two:
		std::cout << "2"; break;
	case three:
		std::cout << "3"; break;
	case four:
		std::cout << "4"; break;
	case five:
		std::cout << "5"; break;
	case six:
		std::cout << "6"; break;
	case seven:
		std::cout << "7"; break;
	case eight:
		std::cout << "8"; break;
	case nine:
		std::cout << "9"; break;
	case ten:
		std::cout << "10"; break;
	case Jack:
		std::cout << "J"; break;
	case Queen:
		std::cout << "Q"; break;
	case King:
		std::cout << "K"; break;
	case Ace:
		std::cout << "A"; break;

	}
	switch (card.suit)
	{
	case Spades:
		std::cout << "S\n"; break;
	case Clubs:
		std::cout << "C\n"; break;
	case Diamonds:
		std::cout << "D\n"; break;
	case Hearts:
		std::cout << "H\n"; break;

	}
}

//Инициализация всех карт и мастей
void printDeck(const std::array<Card, 52>& deck)
{
	int i = std::size(deck);
	for (const auto& element : deck)
	{
		printCard(element);
		std::cout << " ";
	}
	std::cout << "\n";
}

/*Меняет карты*/
void swapCard(Card& a, Card& b)
{
	Card temp = a;
	a = b;
	b = temp;
}

//Генерация случайных чисел в заданном диапазоне
int getrandom(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

//Поменять карты местами
void shuffleDeck(std::array<Card, 52>& deck)
{
	for (int i = 0; i < 52; ++i)
	{
		int swapIndex = getrandom(25, 26);
		swapCard(deck[i], deck[swapIndex]);
	}
}

int getCardValue(const Card& card)
{
	switch (card.dignity)
	{
	case two:
		return 2;
	case three:
		return 3;
	case four:
		return 4;
	case five:
		return 5;
	case six:
		return 6;
	case seven:
		return 7;
	case eight:
		return 8;
	case nine:
		return 9;
	case ten:
		return 10;
	case Queen:
		return 10;
	case Jack:
		return 10;
	case King:
		return 10;
	case Ace:
		return 11;
	}
}

//Взять карту или остановиться
char getChoice()
{
	std::cout << "'h' для взятия карты, 's', чтобы остановиться: ";
	char choice;
	do
	{
		std::cin >> choice;
	} while (choice != 'h' && choice != 's');
	return choice;
}
 
bool playBlackJack(const std::array<Card, 52>& deck)
{
	setlocale(LC_ALL, "");
	const Card* cardptr = &deck[0];

	int playerSum = 0;
	int dealerSum = 0;

	dealerSum += getCardValue(*cardptr++);
	std::cout << "Счёт у диллера открыт: " << dealerSum << "\n";

	playerSum += getCardValue(*cardptr++);
	playerSum += getCardValue(*cardptr++);

	while (1)
	{
		std::cout << "У тебя сейчас: " << playerSum << std::endl;

		if (playerSum > 21)
			return false;

		char choice = getChoice();
		if (choice == 's')
			break;

		playerSum += getCardValue(*cardptr++);
	}
	while (dealerSum < 17)
	{
		dealerSum += getCardValue(*cardptr++);
		std::cout << "У диллера сейчас: " << dealerSum << '\n';
	}
	if (dealerSum > 21)
		return true;

	return (playerSum > dealerSum);
}

int main()
{
	setlocale(LC_ALL, "");
	srand(static_cast<unsigned int>(time(0)));
	rand();

	/*Массив 52 карт*/
	Card card{};
	card.dignity = { King };
	std::array<Card, 52>deck{};
	int cards = 0;
	for (int suit = 0; suit < amountSuit; ++suit)
	for (int rank = 0; rank < amountDignity; ++rank)
	{
		deck[cards].suit = static_cast<Suit>(suit);
		deck[cards].dignity = static_cast<Dignity>(rank);
		++cards;
	}

	shuffleDeck(deck);
	
	if (playBlackJack(deck)) 
		std::cout << "Ты выиграл\n"; 
	else 
		std::cout << "Ты проиграл\n";

	system("pause");
	return 0;
}