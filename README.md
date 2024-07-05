# Parking Lot Manager

## Description

The Cache CDN project provides a caching system for reading text files efficiently. This implementation is designed to reduce the number of disk reads by caching frequently accessed files, making it useful for applications that require frequent file access.


## Features

- Efficient caching of text files
- Customizable freshness count for cache entries
- Tracks statistics such as total requests, file requests, and disk reads
- Provides functionality to purge the cache and mark files as fresh

## Installation
  To use the Cache CDN library in your project, follow these steps:
  1. Clone the repository:
       ```bash
       git clone https://github.com/your-username/cacheCDN.git
  2. Include the header and source files in your project:
      ```cpp
      #include "cacheCDN.h"
## Usage
    Here's a basic example of how to use the Cache CDN library:
    ```cpp
        #include "cacheCDN.h"
        #include <iostream>
      
      using namespace ICS45C::CDN;
      
      int main() {
          Cache cache(3); // Create a cache with a freshness count of 3
          
          std::string filepath = "example.txt";
          
          // Get the content of the file
          std::string content = cache.getText(filepath);
          std::cout << content << std::endl;
          
          // Check if the file is cached
          if (cache.isCached(filepath)) {
              std::cout << "File is cached." << std::endl;
          }
          
          // Get the freshness of the file
          unsigned int freshness = cache.getFreshness(filepath);
          std::cout << "Freshness: " << freshness << std::endl;
          
          // Mark the file as fresh
          cache.markFileFresh(filepath);
          
          // Purge the cache
          cache.purgeCache();
          
          // Get cache statistics
          std::string stats = cache.getStats();
          std::cout << stats << std::endl;
          
          return 0;
      }

## API
1. Constructor
     ```cpp
     Cache(unsigned int freshnessCount);
2. getText
     ```cpp
     std::string getText(std::string filepath);
3. isCached
    ```cpp
    bool isCached(std::string filepath);
4. purgeCache
   ```cpp
   void purgeCache();
5. topFile
   ```cpp
   std::string topFile();
6. getStats
   ```cpp
   std::string getStats();

## Contributing
  Contributions are welcome! Please feel free to submit a Pull Request or open an Issue.

## License
  This project is licensed under the MIT License. See the LICENSE file for details.

   






