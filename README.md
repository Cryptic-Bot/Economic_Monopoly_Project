Economic Monopoly Rules

Note: Currently a work in progress
Note 2: Not a game/add-on with a fancy GUI. Think more a sophisitcated text-based game that does what it needs to do.

> Base Rules

Hi there! 

I made this modified game to spice up Monopoly. 
This is meant to be an add-on rather than a total overhaul and as such still requires a physical monopoly board/setup to work. 

Regular Monopoly is kind of boring. Every trip around the board gives everyone the same amount of income. When does everyone in the real world have the same amount of income? What about economic conditions? Where are the loans? The uncertainty? I mean yes, there is uncertainty to some degree based on where the players land or what cards they get from community chest, but that’s nothing in comparison to the greater economy of the real world. Inflation, government policies, taxes, housing policy, banks, federal banks, jobs. They’re part of what makes the economy of the real world so intricate and interesting. 

So the plan here is to change that and automate a lot of the functions at the same time to keep it simple. I would not want to do the math and keep track of just the loans alone (math ain’t that fun thx). I had fun making this and I hope you get even a fraction of that fun if you decide to play the game.

Happy playing entrepreneurs!

P.S. I added some easter eggs for funzies, so have fun finding them! They’re harmless. Mostly. Probably.



> Primary Differences (to classic Monopoly)

No use of cash! Everything is electronic. There is actually a version of monopoly that does this as well (Monopoly Electronic Banking Edition)
Because the game is played on a single computer (in game version 1.0), the computer stays facing forward (preferably) => cheating is not always easy to fix, eg:
Monetary transfers from one player to another (without permission or need)
Falsely reporting events (such as passing go)
Etc.
But do know that everything is recorded! The event log might be hard to dig through, but it doesn’t ever disappear as long as the game is being played
Endgame is different
Normally bankruptcy alone is endgame (last man standing)
And even then, bankruptcy does not mean the same thing with the addition of loans (bankruptcy = insolvent)
But now there is also the monopoly endgame (having a certain marketshare)
Or potentially? the wealth inequality endgame (haven't decided whether or not to add it yet. Maybe later…)

> Endgame
Game ends when:
1. Bankruptcy: All but one player is bankrupt
2. Monopoly: Any player or group of players occupy greater than or equal to a fixed percentage of market share of properties on the game board
 Variable to number of players for fairness, eg ⅔ market for 2 players
3. (Potentially, haven't decided if I want to do this yet) Wealth Inequality (Net Worth Dominance): Net worth of any player is 5x that of the sum of all other players

> Income
Players receive income when passing GO depending on the selected job/economy setting
Incomes regardless of setting are subject to change with market conditions
  > Settings:
1. Collective Economy
- All players earn an equal fixed income regardless of role or job
- Everyone is assigned a “Comrade” job class
- Emphasizes economic equality and shared prosperity, simulating a system where wealth is evenly distributed
2. Market Economy
- Players are randomly assigned preset jobs, each with distinct income levels
- Simulates a competitive labor market where income varies based on occupation
3. Meritocracy Choice
- Player freely select jobs from preset list
- Requires players to decide balancing income potential, tax risks and abilities
4. Income Volatility
- Players receive randomly assigned incomes without choice for job titles
- Everyone is assigned a “Freelancer” class job
- Simulates economic unpredictability and fluctuating earnings driven by economic conditions and chance

> Functions and Components

  > Loans
1. Bank
Bank will not approve loans when player’s total loans value is greater than 50% of their total assets (cash + property holdings + loans to other players)

Player net worth (PNW) = (Total Assets, TA)  - (Total Liabilities, TL)
TA = (Cash) + (Current Value of Property Holdings) + (Outstanding Loans to Other Players)
TL = (Bank Loans) + (Player to Player Loans) + 

2. Player to Player
- No maximums; the only constraint at start is risk and reward evaluated at player’s discretion
- Players may offer loans at any interest rate, although a suggested rate or range of rates will be given based on economic conditions
- Players have the right to call loans for payback in part or full if they reach the point of bankruptcy, which may lead to unintended financial conditions for other players
- Loans are given at players own risk as giving out excessive leveraging (lending as a percentage of total assets) may lead to quicker bankruptcy under poor economic conditions, unexpected events and/or unexpected financial payments

  > Taxes
1. Income Tax
- Happens when you land on the income tax square or by random event
- Variable to economic conditions and government policy action events
- Base Rate = dependent on current income (0%, 10%, 25%, 40%)
2. Luxury Tax
Happens when you land on the luxury tax square
Variable to economic conditions and government policy action events

  > Properties
Three types of properties in classic Monopoly: streets (w/ color sets), railroads and utilities
Buying unowned properties


Economic Events
Random events that impact property value, rent and/or bank interest rates

Recession/economic crises
Economic booms
Inflation
Deflation
Government subsidies (eg welfare or stimulus checks in times of crisis)


