#pragma once
#include <string>
#include <vector>
#include "Machine.h"
#include "Traits.h"
#include <memory>
class World
{
public:
	static const int DIMENSION = 20; 
	World(); 
	void Attack(bool infectOnAttack,const int x, const int y);
	void Move(MachineState& machState);
	bool IsInBounds(const int xloc, const int yloc) { return (xloc >= 0) && (xloc < DIMENSION) && (yloc >= 0) && (yloc < DIMENSION); }
	bool IsOccupied(const int xloc, const int yloc);
	void LoadZombie(const std::string& filename);
	void LoadSurvivor(const std::string& filename); 
private:
	std::vector<std::shared_ptr<Machine<HumanTraits>>> mSurvivors;
	std::vector<std::shared_ptr<Machine<ZombieTraits>>> mZombies;
	std::vector<std::shared_ptr<MachineState>>  mStates; 
	std::shared_ptr<Machine<HumanTraits>> mHumanGrid[DIMENSION][DIMENSION];
	std::shared_ptr<Machine<ZombieTraits>> mHumanGrid[DIMENSION][DIMENSION]; 
};