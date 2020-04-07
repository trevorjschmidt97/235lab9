#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <fstream>
#include "Set.h"
#include "HashMap.h"

using namespace std;	

int main(int argc, char* argv[])
{
	ifstream in(argv[1]);
	ofstream out(argv[2]);

	string line;
	HashMap<string, string> pokemon;
	HashMap<string, string> move;
	HashMap<string, Set<string>> effective;
	HashMap<string, Set<string>> ineffective;

	while (!in.eof())
	{
		getline(in, line);
		out << line;

		if (line.substr(0, 4) == "Set:")
		{
			Set<string> mySet;
			line = line.substr(5);
			stringstream ss(line);
			string word;
			while (ss >> word)
			{
				mySet.insert(word);
			}
			out << endl << "  [" << mySet.toString() << "]";
			mySet.clear();
		}

		if (line.substr(0, 8) == "Pokemon:")
		{
			line = line.substr(9);
			stringstream ss(line);
			string name;
			string type;
			ss >> name >> type;
			pokemon[name] = type;
		}

		if (line.substr(0, 5) == "Move:")
		{
			line = line.substr(6);
			stringstream ss(line);
			string name;
			string type;
			ss >> name >> type;
			move[name] = type;
		}

		if (line.substr(0, 10) == "Effective:")
		{
			line = line.substr(11);
			stringstream ss(line);
			string word, type;
			ss >> type;
			while (ss >> word)
			{
				effective[type].insert(word);
			}
		}

		if (line.substr(0, 12) == "Ineffective:")
		{
			line = line.substr(13);
			stringstream ss(line);
			string word, type;
			ss >> type;
			while (ss >> word)
			{
				ineffective[type].insert(word);
			}
		}

		if (line.substr(0, 7) == "Battle:")
		{
			int pokeVpoke2;
			int poke2Vpoke;
			// 0 - Ineffective, 1 - Effective, 2 - Super Effective
			line = line.substr(8);
			string poke, attack, poke2, attack2;
			stringstream ss(line);
			ss >> poke >> attack >> poke2 >> attack2;

			// Pretty simple printing to show what types/moves are being used
			out << endl << "  " << poke << "(" << attack << ") vs " << poke2 << " (" << attack2 << ")" << endl;
			out << "  " << poke << " is a " << pokemon[poke] << " type Pokemon." << endl;
			out << "  " << poke2 << " is a " << pokemon[poke2] << " type Pokemon." << endl;
			out << "  " << attack << " is a " << move[attack] << " type move." << endl;
			out << "  " << attack2 << " is a " << move[attack2] << " type move." << endl;
			out << "  " << attack << " is super effective against [" << effective[move[attack]] << "] type Pokemon." << endl;
			out << "  " << attack << " is ineffective against [" << ineffective[move[attack]] << "] type Pokemon." << endl;

			
			if (ineffective[move[attack]].toString().find(pokemon[poke2]) != string::npos)
			{ // If the second pokemon is found in the ineffectiveness of the move
				out << "  " << poke << "'s " << attack << " is ineffective against " << poke2 << endl;
				pokeVpoke2 = 0;
			}
			else if (effective[move[attack]].toString().find(pokemon[poke2]) != string::npos)
			{ // If the second pokemon is found in the effectiveness of the move
				out << "  " << poke << "'s " << attack << " is super effective against " << poke2 << endl;
				pokeVpoke2 = 2;
			}
			else
			{ // the second pokemon is not in the effective nor ineffective move set
				out << "  " << poke << "'s " << attack << " is effective against " << poke2 << endl;
				pokeVpoke2 = 1;
			}

			out << "  " << attack2 << " is super effective against " << "[" << effective[move[attack2]] << "]" << " type Pokemon." << endl;
			out << "  " << attack2 << " is ineffective against [" << ineffective[move[attack2]] << "] type Pokemon." << endl;

			if (ineffective[move[attack2]].toString().find(pokemon[poke]) != string::npos)
			{ // If the first pokemon is found in the ineffectiveness of the move
				out << "  " << poke2 << "'s " << attack2 << " is ineffective against " << poke << endl;
				poke2Vpoke = 0;
			}
			else if (effective[move[attack2]].toString().find(pokemon[poke]) != string::npos)
			{ // If the first pokemon is found in the effectiveness of the move
				out << "  " << poke2 << "'s " << attack2 << " is super effective against " << poke << endl;
				poke2Vpoke = 2;
			}
			else
			{ // the first pokemon is not in the effective nor ineffective move set
				out << "  " << poke2 << "'s " << attack2 << " is effective against " << poke << endl;
				poke2Vpoke = 1;
			}


			if (pokeVpoke2 > poke2Vpoke)
			{
				out << "  " << "In the battle between " << poke << " and " << poke2 << ", " << poke << " wins!" << endl;
			}
			else if (poke2Vpoke > pokeVpoke2)
			{
				out << "  " << "In the battle between " << poke << " and " << poke2 << ", " << poke2 << " wins!" << endl;
			}
			else
			{
				out << "  " << "The battle between " << poke << " and " << poke2 << " is a tie." << endl;
			}
		}

		if (line.substr(0, 7) == "Pokemon")
		{
			out << ": " << pokemon.size() << "/" << pokemon.max_size();
			out << pokemon.toString() << endl;
		}

		if (line.substr(0, 5) == "Moves")
		{
			out << ": " << move.size() << "/" << move.max_size();
			out << move.toString() << endl;
		}

		if (line.substr(0, 13) == "Effectivities")
		{
			out << ": " << effective.size() << "/" << effective.max_size();
			out << effective.toString() << endl;
		}

		if (line.substr(0, 15) == "Ineffectivities")
		{
			out << ": " << ineffective.size() << "/" << ineffective.max_size();
			out << ineffective.toString() << endl;
		}
		out << endl;
	}
	pokemon.clear();
	move.clear();
	effective.clear();
	ineffective.clear();


	system("pause");
	return 0;
}