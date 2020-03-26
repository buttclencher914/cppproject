#include "Database.cpp"

using namespace std;

int main()
{
	Database db;
	bool i = db.Connect(db.getDBPath());
	cout << i;
}