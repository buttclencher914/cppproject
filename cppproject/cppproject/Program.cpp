#include <iostream>
#include "Database.cpp"
#include "Search.cpp"

using namespace std;

//int callback(void*, int, char**, char**);

int main()
{
	cout << "ICT1009 Crawler - Group 2" << endl;
	cout << "================================================================================================================" << endl;

	string word;
	cout << "Enter a keyword to search: " << endl;
	cin >> word;
	cout << "\nResults:" << endl;

	Database db;
	bool i = db.Connect(db.getDBPath());
	Search s = Search(db.getDbObject(), db.getTableName());

	s.SearchData(word);
	cout << "\n";
	s.CountData(word);
	

	//cout << i;
	//db.ReadAllData();
	//s.SearchData("E-scooter");


}

int callback(void* NotUsed, int argc, char** argv,
	char** azColName) {

	int counter = 0;
	NotUsed = 0;

	for (int i = 0; i < argc; i++) {

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		
	}
	printf("\n");

	return 0;
}