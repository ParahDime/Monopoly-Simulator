# Customised monopoly gameplay


<h3>OVERVIEW:</h3>

<p>A twist on how monopoly is traditionally built. Focused on CLI in C++, Monopoly-Simulator allows for the user to customise a heavy amount of the gameplay, such as board, chance and community chest cards, player names and difficulty. Editable information is handled in .txt format, allowing a user friendly approach to its modular design.</p>



<h3>CUSTOMISATION (IN GAME):</h3>

<p>The game allows for a large array of customisation for the player to modify it as they see fit for a more enjoyable simulation. Certain aspects of the game can be modified to make it more interesting for you. These include:</p>
	
<h4>Rounds:</h4>
<p>You can modify the number of rounds played in a game. There is a MINIMUM of 1 round played, and a MAXIMUM of 1000 rounds played.</p>
<h4>Difficulty:</h4>
<p>Selecting a difficulty allows you to change the difficulty for your character. This will mean that:</p>
			
	Amount earned from passing GO will be modified
	Amount earned/paid due to landing on owned property is modified
	Difficulty does not affect other AI players in terms of buying/paying money, nor a large amount of decision tree behaviour
	
<h4>Number of Players:</h4>
<p>Modifies the number of players in the game. There is a minimum of 2 players, and a current MAXIMUM of 6 players.</p>
	
	There cannot be more players than the amount of names loaded into the game.

<h4>Number of Dice:</h4>
<p></p>Modifies the number of dice used, up to 2.</p>
	
	Adding 2 dice will mean that the double rule is added into the game, including triple rolling of doubles rule

<h3>READING THE FILES:</h3>
<p>The program reads in files to get information that allows the game to be played. If they are not recognised, ensure the files are named correctly and in the correct location.<br>Below is a guide to help you customise the file.</p>

	Examples are given at the bottom of this document

<h4>Names.txt</h4>
<p>Available list of players able to be loaded in. Default file has peice names for a base monopoly set, but can be changed to suit your game.</p>

<h4>Board.txt</h4>
<p>Reads in the board for the game to be played on. They can be changed to any type of board as long as it meets the requirements. There is no need to specify the size of the board.</p>
	
<strong>Type 1: <em>Property</em></strong>	Inputted as Type, Name, Cost to purchase, Rent, Colour
<br><strong>Type 2: <em>Utility</em></strong>	Inputted as Type, Name, Cost to purchase, Rent
<br><strong>Type 3: <em>Station</em></strong>	Inputted as Type, Name, Cost to purchase, Rent
<br><strong>Type 4: <em>Go</em></strong>	Inputed as Type, Name
<br><strong>Type 5: <em>Jail</em></strong>	Inputed as Type, Name
<br><strong>Type 6: <em>Go To Jail</em></strong>	Inputed as Type, Name
<br><strong>Type 7: <em>Chance</em></strong>	Inputed as Type, Name
<br><strong>Type 8: <em>Community Chest</em></strong>Inputed as Type, Name
<br><strong>Type 9: <em>Free Parking</em></strong>	Inputed as Type, Name
<br><strong>Type 10: <em>Tax Squares</em></strong>	Inputed as Type, Name, Amount

	Paying Rent:
		When paying rent, different tiles follow different rules. Below is an explanation of how the program calculates rent:

<strong>Type 1: <em>Property</em></strong>	Payment is based upon level of houses, the more houses that are in control of the player, the more the person pays in rent.
<br><strong>Type 2: <em>Utility</em></strong> Based on the amount of utilities under the players control. 
<br><strong>Type 3: <em>Station</em></strong> Based on the amount of stations the player controls. Typically goes up by 50.
<br><strong>Type 10: <em>Tax Squares</em></strong>	Calculates Tax with Modifier (+- 20% default)

		There is no limit to the size of the board, and is currently set to the default board

<h4>Chance.txt</h4>
<p>Contains chance cards, can be changed as long as they meet the requirements.</p>

<strong>Type 1: <em>Gain Money</em></strong>	Inputted as Type, Name, Amount
<br><strong>Type 2: <em>Lose Money</em></strong>	Inputted as Type, Name, Amount
<br><strong>Type 3: <em>Move Position</em></strong>		Inputted as Type, Name, Position, Collect Go
<br><strong>Type 4: <em>Get Out of Jail</em></strong>	Inputted as Type, Name
<br><strong>Type 5: <em>Go To jail</em></strong>	Inputted as Type, Name

	There is no limit to the amount of cards
<h4>Community Chest.txt</h4>
<p>Holds community chest cards, can be changed as long as they meet the requirements</p>
<strong>Type 1: <em>Gain Money</em></strong>	Inputted as Type, Name, Amount
<br><strong>Type 2: <em>Lose Money</strong></em>	Inputted as Type, Name, Amount
<br><strong>Type 3: <em>Move Position</em></strong>		Inputted as Type, Name, Position, Collect Go
<br><strong>Type 4: <em>Get Out of Jail</em></strong>	Inputted as Type, Name
<br><strong>Type 5: <em>Go To jail</em></strong>	Inputted as Type, Name
<br><strong>Type 6: <em>Payment of Property</em></strong>	Inputted as Type, Name, Payment for Properties

	There is no limit to the amount of cards
	(With Type 6, the game will handle the pay [price] for each house and [price] for each hotel)
<br><strong>Type 7: <em>All player collection</em></strong>		Inputted as Type, Name, Amount



<h3>WRITING YOUR OWN BOARD</h3>

<p>Writing your own board is possible, and uses the above list to write your own files. Below are examples based on the file</p>

<h4>board.txt</h4>
	
	1 Fake Street 100, 10, Brown
	2 Power Plant 100 10
	4 Go 
	10 Import Tax 100

<h4>chance.txt, community chest.txt</h4>

	1 You have been paid 100
	3 
	4 Get out of Jail
	6 Annual repairs on your property 10 100
