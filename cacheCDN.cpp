#include "cacheCDN.h"

#include <climits>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

namespace ICS45C {
namespace CDN {
Cache::Cache(unsigned int freshnessCount) : tempCount(freshnessCount) {}
string Cache::getText(std::string filepath) {
  purgeCount += 1;
  if (content.find(filepath) == content.end()) {  // if not found file
    count = 0;
    pathCount[filepath] = 1;
    trackCount[filepath] = tempCount - 1;  // = freshCount
    fileContent.clear();
  } else {  // found file
    count++;
    pathCount[filepath] += 1;
    trackCount[filepath] -= 1;
  }
  if (count == 0) {  // 0 open,read, store, return content
    inFile.open(filepath);
    total_read += 1;
    while (getline(inFile, text)) {
      fileContent += text;
      fileContent.push_back('\n');
      content[filepath] = fileContent;
    }
    // trackCount[filepath] = 0;  // First time call
    inFile.close();
  } else if (count < tempCount) {
    // trackCount[filepath] = tempCount - count;  // 1,2 return copy content
    return content[filepath];
  } else {  // 3
    inFile.open(filepath);
    total_read += 1;
    fileContent.clear();
    while (getline(inFile, text)) {
      fileContent += text;
      fileContent.push_back('\n');
      content[filepath] = fileContent;
    }
    inFile.close();
    count = 0;
    // trackCount[filepath] = tempCount - count;
    return content[filepath];
  }
  return content[filepath];
}

bool Cache::isCached(std::string filepath) {
  if (content.find(filepath) == content.end()) {  // if not found file
    return false;
  } else {  // found file
    return true;
  }
}
unsigned int Cache::getFreshness(std::string filepath) {
  if (tempCount == 0) {
    return 0;
  }
  if (content.find(filepath) == content.end()) {  // not found
    return 0;
  }
  return trackCount[filepath];
}
void Cache::markFileFresh(std::string filepath) {
  if (content.find(filepath) != content.end()) {  // found reset
    trackCount[filepath] = tempCount;
  }  // updated
}
void Cache::purgeCache() { content.clear(); }
string Cache::topFile() {
  if (pathCount.size() == 0) {
    return "";
  }
  int maxValue =
      INT_MIN;  // https://www.techiedelight.com/find-element-with-the-maximum-value-in-a-map-in-cpp/

  for (const auto &entry : pathCount) {
    if (maxValue < entry.second) {
      maxValue = entry.second;
      maxValuePair = entry;
    }
  }
  return maxValuePair.first;
}
std::string Cache::getStats() {
  for (std::pair<std::string, int> p : pathCount) {
    total_key += 1;
  }
  output << "Cache Stats" << endl;
  output << "----------" << endl;
  output << "Total requests: " << purgeCount << endl;
  output << "Total files requested: " << total_key << endl;
  if (total_key != 0) {
    output << "Average requests per file: " << std::fixed
           << std::setprecision(2) << purgeCount / total_key << endl;
  } else {
    output << "Average requests per file: "
           << "0.00" << endl;
  }

  output << "Top file: " << topFile() << " "
         << "(" << requests[topFile()] << " requests)" << endl;
  output << "Total times read from disk: " << total_read << endl;
  output << "----------" << endl;
  return output.str();
}
}  // namespace CDN
}  // namespace ICS45C
   /* Implement any functions and methods here! */