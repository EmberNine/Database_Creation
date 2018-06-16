//Armando Cardona armandocardona@my.unt.edu
//ac0925
/*main.cpp*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;
const int TABLE_SIZE = 193;
const int TABLE_SIZE2 = 19;
const int TABLE_SIZE3 = 193;
const int TABLE_SIZE4 = 1543;
const int SI_TABLE_SIZE = 19;


class HashEntry {
private:

public:
	//#############################################################################################
	//
	//               STRUCTS FOR MY DATA TABLES AS WELL AS TABLES AND CONTSTUCTORS
	//
	//#############################################################################################
	struct ncm //will be used to store the data from data1.txt
	{
		string p_name; //player name
		string p_class; //player class
		string si1_class; //player class
		int p_m_level; // player max spell level 
		ncm* next;
		ncm** tuplelocation;


	};

	struct scl //will be used to store the data from data2.txt
	{
		string s_name; //spell name
		string s_class; //spell class
		int s_m_level; //spell max level
		scl* next;


	};
	struct st //will be used to store the data from data3.txt
	{
		string s_name; //spell name
		string s_type; //spell type
		st* next;


	};
	struct com //combined struct
	{
		string my_name;
		string my_class;
		int my_lvl;
		string spell_name;
		int spell_lvl;
		string spell_type;
		com *next;
	};

	int COUNTP1=0;
	int COUNTP2=0;
	int TCOUNT=0;

	ncm* HashTable1[TABLE_SIZE]; //hashtable for data1.txt
	ncm* siHashTable1[SI_TABLE_SIZE];//hashtable for secondary search index for data1
	scl* HashTable2[TABLE_SIZE2]; //hashtable for data2.txt
	st*  HashTable3[TABLE_SIZE3]; // hashtable for data3.txt
	com* HashTable4[TABLE_SIZE4]; // hashtable for data3.txt

	int data1_globalCount = 0;// These are used to help count and verify datatable entries
	int data2_globalCount = 0;
	int data3_globalCount = 0;
	int data4_globalCount = 0;

	HashEntry() //constructor that fills in default values for the hash table 
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			HashTable1[i] = new ncm;
			HashTable1[i]->p_name = "empty";
			HashTable1[i]->p_class = "empty";
			HashTable1[i]->p_m_level = 0;
			HashTable1[i]->si1_class = "empty";
			HashTable1[i]->tuplelocation = 0;
			HashTable1[i]->next = NULL;
		}
		for (int i = 0; i < SI_TABLE_SIZE; i++)
		{
			siHashTable1[i] = new ncm;
			siHashTable1[i]->p_name = "empty";
			siHashTable1[i]->p_class = "empty";
			siHashTable1[i]->p_m_level = 0;
			siHashTable1[i]->si1_class = "empty";
			siHashTable1[i]->tuplelocation = 0;
			siHashTable1[i]->next = NULL;
		}
		for (int i = 0; i < TABLE_SIZE2; i++)
		{
			HashTable2[i] = new scl;
			HashTable2[i]->s_name = "empty";
			HashTable2[i]->s_class = "empty";
			HashTable2[i]->s_m_level = 0;
			HashTable2[i]->next = NULL;
		}
		for (int i = 0; i < TABLE_SIZE3; i++)
		{
			HashTable3[i] = new st;
			HashTable3[i]->s_name = "empty";
			HashTable3[i]->s_type = "empty";
			HashTable3[i]->next = NULL;
		}
		for (int i = 0; i < TABLE_SIZE4; i++)
		{
			HashTable4[i] = new com;
			HashTable4[i]->my_name = "empty";
			HashTable4[i]->my_class = "empty";
			HashTable4[i]->my_lvl = 0;
			HashTable4[i]->spell_name = "empty";
			HashTable4[i]->spell_lvl = 0;
			HashTable4[i]->spell_type = "empty";
			HashTable4[i]->next = NULL;
		}
	}

	//#############################################################################################
	//
	//                      FUNCTIONS TO READ IN DATA FROM FILES
	//
	//#############################################################################################

	void readData1()
	{
		//------------------------------------------------------------- Reads in data1
		ifstream myReadFile;
		myReadFile.open("data1.txt");
		char pn[50]; //player name
		char pc[50]; //player class
		int ml; //plaser max level
		char dummyline[100];

		if (myReadFile.is_open())
		{
			myReadFile >> dummyline >> dummyline >> dummyline;
		}

		if (myReadFile.is_open())
		{
			int count1 = 1;
			while (myReadFile >> pn >> pc >> ml)
			{
				add_data1(pn, pc, ml);

				count1++;
			}
		}
		myReadFile.close();

	}

	void readData2()
	{
		//------------------------------------------------------------- Reads in data1
		ifstream myReadFile;
		myReadFile.open("data2.txt");
		char pn[50]; //player name
		char pc[50]; //player class
		int ml; //plaser max level
		char dummyline[100];

		if (myReadFile.is_open())
		{
			myReadFile >> dummyline >> dummyline >> dummyline;
		}

		if (myReadFile.is_open())
		{
			int count1 = 1;
			while (myReadFile >> pn >> pc >> ml)
			{
				add_data2(pn, pc, ml);

				count1++;
			}
		}
		myReadFile.close();

	}

	void readData3()
	{
		//------------------------------------------------------------- Reads in data1
		ifstream myReadFile;
		myReadFile.open("data3.txt");
		char pn[50]; //player name
		char pc[50]; //player class
		char dummyline[100];

		if (myReadFile.is_open())
		{
			myReadFile >> dummyline >> dummyline;
		}

		if (myReadFile.is_open())
		{
			int count1 = 1;
			while (myReadFile >> pn >> pc)
			{
				add_data3(pn, pc);

				count1++;
			}
		}
		myReadFile.close();

	}

	//#############################################################################################
	//
	//               FUNCTIONS TO ADD DATA TO TABLES AS THEY ARE BEING READ IN 
	//
	//#############################################################################################

	void add_data1(string n, string c, int ml) // Adds to HashTable
	{

		int index = ncm_Hash(n);
		int index2 = sic_Hash(c);
	
		if (HashTable1[index]->p_name == "empty")
		{
			HashTable1[index]->p_name = n;
			HashTable1[index]->p_class = c;
			HashTable1[index]->p_m_level = ml;

		}

		else
		{
			ncm* j = HashTable1[index];
			ncm* p = new ncm;
			p->p_name = n;
			p->p_class = c;
			p->p_m_level = ml;
			p->next = NULL;

			while (j->next != NULL)
			{
				j = j->next;
			}
			j->next = p;
		}

		//cout << "COUNT: "<< data1_globalCount << endl;
		addsi_data1(index, index2);
	}
	void add_data2(string n, string c, int ml) // Adds to HashTable
	{

		int index = ncm_Hash2(c);

		if (HashTable2[index]->s_class == "empty")
		{
			HashTable2[index]->s_class = c;
			HashTable2[index]->s_name = n;
			HashTable2[index]->s_m_level = ml;

		}

		else
		{
			scl* j = HashTable2[index];
			scl* p = new scl;
			p->s_name = n;
			p->s_class = c;
			p->s_m_level = ml;
			p->next = NULL;

			while (j->next != NULL)
			{
				j = j->next;
			}
			j->next = p;
		}
	}

	void add_data3(string n, string c) // Adds to HashTable
	{

		int index = ncm_Hash(n);
	

		if (HashTable3[index]->s_name == "empty")
		{
			HashTable3[index]->s_name = n;
			HashTable3[index]->s_type = c;
		}
		else
		{
			st* j = HashTable3[index];
			st* p = new st;
			p->s_name = n;
			p->s_type = c;
			p->next = NULL;

			while (j->next != NULL)
			{
				j = j->next;
			}
			j->next = p;
		}
	}

	void add_data4() // combines hash table
	{
		string n; //player name
		string spell; //player spell
		string clas; //player class
		int index1 = 0; //used to iterate through table 1
		int index2 = 0; //used to get class location from table 2
		int index3; // used to get index of Combined table 
		int index4; // used to get index of spell for searching data 3;
		scl* j;
		com* k;
		com* h;
		int BULL;

		while (index1 <= TABLE_SIZE)
		{
			ncm* p = HashTable1[index1];
			if (p->p_name != "empty")
			{
				if (p->next == NULL)
				{
					clas = p->p_class;
					index2 = ncm_Hash2(clas);
					j = HashTable2[index2];
					while (j != NULL)
					{
						spell = j->s_name;
						n = p->p_name;
						index3 = ncm_Hash4(n, spell);
						index4 = ncm_Hash(spell);

						if (HashTable4[index3]->my_name == "empty")
						{
							HashTable4[index3]->my_name = p->p_name;
							HashTable4[index3]->my_class = p->p_class;
							HashTable4[index3]->my_lvl = p->p_m_level;
							HashTable4[index3]->spell_name = j->s_name;
							HashTable4[index3]->spell_lvl = j->s_m_level;
							HashTable4[index3]->spell_type = HashTable3[index4]->s_type;
							HashTable4[index3]->next = NULL;

						}
						else
						{
							k = HashTable4[index3];
							h = new com;
							h->my_name = p->p_name;
							h->my_class = p->p_class;
							h->my_lvl = p->p_m_level;
							h->spell_name = j->s_name;
							h->spell_lvl = j->s_m_level;
							h->spell_type = HashTable3[index4]->s_type;
							h->next = NULL;

							while (k->next != NULL)
							{
								k = k->next;
							}
							k->next = h;
						}

						//cout << "NAME: " << HashTable4[index3]->my_name << endl;
						//cout << "SPELL: " << HashTable4[index3]->spell_name << endl;
						//cout << "INDEX4: " << index4 << endl;

						COUNTP1++;
						//cout << "COUNT: " << data4_globalCount << endl;

						j = j->next;
					}

				}
				else
				{
					while (p != NULL)
					{
						//cout << "PLAYER NAME" << p->p_name << endl;
						//cin >> BULL;
						clas = p->p_class;
						index2 = ncm_Hash2(clas);
						j = HashTable2[index2];
						while (j != NULL)
						{
							spell = j->s_name;
							n = p->p_name;
							index3 = ncm_Hash4(n, spell);
							index4 = ncm_Hash(spell);

							if (HashTable4[index3]->my_name == "empty")
							{
								HashTable4[index3]->my_name = p->p_name;
								HashTable4[index3]->my_class = p->p_class;
								HashTable4[index3]->my_lvl = p->p_m_level;
								HashTable4[index3]->spell_name = j->s_name;
								HashTable4[index3]->spell_lvl = j->s_m_level;
								HashTable4[index3]->spell_type = HashTable3[index4]->s_type;
								HashTable4[index3]->next = NULL;

							}
							else
							{
								k = HashTable4[index3];
								h = new com;
								h->my_name = p->p_name;
								h->my_class = p->p_class;
								h->my_lvl = p->p_m_level;
								h->spell_name = j->s_name;
								h->spell_lvl = j->s_m_level;
								h->spell_type = HashTable3[index4]->s_type;
								h->next = NULL;

								while (k->next != NULL)
								{
									k = k->next;
								}
								k->next = h;
							}

							

							COUNTP2++;

							j = j->next;
						}
						p = p->next;
					}

				}
			}
			else
			{

			}

			index1++;
		}


	}

	void addsi_data1(int index, int index2) // Adds the data into another table but uses the class as secondary index 
	{
		ncm* k = HashTable1[index];
		if (siHashTable1[index2]->si1_class == "empty")
		{
			if (HashTable1[index]->p_class != "empty")
			{
				
				

				while (k->next != NULL)
				{
					k = k->next;
				}
				siHashTable1[index2]->si1_class = k->p_class;
				siHashTable1[index2]->p_name = k->p_name;
				siHashTable1[index2]->p_m_level = k->p_m_level;
			}
			else
			{
				siHashTable1[index2]->si1_class = HashTable1[index]->p_class;
				siHashTable1[index2]->p_name = HashTable1[index]->p_name;
				siHashTable1[index2]->p_m_level = HashTable1[index]->p_m_level;
			}

		}

		else
		{
			ncm* j = siHashTable1[index2];
			ncm* p = new ncm;

			while (k->next != NULL)
			{
				k = k->next;
			}


			while (j->next != NULL)
			{
				j = j->next;
			}

			p->si1_class = k->p_class;
			p->p_name = k->p_name;
			p->p_m_level = k->p_m_level;
			p->next = NULL;
			j->next = p;
		}
	}

	//#############################################################################################
	//
	//        FUNCTIONS TO CREATE A HASH KEY FOR EASY SEARCH AND PLACEMENT WITHIN A TABLE
	//
	//#############################################################################################

	int ncm_Hash(string key1) //hash function
	{
		int hash = 0;
		int index;

		index = key1.length();

		for (int i = 0; i < (int)key1.length(); i++)
		{
			hash = hash + (int)key1[i];

		}

		index = hash % TABLE_SIZE;

		return index;
	}

	int ncm_Hash2(string key1) //hash function
	{
		int hash = 0;
		int index;

		index = key1.length();

		for (int i = 0; i < (int)key1.length(); i++)
		{
			hash = hash + (int)key1[i];

		}

		index = hash % TABLE_SIZE2;

		return index;
	}

	int ncm_Hash4(string name, string spell) //hash function
	{
		int result = 0;
		int i;
		for (i = 0; i < name.size(); i++)
		{
			result += name[i];
		}
		for (i = 0; i < spell.size(); i++)
		{
			result += spell[i];
		}
		result = result % TABLE_SIZE4;
		return result;
	}

	int sic_Hash(string key1) //hash function
	{
		int hash = 0;
		int index;

		index = key1.length();

		for (int i = 0; i < (int)key1.length(); i++)
		{
			hash = hash + (int)key1[i];

		}

		index = hash % SI_TABLE_SIZE;

		return index;
	}

	//#############################################################################################
	//
	//               FUNCTIONS DETERMINE NUMBER OF ITEMS IN BUCKET
	//
	//#############################################################################################

	int numberOfItemsInIndex(int index)
	{		//returns # of items in a bucket
		int count = 0;

		if (HashTable1[index]->p_name == "empty")
		{
			return count;
		}
		else
		{
			count++;
			ncm* p = HashTable1[index];
			while (p->next != NULL)
			{
				count++;
				p = p->next;
			}
		}
		return count;
	}

	int numberOfItemsInIndex2(int index)
	{		//returns # of items in a bucket
		int count = 0;

		if (HashTable2[index]->s_name == "empty")
		{
			return count;
		}
		else
		{
			count++;
			scl* p = HashTable2[index];
			while (p->next != NULL)
			{
				count++;
				p = p->next;
			}
		}
		return count;
	}

	int numberOfItemsInIndex3(int index)
	{		//returns # of items in a bucket
		int count = 0;

		if (HashTable3[index]->s_name == "empty")
		{
			return count;
		}
		else
		{
			count++;
			st* p = HashTable3[index];
			while (p->next != NULL)
			{
				count++;
				p = p->next;
			}
		}
		return count;
	}

	int numberOfItemsInIndex4(int index)
	{		//returns # of items in a bucket
		int count = 0;

		if (HashTable4[index]->my_name == "empty")
		{
			return count;
		}
		else
		{
			count++;
			com* p = HashTable4[index];
			while (p->next != NULL)
			{
				count++;
				p = p->next;
			}
		}
		return count;
	}

	int sinumberOfItemsInIndex(int index)
	{		//returns # of items in a bucket
		int count = 0;

		if (siHashTable1[index]->si1_class == "empty")
		{
			return count;
		}
		else
		{
			count++;
			ncm* p = siHashTable1[index];
			while (p->next != NULL)
			{
				count++;
				p = p->next;
			}
		}
		return count;
	}

	//#############################################################################################
	//
	//           FUNCTIONS TO PRINT THE BUCKETS WITHIN THE DATA TABLE WITH ONLY ONE ITEM 
	//
	//#############################################################################################

	void printTable()
	{		//Prints hash table info
		int number;

		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (HashTable1[i]->p_name != "empty")
			{
				number = numberOfItemsInIndex(i);
				data1_globalCount += number;

				if (number == 1)
				{

					cout << "-----------------\n";
					cout << "index = " << i << endl;
					cout << HashTable1[i]->p_name << endl;
					cout << HashTable1[i]->p_class << endl;
					cout << HashTable1[i]->p_m_level << endl;
					cout << "# of players in bucket = " << number << endl;
					cout << "PLAYER COUNT = " << data1_globalCount << endl;
					cout << "-----------------\n";

				}
				else
				{
					printItemsInIndex(i);
				}

			}
			else
			{

			}

		}
	}

	void printTable2()
	{		//Prints hash table info
		int number;

		for (int i = 0; i < TABLE_SIZE2; i++)
		{
			if (HashTable2[i]->s_class != "empty")
			{
				number = numberOfItemsInIndex2(i);
				data2_globalCount += number;

				if (number == 1)
				{
					cout << "-----------------\n";
					cout << "INDEX = " << i << endl;
					cout << "SPELL NAME = " << HashTable2[i]->s_name << endl;
					cout << "SPELL CLASS = " << HashTable2[i]->s_class << endl;
					cout << "SPELL MAX LEVEL = " << HashTable2[i]->s_m_level << endl;
					cout << "# of spells in bucket = " << number << endl;
					cout << "SPELL COUNT = " << data2_globalCount << endl;
					cout << "-----------------\n";
				}
				else
				{
					printItemsInIndex2(i);
				}

			}
			else
			{

			}

		}
	}

	void printTable3()
	{		//Prints hash table info
		int number;

		for (int i = 0; i < TABLE_SIZE3; i++)
		{
			if (HashTable3[i]->s_name != "empty")
			{
				number = numberOfItemsInIndex3(i);
				data3_globalCount += number;

				if (number == 1)
				{
					cout << "-----------------\n";
					cout << "index = " << i << endl;
					cout << HashTable3[i]->s_name << endl;
					cout << HashTable3[i]->s_type << endl;
					cout << "# of spells in bucket = " << number << endl;
					cout << "SPELL COUNT = " << data3_globalCount << endl;
					cout << "-----------------\n";
				}
				else
				{
					printItemsInIndex3(i);
				}

			}
			else
			{

			}

		}
	}

	void printTable4()
	{		//Prints hash table info
		int number;
		
		

		for (int i = 0; i < TABLE_SIZE4; i++)
		{
			if (HashTable4[i]->my_name != "empty")
			{
				number = numberOfItemsInIndex4(i);
				//data3_globalCount += number;

				if (number == 1)
				{
					cout << "-----------------\n";
					cout << "NAME: " << HashTable4[i]->my_name << endl;
					cout << "SPELL: " << HashTable4[i]->spell_name << endl;
					cout << "INDEX4: " << i << endl;
					TCOUNT = COUNTP1 + COUNTP2;
					cout << "TOTAL COUNT: " << TCOUNT << endl;
					cout << "-----------------\n";
				}
				else
				{
					printItemsInIndex4(i);
				}

			}
			else
			{

			}

		}
	}

	void sid1printTable() //prints table for secondary index of data 1
	{		//Prints hash table info
		int number;
		ncm* p = new ncm;

		for (int i = 0; i < SI_TABLE_SIZE; i++)
		{
			if (siHashTable1[i]->si1_class != "empty")
			{
				number = sinumberOfItemsInIndex(i);
				//data1_globalCount += number;

				if (number == 1)
				{
				cout << "-----------------\n";
				cout<< "PLAYER CLASS: " << siHashTable1[i]->si1_class<<endl;
				cout << "PLAYER NAME: " << siHashTable1[i]->p_name << endl;
				cout << "PLAYER LEVEL: " << siHashTable1[i]->p_m_level << endl;
				//cout << "PLAYER COUNT = " << data1_globalCount << endl;
				cout << "-----------------\n";
				}
				else
				{
				siprintItemsInIndex(i, number);
				}

			}
			else
			{

			}

		}
		delete p;
	}

	//#############################################################################################
	//
	//               FUNCTIONS TO PRINT BUCKETS WITH MORE THAN ONE ITEM IN THEM
	//

	//#############################################################################################

	void printItemsInIndex(int index)
	{		//prints all contents of a bucket
		ncm* p = HashTable1[index];
		int number = numberOfItemsInIndex(index);


		if (p->p_name != "empty")
		{
			while (p != NULL)
			{
				cout << "--------------------\n";
				cout << "index = " << index << endl;
				cout << p->p_name << endl;
				cout << p->p_class << endl;
				cout << p->p_m_level << endl;
				cout << "--------------------\n";
				p = p->next;
			}
		}
	}
	void siprintItemsInIndex(int index, int number)
	{		//prints all contents of a bucket
		ncm* p = siHashTable1[index];

		if (p->si1_class != "empty")
		{
			while (p != NULL)
			{
				cout << "--------------------\n";
				cout << "PLAYER CLASS: " <<  p->si1_class << endl;
				cout << "PLAYER NAME: " << p->p_name << endl;
				cout << "PLAYER LEVEL: " << p->p_m_level << endl;
				cout << "index2 = " << index << endl;



				cout << "# OF PLAYERS IN BUCKET: " << number << endl;
				cout << "--------------------\n";
				p = p->next;
			}
		}
	}


	void printItemsInIndex2(int index)
	{		//prints all contents of a bucket
		scl* p = HashTable2[index];
		int number = numberOfItemsInIndex2(index);

		if (p->s_class != "empty")
		{
			while (p != NULL)
			{
				cout << "--------------------\n";
				cout << "index = "<< index << endl;
				cout << "SPELL NAME = " << p->s_name << endl;
				cout << "SPELL CLASS = " << p->s_class << endl;
				cout << "SPELL MAX LEVEL = " << p->s_m_level << endl;
				cout << "# of spells in bucket = " << number << endl;
				cout << "SPELL COUNT = " << data2_globalCount << endl;
				cout << "--------------------\n";
				p = p->next;
			}
		}
	}

	void printItemsInIndex3(int index)
	{		//prints all contents of a bucket
		st* p = HashTable3[index];
		int number = numberOfItemsInIndex3(index);

		if (p->s_name != "empty")
		{
			while (p != NULL)
			{
				cout << "--------------------\n";
				cout << "index = " << index << endl;
				cout << p->s_name << endl;
				cout << p->s_type << endl;
				cout << "# of spells in bucket = " << number << endl;
				cout << "SPELL COUNT = " << data3_globalCount << endl;
				cout << "--------------------\n";
				p = p->next;
			}
		}
	}

	void printItemsInIndex4(int index)
	{		//prints all contents of a bucket
		com* p = HashTable4[index];
		int number = numberOfItemsInIndex4(index);

		if (p->my_name != "empty")
		{
			while (p != NULL)
			{
				cout << "-----------------\n";
				cout << "NAME: " << HashTable4[index]->my_name << endl;
				cout << "SPELL: " << HashTable4[index]->spell_name << endl;
				cout << "INDEX4: " << index << endl;
				TCOUNT = COUNTP1 + COUNTP2;
				cout << "TOTAL COUNT: " << TCOUNT << endl;
				cout << "-----------------\n";
				p = p->next;
			}
		}
	}


	//#############################################################################################
	//
	//               FUNCTIONS TO SEARCH DATA 
	//
	//#############################################################################################

	void searchForname(string name)
	{		//Finds user-entered word in hash table
		int index = ncm_Hash(name);
		ncm* p = HashTable1[index];

		while (p != NULL)
		{
			if (p->p_name == name)
			{
				cout << "Player was found!" << endl;

				cout << "PLAYER: " << p->p_name << endl;
				cout << "CLASS: " << p->p_class << endl;
				cout << "LEVEL: " << p->p_m_level << endl;
				break;
			}
			else
			{
				p = p->next;
			}
		}
		if (p == NULL)
		{
			cout << "ERROR: PLAYER NOT FOUND"<< endl;
			
		}
		
	}

	string searchForSpellType(string name)
	{		//Finds user-entered spell type given a spell name in hash table
		int index = ncm_Hash(name);
		st* p = HashTable3[index];
		string spellType;
		while (p != NULL)
		{
			if (p->s_name == name)
			{
				spellType = p->s_type;
				return spellType;
			}
			else
			{
				p = p->next;
			}
		}
		cout << "ERROR: PLAYER NOT FOUND" << endl;
	}

	void printCount()
	{
		cout << "COUNT: " << COUNTP1 << endl;
		cout << "COUNT: " << COUNTP2 << endl;
		TCOUNT = COUNTP1 + COUNTP2;
		cout << "TOTAL COUNT: " << TCOUNT << endl;
	}


	//#############################################################################################
	//
	//               FUNCTIONS TO ANSWER QUESTIONS
	//
	//#############################################################################################

	void q1(string namez) //question 1
	{
		// this is assuming the question is asking the types of highest level spells that Jovani knows as well as the highest level spells that Williams knows
		string name=namez;
		string class1; //used to store the class of person 1
		string spell1; //used to store the max spell of person 1
		int maxlvl1; //used to store first persons max level
		int maxspell1=0;//used to store max spell level of person1 class

		// first person
		int index = ncm_Hash(name);
		ncm* p = HashTable1[index];

		while (p != NULL) // this while finds the player
		{
			if (p->p_name == name)
			{			
				class1 = p->p_class;
				maxlvl1 = p->p_m_level;
				//cout << "PLAYER: " << p->p_name << endl;
				//cout << "MAX LEVEL: " << maxlvl1 << endl;
				p = p->next;
			}
			else
			{
				p = p->next;
			}
		}
		//cout << "ERROR: PLAYER NOT FOUND" << endl;
		index = ncm_Hash2(class1);
		scl* n = HashTable2[index];

		while (n != NULL) //this while loops figuires out what the highest spell level they can perform given the current player spell level and class. This is done becuase a level 7 might have a spell they can cast at level 4 and the next one be a level 8. 
		{
			if (n->s_m_level <= maxlvl1)
			{
				
				if (n->s_m_level > maxspell1)
				{
					maxspell1 = n->s_m_level;
				}
				//cout << "PLAYER: " << p->p_name << endl;
				//cout << "MAX LEVEL: " << maxlvl1 << endl;
				n = n->next;
			}
			else
			{
				n = n->next;
			}
		}

		n = HashTable2[index];
		cout << endl << endl;
		cout << "STRONGEST SPELLS " << name << " CAN PERFORM AS A "  << class1 << ": "  << endl;
		while (n != NULL)
		{
			if (n->s_m_level == maxspell1) //if spell level is equal to max spell the player can cast
			{
				cout << "----------------------------------" << endl;
				cout << "SPELL NAME: " << n->s_name << endl;
				cout << "SPELL LEVEL: " << maxspell1 << endl;
				spell1 = searchForSpellType(n->s_name);
				cout << "SPELL TYPE: " << spell1 << endl;
				cout << "----------------------------------" << endl;
				
				n = n->next;
			}
			else
			{
				n = n->next;
			}
		}
		
	}

	void q2(string spellz) //function to figuire out who can currently learn wish 
	{
		string spell1 = spellz;
		int spelllvl; //spell level that class needs in order to perform that spell 

		for (int i = 0; i < TABLE_SIZE2; i++)
		{
			if (HashTable2[i]->s_class != "empty")
			{
				if (HashTable2[i]->s_name == spell1)
				{
					spelllvl = HashTable2[i]->s_m_level;
					q2_p2(spell1, HashTable2[i]->s_class, spelllvl);
					//cout << "CLASS THAT CAN PERFORM THIS SPELL: " << HashTable2[i]->s_class << endl;
					//cout << "LEVEL THAT CLASS NEEDS TO PERFORM SPELL: " << spelllvl << endl;
				}
				else
				{
					scl* n = HashTable2[i];
					while (n != NULL) 
					{
						if (n->s_name == spell1)
						{
							spelllvl = n->s_m_level;
							q2_p2(spell1, n->s_class, spelllvl);
							//cout << "CLASS THAT CAN PERFORM THIS SPELL: " << n->s_class << endl;
							//cout << "LEVEL THAT CLASS NEEDS TO PERFORM SPELL: " << spelllvl << endl;
							n = n->next;
						}
						else
						{
							n = n->next;
						}
					}
				}
			}
		}
	}

	void q2v2(string spellz) //function to figuire out who can currently learn wish 
	{
		string spell1 = spellz;
		int spelllvl; //spell level that class needs in order to perform that spell 
		for (int i = 0; i < TABLE_SIZE2; i++)
		{
			if (HashTable2[i]->s_class != "empty")
			{
				if (HashTable2[i]->s_name == spell1)
				{
					spelllvl = HashTable2[i]->s_m_level;
					q2_p2v2(spell1, HashTable2[i]->s_class, spelllvl);
				}
				else
				{
					scl* n = HashTable2[i];
					while (n != NULL)
					{
						if (n->s_name == spell1)
						{
							spelllvl = n->s_m_level;
							q2_p2v2(spell1, n->s_class, spelllvl);
							n = n->next;
						}
						else
						{
							n = n->next;
						}
					}
				}
			}
		}
	}

	void q2_p2(string spell1, string class1, int maxlvl) //question 2 part 2 used to search datatable 4
	{
		for (int i = 0; i < TABLE_SIZE4; i++)
		{
			if (HashTable4[i]->my_name != "empty") 
			{
				if (HashTable4[i]->spell_name == spell1 && HashTable4[i]->my_lvl >= maxlvl && HashTable4[i]->my_class == class1) //conditions to match what we are looking for
				{
					cout << HashTable4[i]->my_name << " CAN CURRENTLY LEARN SPELL: " << HashTable4[i]->spell_name << endl;
				}
				else
				{
					com* n = HashTable4[i];
					while (n != NULL) //iterates through the buckets
					{
						if (n->spell_name == spell1 && n->my_lvl >= maxlvl && n->my_class == class1)
						{
							cout << n->my_name << " CAN CURRENTLY LEARN SPELL: " << n->spell_name << endl;
							n = n->next;
						}
						else
						{
							n = n->next;
						}
					}
				}
			}
		}


	}
	void q2_p2v2(string spell1, string class1, int maxlvl) //question 2 part 2 used to search datatable 4
	{
		for (int i = 0; i < TABLE_SIZE4; i++)
		{
			if (HashTable4[i]->my_name != "empty")
			{
				if (HashTable4[i]->spell_name == spell1 && HashTable4[i]->my_class == class1) //conditions to match what we are looking for
				{
					cout << HashTable4[i]->my_name << " IS IN GENERAL ABLE TO LEARN SPELL: " << HashTable4[i]->spell_name << endl;
					
				}
				else
				{
					com* n = HashTable4[i];
					while (n != NULL) //iterates through the buckets
					{
						if (n->spell_name == spell1 && n->my_class == class1)
						{
							cout << n->my_name << " IS IN GENERAL ABLE TO LEARN SPELL: " << n->spell_name << endl;
							n = n->next;
						}
						else
						{
							n = n->next;
						}
					}
				}
			}
		}


	}

	void q3(string class1)
	{
		string name;
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (HashTable1[i]->p_name!="empty")
			{
				if (HashTable1[i]->p_class == class1)
				{
					name = HashTable1[i]->p_name;
					q1(name);
				}
				else
				{
					ncm* n = HashTable1[i];
					while (n != NULL)
					{
						if (n->p_class == class1)
						{
							name = n->p_name;
							q1(name);
							n = n->next;
						}
						else
						{
							n = n->next;
						}
					}
				}
			}
			
		}
	}

	void q4(string type1)
	{
		string sname; //spell name
		for (int i = 0; i < TABLE_SIZE3; i++) //looks for spells of type1
		{
			if (HashTable3[i]->s_name!= "empty")
			{
				if (HashTable3[i]->s_type == type1)
				{
					sname = HashTable3[i]->s_name;
					q4_p2(sname);

				}
				else
				{
					st* n = HashTable3[i];
					while (n != NULL)
					{
						if (n->s_type == type1)
						{
							sname = n->s_name;
							q4_p2(sname);
							n = n->next;
						}
						else
						{
							n = n->next;
						}
					}
				}
			}

		}
	}

	void q4_p2(string spell1)
	{
		string sname = spell1; //spell name
		int spelllvl=0;
		string class1;
		for (int i = 0; i < TABLE_SIZE2; i++) //looks for the highest level spells of type1
		{
			if (HashTable2[i]->s_name != "empty")
			{
				if (HashTable2[i]->s_name == sname)
				{
					
					if (spelllvl < HashTable2[i]->s_m_level) //replaces the spelllvl only with something higher
					{
						
							spelllvl = HashTable2[i]->s_m_level;
						
						
					}

					
				}
				else
				{
					scl* n = HashTable2[i];
					while (n != NULL)
					{
						if (n->s_name == spell1)
						{
							if (spelllvl < n->s_m_level)
							{		
									spelllvl =n->s_m_level;					
							}
							n = n->next;
						}
						else
						{
							n = n->next;
						}
					}
				}
			}
		}





		for (int i = 0; i < TABLE_SIZE2; i++) //looks for the highest level spells of type1
		{
			if (HashTable2[i]->s_name != "empty")
			{
				if (HashTable2[i]->s_name == sname)
				{

					if (spelllvl == HashTable2[i]->s_m_level) //replaces the spelllvl only with something higher
					{
						spelllvl = HashTable2[i]->s_m_level;
						class1 = HashTable2[i]->s_class;
						cout << "THE PLAYERS WHO CAN LEARN THE STRONGEST " << spell1 << " AS CLASS " << class1 << " ARE: " << endl;
						q4_p3(spelllvl, spell1, class1);
					}


				}
				else
				{
					scl* n = HashTable2[i];
					while (n != NULL)
					{
						if (n->s_name == spell1)
						{
							if (spelllvl == n->s_m_level)
							{
								spelllvl = n->s_m_level;
								class1 = n->s_class;
								cout << "THE PLAYERS WHO CAN LEARN THE STRONGEST " << spell1 << " AS CLASS "<< class1 <<  " ARE: " << endl;
								q4_p3(spelllvl, spell1, class1);
								
								
							}


							n = n->next;
						}
						else
						{
							n = n->next;
						}
					}
				}
			}

		}
		//by the time its out of the loop i Have the highest level spell of a certain type
		
		
		//q4_p3(spelllvl, spell1, class1);
	}

	void q4_p3(int maxlvl, string spell1, string class1)
	{
		string name;
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			if (HashTable1[i]->p_name != "empty")
			{
				if (HashTable1[i]->p_m_level >= maxlvl && HashTable1[i]->p_class==class1)
				{
					name = HashTable1[i]->p_name;
					cout << "-------------------------------------------" << endl;
					cout << "NAME: " << name << endl;
					cout << "CLASS: " << HashTable1[i]->p_class << endl;
					cout << "SPELL: " << spell1 << endl;
					cout << "-------------------------------------------" << endl;
				}
				else
				{
					ncm* n = HashTable1[i];
					while (n != NULL)
					{
						if (n->p_m_level >= maxlvl && n->p_class == class1)
						{
							name = n->p_name;
							cout << "-------------------------------------------" << endl;
							cout << "NAME: " << name << endl;
							cout << "CLASS: " << n->p_class << endl;
							cout << "SPELL: " << spell1 << endl;
							cout << "-------------------------------------------" << endl;
							n = n->next;
						}
						else
						{
							n = n->next;
						}
					}
				}
			}

		}
	}

};

int main()
{		//Main
	HashEntry hashObj;
	string playerName;
	int choice=0;
	int pause;
	string person1; // string to hold a person name
	string person2;// string to hold a person name
	string spell1;// string to hold a spell name
	string class1;
	string type1;

	hashObj.readData1();
	hashObj.readData2();
	hashObj.readData3();
	hashObj.add_data4();
	
	
	
	
	


	
	//hashObj.printCount();
	


	
	

	while (choice != 12)
	{
		cout << "\n----------------------\n";
		cout << "SETS LOADED IN, PLEASE MAKE A SELECTION\n";
		cout << "----------------------\n";
		cout << "1.What type(s) are the highest level spells that Jovani and William know?\n";
		cout << "2.What are the names of the characters that can learn wish currently (at their given player level)? What characters can learn wish in general?\n";
		cout << "3.What are the types of the highest level spells each cleric can cast?\n";
		cout << "4.What are the names of each character that can cast the highest level Illusion spells.\n";
		cout << "5.Print data table 1.\n";
		cout << "6.Print data table 2.\n";
		cout << "7.Print data table 3.\n";
		cout << "8.Print combined data table.\n";
		cout << "9.Print secondary index for data table 1.\n";
		cout << "10.Search for a player.\n";
		cout << "Enter your choice: ";

		cin >> choice;
		switch (choice) //Switch cases for menu input
		{
		case 1:
			person1 = "Jovani";
			person2 = "William";
			hashObj.q1(person1);
			hashObj.q1(person2);

			break;
		case 2:
			spell1 = "Wish";
			hashObj.q2(spell1);
			hashObj.q2v2(spell1);
			break;
		case 3:
			class1 = "Cleric";
			hashObj.q3(class1);
			break;
		case 4:
			type1 = "Illusion";
			hashObj.q4(type1);
			break;
		case 5:
			hashObj.printTable();
			break;
		case 6:
			hashObj.printTable2();
			break;
		case 7:
			hashObj.printTable3();
			break;
		case 8:
			hashObj.printTable4();
			break;
		case 9:
			hashObj.sid1printTable();
			break;
		case 10:
			cout << "What player would you like to search for?" << endl;
			cin >> playerName;
			hashObj.searchForname(playerName);
			break;
		case 11:
			;
			break;
		case 12:
			;
			break;
		default:
			cout << "\nEnter correct option\n";

		}
	}
	
	return 0;
}