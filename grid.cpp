/********************************************INCLUDES**********************************************/
/* Project files */
#include "grid.h"
/**************************************************************************************************/


/************************************CONSTRUCTORS' DEFINITION*************************************/
/**
 * \details Initialize the grid when it is created.
 */
Grid::Grid()
{
	int i, j;
	
	for(i = 0; i < NB_LINE; i++)
	{
		for(j = 0; j < NB_COLUMN; j++)
		{
			grid[i][j] = EMPTY;
		}
	}
}

Grid::Grid(const Grid& g)
{
	int i,j;
	
	for (i = 0; i < NB_LINE; i++)
	{
		for (j = 0; j < NB_COLUMN; j++)
		{
			grid[i][j] = g.GetGrid(i, j);
		}
	}
}

/**************************************************************************************************/


/**************************************ACCESSORS' DEFINITION**************************************/
Box Grid::GetGrid(int line, int column) const
{
	return grid[line][column];
}

/* int Grid::GetValue() const
{
	return value;
}*/

/* void Grid::SetValue(int newValue)
{
	value = newValue;
} */

/**************************************************************************************************/


/**************************************METHODS' DEFINITION****************************************/
/**
 * \details Print the grid on the standard output.
 * \param [OPTIONNAL] Stream on which we will print the grid (default = std::cout)
 */
void Grid::Print(std::ostream& cout) const
{
	int i, j;
	
	for(i = 0; i < NB_LINE; i++)
	{
		for(j = 0; j < NB_COLUMN; j++)
		{
			cout<<grid[i][j]<<" ";
		}
		cout<<std::endl;
	}
	//cout<<"Value: "<<value<<std::endl;
	cout<<std::endl;
}

/**
 * \details Choose the lower box in the column choosen and add the color of the player
 * \param
 * \param
 * \return true if the player managed to play else false
 */
bool Grid::Play(Box player, int column)
{
	int i = NB_LINE - 1;
	bool returnValue;
	
	while((grid[i][column] != EMPTY) and (i > 0))
	{
		i--;
	}
	if (grid[i][column] != EMPTY)
	{
		std::cout<<"Error : column complete"<<std::endl;
		returnValue = false;
	}
	else
	{
		//std::cout<<"Player "<<player<<" played: ("<<column<<","<<i<<")"<<std::endl;
		grid[i][column] = player;
		returnValue = true;
	}
	// value = Mark(player);
	//std::cout<<"Value: "<<Mark(player)<<std::endl;
	return returnValue;
}

/**
 * \details Tests the grid in order to know if someone won
 * \return EMPTY if noone won else return the color of the winner
 */
bool Grid::Victory() const
{
	int i = 0;
	int j = 0;
	bool victory = false;
	
	/*for (i = 0; i < NB_LINE; i++)
	{
		for(j = 0; j < NB_COLUMN; j++)
		{
			
		}
	}*/
	// Line victory
	while ((i < NB_LINE) and (victory != true))
	{
		while ((j <= (NB_COLUMN - 4)) and (victory != true))
		{
			if (grid[i][j] != EMPTY)
				if ((grid[i][j] == grid[i][j + 1]) and (grid[i][j] == grid[i][j + 2]) and (grid[i][j] == grid[i][j + 3]))
					victory = true;
			j++;
		}
		j = 0;
		i++;
	}
	// Column victory
	i = 0;
	j = 0;
	while ((i <= (NB_LINE - 4)) and (victory != true))
	{
		while ((j < NB_COLUMN) and (victory != true))
		{
			if (grid[i][j] != EMPTY)
				if ((grid[i][j] == grid[i + 1][j]) and (grid[i][j] == grid[i + 2][j]) and (grid[i][j] == grid[i + 3][j]))
					victory = true;
			j++;
		}
		j = 0;
		i++;
	}
	// Diagonal victory
	i = 0;
	j = 0;
	while ((i <= (NB_LINE - 4)) and (victory != true))
	{
		while ((j <= (NB_COLUMN - 4)) and (victory != true))
		{
			if (grid[i][j] != EMPTY)
				if ((grid[i][j] == grid[i + 1][j + 1]) and (grid[i][j] == grid[i + 2][j + 2]) and (grid[i][j] == grid[i + 3][j + 3]))
					victory = true;
			j++;
		}
		j = 0;
		i++;
	}
	// Antidiagonal victory
	i = 0;
	j = 3;
	while ((i <= (NB_LINE - 4)) and (victory != true))
	{
		while ((j < NB_COLUMN) and (victory != true))
		{
			if (grid[i][j] != EMPTY)
				if ((grid[i][j] == grid[i + 1][j - 1]) and (grid[i][j] == grid[i + 2][j - 2]) and (grid[i][j] == grid[i + 3][j - 3]))
					victory = true;
			j++;
		}
		j = 3;
		i++;
	}
	return victory;
}

/**
 * \details
 * \return
 */
int Grid::Mark(Box player) const
{
	int i = 0; /* Counter */
	int j = 0; /* Counter */
	int k = 0; /* Counter */
	int value = 0; /* Return value */
	
	for (i = 0; i < NB_LINE; i++)
	{
		for(j = 0; j < NB_COLUMN; j++)
		{
			if (grid[i][j] != EMPTY)
			{
				for(k = -1; k <= 1; k++)
				{
					if (grid[i][j] == grid[i - 1][j + k])
					{
						switch (k)
						{
							case -1: // Diagonal
								if (((i - 3) > 0) \
								and ((j - 3) > 0) \
								and ((grid[i - 2][j - 2] == grid[i][j]) or (grid[i - 2][j - 2] == EMPTY)) \
								and ((grid[i - 3][j - 3] == grid[i][j]) or (grid[i - 3][j - 3] == EMPTY)))
								{
									if ((grid[i - 2][j - 2] == player) and (grid[i - 3][j - 3] == player))
									{
										if (grid[i][j] == player)
											value += 100;
										else
											value -= 1000;
									}
									if ((grid[i - 2][j - 2] == player) or (grid[i - 3][j - 3] == player))
									{
										if (grid[i][j] == player)
											value += 10;
										else
											value -= 100;
									}
									if ((grid[i - 2][j - 2] == EMPTY) and (grid[i - 3][j - 3] == EMPTY))
									{
										if (grid[i][j] == player)
											value += 1;
										else
											value -= 1;
									}
								}
								break;
							case 0: // Column
								if (((i - 3) > 0) \
								and ((grid[i - 2][j] == grid[i][j]) or (grid[i - 2][j] == EMPTY)) \
								and ((grid[i - 3][j] == grid[i][j]) or (grid[i - 3][j] == EMPTY)))
								{
									if ((grid[i - 2][j] == player) and (grid[i - 3][j] == player))
									{
										if (grid[i][j] == player)
											value += 100;
										else
											value -= 1000;
									}
									if ((grid[i - 2][j] == player) or (grid[i - 3][j] == player))
									{
										if (grid[i][j] == player)
											value += 10;
										else
											value -= 100;
									}
									if ((grid[i - 2][j] == EMPTY) and (grid[i - 3][j] == EMPTY))
									{
										if (grid[i][j] == player)
											value += 1;
										else
											value -= 1;
									}
								}
								break;
							case 1: // Antidiagonal
								if (((i - 3) > 0) \
								and ((j + 3) < NB_COLUMN) \
								and ((grid[i - 2][j + 2] == grid[i][j]) or (grid[i - 2][j + 2] == EMPTY)) \
								and ((grid[i - 3][j + 3] == grid[i][j]) or (grid[i - 3][j + 3] == EMPTY)))
								{
									if ((grid[i - 2][j + 2] == player) and (grid[i - 3][j + 3] == player))
									{
										if (grid[i][j] == player)
											value += 100;
										else
											value -= 1000;
									}
									if ((grid[i - 2][j + 2] == player) or (grid[i - 3][j + 3] == player))
									{
										if (grid[i][j] == player)
											value += 10;
										else
											value -= 100;
									}
									if ((grid[i - 2][j + 2] == EMPTY) and (grid[i - 3][j + 3] == EMPTY))
									{
										if (grid[i][j] == player)
											value += 1;
										else
											value -= 1;
									}
								}
								break;
						}
					}
					if (grid[i][j] == grid[i][j + k])
					{
						switch (k)
						{
							case -1: // Line
								if (((j - 3) > 0) \
								and ((grid[i][j - 2] == grid[i][j]) or (grid[i][j - 2] == EMPTY)) \
								and ((grid[i][j - 3] == grid[i][j]) or (grid[i][j - 3] == EMPTY)))
								{
									if ((grid[i][j - 2] == player) and (grid[i][j - 3] == player))
									{
										if (grid[i][j] == player)
											value += 100;
										else
											value -= 1000;
									}
									if ((grid[i][j - 2] == player) or (grid[i][j - 3] == player))
									{
										if (grid[i][j] == player)
											value += 10;
										else
											value -= 100;
									}
									if ((grid[i][j - 2] == EMPTY) and (grid[i][j - 3] == EMPTY))
									{
										if (grid[i][j] == player)
											value += 1;
										else
											value -= 1;
									}
								}
								break;
							case 1: // Line
								if (((j + 3) < NB_COLUMN) \
								and ((grid[i][j + 2] == grid[i][j]) or (grid[i][j + 2] == EMPTY)) \
								and ((grid[i][j + 3] == grid[i][j]) or (grid[i][j + 3] == EMPTY)))
								{
									if ((grid[i][j + 2] == player) and (grid[i][j + 3] == player))
									{
										if (grid[i][j] == player)
											value += 100;
										else
											value -= 1000;
									}
									if ((grid[i][j + 2] == player) or (grid[i][j + 3] == player))
									{
										if (grid[i][j] == player)
											value += 10;
										else
											value -= 100;
									}
									if ((grid[i][j + 2] == EMPTY) and (grid[i][j + 3] == EMPTY))
									{
										if (grid[i][j] == player)
											value += 1;
										else
											value -= 1;
									}
								}
								break;
						}
					}
					if (grid[i][j] == grid[i + 1][j + k])
					{
						switch (k)
						{
							case -1: // Antidiagonal
								if (((i + 3) < NB_LINE) \
								and ((j - 3) > 0) \
								and ((grid[i + 2][j - 2] == grid[i][j]) or (grid[i + 2][j - 2] == EMPTY)) \
								and ((grid[i + 3][j - 3] == grid[i][j]) or (grid[i + 3][j - 3] == EMPTY)))
								{
									if ((grid[i + 2][j - 2] == player) and (grid[i + 3][j - 3] == player))
									{
										if (grid[i][j] == player)
											value += 100;
										else
											value -= 1000;
									}
									if ((grid[i + 2][j - 2] == player) or (grid[i + 3][j - 3] == player))
									{
										if (grid[i][j] == player)
											value += 10;
										else
											value -= 100;
									}
									if ((grid[i + 2][j - 2] == EMPTY) and (grid[i + 3][j - 3] == EMPTY))
									{
										if (grid[i][j] == player)
											value += 1;
										else
											value -= 1;
									}
								}
								break;
							case 0: // Column
								if (((i + 3) < NB_LINE) \
								and ((grid[i + 2][j] == grid[i][j]) or (grid[i + 2][j] == EMPTY)) \
								and ((grid[i + 3][j] == grid[i][j]) or (grid[i + 3][j] == EMPTY)))
								{
									if ((grid[i + 2][j] == player) and (grid[i + 3][j] == player))
									{
										if (grid[i][j] == player)
											value += 100;
										else
											value -= 1000;
									}
									if ((grid[i + 2][j] == player) or (grid[i + 3][j] == player))
									{
										if (grid[i][j] == player)
											value += 10;
										else
											value -= 100;
									}
									if ((grid[i + 2][j] == EMPTY) and (grid[i + 3][j] == EMPTY))
									{
										if (grid[i][j] == player)
											value += 1;
										else
											value -= 1;
									}
								}
								break;
							case 1: // Diagonal
								if (((i + 3) < NB_LINE) \
								and ((j + 3) < NB_COLUMN) \
								and ((grid[i + 2][j + 2] == grid[i][j]) or (grid[i + 2][j + 2] == EMPTY)) \
								and ((grid[i + 3][j + 3] == grid[i][j]) or (grid[i + 3][j + 3] == EMPTY)))
								{
									if ((grid[i + 2][j + 2] == player) and (grid[i + 3][j + 3] == player))
									{
										if (grid[i][j] == player)
											value += 100;
										else
											value -= 1000;
									}
									if ((grid[i + 2][j + 2] == player) or (grid[i + 3][j + 3] == player))
									{
										if (grid[i][j] == player)
											value += 10;
										else
											value -= 100;
									}
									if ((grid[i + 2][j + 2] == EMPTY) and (grid[i + 3][j + 3] == EMPTY))
									{
										if (grid[i][j] == player)
											value += 1;
										else
											value -= 1;
									}
								}
								break;
						}
					}
				}
			}
		}
	}
	return value;
}

/**************************************************************************************************/

