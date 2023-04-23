#include <iostream>
//#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <unordered_map>
#include "mymap.h"
#include "PriorityQueue.h"
#include "bitstream.h"


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
			
			for(int i = 0; i < 128; i++)
				keys.push_back(i);

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
				
				// 129 stands for not a character
				linked_node -> character = 129;

				// add count and link the nodes
				linked_node -> count = first_node -> count + second_node->count;
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

		// HuffmanNode* insertNode(mymap<int, int>& encoding_map) {
			
		// }
		HuffmanNode* createNode(int c) {
			HuffmanNode* node = new HuffmanNode();
			node -> character = c;
			node -> count = 0;
			node -> zero = nullptr;
			node -> one = nullptr;
			return node;
		}
		
		HuffmanNode* buildTree(string& filename, vector<string>& info) {
			mymap<int, string> encoding_map;
			ifstream fs(filename);
			string line;

			int a; 
			string b;
			
			while(fs >> a >> b) {
				encoding_map.put(a, b);
				info.push_back(b);
			}


			HuffmanNode* root = createNode(129);
			for (auto i : encoding_map) {
				string path = encoding_map.get(i);
				HuffmanNode* current = root;
				int path_length = path.length();
				for (int j = 0; j < path_length; j++) {
					if (path[j] == '0') {
						if (current -> zero == nullptr) {
							HuffmanNode* node = createNode(129);
							current -> zero = node;
							current = node;
							if (j == path_length-1) {
								current -> character = i;
							}
						} else {
							current = current -> zero;
							if (j == path_length-1) {
								current -> character = i;
							}
						}
					} else {
						if (current -> one == nullptr) {
							HuffmanNode* node = createNode(129);
							current -> one = node;
							current = node;
							if (j == path_length-1) {
								current -> character = i;
							}
						} else {
							current = current -> one;
							if (j == path_length-1) {
								current -> character = i;
							}
						}
					}
				}
			}
			
			// mymap<int, string> v = buildEncodingMap(root);
			// cout << v.toString() << endl;

			return root;
		}

		// recursively frees the memory allocated to the Huffman tree
		void freeTree(HuffmanNode* node) {
			if(node == nullptr)
				return;

			freeTree(node -> zero);
			freeTree(node -> one);

			delete node;
		}


		void encode(HuffmanNode* root, vector<string>& info, string& filename) {
			ofbitstream output(filename + ".hc");
			ifstream input(filename);
			
			char c;
			string result = "";
			while (input.get(c)) {
				result += info[(int)c];
			}
			result += info[0];

			for (char c : result) {
            	output.writeBit(c == '0' ? 0 : 1);
        	}
			input.close();
    		output.close();
		}

		void decode(HuffmanNode* root, string& filename) {
			ifbitstream input(filename);
			ofstream output(filename + ".hc");
			
			// initialize variables
			string result = "";
			HuffmanNode* node = root;
			
			// while not eof, read chars from input
			while (!input.eof()) {
				// if reach a leaf node, add to result
				if (node -> character != 129) {
					// if is other than eof, add to result and output and reset node to root

					if (node -> character == 0) {
						input.close();
    					output.close();
						return;
					}

					output.put(char(node -> character));
					result += char(node -> character);
					node = root;
				}
				
				// if is not a leaf node, read bit from input and traverse the tree
				int bit = input.readBit();
				if (bit == 0) {
					node = node -> zero;
				} else {
					node = node -> one;
				}
			}
			input.close();
    		output.close();
		}




		// compresses the file
		// string compress(string filename) {
		// 	ifstream fs(filename);
		// 	unordered_map<int, int>  map;
		// 	int size = 0;

		// 	map = getFrequency(filename);
		// 	HuffmanNode* huffNode = buildEncodingTree(map);
		// 	mymap<int, string> theMap = buildEncodingMap(huffNode);

		// 	ofbitstream output(filename + ".huf");
		// 	output << map;

		// 	string str = encode(fs, theMap, output, size, true);

		// 	fs.close();
		// 	output.close();

		// 	freeTree(huffNode);

		// 	return str;
		// }

// 	string compress(string filename) {
// 		ifstream fs(filename);
// 		hashmap hashMap;
// 		int size = 0;

// 		buildFrequencyMap(filename, true, hashMap);
// 		// huffNode should be the one we get from command 2
// 		HuffmanNode* huffNode = buildEncodingTree(hashMap);

// 		mymap<int, string> theMap = buildEncodingMap(huffNode);

// 		// Need do ourselfs
// 		ofbitstream output(filename + ".huf");
// 		output << hashMap;


// 		string str = encode(fs, theMap, output, size, true);

// 		fs.close();
// 		output.close();

// 		freeTree(huffNode);

// 		return str;
// }


		
};


