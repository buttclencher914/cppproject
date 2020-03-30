#include <iostream>
#include "Database.cpp"
#include "Search.cpp"

using namespace std;

//int callback(void*, int, char**, char**);

int main()
{
	Database db;
	bool i = db.Connect(db.getDBPath());
	Search s = Search(db.getDbObject(), db.getTableName());
	//cout << i;
	//db.ReadAllData();
	s.SearchData("E-scooter");

}

int callback(void* NotUsed, int argc, char** argv,
	char** azColName) {

	NotUsed = 0;

	for (int i = 0; i < argc; i++) {

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}