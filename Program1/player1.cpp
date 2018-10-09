/*
Rebecca Aloisio
CSCI 330 001
Fall 2018
Program 1
This program contains the functions necessary to run a player in the game
*/
#include "player1.h"
#include "gamespace.h"
#include "voc.h"
#include "dice.h"
#include <string>
#include <cmath>
#include <iostream>
    using namespace std;
    using namespace GameSpace;

const string PlayerClass::DFLT_NAME = "DEFAULT";
const PlayerClass::RaceType PlayerClass::DFLT_RACE = PlayerClass::HUMAN;
const VocRules::VocType PlayerClass::DFLT_VOC[PlayerClass::TOTAL_RACES] = {VocRules::FTR, VocRules::WIZ, VocRules::BBN,
                                                                            VocRules::NNE, VocRules::NNE};
const int PlayerClass::DEAD = -10;
const int PlayerClass::DISABLED = 0;	
const int PlayerClass::TOTAL_ABIL;
const int PlayerClass::TOTAL_RACES;
const int PlayerClass::TOTAL_HUMAN;
const int PlayerClass::TOTAL_MONST;
const int PlayerClass::TOTAL_MON_STAT;
const int PlayerClass::INIT_NUM_DIE = 3;
const int PlayerClass::INIT_DIE_FACES = 6;
const int PlayerClass::HP_DIE = 1;
const int PlayerClass::OFF_BOARD = -1;
const string PlayerClass::RACE_STRINGS[TOTAL_RACES] = {"HUMAN", "ELF", "ORC", "TROLL", "OGRE"};

const int PlayerClass::ABILITY_ADJ_TABLE[TOTAL_HUMAN][TOTAL_ABIL] = {
    //				  DEX CON INT CHA STR WIS
    /*row 0 - HUMAN*/ {0,  0,  0,  0,  0,  0},
    /*row 1 - ELF  */ {2, -2,  0,  0,  0,  0},
    /*row 2 - ORC  */ {0,  0, -2, -2,  2, -1},
    };
const int PlayerClass::MON_STAT_TABLE[TOTAL_MONST][TOTAL_ABIL + TOTAL_MON_STAT] = {
    //				  DEX CON INT CHA STR WIS #ofDie #ofFaces HPBonus
    /*row 0 - TROLL*/ {14, 23,  6,  6, 23,  9,   6,     8,      36},
    /*row 1 - OGRE */ {8,  15,  6,  7, 21, 10,   4,     8,       8},
    };    
  
PlayerClass::PlayerClass(){
	SetName(DFLT_NAME);
	SetRace(PlayerClass::DFLT_RACE);
	SetVoc(DFLT_VOC[race]);
	PlayerClass::SetCell(OFF_BOARD, OFF_BOARD);
	SetStats();
	
	return;
}

PlayerClass::PlayerClass(std::string iniName){
	SetName(iniName);
	SetRace(PlayerClass::DFLT_RACE);
	SetVoc(DFLT_VOC[race]);
	PlayerClass::SetCell(OFF_BOARD, OFF_BOARD);
	SetStats();
	
	return;
}

PlayerClass::PlayerClass(std::string iniName, PlayerClass::RaceType iniRace){
	SetName(iniName);
	SetRace(iniRace);
	SetVoc(DFLT_VOC[race]);
	PlayerClass::SetCell(OFF_BOARD, OFF_BOARD);
	SetStats();
	
	return;
}

PlayerClass::PlayerClass(std::string iniName, PlayerClass::RaceType iniRace, VocRules::VocType iniVoc){
	SetName(iniName);
	SetRace(iniRace);
	SetVoc(iniVoc);
	PlayerClass::SetCell(OFF_BOARD, OFF_BOARD);
	SetStats();
	
	return;
}




void PlayerClass::SetName(string iniName){
    iniName = TrimStr(iniName);
    
	if(iniName.size() < 1){
		name = DFLT_NAME;
	}else{
		name = iniName;
	}
	
	return;
}

void PlayerClass::SetRace(PlayerClass::RaceType iniRace){
	if(0 <= iniRace and iniRace < TOTAL_RACES){
		race = iniRace;
	}else{
		race = PlayerClass::DFLT_RACE;
	}
	
	return;
}




void PlayerClass::SetVoc(VocRules::VocType iniVoc){
	if(0 < iniVoc and iniVoc < VocRules::NUM_VOC and PlayerClass::IsHumanoid()){
		voc = iniVoc;
	}else{
		voc = DFLT_VOC[race];
	}
	
	return;
}

void PlayerClass::SetStats(){
	xp = 0;
	PlayerClass::SetCell(OFF_BOARD, OFF_BOARD);
	if(PlayerClass::IsHumanoid()){
		MakeHuman();
	}else{
		MakeMonst();
	}
	
	return;
}

int PlayerClass::SetMaxHP(int number, int numFaces, int mod){
    int value;
    
    value = Dice::Roll(name, GameSpace::HP, number, numFaces) + mod;
    
    if(value < 1){
        value = 1;
    }
    
    return value;
}

void PlayerClass::MakeHuman(){
	int i;
	VocRules * vocRulesPtr = VocRules::GetVocRules();
    
    level = 1;
	
	for(i = DEX; i < TOTAL_ABIL; i++){
		ability[i] = Dice::Roll(Name(), GameSpace::RollType(i), INIT_NUM_DIE, INIT_DIE_FACES) + ABILITY_ADJ_TABLE[race][i];
	}
	
	maxHP = PlayerClass::SetMaxHP(PlayerClass::HP_DIE, vocRulesPtr->HitDie(PlayerClass::voc), PlayerClass::AbilityMod(CON));
	currentHP = maxHP;
    
	
	return;
}







void PlayerClass::MakeMonst(){
	int i;
    VocRules * vocRulesPtr = VocRules::GetVocRules();
    
    level = 0;
	
	for(i = DEX; i < TOTAL_ABIL; i++){
		ability[i] = MON_STAT_TABLE[race - TOTAL_HUMAN][i];
	}
	
	maxHP = PlayerClass::SetMaxHP(MON_STAT_TABLE[race - TOTAL_HUMAN][NUMDIE], MON_STAT_TABLE[race - TOTAL_HUMAN][NUMFACES], 
            MON_STAT_TABLE[race - TOTAL_HUMAN][HPBONUS]);
	currentHP = maxHP;
    
	
	return;
}


//observers
string PlayerClass::Name() const{
	return name;
}

PlayerClass::RaceType PlayerClass::Race() const{
	return race;
}

string PlayerClass::RaceStr() const{
	return PlayerClass::RACE_STRINGS[race];
}

VocRules::VocType PlayerClass::Voc() const{
	return voc;
}

string PlayerClass::VocStr() const{
    VocRules * vocRulesPtr = VocRules::GetVocRules();
        
    string s = vocRulesPtr->VOC_STR[voc];
    
	return s;
}

int PlayerClass::Row() const{
	return cell.row;
}

int PlayerClass::Col() const{
	return cell.column;
}

int PlayerClass::Level() const{
	return level;
}



int PlayerClass::HP() const{
	return currentHP;
}

int PlayerClass::MaxHP() const{
	return maxHP;
}

long PlayerClass::XP() const{
	return xp;
}

int PlayerClass::Ability(PlayerClass::AbilityType abil) const{
	int stat;
	
	if(0 <= abil and abil < PlayerClass::TOTAL_ABIL){
		stat = ability[abil];
	}else{
		stat = 0;
	}
	
	return stat;
}

bool PlayerClass::IsHumanoid() const{
	return race < TROLL;
}

bool PlayerClass::IsMonster() const{
	return race >= TROLL;
}

bool PlayerClass::IsDead() const{
	bool dead = false;
	
	if(currentHP <= PlayerClass::DEAD){
		dead = true;
	}
	if(ability[PlayerClass::CON] == 0){
		dead = true;
	}
	
	return dead;
}

bool PlayerClass::IsDying() const{
	return (PlayerClass::DISABLED > currentHP);
}

bool PlayerClass::IsDisabled() const{
	return currentHP <= PlayerClass::DISABLED;
}







//transformers
bool PlayerClass::ValidAbil(PlayerClass::AbilityType& abil) const{
    bool valid = true;
    
    if(0 > abil or abil > TOTAL_ABIL){
        valid = false;
    }
    
    return valid;
}

int PlayerClass::AbilityMod(PlayerClass::AbilityType abil) const{
	int mod;
	
	if(ValidAbil(abil)){
		mod = floor((float(ability[abil]) / 2.0) - 5.0);
	}else{
       return 0; 
    }
	
	return mod;
}


bool PlayerClass::SetCell(int newRow, int newCol){
	bool set = true;
	
	if(newRow == newCol and newRow == OFF_BOARD){
		cell.row = OFF_BOARD;
		cell.column = OFF_BOARD;
	}else if(newRow > -1 and newCol > -1 and newRow < NUMROWS and newCol < NUMCOLS){
		cell.row = newRow;
		cell.column = newCol;
	}else{
		set = false;
	}
	
	return set;
}


int PlayerClass::UpdateHP(int modification){
	if(not PlayerClass::IsDead()){
        if(currentHP + modification <= maxHP){
            currentHP = currentHP + modification;
        }else{
            currentHP = maxHP;
        }
    }
	
	return currentHP;
}







void PlayerClass::LevelUp(){
    VocRules * vocRulesPtr = VocRules::GetVocRules();
    
    level++;
    maxHP = maxHP + PlayerClass::SetMaxHP(PlayerClass::HP_DIE, vocRulesPtr->HitDie(voc), PlayerClass::AbilityMod(CON));
    currentHP = maxHP;
    
	return;
}

long PlayerClass::UpdateXP(int value){
    VocRules * vocRulesPtr = VocRules::GetVocRules();
        
	if(PlayerClass::IsHumanoid() and not PlayerClass::IsDisabled()){
		if(value > 0){
			xp = xp + value;
		}
		while(xp >= vocRulesPtr->XPforPromotion(level + 1) and level < vocRulesPtr->LEVEL_MAX){
			PlayerClass::LevelUp();
		}
	}
	
	return xp;
}


//operators
bool PlayerClass::operator ==(const PlayerClass& p) const{
	bool same = false;
	
	if(Ucase(name) == Ucase(p.Name())){
		same = true;
	}
	
	return same;
}

bool PlayerClass::operator !=(const PlayerClass& p) const{
	bool different = false;
	
	if(Ucase(name) != Ucase(p.Name())){
		different = true;
	}
	
	return different;
}











void PlayerClass::Write(std::ostream& out) const{
	int i;
	
	out << PlayerClass::RaceStr() << '#' << PlayerClass::VocStr() << '#' << PlayerClass::Level()  << '#' << PlayerClass::Name() 
		<< "#(" << PlayerClass::Row() << ',' << PlayerClass::Col() << ")#" << PlayerClass::MaxHP() << '#' << PlayerClass::HP() << "#[";
	for(i = PlayerClass::DEX; i < PlayerClass::TOTAL_ABIL; i++){
		out << PlayerClass::Ability(static_cast<PlayerClass::AbilityType>(i));
        if(i != PlayerClass::TOTAL_ABIL - 1){
            out << '#';
        }
	}
	out << "]#" << PlayerClass::XP() << endl;
        
    return;
}

ostream& operator <<(ostream& out, const PlayerClass& c){
    c.Write(out);
    
    return out;
}

