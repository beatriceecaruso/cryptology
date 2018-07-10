//btrans: block transposition by byte
// flags: -e to encrypt, -d to decrypt, -b<n> for blocksize n, and -k<filename> for file containing the key

#include <iostream>
#include <bitset>
#include <unistd.h>
#include <getopt.h>
#include <vector>
#include <iomanip>
#include <fstream>
#include "crypto.h"
using namespace std;
using namespace crypto;

main (int argc, char* argv[]){

  vector <unsigned char> encrypted_input;
  vector <unsigned char> plaintext_input;
  vector <unsigned char> encrypted_output;
  vector <unsigned char> decrypted_output;

  int opt;
  int block_size = 8;
  char* keyfile;
  char function_choice = 'x';
  char encrypt = 'c';
  char decrypt = 'd';

  while ((opt = getopt(argc, argv, "b:k:ed")) != -1){
    switch (opt){
        case 'b':
        block_size = atoi(optarg);
        cout << block_size << endl;
        break;
        case 'k':
        keyfile = optarg;
        break;
        case 'e':
        function_choice = 'e';
        break;
        case 'd':
        function_choice = 'd';
        break;
        default:
        cerr << "Error: invalid argument(s). Valid flags are b,k,e, and d. ";
        cerr << "See README for more detail on correct input." << endl;
    }
  }

//cout << function_choice << endl;

/** IF ENCRYPTING */
  if (function_choice == 'e'){
    crypto::InputBinaryToVector(&plaintext_input);

    int buffer1;
    vector<int> key;

/** READ IN keyfile to vector<int> key */
    ifstream infile;
    infile.open(keyfile);
    while (true){
      infile >> hex >> buffer1;
      if (infile.eof())
        break;
      else {
        key.push_back(buffer1);
      }
    }
    infile.close();

/** Use key vector to create encrypted_output vector*/
    int block_size = key.size();
    //cout << block_size << endl;
    int plaintext_size = plaintext_input.size();
    //cout << plaintext_size << endl;
    int extra_bytes = plaintext_size%block_size;
    //cout << extra_bytes << endl;
    encrypted_output.resize(plaintext_size - extra_bytes);
    //cout << encrypted_output.size() << endl;;

    int j = 0;
    int block = 0;
    for (int i = 0; i < (plaintext_size - extra_bytes); i++){
      encrypted_output.at(i) = plaintext_input.at(block + key.at(j));
      //cout << "char: " << encrypted_output.at(i) << " pos: " << i << " block: " << block;
      //cout << " j: "<< j << " plain was: " << plaintext_input.at(i) << endl;
      if (j == 3){
        j=0;
        block = block + 4;
      }
      else {
        j++;
      }
    }

/** Now encrypted_output has the correct values */
  crypto::PrintVectorAsBinary(&encrypted_output);
  }


/**IF DECRYPTING */
  if (function_choice == decrypt) {
    cout << "decrypting" << endl;
    crypto::InputBinaryToVector(&encrypted_input);

    int buffer1;
    vector<int> key;

/** READ IN keyfile to vector<int> key */
    ifstream infile;
    infile.open(keyfile);
    while (true){
      infile >> hex >> buffer1;
      if (infile.eof())
        break;
      else {
        key.push_back(buffer1);
      }
    }
    infile.close();

/** Use key vector to create decrypted_output vector*/
    int block_size = key.size();
    cout << block_size << endl;
    int encrypted_size = encrypted_input.size();
    cout << encrypted_size << endl;
    int extra_bytes = encrypted_size%block_size;
    cout << extra_bytes << endl;
    decrypted_output.resize(encrypted_size - extra_bytes);
    cout << decrypted_output.size() << endl;;

    int j = 0;
    int block = 0;
    for (int i = 0; i < (encrypted_size - extra_bytes); i++){
      decrypted_output.at(i) = encrypted_input.at(block + key.at(j));
      cout << "char: " << decrypted_output.at(i) << " pos: " << i << " block: " << block;
      cout << " j: "<< j << " crypted was: " << encrypted_input.at(i) << endl;
      if (j == 3){
        j=0;
        block = block + 4;
      }
      else {
        j++;
      }
    }

/** Now decrypted_output has the correct values */
  crypto::PrintVectorAsBinary(&decrypted_output);

  }

  return 0;
}
