#ifndef CRYPTO_
#define CRYPTO_

#include <vector>

namespace crypto{

/** Section A: input */
void InputBinaryToVector(std::vector<unsigned char>*);
void InputHexToVector(vector<unsigned char>*);

/** Section B: output */
void PrintVectorAsHex(std::vector<unsigned char>*);
void PrintUnPadVector(std::vector<unsigned char>*);
void PrintVectorAsBinary(std::vector<unsigned char>*);

/** Section C: padding/unpadding */
void PadMessage(std::vector<unsigned char>*, int);
bool UnPadMessage(std::vector<unsigned char>*);

}

#endif
