#include "node.h"
#include <sstream>

void NBlock::AddStatement(NStatement* statement)
{
	mStatements.push_back(statement);
}

void NBlock::CodeGen(CodeContext& context) const
{
	// TODO: Loop through statements in list and code gen them
	for each (NStatement* state in mStatements)
	{
		state->CodeGen(context); 
	}
}

NNumeric::NNumeric(std::string& value)
{
	mvalue = std::atoi(value.c_str());
}

NRotate::NRotate(NNumeric* dir)
	: mDir(dir)
{
}

void NRotate::CodeGen(CodeContext& context) const
{
	if (mDir->mvalue == 0)
	{
		context.mOps.push_back("rotate,0");
	}
	else if (mDir->mvalue == 1)
	{
		context.mOps.push_back("rotate,1");
	}
}



void NForward::CodeGen(CodeContext & context) const
{
	context.mOps.push_back("forward");
}

void NRangedAttack::CodeGen(CodeContext & context) const
{
		context.mOps.push_back("ranged_attack");

}

void NAttack::CodeGen(CodeContext & context) const
{
	context.mOps.push_back("attack");
}

Is_Human::Is_Human(int n) : mValue(n)
{
}

void Is_Human::CodeGen(CodeContext & context) const
{
	context.mOps.push_back("test_human,"+mValue);
}

Is_Zombie::Is_Zombie(int n) : mValue(n)
{
}

void Is_Zombie::CodeGen(CodeContext & context) const
{
	context.mOps.push_back("test_zombie," + mValue);
}

void Is_Passable::CodeGen(CodeContext & context) const
{
	context.mOps.push_back("test_passable");
}

void Is_Random::CodeGen(CodeContext & context) const
{
	context.mOps.push_back("test_random");

}

void Is_Wall::CodeGen(CodeContext & context) const
{
	context.mOps.push_back("test_wall");
}

Is_Test::Is_Test(std::string testname) : mTestname(testname), mNumber(-1)
{
}

Is_Test::Is_Test(std::string testname, int number) : mTestname(testname), mNumber(number)
{
}

void Is_Test::CodeGen(CodeContext & context) const
{
}
