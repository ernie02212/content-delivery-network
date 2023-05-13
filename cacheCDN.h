#ifndef __CACHECDN_H__
#define __CACHECDN_H__
#include <climits>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
/* Add any includes here! */
using namespace std;
namespace ICS45C {
namespace CDN {

/* Define your class here! */
class Cache {
 private:
  unsigned int freshnessCount;
  unsigned int tempCount;
  string key;
  string filepath;
  ifstream inFile;
  string fileContent;
  string text;
  map<string, string> content;
  map<string, unsigned int> trackCount;
  map<string, int> pathCount;
  pair<string, int> maxValuePair;
  map<string, int> requests;

 public:
  int temp;
  float purgeCount = 0;
  unsigned int count = 0;
  int total_read;
  stringstream output;
  float total_key = 0;
  Cache(unsigned int freshnessCount);
  string getText(std::string filepath);
  bool isCached(std::string filepath);
  unsigned int getFreshness(std::string filepath);
  void markFileFresh(std::string filepath);
  void purgeCache();
  std::string topFile();
  std::string getStats();
};
}  // namespace CDN
}  // namespace ICS45C

#endif  // __CACHECDN_H__