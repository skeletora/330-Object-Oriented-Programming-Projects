/*
Rebecca Aloisio
CSCI 330 001
Fall 2018
Program 1
This program contains the functions necessary to run a player in the game
*/
#ifndef PLAYER_DOT_H
#define PLAYER_DOT_H

#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include <string>
#include <cmath>
#include <iostream>

class PlayerClass{
	public:
		struct CellT{
			int row;
			int column;
		};
		enum AbilityType {DEX = 0, CON, INT, CHA, STR, WIS};
		enum RaceType {HUMAN = 0, ELF, ORC, TROLL, OGRE};
		enum MonStat {NUMDIE = 6, NUMFACES, HPBONUS};
	
		PlayerClass();
            //Narrative: Creates a player with the default values
            //Pre-condition: None
            //Post-condition: A PlayerClass initialized to the default values of name = "DEFAULT", race = HUMAN, voc = FTR
		PlayerClass(std::string iniName);
            //Narrative: Creates a player with the specified name
            //Pre-condition: None
            //Post-condition: A PlayerClass initialized to the values of name = iniName, race = HUMAN, voc = FTR
		PlayerClass(std::string iniName, RaceType iniRace);
            //Narrative: Creates a player with the specified name and race
            //Pre-condition: None
            //Post-condition: A PlayerClass initialized to the values of name = iniName, race = iniRace, 
            //                  voc = default vocation for race
		PlayerClass(std::string iniName, RaceType iniRace, VocRules::VocType iniVoc);
            //Narrative: Creates a player with the specified name, race, and vocation
            //Pre-condition: None
            //Post-condition: A PlayerClass initialized to the values of name = iniName, race = iniRace, voc = iniVoc
		
		std::string Name() const;
            //Narrative: returns the player’s name
            //Pre-condition: None
            //Post-condition: The player’s name is returned and no other changes are made
		RaceType Race() const;
            //Narrative: returns the player’s race
            //Pre-condition: None
            //Post-condition: The player’s race is returned and no other changes are made
        
		std::string RaceStr() const;
            //Narrative: returns the player’s race as a string
            //Pre-condition: None
            //Post-condition: The player’s race is returned as a string in all caps.
		VocRules::VocType Voc() const;
            //Narrative: returns the player’s voc
            //Pre-condition: None
            //Post-condition: The player’s voc is returned and no other changes are made
		std::string VocStr() const;
            //Narrative: returns the player’s voc as a string
            //Pre-condition: None
            //Post-condition: The player’s voc is returned as a string in all caps.
		int Row() const;
            //Narrative: returns the row the player is currently on on the board
            //Pre-condition: None
            //Post-condition: The player’s row is returned and no other changes are made
		int Col() const;
            //Narrative: returns the column the player is currently on on the board
            //Pre-condition: None
            //Post-condition: The player’s column is returned and no other changes are made
		int Level() const;
            //Narrative: returns the player’s level
            //Pre-condition: None
            //Post-condition: The player’s level is returned and no other changes are made
		int HP() const;
            //Narrative: returns the player’s currentHP
            //Pre-condition: None
            //Post-condition: The player’s currentHP is returned and no other changes are made
		int MaxHP() const;
            //Narrative: returns the player’s maxHP
            //Pre-condition: None
            //Post-condition: The player’s maxHP is returned and no other changes are made
		long XP() const;
            //Narrative: returns the player’s xp
            //Pre-condition: None
            //Post-condition: The player’s xp is returned and no other changes are made
		int Ability(AbilityType abil) const;
            //Narrative: returns the player’s ability stat in the specified ability
            //Pre-condition: None
            //Post-condition: The player’s ability stat is returned.  If an invalid ability is passed, 0 is returned.
		bool IsHumanoid() const;
            //Narrative: Determines if the player is humanoid or not
            //Pre-condition: None
            //Post-condition: True if the player is HUMAN, ELF, or ORC and false if they’re not
		bool IsMonster() const;
            //Narrative: Determines if the player is a monster or not
            //Pre-condition: None
            //Post-condition: True if the player is a TROLL or OGRE and false if they’re not
        bool IsDead() const;
            //Narrative: Determines if the player is dead or not
            //Pre-condition: None
            //Post-condition: True if the player's currentHP is equal to or below DEAD or 
            //                  if their constitution is below 0 and false if they don't meet these requirements
		bool IsDying() const;
            //Narrative: Determines if the player is dying or not
            //Pre-condition: None
            //Post-condition: True if the player's currentHP is below DISABLED and false otherwise
		bool IsDisabled() const;
            //Narrative: Determines if the player is rendered unable to take actions or not
            //Pre-condition: None
            //Post-condition: True if the player's currentHP is equal to or below DISABLED(0) and false otherwise
        
		int AbilityMod(AbilityType abil) const;
            //Narrative: Calculates the ability modifier based off of the player’s ability stat and returns it
            //Pre-condition: None
            //Post-condition: The ability modifier is returned and no other changes occurred
		bool SetCell(int newRow, int newCol);
            //Narrative: Updates the player’s current coordinates regardless of other fields.
            //Pre-condition: newRow and newCol must either both equal -1 or be greater than or equal to 0.
            //Post-condition: If coordinates are set the function returns true. In all other cases the function returns false.
		int UpdateHP(int modification);
            //Narrative: Updates the player’s HP by modification. A positive value will increase HP up to maxHP.  
            //              If value is less than zero, the HP is decreased.  HP can only be changed if the player is not DEAD.
            //Pre-condition: None
            //Post-condition: The updated HP is returned
		long UpdateXP(int value);
            //Narrative: Updates the player’s XP by value. A positive value will increase XP. An increase in XP could 
            //              cause a humanoid to be promoted to the next level within their vocation. If value is 
            //              less than zero, the XP is unchanged.   If a player is DISABLED, they cannot gain XP.
            //Pre-condition: None
            //Post-condition: The updated XP is returned
		bool operator ==(const PlayerClass& p) const;
            //Narrative: Compares the player to another player to see if they’re the same
            //Pre-condition: None
            //Post-condition: Returns true if they have the same, non case-sensitive name and false otherwise
		bool operator !=(const PlayerClass& p) const;
            //Narrative: Compares the player to another player to see if they’re different
            //Pre-condition: None
            //Post-condition: Returns false if they have the same, non case-sensitive name and true otherwise
		void Write(ostream& out) const;
            //Narrative: Outputs the player’s data
            //Pre-condition: None
            //Post-condition: Outputs the player's data in a single line with # separating the different parts
		
	
	private:
		static const int TOTAL_ABIL = 6;
        static const int TOTAL_RACES = 5;
        static const int TOTAL_HUMAN = 3;
        static const int TOTAL_MONST = 2;
        static const int TOTAL_MON_STAT = 3;
        static const std::string DFLT_NAME;
		static const RaceType DFLT_RACE;
		static const VocRules::VocType DFLT_VOC[TOTAL_RACES];
		static const int DEAD;
		static const int DISABLED;	
		static const std::string RACE_STRINGS[TOTAL_RACES];
		static const int ABILITY_ADJ_TABLE[TOTAL_HUMAN][TOTAL_ABIL];
		static const int MON_STAT_TABLE[TOTAL_MONST][TOTAL_ABIL + TOTAL_MON_STAT];
		static const int OFF_BOARD;
		static const int INIT_NUM_DIE;
		static const int INIT_DIE_FACES;
        static const int HP_DIE;
		
		std::string name;
		RaceType race;
		CellT cell;
		VocRules::VocType voc;
		int level;
		long xp;
		int currentHP;
		int maxHP;
		int ability[TOTAL_ABIL];
        
        void SetName(std::string iniName);
            //Narrative: Validates an inputted string and, if valid, has its value assigned to name
            //Pre-condition: None
            //Post-condition: name with a new value
        void SetRace(RaceType iniRace);
            //Narrative: Validates an inputted RaceType and, if valid, has its value assigned to race
            //Pre-condition: None
            //Post-condition: race with a new value
        void SetVoc(VocRules::VocType iniVoc);
            //Narrative: Validates an inputted VocType and, if valid, has its value assigned to voc
            //Pre-condition: None
            //Post-condition: voc with a new value
		void SetStats();
            //Narrative: Initializes stats for the PlayerClass
            //Pre-condition: None
            //Post-condition: Level, xp, currentHP, maxHP, cell, and ability are all initialized.
        
        int SetMaxHP(int number, int numFaces, int mod);
            //Narrative: Calculates the maxHP and its later increases.  If the calculated value is 
            //              less than or equal to 0, returns 1.
            //Pre-condition: number and numFaces are valid values for a player's hitdie roll
            //Post-condition: Returns the calculated value.
		void MakeHuman();
            //Narrative: Initializes stats for a humanoid PlayerClass
            //Pre-condition: None
            //Post-condition: level, ability, currentHP, and maxHP initialized
		void MakeMonst();
            //Narrative: Initializes stats for monster PlayerClass
            //Pre-condition: None
            //Post-condition: level, ability, currentHP, and maxHP initialized
        bool ValidAbil(AbilityType& abil) const;
            //Narrative: Checks that the passed ability is a valid one
            //Pre-condition: None
            //Post-condition: Returns true if abil is a valid AbilityType and false otherwise
        void LevelUp();
            //Narrative: Handles the changes in a characters stats when they level up
            //Pre-condition: None
            //Post-condition: Level will have been increased by 1, maxHP will have been increased, 
            //                  and currentHP has been set to maxHP
        
};

ostream& operator <<(ostream& out, const PlayerClass& c);
    //Narrative: Outputs the specified player’s data
    //Pre-condition: None
    //Post-condition: Outputs the specified player's data in a single line with # separating the different parts

#endif
