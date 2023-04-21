#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include "hashmap.cpp"
#include "mymap.h"
#include "PriorityQueue.h"


class Huffman {
	private:

	public:
		/* helper function which inserts or increment a charcter into
		the hashmap depending on whether or not hashmap contains it */
		void getMap(char& c, hashmap &map) {
			if(!map.containsKey(c))
				map.put(c, 1);
			else
				map.put(c, map.get(c) + 1);
		}

		// builds a huffman information file using a string or the file
		void buildfile(string filename) {
			hashmap map;
			ifstream fs(filename);
			char c;
			while(fs.get(c))
				getMap(c, map);
			fs.close();

			map.put(256, 1);
		}
	
};