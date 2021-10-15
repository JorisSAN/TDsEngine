#pragma once
#include "Actor.h"
#include "Cube.h"
#include "Component.h"
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <limits.h>
void ReadFile(int numEtage, Actor* level)
{
	for (int i = 0; i < numEtage; i++)
	{
		//std::cout << "AAAAAAAAAAAA";

		std::ifstream file("../../assets/txtlevel/Etage" + std::to_string(i));
		if (!file)
		{

			std::cout << "NotFind";

			return;
		}
		int nbrow = 0;
		int nbline = 0;
		std::string line;
		while (std::getline(file, line))
		{
			//std::cout << "line"<< std::to_string(nbline);

			for (std::string::iterator it = line.begin(); it != line.end(); ++it)
			{
				std::cout << *it;

				std::string aaa;
				switch (*it) 
				{
					case 'X': 
					{
						aaa = "cube" + std::to_string(i) + std::to_string(nbrow) + std::to_string(nbline);
						Cube* cube = new Cube(level, &aaa[0]);
						cube->setPosition(nbrow*2, i*2, nbline*2);
						// at position nbrow , numEtage , nbline 
					}
					break;
					case '0': 
					{
						//Leved add ennemy

					}
					break;
					case 'T':
					{
						//level add Teleporteur

					}
						break;
					case 'S': 
					{

						//set player start
					}
					break;
					case 'E':
					{
						//set player end

					}
						break;
					default: 
					{

					}
					break;
				}
				nbrow++;
			}
			nbline++;
			std::cout << "\n";

			nbrow = 0;
		}
		std::cout << "\n";
		std::cout << "\n";

		file.close();
	}

};
