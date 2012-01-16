/*******************************************INCLUDES**********************************************/
/* Standard Libraries */
#include <iostream>

/* Project files */
#include "node.h"
/*************************************************************************************************/


/************************************CONSTRUCTORS' DEFINITION*************************************/
/**
 * \details Initialize the grid when it is created.
 */
Node::Node(Box p, int m, const Grid& grid)
{
	player = p;
	father = Grid(grid);
	move = m;
	value = grid.Mark(p);
}

//Node::Node() {}

Node::Node(const Node& n)
{
	player = n.GetPlayer();
	sons = n.GetSons();
	father = n.GetFather();
	move = n.GetMove();
	value = n.GetValue();
}

void Node::UpdateValue()
{
	value = father.Mark(player);
}

void Node::CreateChildren()
{
	int i;
	Node tempNode(EMPTY, -1, father);
	Box tempPlayer;
	
	if (player == BLUE)
		tempPlayer = RED;
	else
		tempPlayer = BLUE;
	for (i = 0; i < NB_COLUMN; i++)
	{
		if (father.GetGrid(0, i) == EMPTY)
		{
			tempNode = Node(tempPlayer, i, father);
			tempNode.GetFather().Play(player, i);
			tempNode.UpdateValue();
			/*std::cout<<"[DEBUG] valeurs de tempNode:"<<std::endl;
			std::cout<<"\ttempPlayer:"<<tempNode.GetPlayer()<<std::endl;
			std::cout<<"\tvalue:"<<tempNode.GetValue()<<std::endl;
			std::cout<<"\tfather.Mark(tempPlayer):"<<father.Mark(tempPlayer)<<std::endl;
			std::cout<<"\tmove:"<<tempNode.GetMove()<<std::endl;
			std::cout<<"[/DEBUG]"<<std::endl<<std::endl;*/
			sons.push_back(tempNode);
		}
	}
}

void Node::CreateTree(int depth)
{
	std::list<Node>::iterator it;
	int tempValue = 0;
	int tempMove = 0;
	
	if ((!father.Victory()) and (depth >= 0))
	{
		CreateChildren();
		for(it = sons.begin(); it != sons.end(); it++)
			(*it).CreateTree(depth - 1);
	}
	if (! sons.empty())
	{
		tempValue = sons.begin()->GetValue();
		for(it = sons.begin(); it != sons.end(); it++)
		{
			//std::cout<<"[DEBUG] comparaison de values:"<<std::endl;
			//std::cout<<"\tit->GetValue():"<<(*it).GetValue()<<std::endl;
			//std::cout<<"\ttemp:"<<tempValue<<std::endl;
			//std::cout<<"\ttest:"<<((*it).GetValue() > tempValue)<<std::endl;
			//std::cout<<"[/DEBUG]"<<std::endl<<std::endl;
			if (player == BLUE) // BLUE wants best value
			{
				if ((*it).GetValue() > tempValue) // Getting maximum value
				{
					//std::cout<<"\ttemp1:"<<tempValue<<std::endl;
					//std::cout<<"\tit->GetValue():"<<(*it).GetValue()<<std::endl;
					tempValue = (*it).GetValue();
					tempMove = (*it).GetMove();
					//std::cout<<"\ttemp2:"<<temp<<std::endl;
				}
			}
			else // RED wants worse value
			{
				if ((*it).GetValue() < tempValue) // Getting minimum value
				{
					//std::cout<<"\ttemp1:"<<tempValue<<std::endl;
					//std::cout<<"\tit->GetValue():"<<(*it).GetValue()<<std::endl;
					tempValue = (*it).GetValue();
					tempMove = (*it).GetMove();
					//std::cout<<"\ttemp2:"<<temp<<std::endl;
				}
			}
		}
		//std::cout<<"\ttemp/value:"<<temp<<std::endl;
		move = tempMove;
		value = tempValue;
	}
}

void Node::Print()
{
	std::list<Node>::iterator it;
	
	std::cout<<"[DEBUG]: Contenu de node "<<std::endl;
	std::cout<<"player :"<<player<<std::endl;
	std::cout<<"move :"<<move<<std::endl;
	std::cout<<"value :"<<value<<std::endl;
	std::cout<<"grid :"<<std::endl;
	father.Print();
	std::cout<<"Fils :"<<std::endl;
	if (! sons.empty())
	{
		for(it = sons.begin(); it != sons.end(); it++)
		{
			it->Print();
		}
	}
	std::cout<<"/Fils"<<std::endl;
	std::cout<<"[/DEBUG]"<<std::endl<<std::endl;
}

int Node::GetBestMove()
{
	return move;
}

void Node::Cleanse()
{
	std::list<Node>::iterator it;
	
	for (it = sons.begin(); it != sons.end(); it++)
	{
		(*it).Cleanse();
	}
	sons.clear();
}
