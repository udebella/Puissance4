#ifndef GRID_H
#define GRID_H

/********************************************INCLUDES**********************************************/
/* Standard Libraries */
#include <iostream>
#include <limits.h>

/* Project files */
#include "main.h"
/**************************************************************************************************/


/****************************************CLASS'S DEFINITION****************************************/
class Grid
{
	private:
		/* Attributes */
		Box grid[NB_LINE][NB_COLUMN]; /*!< Game's grid */
	
	public:
		/* Constructors */
		Grid(); /*!< Class's constructor */
		Grid(const Grid& g);
		
		/* Accessors */
		Box GetGrid(int line, int column) const;
		// int GetValue() const;
		// void SetValue(int newValue);
		
		/* Methods */
		void Print(std::ostream& cout = std::cout) const; /*!< Print the grid in standard output */
		bool Play(Box player, int column); /*!< Edit the grid when a player plays */
		bool Victory() const;
		int Mark(Box player) const;
};

/**************************************************************************************************/

#endif
