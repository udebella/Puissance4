#ifndef NODE_H
#define NODE_H

/********************************************INCLUDES**********************************************/
/* Standard Libraries */
#include <list>

/* Project files */
#include "grid.h"
#include "main.h"
/**************************************************************************************************/


/****************************************CLASS'S DEFINITION****************************************/
class Node
{
	private:
		/* Attributes */
		Box player;
		Grid father;
		std::list<Node> sons;
		int value;
		int move;
	
	public:
		/* Constructors */
		Node(Box player, int m, const Grid& grid); /*!< Class's constructor */
		Node(const Node& n);
		//Node();
		void CreateChildren();
		void CreateTree(int depth);
		void Print();
		const Grid& GetFather() const {return father;}
		Grid& GetFather() {return father;}
		int GetValue() const {return value;}
		int GetMove() const {return move;}
		const std::list<Node>& GetSons() const {return sons;}
		Box GetPlayer() const {return player;}
		int GetBestMove();
		void Cleanse();
		void UpdateValue();
};

/**************************************************************************************************/

#endif
