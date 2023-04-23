#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Huffman.h"

using std::cout;
using std::cin;
using std::string;

bool check_file(string file_name) {
    ifstream myFile(file_name);
    if(myFile.fail()){
        return false;
    }
    myFile.close();
    return true;
}


void displayCommands(){
  cout << "\nOperation are given by digits 1 through 5\n\n";
  cout << "  1 <filename> - create a new Huffman Information file from an original file\n";
  cout << "  2 <filename> - load a Huffman Information file \n";
  cout << "  3 <filename> - compress a file using the current Huffman Information file\n";
  cout << "  4 <filename> - decompress a file using the current Huffman Information file\n";
  cout << "  5            - quit the program\n\n";

}

int main(int argc, char** argv){
  Huffman huffman;
  HuffmanNode* root = nullptr;
  vector<string> bits;

  cout << "Welcome to File Compression program\n";

  displayCommands();
  
  bool done = false;
  string line;
  string input;

  do {
    cout << "cmd> ";

    // read a complete line
    std::getline(std::cin, line);

    // now create a "stringstream" on the line just read
    std::stringstream ss(line);

    // clear input from any previous value
    input = "";

    // get command character
    char command;
    ss >> command;
    //cout << "Debug command:" << command << "***\n";
    
    if(command == '1'){
        ss >> input;
        if (!check_file(input)) {
          cout << "File does not exist!" << endl;
        } else {
          huffman.buildfile(input);
        }
        
        // build a new .hi file using the information in the file: input
        
       
    }

    if(command == '2'){
        ss >> input;
        // load a .hi file to later perform compression and decompression
        if (!check_file(input)) {
          cout << "File does not exist!" << endl;
        } else {
          root = huffman.buildTree(input, bits);
        }
        
        
    }
        
    if(command == '3'){
        ss >> input;
        if (root != nullptr) {
          if (!check_file(input)) {
            cout << "File does not exist!" << endl;
          } else {
            huffman.encode(root, bits, input);
          }

        } else {
          cout << "Please run command 2 first!" << endl;
        }
        // use the current .hi file to compress the file in input
    }

    if(command == '4'){
        ss >> input;
        if (root != nullptr) {
          if (!check_file(input)) {
            cout << "File does not exist!" << endl;
          } else {
            huffman.decode(root, input);
          }
        } else {
          cout << "Please run command 2 first!" << endl;
        }
        // use the current .hi file to decompress the file in input
        // note if the file was not compressed using the same .hi file, the output will be meaningless
    }

    if(command == '5' || command == 'q'){
        if (root != nullptr) {
          huffman.freeTree(root);
        }

        done = true;
    }


  } while(!done && !cin.eof());

  return 0;
}
