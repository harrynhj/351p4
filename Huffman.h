#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <unordered_map>
#include "mymap.h"
#include "PriorityQueue.h"


class Huffman {
	private:
		
		/* helper function which inserts or increment a charcter into
		the hashmap depending on whether or not hashmap contains it */
		void getMap(int& c, unordered_map<int, int> &map) {
			if(map.find(c) == map.end())
				map.emplace(c, 1);
			else
				map.at(c)++;
		}

		PriorityQueue pq;
	
	public:

		// builds a huffman information file using a string or the file
		unordered_map<int, int> getFrequency(string& filename) {
			unordered_map<int, int> frequency_map;
			ifstream fs(filename);
			char c;
			while(fs.get(c)) {
				int ascii = c;
				getMap(ascii, frequency_map);
			}
			
			fs.close();

			// for (auto i : frequency_map)
			// 	cout << "key: " << i.first << " value: " << i.second << endl;
			
			// cout << "----------------" << endl;

			return frequency_map;
		}

		
		HuffmanNode* buildEncodingTree(unordered_map<int, int>& map) {
			// create a priority queue and push all the nodes into it
			PriorityQueue pq;
			
			vector<int> keys; // create a vector of all the keys
			
			// for(auto x: map) {
			for(int i = 0; i < 128; i++) {
				// keys.push_back(x.first); // this is all the ascii chars 0 - 127
				// if(map.contains(i)) {
					
				// }
				keys.push_back(i);
				
			}

			// for range loop, this will push back node into priority queue
			for (auto i : keys) {
				HuffmanNode* node = new HuffmanNode();
				node -> character = i;
				
				if(map.find(i) != map.end())
					node -> count = map.at(i);
				else 
					node -> count = 0;

				node -> zero = nullptr;
				node -> one = nullptr;
				pq.push(node);
			}
			
			
			// build huffman tree
			while (pq.size() > 1) {
				// pop two nodes and save them
				HuffmanNode* first_node = pq.top();
				pq.pop();

				HuffmanNode* second_node = pq.top();
				pq.pop();

				// create a new node
				HuffmanNode* linked_node = new HuffmanNode();
				
				// 257 stands for not a character
				linked_node -> character = 129;

				// add count and link the nodes
				linked_node -> count = first_node->count + second_node->count;
				linked_node -> zero = first_node;
				linked_node -> one = second_node;
				
				// push the new node into the queue
				pq.push(linked_node);
			}
			return pq.top();
		}

		// helper for buildEncodingMap
		void recursiveHelperBuildEncode(HuffmanNode* root, mymap<int, string>& encodingMap, string str) {
			if(root == nullptr)
				return;

			if(root -> character != 129)
				encodingMap.put(root -> character, str);

			recursiveHelperBuildEncode(root -> zero, encodingMap, str + "0");
			recursiveHelperBuildEncode(root -> one, encodingMap, str + "1");
		}

		// encodes all the chars inside the map
		mymap<int, string> buildEncodingMap(HuffmanNode* tree) {
			mymap<int, string> encodingMap;
			recursiveHelperBuildEncode(tree, encodingMap, "");
			return encodingMap;
		}

		void buildfile(string filename) {
			unordered_map<int, int> frequency_map = getFrequency(filename);
			HuffmanNode* root = buildEncodingTree(frequency_map);
			mymap<int, string> encoding_map = buildEncodingMap(root);
			
			ofstream file (filename + ".hi");
			
			for(int i = 0; i < 128; i++) {
				file << i << "    " << encoding_map.get(i) << endl;
			}

			file.close();
		}

		HuffmanNode* insertNode(mymap<int, int>& encoding_map) {
			
		}
		
		void buildTree(string& filename) {
			mymap<int, int> encoding_map;
			ifstream fs(filename);
			string line;

			int a, b;
						
			if(!fs.is_open())
				cout << "Could Not Open";
			
			while(fs >> a >> b)
				encoding_map.put(a, b);

			
		}

	
};


