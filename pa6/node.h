#pragma once

#include <list>
#include <vector>
#include <string>
#include <map>

struct CodeContext
{
	std::vector<std::string> mOps;
};

class Node
{
public:
	virtual void CodeGen(CodeContext& context) const = 0;
};

class NNumeric : public Node
{
public:
	NNumeric(std::string& value);
	int mvalue;
	virtual void CodeGen(CodeContext& context) const override { }
};

class NStatement : public Node
{
};

class NRotate : public NStatement
{
public:
	NRotate(NNumeric* dir);
	virtual void CodeGen(CodeContext& context) const override;
private:
	NNumeric* mDir;
};

class NBoolean : public Node
{
};

class NBlock : public Node
{
public:
	NBlock() { mbMainBlock = false; }
	virtual void CodeGen(CodeContext& context) const override;
	void AddStatement(NStatement* statement);
	void SetMainBlock() { mbMainBlock = true; }
private:
	std::list<NStatement*> mStatements;
	bool mbMainBlock;
};

class NForward : public NStatement
{
public:
	NForward(){}
	virtual void CodeGen(CodeContext& context) const override;
};

class NAttack : public NStatement
{
public:
	virtual void CodeGen(CodeContext& context) const override;
};

class NRangedAttack : public NStatement
{
public:
	virtual void CodeGen(CodeContext& context) const override;
}; 

class Is_Test : public Node
{
public:
	Is_Test(std::string testname);
	Is_Test(std::string testname, int number); 
	virtual void CodeGen(CodeContext& context) const override;
private:
	std::string mTestname; 
	int mNumber;
};

class Is_Human : public NStatement
{
public:
	Is_Human(int n); 
	virtual void CodeGen(CodeContext& context) const override;
private:
	int mValue; 
};

class Is_Zombie : public NStatement
{
public:
	Is_Zombie(int n);
	virtual void CodeGen(CodeContext& context) const override;
private:
	int mValue; 
};

class Is_Passable : public NStatement
{
public:
	virtual void CodeGen(CodeContext& context) const override;
};

class Is_Random : public NStatement
{
public:
	virtual void CodeGen(CodeContext& context) const override;
};

class Is_Wall : public NStatement
{
public:
	virtual void CodeGen(CodeContext& context) const override;
};