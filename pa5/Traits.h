#pragma once
struct ZombieTraits
{
	const static int ACTIONS_PER_TURN = 1;
	const static bool INFECT_ON_ATTACK = true;
};

struct HumanTraits
{
	const static int ACTIONS_PER_TURN = 2;
	const static bool INFECT_ON_ATTACK = false;
};
