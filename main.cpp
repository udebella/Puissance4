/********************************************INCLUDES**********************************************/
/* Standard Libraries */
#include <cstdlib>
#include <iostream>
#include <time.h>

/* Qt Libraries */
// #include <QApplication> /* unused for now */

/* Project files */
#include "main.h"
#include "grid.h"
#include "node.h"
/**************************************************************************************************/


/******************************************MAIN FUNCTION*******************************************/
int main(int argc, char* argv[])
{
	Grid grid;
	int value;
	Box player = RED;
	bool debug = false;
	//int i;
	//clock_t start, end;
	//double elapsed;
	
	if ((argc == 2) and (*argv[1] == 'O'))
	{
		std::cout<<"[Mode debug: ON]"<<std::endl;
		debug = true;
	}
	else
	{
		std::cout<<"[Mode debug: OFF]"<<std::endl;
	}
	/*grid.Print();
	start = clock(); // Start clock
	test.CreateTree(DEPTH_AI);
	end = clock(); // stop clock
	elapsed = ((double)end - start) / CLOCKS_PER_SEC;
	std::cout<<"\tExecution Time: "<<elapsed<<" sec"<<std::endl; // print clock*/
	/*std::cout<<"DEBUT DE PRINT"<<std::endl;
	std::cout<<"Value: "<<test.GetValue()<<std::endl;
	std::cout<<"BestMove: "<<test.GetBestMove()<<std::endl;
	test.Print(2);
	std::cout<<"FIN DE PRINT"<<std::endl;*/
	/*grid.Play(RED, test.GetBestMove());
	std::cout<<"FINAL GRID"<<std::endl;
	grid.Print();
	test.Cleanse();*/
	while(! grid.Victory())
	{
		if (player == RED)
			player = BLUE;
		else
			player = RED;
		grid.Print();
		std::cout<<"Player: "<<player<<std::endl;
		if (player == BLUE)
		{
			std::cout<<"Choose a column: ";
			std::cin>>value;
		}
		else
		{
			Node test(RED, -1, grid);
			test.CreateTree(DEPTH_AI);
			value = test.GetBestMove(); // TODO Ya du boulot sur la gestion de l'arbre !
			std::cout<<"Player plays: "<<value<<std::endl;
			if (debug == true)
			{
				std::cout<<"\t\t\tDEBUT DE PRINT"<<std::endl;
				test.Print();
				std::cout<<"\t\t\tFIN DE PRINT"<<std::endl;
				std::cout<<std::endl<<"Final grid :"<<std::endl;
			}
			test.Cleanse();
		}
		grid.Play(player, value);
		std::cout<<"Valeur de la grille: "<<grid.Mark(player)<<std::endl;
		std::cout<<"Fin du tour\n";
		//std::cout<<"Value of the grid: "<<grid.Mark(player)<<std::endl;
	}
	grid.Print();
	std::cout<<player<<" won !"<<std::endl;
	return EXIT_SUCCESS;
}
/**************************************************************************************************/
