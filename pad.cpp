//pad: pads a file
//flags: -p to pad a file, -u to unpad, -b<n> for block length n

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <getopt.h>
#include <vector>
#include "crypto.h"
using namespace std;
using namespace crypto;

main (int argc, char* argv[]){

  vector <unsigned char> message_bytes;
  vector <unsigned char> hex_input;

/** Parse command-line arguments with getopt() */
  int opt;
  int block_size = 8;
  bool success;

  while ((opt = getopt(argc, argv, "b:up")) != -1) {
    switch (opt){
/** When -b<n> is given, pad using n as block_size */
      case 'b':
      //cout << "case b with argument " << optarg << endl;
      block_size = atoi(optarg); //get val of argument and save as int (optarg is char[])
      if (block_size > 256 || block_size < 1){
        cerr << "Error: invalid block size n. n must be between 1 and 256" << endl;
        return 1;
      }
      //cout << "block size is " << block_size << endl;
/** -p is given (PAD) - note there is no break statement between case 'b' and case 'p' */
      case 'p':
      //cout << "case p for pad" << endl;
      //cout << "pad number is " << block_size << endl;
      crypto::InputBinaryToVector(&message_bytes);
      crypto::PadMessage(&message_bytes, block_size);
      crypto::PrintVectorAsHex(&message_bytes);
      break;
/** -u is given (UNPAD) - recall that we can redirect the standard output stream
if we want an unpadded file. */
      case 'u':
      //cout << "case u for unpad" << endl;
      crypto::InputHexToVector(&hex_input);
      success = crypto::UnPadMessage(&hex_input);
      if (success == 0){
        return 1;
      }
      crypto::PrintVectorAsHex(&hex_input);
      break;
      default:
      cerr << "Error: invalid flag or flags. Falid flags are -p, -u, or -k." << endl;
    }
  }
  return 0;
}
