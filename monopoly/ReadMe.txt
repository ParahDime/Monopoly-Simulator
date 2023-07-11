READ ME

Customised monopoly gameplay

OVERVIEW:
A design twist on monopoly that I created after making a watered down version of monopoly but wanted something a bit more interesting. 
It allows you to build your own custom monopoly board using the tools available (the .txt files)

CUSTOMISATION (IN GAME):
The game allows you to customise the experience of the game for your player (Player 1). Certain aspects of the game can be modified to make it more interesting for you. These include:
	Rounds:
		You can modify the number of rounds played in a game. Currently it is set so that there is a MINIMUM of 1 round played, and a MAXIMUM of 1000 rounds played at current.
	Difficulty:
		Selecting a difficulty allows you to change the difficulty for your character. This will mean that:
			Amount earned from passing GO will be modified
			Amount earned/paid due to landing on owned property is modified

		Difficulty does not affect other AI players in terms of buying/paying money.
	Number of Players:
		Modifies the number of players in the game. Currently there is a minimum of 2 players, and a MAXIMUM of 6 players
		(note there cannot be more players than the amount of names loaded into the game)
	Number of Dice:
		Modifies the number of dice used. This can either be 1 die, or 2 dice
		(note that adding 2 dice will mean that the double rule is added into the game, including triple rolling of doubles rule)

READING THE FILES:
The program reads in files to get information that allows the game to be played. Below is a guide to help you customise the file

names.txt
	Available list of players able to be loaded in. Currently a list of default items, but can be changed to suit your game

Board.txt
	Reads in the board for the game to be played on. They can be changed to any type of board as long as it meets the requirements
	Type 1: Property
		Inputted as Type, Name, Cost to purchase, Rent, Colour
	Type 2: Utility
		Inputted as Type, Name, Cost to purchase, Rent
	Type 3: Station
		Inputted as Type, Name, Cost to purchase, Rent
	Type 4: Go
		Inputed as Type, Name
	Type 5: Jail
		Inputed as Type, Name
	Type 6: Go To Jail
		Inputed as Type, Name
	Type 7: Chance
		Inputed as Type, Name
	Type 8: Community Chest
		Inputed as Type, Name
	Type 9: Free Parking
		Inputed as Type, Name
	Type 10: Tax Squares
		Inputed as Type, Name, Amount

	Paying Rent:
		When paying rent, different tiles follow different rules. Below is an explanation of how the program calculates rent:

	Type 1: Property
		Payment is based upon level of houses, the more houses that are in control of the player, the more the person pays in rent
	Type 2: Utility
		
	Type 3: Station

	Type 6: Go to Jail
		Calculate
	Type 10: Tax Squares
		Calculates Tax with Modifier (+- 20%)

		There is no limit to the size of the board, and is currently set to the default board

Chance.txt
	Contains the chance cards, can be changed as long as they meet the requirements
	Type 1: Gain Money
		Inputted as Type, Name, Amount
	Type 2: Lose Money
		Inputted as Type, Name, Amount
	Type 3: Move Position
		Inputted as Type, Name, Position, Collect Go
	Type 4: Get Out of Jail
		Inputted as Type, Name
	Type 5: Go To jail
		Inputted as Type, Name

		there is no limit to the amount of cards
Community Chest.txt
	holds the community chest cards, can be changed as long as they meet the requirements
		Type 1: Gain Money
		Inputted as Type, Name, Amount
	Type 2: Lose Money
		Inputted as Type, Name, Amount
	Type 3: Move Position
		Inputted as Type, Name, Position, Collect Go
	Type 4: Get Out of Jail
		Inputted as Type, Name
	Type 5: Go To jail
		Inputted as Type, Name
	Type 6: Payment of Property
		Inputted as Type, Name, Payment for Properties
	(With Type 6, the game will handle the pay [price] for each house and [price] for each hotel)
	Type 7: All player collection
		Inputted as Type, Name, Amount

WRITING YOUR OWN BOARD
Writing your own board is possible, and uses the above list to write your own files. Below are examples based on the file

board.txt
	1 Fake Street 100, 10, Brown
	2 Power Plant 100 10
	4 Go 
	10 Import Tax 100

chance.txt, community chest.txt
	1 You have been paid 100
	3 
	4 Get out of Jail
	6 Annual repairs on your property 10 100

