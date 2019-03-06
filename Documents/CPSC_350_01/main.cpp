/*
  a. Full Name: James Romero
  b. Student ID: 2334232
  c. Chapman email: jaromero@chapman.edu
  d. Course number and section: 350
  e. Assignment Number: 01
  */

#include "LifeGame.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void gamedata();

int main(int argc, char** argv)
{
  cout << "Welcome to Game of Life" << endl;
  cout << "Type 'Play' to start game, or 'Quit' to exit:";
    string choice;
    cin >> choice;

    if (choice == "Play" || choice == "play")
    {
      LifeGame Assignment2;

      Assignment2.Complete_System_Data(); // sets up the game

      Assignment2.Game_of_Life(); // runs the game loop
      cout << "Would you like to Play again? or Quit?" << endl;
			cout << "'Play' to play again, or 'Quit' to Quit." << endl;
			string choice;
			cin >> choice;
			if (choice == "Play")
			{
        LifeGame Assignment2;

        Assignment2.Complete_System_Data(); // sets up the game

        Assignment2.Game_of_Life(); // runs the game loop
			}
			else if (choice == "Quit")
			{
				return 0;
			}
    }

    else if (choice == "Quit")
    {
      return 0;
    }
}

void gamedata()
{
  LifeGame Assignment2;

  Assignment2.Complete_System_Data(); // sets up the game

  Assignment2.Game_of_Life(); // runs the game loop
}
/*
JamesMacBookPro:CPSC_350_01 jlloyd$ g++ main.cpp LifeGame.cpp
JamesMacBookPro:CPSC_350_01 jlloyd$ ./a.out
-------------------------------------------------------------------
                -x-x-x-x-x-Game of Life-x-x-x-x-x
-------------------------------------------------------------------
                               By: J.H. Conway

-------------------------------------------------------------------

 Game of Life is a simulation that models
 the life cycle of bacteria, providing
 entertainment wrapped up in what some
 would call mathematical elegance.

-------------------------------------------------------------------

 Would you like to start with a random configuration, or a flatfile configuration?
Respond with 'file' or 'random': file
Please enter .txt file name: test.txt
Now you will choose boundary conditions.

Boundary Modes and Conditions:


Classic Mode: All locations off the grid are considered to be empty
Doughnut mode: The grid is wrapped around itself horizontally and vertically,
resulting in a torus (doughnut) shape.
Mirror Mode: References off the grid are bounced back as though the wall were
a mirror.
Choose boundary mode: Classic, Doughnut, or Mirror? type C, D, or M: C
Did you want the game to pause automatically, have you press 'enter' to continue, or output results? Type P, E, or O: P
0
-X--X-----
--XX--X---
-X--X--X--
----X-----
---XX--X--
--X--XX---
---XX-X---
----X-X---
--X----X--
----------
1
--XX------
-XXXXX----
--X-XX----
----XX----
---XX-X---
--X---XX--
---XX-XX--
----X-XX--
----------
----------

2

-X--------
-X---X----
-XX---X---
------X---
---XX-XX--
--X-------
---XX---X-
---XX-XX--
----------
----------

3
----------
XX--------
-XX--XX---
--XX--X---
---X-XXX--
--X--X-X--
--X-XX-X--
---XXX-X--
----------
----------
4
----------
XXX-------
X--X-XX---
-X-X------
---X-X-X--
--X----XX-
--X----XX-
---X-X----
----X-----
----------


5
-X--------
XXX-------
X--XX-----
---X-X----
---XX-XXX-
--XX------
--XX--XXX-
---XX-----
----X-----
----------

6
XXX-------
X-XX------
X--XX-----
--X--XXX--
-----XXX--
-----X----
-------X--
--X-XX-X--
---XX-----
----------
n+
14
----------
--XX------
-X-----X--
--XX--X---
----------
----------
----------
----------
----------
----------

15
----------

--X-------
-X--------
--X-------
----------
----------
----------
----------
----------
----------

16
----------
----------
-XX-------
----------
----------
----------
----------
----------
----------
----------

17
----------
----------
----------
*/
//Mirror Mode
/*Mirror Mode: References off the grid are bounced back as though the wall were
a mirror.
Choose boundary mode: Classic, Doughnut, or Mirror? type C, D, or M: M
Did you want the game to pause automatically, have you press 'enter' to continue, or output results? Type P, E, or O: E
0
-X--X-----
--XX--X---
-X--X--X--
----X-----
---XX--X--
--X--XX---
---XX-X---
----X-X---

--X----X--
----------
Please press enter to continue simulation:
1
-X--XX----
-XXXXX----
--X-XX----
----XX----
---XX-X---
--X---XX--
---XX-XX--
----X-XX--
----------
----------
Please press enter to continue simulation:

2
XX----X---
-X----X---
-XX---X---
------X---
---XX-XX--
--X-------
---XX---X-
---XX-XX--
----------
Linter
Severity  Provider  Description Line
Git
GitHub
Too many changes

The repository at /Users/jlloyd has too many changed files to display in Atom. Ensure that you have set up an appropriate .gitignore file.
*/
