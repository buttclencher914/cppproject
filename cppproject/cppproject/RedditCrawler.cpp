#include <iostream>
#include <curl/curl.h>
#include <string>
#include <json/json.h>
#include <json/reader.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <fstream>


#define SIZE 10
#define POSTS 5
#define JSONCPP_STRING   std::string
#define CURL_STATICLIB


using namespace std;

bool replace(string& str, const string& from, const string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == string::npos) {
		return false;
	}
	else {
		str.replace(start_pos, from.length(), to);
		return true;
	}
}

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param) {
	string& text = *static_cast<string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

int main() {
	//search term
	string searchTopic = "PMD E-scooter";
	string csvName = "redditCrawler";

	//create and open file
	ofstream crawlerFile;
	crawlerFile.open(csvName + ".csv");
	crawlerFile << "NoOfComments, URL, Upvotes,Title,Comments\n";

	CURL* curl;
	CURLcode res;
	string result;
	string searchTerm(searchTopic);

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
		//paste this url to browser to see json example https://www.reddit.com/search/.json?q=pmd&type=sr%2Cuser&limit=3
		string url = "https://www.reddit.com/search/.json?q=";
		url += searchTerm;
		url += "&type=sr%2Cuser&limit=";
		url += to_string(SIZE);
		replace(url, " ", "%20");
		cout << "Searching for " << searchTerm << endl;
		cout << "Search for " << SIZE << "subreddits" << endl;
		cout << url << endl;

		//url must be in C string *****IMPT********** url.c_str()
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		Json::Value value;

		JSONCPP_STRING errs;
		Json::CharReaderBuilder readerBuilder;
		std::unique_ptr<Json::CharReader> const reader(readerBuilder.newCharReader());
		bool res = reader->parse(result.c_str(), result.c_str() + result.length(), &value, &errs);
		if (res && errs.empty()) {
			for (int i = 0; i < SIZE; i++) {
				//get title and url
				cout << value["data"]["children"][i]["data"]["title"] << endl;
				string url("https://www.reddit.com");
				url += value["data"]["children"][i]["data"]["url"].asString();
				url += "top/.json?limit=";
				url += to_string(POSTS);
				url += "&t=all";

				cout << url << endl;

				CURL* curl;
				CURLcode res;
				string result;

				curl = curl_easy_init();
				if (curl) {
					curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);

					/* Perform the request, res will get the return code */
					res = curl_easy_perform(curl);
					/* Check for errors */
					if (res != CURLE_OK) {
						fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

						//Paste this Url to browser to see json example https://www.reddit.com/r/pmd/top/.json?limit=3&t=all

						Json::Value value;

						// parse
						JSONCPP_STRING errs;
						Json::CharReaderBuilder readerBuilder;
						std::unique_ptr<Json::CharReader> const reader(readerBuilder.newCharReader());
						bool res = reader->parse(result.c_str(), result.c_str() + result.length(), &value, &errs);
						if (res && errs.empty()) {
							for (int j = 0; j < POSTS; j++) {
								//write to file
								crawlerFile << value["data"]["children"][j]["data"]["num_comments"] << ",";

								string templink;
								templink = value["data"]["children"][j]["data"]["permalink"].asString();
								crawlerFile << "https://www.reddit.com" << templink << ",";

								crawlerFile << value["data"]["children"][j]["data"]["ups"] << ",";
								crawlerFile << value["data"]["children"][j]["data"]["title"] << ",";
								crawlerFile << value["data"]["children"][j]["data"]["selftext"] << endl;

							}
						}
					}

				}

			}
			crawlerFile.close();
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}



