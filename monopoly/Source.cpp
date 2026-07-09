#include "src/Header.h"
#include "src/CPlayer.h"
#include "src/CGame.h"
#include "src/Board/CTile.h"
#include "src/Board/CTileSort.h"
#include "src/Card/CCardSort.h"
#include "src/Card/CCard.h"
#include "src/Logger.h"

void Test()
{
	cout << "Function called\n";
}



//returns an int between the range high and low
int ReturnInt(int low, int high)
{
	unique_ptr<int> getInt = make_unique<int>();
	unique_ptr<string> convertString = make_unique<string>();

	do {
		cin >> *getInt;

	} while (*getInt < low || *getInt > high);

	return *getInt;
}



//returns either a y or n
char ReturnChar()
{
	unique_ptr<char> getChar = make_unique<char>();

	do {
		*getChar = getchar();
	} while (*getChar != 'y' && *getChar != 'n');

	return *getChar;
}



//check if user is happy with the customisation options
//bool used to show it changes are still needed (then set to true)
bool VerifyCustomisation(unique_ptr<CGame>& cGame, unique_ptr<Logger>& ioLog)
{
	system("cls");
	ioLog->writeToFile("=====================================================================");
	ioLog->writeToFile("			MONOPOLY SIMULATOR CONFIGURATION");
	ioLog->writeToFile("=====================================================================\n");
	ioLog->writeToFile("[+] Max number of rounds: " + to_string(cGame->GetMaxRound()));
	ioLog->writeToFile("[+] Number of players: " + to_string(cGame->GetPlayers()));
	ioLog->writeToFile("[+] Difficulty: " + cGame->GetDifficulty());
	ioLog->writeToFile("[+] Number of dice used: " + to_string(cGame->GetDiceNo()));
	ioLog->writeToFile("[+] Number of dice sides: " + to_string(cGame->GetHighRoll()) + "\n");
	
	ioLog->writeToFile("=====================================================================\n");
	
	cout << "Are these customisation options correct?	 y / n\n";
	if (ReturnChar() == 'n')
	{
		return true;
	}
	else
	{
		//return
		ioLog->writeToFile("Customisation options set\n\n");
		return false;
	}
}



//use options to check what to change
void CreateCustomisation(unique_ptr<CGame>& cGame, unique_ptr<Logger>& ioLog)
{
	unique_ptr<int> getInt = make_unique<int>();

	//max no of rounds
	cout << "Enter number of rounds\n min: 1\n max: 1000\n";

	//get number of rounds

	*getInt = ReturnInt(1, 1000);
	cout << "Number of rounds set to " << *getInt << "\n\n";
	cGame->SetMaxRound(*getInt);


	//difficulty easy normal hard
	cout << "Enter difficulty setting:\n 1: Easy\n 2: Normal\n 3: Hard\n";

	*getInt = ReturnInt(1, 3);
	cout << "Difficulty set to ";
	//switch determines output to console
	switch (*getInt)
	{
	case 1:
		cout << "Easy\n\n";
		//set pass go money here
		break;
	case 2:
		cout << "Normal\n\n";
		break;
	case 3:
		cout << "Hard\n\n";
		break;
	default:
		break;
	}
	cGame->SetDifficulty(*getInt);

	//set difficulty

	cout << "Enter number of players:\n min: 2\n max: 6\n";
	*getInt = ReturnInt(2, 6);
	cout << "Number of players set to " << *getInt << ".\n\n";

	cGame->SetPlayers(*getInt);

	//no of dice / sides of dice

	//define dice side here
	int dice[6] = { 4, 6, 10, 12, 15, 20 };
	cout << "Select a sided die\n";
	for (const auto& die : dice) {
		std::cout << die << "\t";
	}

	int playerInput = -1;
	bool matchFound = false;

	while (!matchFound) {
		std::cin >> playerInput;
		for (const auto& face : dice) {
			if (playerInput == face) {
				matchFound = true;
				cGame->SetHighRoll(playerInput);
				break;
			}
		}
		if (!matchFound) {
			std::cout << "Invalid choice\n";
		}
	}

	cout << playerInput << " sided die picked\n";

	cout << "Would you like to use 2 dice?\n y / n\n";
	if (ReturnChar() == 'y')
	{
		cout << "Set number of dice to 2.\n\n";
		cGame->SetDiceNo(2);
		//set it to have 2 dice rolls
	}
	else
	{
		cout << "1 dice will be used instead\n\n";
		cGame->SetDiceNo(1);
		//have 1 dice roll
	}

	//check if the user is happy with their customisation
	if (VerifyCustomisation(cGame, ioLog) == true)
	{
		CreateCustomisation(cGame, ioLog);
	}
	else
	{
		return;
	}
}

//check whether customisation occurs
bool CheckCustomisation()
{
	unique_ptr<bool> checkCustom = make_unique<bool>();

	cout << "Set customisation options?\n y / n\n";

	if (ReturnChar() == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}

}



//rolls a random number
int RNG(int low, int high)
{
	unique_ptr<int> num = make_unique<int>();

	//make random here

	*num = static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * high + low);

	//if equal to 0, recursive call
	if (*num == 0)
	{
		RNG(low, high);
	}

	return *num;
}

string GetPositionSuffix(int rank)
{
	if (rank >= 11 && rank <= 13) {
		return std::to_string(rank) + "th";
	}

	const std::string SUFFIXES[] = { "th", "st", "nd", "rd" };

	int lastDigit = rank % 10;

	//if last digit > 3, return th
	std::string suffix = (lastDigit <= 3) ? SUFFIXES[lastDigit] : "th";

	return std::to_string(rank) + suffix;
}

//output each player's total
void OutputPlayers(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, unique_ptr<Logger>& ioLog, bool gameEnd)
{
	unique_ptr<int> pPlayerNo = make_unique<int>(0);
	std::sort(aPlayers.begin(), aPlayers.end(), [](const auto& a, const auto& b) {
		return a->GetMoney() > b->GetMoney();
		});

	if (gameEnd)
	{
		ioLog->writeToFile("=====================================================================");
		ioLog->writeToFile("		Rounds played: " + to_string(cGame->GetCurrentRound()));
		ioLog->writeToFile("=====================================================================\n");
	}
	else {
		ioLog->writeToFile("=====================================================================");
		ioLog->writeToFile("		End of round " + to_string(cGame->GetCurrentRound()));
		ioLog->writeToFile("=====================================================================\n");
	}

	string position;
	int rank;
	for (auto i = aPlayers.begin(); i != aPlayers.end(); i++)
	{
		rank = distance(aPlayers.begin(), i) + 1;
		position = GetPositionSuffix(rank);
		//output their name and money
		ioLog->writeToFile(position + " " + aPlayers[*pPlayerNo]->GetName() + " balance: " + char(156) + to_string(aPlayers[*pPlayerNo]->GetMoney()));
		//position
		if (aPlayers[*pPlayerNo]->IsBankrupt())
		{
			ioLog->writeToFile("BANKRUPT");
		}
		ioLog->writeToFile("\n");
		++*pPlayerNo;
	}
}



//shows which player has won
void GameEnd(unique_ptr<CGame>& cGame, vector<CPlayer*>& aPlayers, unique_ptr<Logger>& ioLog)
{
	//for loop
	std::sort(aPlayers.begin(), aPlayers.end());

	OutputPlayers(cGame, aPlayers, ioLog, true);
	
	cout << "Would you like to print game results?\n y / n\n";

	if (ReturnChar() == 'y')
	{
		//open file
		unique_ptr<string> fileName = make_unique<string>();
		*fileName = "config/results.txt";
		ofstream file(*fileName);

		//dump stats into the file
		//game information (customisation)
		
		file << "Rounds selected: " << cGame->GetMaxRound() << "\n";
		file << "Rounds played: " << cGame->GetCurrentRound() << "\n";
		file << "Difficulty selected: " << cGame->GetDifficulty() << "\n";
		file << "Number of dice used: " << cGame->GetDiceNo() << "\n";
		file << "Number of players: " << aPlayers.size() << "\n\n";

		//stats for each player
		for (int i = 0; i < aPlayers.size(); i++)
		{
			file << "Player " << i << ": " << aPlayers[i]->GetName() << "\n";
			file << "Player money: " << char(156) << aPlayers[i]->GetMoney() << "\n\n";
		}
		//use function if possible

		//close the file
		file.close();
	}
	else {
		cout << "Game results will not be saved \n";
		return;
	}

	return;

}


//calculates and deals with build repair cards
void BuildRepairs(vector<CPlayer*>& aPlayers, vector<CCard*>& aCards, vector<CTile*>& aBoard, unique_ptr<CGame>& cGame, 
	unique_ptr<int>& pCard, int position, unique_ptr<Logger>& ioLog)
{
	int* pHouses = new int;
	int* pHotels = new int;
	*pHouses = 0;
	*pHotels = 0;

	//go through list of properties
	for (int i = 0; i < aBoard.size() - 1; i++)
	{
		//if item is property AND owned by player
		if ((aBoard[i]->GetType() == 1) && (aBoard[i]->GetOwner() == position))
		{

			//add no. of houses to tally
			if (aBoard[i]->GetHotels() != 0) //if hotel is present
			{
				*pHotels += aBoard[i]->GetHotels();
			}
			else if(aBoard[i]->GetHouses() != 0)//no hotel is present (will count houses instead)
			{
				*pHouses += aBoard[i]->GetHouses();
			}
			else
			{

			}

		}
	}

	
	//finalise cost of repairs
	ioLog->writeToFile("[ Repairs ]: " + aPlayers[position]->GetName() + " pays repairs for " + to_string(*pHouses) + " houses and " + to_string(*pHotels) + " hotels.\n");
	*pHouses = *pHouses * aCards[*pCard]->GetHouseCost();
	*pHotels = *pHotels * aCards[*pCard]->GetHotelCost();

	ioLog->writeToFile("\n[ Houses: " + to_string(*pHouses));
	ioLog->writeToFile("[ Hotels ]: " + to_string(*pHotels) + "\n");
	//add to the total
	*pHouses += *pHotels;
	//deduct amount from player for repairs

	aPlayers[position]->TakeMoney(*pHouses, cGame);

	delete pHouses;
	delete pHotels;
}

//moves the player based on the card
void MoveResolve(vector<CCard*>& aCards, vector<CPlayer*>& aPlayers, vector<CTile*>& aBoard, unique_ptr<CGame>& cGame,
	unique_ptr<int>& pCard, int position, unique_ptr<Logger>& ioLog)
{

	unique_ptr<int> pPosition = make_unique<int>();

	//find position to move
	if (aCards[*pCard]->GetSpecific()) { //else specific name

		//give pPosition the part
		//use for loop to find location
		for (int i = 0; i == aBoard.size() - 1; i++)
		{
			if (aBoard[i]->GetName() == aCards[*pCard]->GetNaming())
			{
				break;
			}
		}
	}
	else { //if type is true (ie nearest)
		//take player position, lap board to find next

		//put pPosition as the current player position
		*pPosition = aPlayers[position]->GetPosition();

		//while player position type is NOT equal to set position of cCardMove class
		while (aBoard[*pPosition]->GetType() != aCards[*pCard]->GetTyping())
		{
			++*pPosition;
			//if position number is bigger or equal to the size of the board (starts from zero)
			//reset position
			if (*pPosition >= aBoard.size())
			{
				*pPosition = 0;
			}
		}
	}
	//move player to selected location
	aPlayers[position]->MovePosition(*pPosition);


	//use player landing again to handle landing (if 1 2 or 3)
	if (aBoard[*pPosition]->GetType() <= 3) {
		ioLog->writeToFile("[Moved]: " + aBoard[*pPosition]->GetName() + "\n");
	}
}


//resolves a chance or community chest card
void ResolveCard(vector<CCard*>& aCards, vector<CPlayer*>& aPlayers, vector<CTile*>& aBoard, unique_ptr<CGame>& cGame, int position, unique_ptr<Logger>& ioLog)
{

	unique_ptr<int> pCard = make_unique<int>();
	*pCard = RNG(1, aCards.size() - 1);

	aCards[*pCard]->GetText(ioLog);

	
	//find the type of the chance card with the RNG function
	switch (aCards[*pCard]->GetType())
	{
	case 1:
		//player earns money
		aPlayers[position]->GiveMoney(aCards[*pCard]->GetMoney(), cGame);
		break;
	case 2:
		//player loses money
		aPlayers[position]->TakeMoney(aCards[*pCard]->GetMoney(), cGame);
		break;
	case 3:
		//player moves to a position
		MoveResolve(aCards, aPlayers, aBoard, cGame, pCard, position, ioLog);
		break;
	case 4:
		//player gets a 'get out of jail free card

		//if player has card, stay's the same
		if (aPlayers[position]->getJailCard() == true)
		{
			ioLog->writeToFile(aPlayers[position]->GetName() + " already has a get out of jail card.\n");
		}
		else
		{
			//sets players get of jail card status to true
			aPlayers[position]->changeJailCard();
		}
		break;
	case 5:
		//player goes to jail
		aBoard[aPlayers[position]->GetPosition()]->GoToJail(cGame, aBoard, aPlayers, position, ioLog);
		break;
	case 6:
		//move to function
		BuildRepairs(aPlayers, aCards, aBoard, cGame, pCard, position, ioLog);
		break;
	case 7:
		//player collects money from other players

		//calculate no. of players (minus player)
		
		*pCard = (aPlayers.size() - 2) * 10;
		//give player the money x no of other players x 10
		aPlayers[position]->GiveMoney(*pCard, cGame);
		//take money from other players x 10
		for (int i = 0; i < aPlayers.size() - 1; i++)
		{
			if (i != position)
			{
				aPlayers[i]->TakeMoney(10, cGame);
			}
		}
		break;
	default:
		break;
	}
	//pick card from specified and output (in class)

	//carry out action specified

}


//handles where the player lands on the board
void playerLanding(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, int position, unique_ptr<int>& pDieRoll,
	vector<CCard*>& aChance, vector<CCard*>& aCommunityChest, unique_ptr<Logger>& ioLog)
{
	//player lands on X square
	if (aPlayers[position]->GetJailCounter() == 0)
	{
		ioLog->writeToFile("[ Landed ]:   " + aBoard[aPlayers[position]->GetPosition()]->GetName());
	}
	else
	{
		ioLog->writeToFile("[ In Jail ]: ");
	}
	

	
	//tiles[playerlist(player)->getTile->Get type of tile
	switch (aBoard[aPlayers[position]->GetPosition()]->GetType())
	{
	case 1:
		//player lands on a property tile

		//if it has no owner of the tile
		if (aBoard[aPlayers[position]->GetPosition()]->GetOwner() == -1) 
		{
			if (aPlayers[position]->GetMoney() >= aBoard[aPlayers[position]->GetPosition()]->GetPrice())
			{
				aBoard[aPlayers[position]->GetPosition()]->BuyProperty(cGame, aPlayers, position, ioLog);
				//cout << aBoard[aPlayers[position]->GetPosition()]->GetOwner() << "number";
			}
			else {
				cout << "Not enough money to buy the property\n";
			}
		}
		//if property is not owned by the player
		else if (aBoard[aPlayers[position]->GetPosition()]->GetOwner() != position || aBoard[aPlayers[position]->GetPosition()]->GetOwner() != -1)
		{
			//counts the number of properties in the same group
			unique_ptr<int> pGroupOwned = make_unique<int>(0);

			//for loop to find how many are owned by player who owns the tile
				for (auto const& it : aBoard)
				{
					//if the group is the same as the tile landed on
					//AND owned by the same player
					if (it->GetGroup() == aBoard[aPlayers[position]->GetPosition()]->GetGroup() && it->GetOwner() == aBoard[aPlayers[position]->GetPosition()]->GetOwner())
					{
						++* pGroupOwned;
					}
					//if type = utility and owner of that tile also owns this tile
				}

				aBoard[aPlayers[position]->GetPosition()]->PayRent(cGame, aPlayers, position, ioLog);

		}
		//else if it is owned by the player
		else if (aBoard[aPlayers[position]->GetPosition()]->GetOwner() == position)
		{
			//put house on the property
			unique_ptr<int> counter = make_unique<int>();
			unique_ptr<bool> allTrue = make_unique<bool>();
			
			//if mortgaged, AND player has more money than unmortgage price
			if ((aBoard[aPlayers[position]->GetPosition()]->IsMortgaged())
				&& (aPlayers[position]->GetMoney() >= aBoard[aPlayers[position]->GetPosition()]->GetPrice() * 1.1))
			{
				aBoard[aPlayers[position]->GetPosition()]->PayMortgageTile(cGame, aPlayers, position, ioLog);
			}

			*allTrue = true;
			//set to the last 5 (10, if 11, etc)
			
			//find the buildings that are min 5 ahead
			for (int i = *counter; i > *counter + 5; i++)
			{
				//if type = 1 and colour is same as tile on
				if ((aBoard[aPlayers[position]->GetPosition()]->GetType() == 1) 
					&& (aBoard[aPlayers[position]->GetPosition()]->GetOwner() != position))
				{
					*allTrue = false;
					break;
				}
				else {
					//is either not equal to 1, or owner is the player (would return true)
				}
			}

			if (*allTrue == true) //if all properties are owned by the player
			{
				//if no of houses is less than 4 and no hotel
				if (aBoard[aPlayers[position]->GetPosition()]->GetHouses() < 4 
					&& aBoard[aPlayers[position]->GetPosition()]->GetHotels() < 1)
				{
					//check if player can afford to place a house
					aBoard[aPlayers[position]->GetPosition()]->SetHouses(aPlayers, cGame, position, ioLog);
				}
				//else if no of houses is equal to 4
				else if (aBoard[aPlayers[position]->GetPosition()]->GetHouses() >= 4)
				{
					//check if player can afford to place a hotel down
					aBoard[aPlayers[position]->GetPosition()]->SetHotels(aPlayers, cGame, position, ioLog);
				}
				//else if a hotel is already on the property
				else if (aBoard[aPlayers[position]->GetPosition()]->GetHotels() >= 1)
				{
					ioLog->writeToFile("[ Notice ]: Maximum buildings placed on property");
				}
				else
				{

				}				
			}
		}
		break;
	case 2:
		//player lands on utility
		if (aBoard[aPlayers[position]->GetPosition()]->GetOwner() == -1) //if it has no owner of the tile
		{
			aBoard[aPlayers[position]->GetPosition()]->BuyProperty(cGame, aPlayers, position, ioLog);
			//buy property
		}
		//if property is not owned by the player
		else if (aBoard[aPlayers[position]->GetPosition()]->GetOwner() != position || aBoard[aPlayers[position]->GetPosition()]->GetOwner() != -1) 
		{
			unique_ptr<int> pUtilityOwned = make_unique<int>(0);

			//for loop to find how many are owned by player who owns the tile
			for (auto const& it : aBoard)
			{
				//if type = utility and owner of that tile also owns this tile
				if (it->GetType() == 2 && it->GetOwner() == aBoard[aPlayers[position]->GetPosition()]->GetOwner())
				{
					++*pUtilityOwned;
				}
			}

			aBoard[aPlayers[position]->GetPosition()]->PayBill(cGame, aBoard, aPlayers, position, pDieRoll, pUtilityOwned, ioLog);
		}
		//else if not enough money to pay OR owned by the player

		break;
	case 3:
		//player lands on a station tile
		if (aBoard[aPlayers[position]->GetPosition()]->GetOwner() == -1)
		{
			aBoard[aPlayers[position]->GetPosition()]->BuyProperty(cGame, aPlayers, position, ioLog);//buy property
		}
		else if (aBoard[aPlayers[position]->GetPosition()]->GetOwner() != position || aBoard[aPlayers[position]->GetPosition()]->GetOwner() == -1)
		{
			unique_ptr<int> pStationOwned = make_unique<int>(0);

			//for loop to find how many are owned by player who owns the tile
			for (auto const& it : aBoard)
			{
				//if type = utility and owner of that tile also owns this tile
				if (it->GetType() == 2 && it->GetOwner() == aBoard[aPlayers[position]->GetPosition()]->GetOwner())
				{
					++*pStationOwned;
				}
			}

			aBoard[aPlayers[position]->GetPosition()]->PayFare(cGame, aBoard, aPlayers, position, pStationOwned, ioLog);//pay rent
		}
		break;
	case 4:
		//player lands on a go tile
		//nothing happens
		break;
	case 5: //player lands on a jail tile
		if (aPlayers[position]->GetJailCounter() == 0)
		{
			aBoard[aPlayers[position]->GetPosition()]->PassingJail(aPlayers, position, ioLog);
		}
		
		break;
	case 6: //player lands on go to jail
		aBoard[aPlayers[position]->GetPosition()]->GoToJail(cGame, aBoard, aPlayers, position, ioLog);
		break;
	case 7:
		//player lands on chance
		ioLog->writeToFile(aPlayers[position]->GetName() + " picks a chance card\n");
		ResolveCard(aChance, aPlayers, aBoard, cGame, position, ioLog);
		
		break;
	case 8:
		//player lands on community chest
		ioLog->writeToFile(aPlayers[position]->GetName() + " picks a community chest card\n");
		ResolveCard(aCommunityChest, aPlayers, aBoard, cGame, position, ioLog);
		
		break;
	case 9:
		//player lands on free parking
		aBoard[aPlayers[position]->GetPosition()]->OutputText(aPlayers, position, ioLog);
		break;
	case 10:
		aBoard[aPlayers[position]->GetPosition()]->PayTax(cGame, aPlayers, position, ioLog);
		//player lands on tax
		break;

	default:
		ioLog->writeToFile("[ Error]: Tile not specified\n");
		break;
	}
}



//player moves
void playerTurn(unique_ptr<CGame>& cGame, vector<CTile*>& aBoard, vector<CPlayer*>& aPlayers, vector<CCard*>& aChance, vector<CCard*>& aCommunityChest, unique_ptr<Logger>& ioLog, unique_ptr<int>& bankruptCount)
{
	//holds the dice number
	unique_ptr<int> pDieRoll = make_unique<int>(0);
	unique_ptr<int> pSecondDie = make_unique<int>();

	for (int i = 0; i < cGame->GetPlayers(); i++)
	{
		if (!aPlayers[i]->IsBankrupt())
		{
			ioLog->writeToFile("===============");
			ioLog->writeToFile(">>   " + aPlayers[i]->GetName() + "'s turn!");
			ioLog->writeToFile("===============\n");

			//roll dice
			if (aPlayers[i]->GetJailCounter() == 0)
			{
				*pDieRoll = cGame->rollDice();
			}

			//if value is 1 and one die
			else if (aPlayers[i]->GetJailCounter() == 1)
			{
				if (cGame->rollDice() == 6 && cGame->GetDiceNo() == 1)
				{
					ioLog->writeToFile("[ Max Roll ]: " + aPlayers[i]->GetName() + " left jail early\n");
					//pay fine
					aPlayers[i]->TakeMoney(50, cGame);
					//get out of prison
					aPlayers[i]->SetJailCounter(0);

					*pDieRoll = cGame->rollDice();
				}
				else
				{
					//pay turn
					aPlayers[i]->PassTurn();
				}
			}
			else //if value is higher than 1 and 2 dice
			{
				*pDieRoll = cGame->rollDice();
				*pSecondDie = cGame->rollDice();
				//if player rolls a six
				if (*pDieRoll == *pSecondDie)
				{
					ioLog->writeToFile("[ Doubles ]: " + aPlayers[i]->GetName() + " left jail early\n");
					//pay fine
					aPlayers[i]->TakeMoney(50, cGame);
					//get out of prison
					aPlayers[i]->SetJailCounter(0);

					*pDieRoll = cGame->rollDice();
				}
				else //else player waits a turn
				{
					aPlayers[i]->PassTurn();
				}

				//drop to zero
			}
			
			unique_ptr<int> pTotalRoll = make_unique<int>();

			//if player selected 2 die
			if (cGame->GetDiceNo() == 2 && aPlayers[i]->GetJailCounter() == 0)
			{			
				*pSecondDie = cGame->rollDice();

				//if double, roll again
				if (*pSecondDie == *pDieRoll)
				{
					*pDieRoll += *pSecondDie;

					ioLog->writeToFile("[ DOUBLE ]: rolled 2 " + to_string(*pSecondDie) + "! Roll again\n");

					//rolls the die again
					*pSecondDie = cGame->rollDice();
					unique_ptr<int> pThirdDie = make_unique<int>();
					*pThirdDie = cGame->rollDice();

					*pDieRoll = *pDieRoll + *pSecondDie + *pThirdDie;

					//if doubles a second time
					if (*pSecondDie == *pThirdDie)
					{
						ioLog->writeToFile("[ DOUBLES again ]:  rolled 2 " + to_string(*pSecondDie) + "! Roll doubles again and move to jail\n");

						*pSecondDie = cGame->rollDice();
						*pThirdDie = cGame->rollDice();

						*pDieRoll = *pDieRoll + *pSecondDie + *pThirdDie;

						//if doubles a third time
						if (*pSecondDie == *pThirdDie)
							ioLog->writeToFile("[ DOUBLES again ]: rolled 2 " + to_string(*pSecondDie) + "! " + aPlayers[i]->GetName() + " goes straight to jail");
						{
							//for every tile on the board
							for (auto const& it : aBoard)
							{
								if (it->GetType() == 6)
								{
									aPlayers[i]->SetPosition(i);
									aPlayers[i]->SetJailCounter(2);
									*pDieRoll = 0;
								}
							}
						}
						*pSecondDie = 0;
						*pThirdDie = 0;

					}

					*pDieRoll += *pSecondDie;
					//if another double, straight to jail
				}

			} //end of players rolling die

			//move player position
			ioLog->writeToFile("[ Rolled ]:   " + to_string(*pDieRoll));

			aPlayers[i]->MovePosition(*pDieRoll);
			//if past go, gain 200 munny

			if (aPlayers[i]->GetPosition() >= aBoard.size())
			{
				//player has lapped the board, and removes the board size from position counter
				aPlayers[i]->BoardLap(aBoard.size());

				//if the first player laps the board
				if (i == 0)
				{
					aPlayers[i]->GiveMoney(cGame->GetGoMoney(i), cGame);
				}
				//else if other players lap the board
				else
				{
					aPlayers[i]->GiveMoney(cGame->GetGoMoney(), cGame);
				}

			}

			//head to player landing to see where player landed
			playerLanding(cGame, aBoard, aPlayers, i, pDieRoll, aChance, aCommunityChest, ioLog);

			//check if player has minus money
			if (aPlayers[i]->GetMoney() <= 0)
			{
				ioLog->writeToFile("[ No Cash ]: " + aPlayers[i]->GetName() + " will have to mortgage properties\n");

				for (auto const& it : aBoard)
				{
					//if owned by the player
					if (aBoard[aPlayers[i]->GetPosition()]->GetOwner() == i)
					{
						aBoard[i]->MortgageTile(cGame, aPlayers, i);//mortgage the property

					}

					//if player has more than 0, break
					if (aPlayers[i]->GetMoney() > 0)
					{
						//if yes, mortgage properties until balance is above zero
						break;
					}
				}

				//if already mortgaged all of them, reset properties owned by them, set stats to zero / delete
				if (aPlayers[i]->GetMoney() < 0)
				{
					ioLog->writeToFile("[ BANKRUPT ]: No money left after mortgaging properties\n");
					(*bankruptCount)++;

					//cycle through all tiles
					for (int j = 0; j < aBoard.size() - 1; j++)
					{
						//if owner was player
						if (aBoard[aPlayers[i]->GetPosition()]->GetOwner() == i)
						{
							aBoard[aPlayers[i]->GetPosition()]->ResetTile();
						}
					}
					//player is set to be bankrupt
					aPlayers[i]->SetBankrupt();
				}

			}

			string cash = "[Cash]:   ";
			ioLog->writeToFile(cash + char(156) + to_string(aPlayers[i]->GetMoney()) + "\n\n");
		}

		
	}
	
	//roll dice
	if (cGame->isPlaying())
	{
		OutputPlayers(cGame, aPlayers, ioLog, false);
		cout << "Press any key to continue to the next round\n";
		while (std::cin.get() != '\n') {
			//Loop runs and discards any characters typed before Enter
		}
		system("cls");
	}
}



//picks the players name
void playerName(vector<string>& aNames, CPlayer* pPlayer)
{
	unique_ptr<int> random = make_unique<int>();

	//use random function for randomising names
	*random = RNG(1, aNames.size()) - 1;
	////find name from vector list

	pPlayer->SetName(aNames[*random]);

	aNames.erase(aNames.begin() + *random);
	
}



//input data for the tiles
void InputTiles(ifstream& file, unique_ptr<CGame>& cGame, vector<CTile*>& aBoard)
{
	unique_ptr <int> type = make_unique<int>(0); //0 used as placeholder

	for (int i = 0; !file.eof(); i++)
	{	
		file >> *type;

		aBoard.push_back(pNewTile(ETileType(*type), file));
		aBoard[i]->SetType(*type);

		if (*type >= 1 && *type <= 3)
		{
			cGame->MaxTileCount();
		}
	}
}

void InputCards(ifstream& file, vector<CCard*>& aCards)
{
	//read in cards here

	//for each card in the file
	unique_ptr<int> type = make_unique<int>(0); //0 is used as a placeholder

	for (int i = 0; !file.eof(); i++)
	{
		file >> *type;
		aCards.push_back(pNewCard(ECardType(*type), file));
		aCards[i]->SetType(*type);
		*type = NULL;
	}
}


//reads the file and inputs the stirngs into a vector for picking names
void ReadFile(istream& file, vector<string>& aNames)
{
	unique_ptr<string> nameHolder = make_unique<string>();

	while (!file.eof())
	{
		//push back vector with names in the file
		file >> *nameHolder;
		aNames.push_back(*nameHolder);
		
	}
}



//checks the file can be read
template <class S, class T> bool CheckFile(S& file, T& fileName)
{
	if (!file)
	{
		cout << "ERROR!\n";
		cout << "File could not be loaded\n";
		return false;
	}
	else
	{
		cout << *fileName << " loaded successfully\n";
		return true;
	}

}



int main()
{
	unique_ptr<string> fileName = make_unique<string>();
	unique_ptr<Logger> ioLog = make_unique<Logger>();
	unique_ptr<int> bankruptCount = make_unique<int>(0);

	//vectors
	vector<string> aNames = {};
	vector<CTile*> aBoard = {};
	vector<CPlayer*> aPlayers = {};

	vector<CCard*> aChanceCards = {};
	vector<CCard*> aCommunityChestCards = {};

	//initialises the bank, round number, max round number, highest dice roll, lowest dice roll
	unique_ptr<CGame> cGame = make_unique<CGame>();

	srand(time(0)); //set the seed for randomising 

	//check if customisation occurs
	if (CheckCustomisation() == true)
	{
		CreateCustomisation(cGame, ioLog);//semd to a function
	}

	//if files have a specific names that are changed

	system("cls");
	//read in files
	
	*fileName = "config/names.txt";
	ifstream nameFile(*fileName);
	if (CheckFile(nameFile, fileName))
	{
		//read names into the vector
		ReadFile(nameFile, aNames);
	}
	else
	{
		return 0;
	}
	nameFile.close();

	*fileName = "config/board.txt";
	ifstream tileFile(*fileName);
	if (CheckFile(tileFile, fileName))
	{
		//read tiles into the vector
		InputTiles(tileFile, cGame, aBoard);
	}
	else
	{
		return 0;
	}
	tileFile.close();

	//load in chance tiles

	*fileName = "config/chance.txt";
	ifstream chanceFile(*fileName);
	if (CheckFile(chanceFile, fileName))
	{
		//read tiles into the vector
		InputCards(chanceFile, aChanceCards);
	}
	else
	{
		return 0;
	}
	tileFile.close();

	//load in community chest tiles

	*fileName = "config/community chest.txt";
	ifstream chestFile(*fileName);
	if (CheckFile(chestFile, fileName))
	{
		//read tiles into the vector
		InputCards(chestFile, aCommunityChestCards);
	}
	else
	{
		return 0;
	}
	tileFile.close();
	cout << "\n";
	 
	try {
		//pick usernames
		for (int i = 0; i <= cGame->GetPlayers() - 1; i++)
		{
			CPlayer* playerPtr = new CPlayer;
			playerPtr->SetValues(cGame);
			playerName(aNames, playerPtr);

			aPlayers.push_back(playerPtr);

			cout << "Player: " << aPlayers[i]->GetName() << " initialised\n\n";

		}
	}
	catch (...) {
		cout << "An unknown error occured. Ending simulation..\n";
		return 0;
	}
	
	
	aNames.clear();
	system("cls");

	//game loop
	ioLog->writeToFile("=====================================================================\n");
	ioLog->writeToFile("			Monopoly simulator\n");
	ioLog->writeToFile("=====================================================================\n\n");

	while (cGame->GetMaxRound() > cGame->GetCurrentRound() && *bankruptCount <= (aPlayers.size() - 2))
	{
		ioLog->writeToFile("=====================================================================");
		ioLog->writeToFile("				Round " + std::to_string((cGame->GetCurrentRound() + 1)));
		ioLog->writeToFile("=====================================================================\n");

		playerTurn(cGame, aBoard, aPlayers, aChanceCards, aCommunityChestCards, ioLog, bankruptCount);

		cGame->NextRound();
	}
	
	GameEnd(cGame, aPlayers, ioLog);
	//delete items here
	
	aBoard.clear();
	aPlayers.clear();

	ioLog->closeFile();

	_CrtDumpMemoryLeaks();
	return 0;
	
}