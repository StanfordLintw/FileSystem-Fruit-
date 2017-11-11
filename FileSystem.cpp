#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<cctype>
#include<cstdlib>
#define maxnumber 100

using namespace std;

void initializeFile();
void loadFile();
void saveFile();
void listRecord(void);
void updateRecord(void);
void insertRecord(void);
void deleteRecord(void);
int  instructions();

int idArray[maxnumber];
char nameArray[maxnumber][15];
int quantityArray[maxnumber];
float priceArray[maxnumber];

int main()
{
	int choice;

	fstream file("fruit.dat", ios::in);
	void(*f[])(void) =
	{ listRecord,updateRecord,insertRecord,deleteRecord };

	if (!file)
	{
		cout << "There is no file: fruit.date!\n";
		cout << "New file is initialized!\n";
		initializeFile();
	}
	else
	{
		loadFile();
		cout << "Data of fruit.dat is loaded!\n";
	}

	while ((choice = instructions()) != 5)
		(*f[choice - 1])();
	saveFile();
	cout << "Bye." << endl;
	system("pause");
	return 0;
}//end main

void initializeFile()
{
	ofstream fRef("fruit.dat", ios::out | ios::binary);
	int id = -1;
	char name[15] = "";
	int quantity = -1;
	float price = -1;
	//fill file with blank records
	for (int i = 0; i<maxnumber; i++)
	{
		fRef.write(
			reinterpret_cast<char*>(&id), sizeof(id));
		fRef.write(
			reinterpret_cast<char*>(&name), sizeof(name));
		fRef.write(
			reinterpret_cast<char*>(&quantity), sizeof(quantity));
		fRef.write(
			reinterpret_cast<char*>(&price), sizeof(price));
		idArray[i] = id;
		strcpy_s(nameArray[i], name);
		quantityArray[i] = quantity;
		priceArray[i] = price;
	}
	fRef.close();
}

void loadFile()
{
	int id;
	char name[15];
	int quantity;
	float price;
	fstream fRef("fruit.dat", ios::in);

	for (int i = 0; i<maxnumber && !fRef.eof(); i++)
	{
		fRef.read(reinterpret_cast<char*>(&id), sizeof(id));
		fRef.read(reinterpret_cast<char*>(&name), sizeof(name));
		fRef.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
		fRef.read(reinterpret_cast<char*>(&price), sizeof(price));

		idArray[i] = id;
		strcpy_s(nameArray[i], name);
		quantityArray[i] = quantity;
		priceArray[i] = price;
	}
	fRef.close();
}
void saveFile()
{
	fstream fRef("fruit.dat", ios::out | ios::binary);
	for (int i = 0; i<maxnumber; i++)
	{
		fRef.write(reinterpret_cast<char*>(&idArray[i]), sizeof(idArray[i]));
		fRef.write(reinterpret_cast<char*>(&nameArray[i]), sizeof(nameArray[i]));
		fRef.write(reinterpret_cast<char*>(&quantityArray[i]), sizeof(quantityArray[i]));
		fRef.write(reinterpret_cast<char*>(&priceArray[i]), sizeof(priceArray[i]));
	}
	fRef.close();
}
int instructions()
{
	int choice;
	do
	{
		cout << "Enter a choice:" << endl
			<< "1 List all fruits." << endl
			<< "2 Update record." << endl
			<< "3 Insert record." << endl
			<< "4 Delete record." << endl
			<< "5 End program." << endl;
		cout << "?";
		cin >> choice;
		if (choice>5 || choice<1)
			cout << "Input error!!" << endl;
		else
			return choice;
	} while (choice != 5);
}

void listRecord(void)
{
	cout << setw(7) << "Record#" << "    " << left
		<< setw(21) << "fruit name" << left
		<< setw(14) << "Quantity" << left
		<< setw(7) << "Price" << endl;
	for (int i = 0; i<maxnumber; i++)
	{
		if (idArray[i]>0 && idArray[i] <= maxnumber)
		{
			cout << left << setw(7) << idArray[i] << "    "
				<< left << setw(21) << nameArray[i]
				<< left << setw(14) << quantityArray[i]
				<< left << setw(7) << fixed << setprecision(2) << priceArray[i] << endl;

		}
	}
}

void updateRecord(void)
{
	int id;
	char name[15];
	int quantity;
	float price;

	cout << "Enter the fruit number for update:";
	cin >> id;

	if ((id>0) && (id<maxnumber) && (idArray[id - 1] != -1))
	{
		cout << setw(7) << idArray[id - 1] << "   " << left
			<< setw(21) << nameArray[id - 1] << left
			<< setw(14) << quantityArray[id - 1] << left
			<< setw(7) << fixed << setprecision(2) << priceArray[id - 1] << left << endl;
		cout.unsetf(ios::fixed);
		cout << "Enter the fruit name:";
		cin.ignore(); //ignore the newline on the input stream
		cin.getline(name, 15, '\n');
		cout << "Enter quantity and price:";
		cin >> quantity >> price;

		strcpy_s(nameArray[id - 1], name);
		quantityArray[id - 1] = quantity;
		priceArray[id - 1] = price;
		cout << "Record updated." << endl;
	}
	else
		cerr << "Cannot update.The record is empty." << endl;
	saveFile();
}

void insertRecord(void)
{
	int id;
	char name[15];
	int quantity;
	float price;
	int i = 0;

	while ((idArray[i] != -1) && (i<maxnumber))
		i++;
	if (i <= maxnumber)
	{
		cout << "Enter the fruit number for insertion:";
		cin >> id;
		if (idArray[id - 1] == -1)
		{
			cout << "Enter the fruit name:";
			cin.ignore();
			cin.getline(name, 15, '\n');
			cout << "Enter quantity and price:";
			cin >> quantity >> price;
			idArray[id - 1] = id;
			strcpy_s(nameArray[id - 1], name);
			quantityArray[id - 1] = quantity;
			priceArray[id - 1] = price;
			cout << "Record inserted." << endl;
		}
		else
			cerr << "Cannot insert.The record contains information." << endl;
	}
	else
		cerr << "Cannot insert.The file is full." << endl;
	saveFile();
}

void deleteRecord(void)
{
	int id;
	cout << "Enter the fruit number for deletion:";
	cin >> id;

	if ((id>1) && (id<maxnumber) && (idArray[id - 1] != -1))
	{
		idArray[id - 1] = -1;
		strcpy_s(nameArray[id - 1], "");
		quantityArray[id - 1] = -1;
		priceArray[id - 1] = -1;
		cout << "Record deleted" << endl;
	}
	else
		cerr << "Cannot delect.The is empty." << endl;
	saveFile();
}



