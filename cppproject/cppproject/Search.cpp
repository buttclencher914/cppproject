#include "sqlite3.h"
#include <string>
using namespace std;

class Search
{
private:
	sqlite3* db;
	string tablename;
	char* ErrMsg = 0;
public:
	Search(sqlite3* dbt, string tblname)
	{
		db = dbt;
		tablename = tblname;
	}
	bool SearchData(string search)
	{
		int callback(void*, int, char**, char**);

		sqlite3_stmt* stmt = 0;

		string statement = "SELECT ARTICLE FROM " + tablename + " WHERE content like '%" + search + "%'";

		int rc = sqlite3_exec(db, statement.c_str(), callback, 0, &ErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", ErrMsg);
			sqlite3_free(ErrMsg);
		}
		else {
			fprintf(stdout, "Search successfully\n");
		}
		//sqlite3_close(db);
		return 0;
	}
	bool ReadAllData()
	{
		int callback(void*, int, char**, char**);

		sqlite3_stmt* stmt = 0;

		string statement = "SELECT * FROM " + tablename;

		int rc = sqlite3_exec(db, statement.c_str(), callback, 0, &ErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", ErrMsg);
			sqlite3_free(ErrMsg);
		}
		else {
			fprintf(stdout, "Read All Data successfully\n");
		}
		//sqlite3_close(db);
		return 0;
	}

	bool CountData(string search)
	{
		int callback(void*, int, char**, char**);

		sqlite3_stmt* stmt = 0;

		string statement = "SELECT COUNT(ARTICLE) AS ResultsFound FROM " + tablename + " WHERE content like '%" + search + "%'";

		int rc = sqlite3_exec(db, statement.c_str(), callback, 0, &ErrMsg);

		//if (rc != SQLITE_OK) {
		//	fprintf(stderr, "SQL error: %s\n", ErrMsg);
		//	sqlite3_free(ErrMsg);
		//}
		//else {
		//	fprintf(stdout, "Returned number of rows\n");
		//}
		//sqlite3_close(db);
		return 0;
	}
};