#pragma once
#include "Actor.h"
#include "Cube.h"
#include "Component.h"
#include "Teleporteur.h"
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <limits.h>
#include "Enemy.h"



void ReadFile(int numEtage, Actor* level,Actor* fpchara)
{
	for (float i = 0; i < numEtage; i++)
	{
		//std::cout << "AAAAAAAAAAAA";

		std::ifstream file("../../../../assets/txtLevel/Etage" + std::to_string((int)i));
		if (!file)
		{

			std::cout << "NotFind";
			std::cout << "../../../assets/txtLevel/Etage" + std::to_string((int)i);

			return;
		}
		float nbrow = 0;
		float nbline = 0;
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
						aaa = "cube " + std::to_string((int)i) +" "+ std::to_string((int)nbrow) +" "+ std::to_string((int)nbline);
						Cube* cube = new Cube(level, &aaa[0]);
						cube->setPosition(nbrow*2, i*2, nbline*2);
						aaa += "colision";
						CollisionComponent* col = new CollisionComponent(level, &aaa[0]);
						col->setPosition(nbrow * 2, i * 2, nbline * 2);
						col->setScale(1,1,1);

						// at position nbrow , numEtage , nbline 
					}
					break;
					case 'E': 
					{
						//Leved add ennemy
						aaa = "enemy"+std::to_string((int)i) + " " + std::to_string((int)nbrow) + " " + std::to_string((int)nbline);
						Enemy* enemy = new Enemy(&aaa[0]);
						enemy->setWorldPosition(nbrow * 2, i * 2, nbline * 2);
					}
					break;
					case 'T':
					{
						//level add Teleporteur
						aaa = "teleporteur" + std::to_string((int)i) + " " + std::to_string((int)nbrow) + " " + std::to_string((int)nbline);
						float telepPos[3] = { nbrow * 2,(i * 2) + 4*2,nbline * 2 };
						Teleporteur* teleporteur = new Teleporteur(&aaa[0],telepPos);
						teleporteur->setWorldPosition(nbrow * 2, i * 2, nbline * 2);
						
					}
						break;
					case 'S': 
					{
						//set player start
						fpchara->setWorldPosition(nbrow * 2, i * 2, nbline * 2);
					}
					break;
					case '0':
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
