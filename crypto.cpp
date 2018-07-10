/** crypto_definitions.cpp */
/** Function definitions for functions declared in namespace crypto */

/** INCLUDES THE FOLLOWING FUNCTIONS:
InputBinaryToVector; PadMessage; InputHexToVector; PrintVectorAsHex;
UnPadMessage; PrintUnPadVector; PrintVectorAsBinary
END OF FUNCTION LIST */

#include <vector>
#include "crypto.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <getopt.h>

namespace crypto{
using std::endl;

void InputBinaryToVector(std::vector<unsigned char>* message){
  char* buffer = new char;
  while (true){
    std::cin.read(buffer,1);
    if (std::cin.eof())
      break;
    else
      message->push_back(*buffer);
  }
  delete buffer;
}

void InputHexToVector(std::vector<unsigned char>* hex_input){
  unsigned int buffer1;
  unsigned char buffer2;
  while (true){
    std::cin >> std::hex >> buffer1;
    if (std::cin.eof())
      break;
    else
      buffer2 = (unsigned char) buffer1;
      //std::cout << std::dec << buffer2;
      hex_input->push_back(buffer1);
  }
}

void PadMessage(std::vector<unsigned char>* message, int block_size){
  int n = message->size();
  int pad_number = block_size- (n%block_size);
  //std::cout << "message size: " << n << " and pad number " <<pad_number << endl;
  unsigned char pad_char = (unsigned char) pad_number;
  for (int i = 0; i != pad_number; i++){
    message->push_back(pad_char);
  }
}

bool UnPadMessage(std::vector<unsigned char>* hex_input){
  int s = hex_input->size();
  int last = hex_input->at(s-1);
  //std::cout << s << endl;
  //std::cout << std::dec << "last is " << last << endl;
  for (int i = 1; i != last; i++){
    //std::cout << hex_input->at(s - i) << " " << endl;
    if ((int) hex_input->at(s - i) != last){
      std::cerr << std::hex << "Error: inconsistent pad byte values" << endl;
      return 0;
    }
  }
  /** if we made it through the for-loop the padding is fine. unpad doesn't take
  a blocksize, but we can check if the pad value is larger than the blocksize, which
  would suggest bad padding - see below for this check. */

  hex_input->resize(s-last);
  //std::cout << "new size: " << hex_input->size() << std::endl;

  if (hex_input->size() < last){
    std::cerr << "Warning! Number of bytes of padding is greater than blocksize." << endl;
  }

  return 1;
}

void PrintVectorAsBinary(std::vector<unsigned char>* output){
  for (auto i=output->begin(); i != output->end(); ++i){
    std::cout << *i << endl;
  }
  std::cout << std::endl;
}

void PrintVectorAsHex(std::vector<unsigned char>* message){
  for (auto i=message->begin(); i != message->end(); ++i){
    std::cout << std::hex <<std::setw(2) << std::setfill('0') << +*i << " " << endl;
  }
  std::cout << std::endl;
}

}
