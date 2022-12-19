/*
Name: Arsalan Farrokhi U97331543, Kevin Tran U56161476.
*/
#ifndef HUFFMAN
#define HUFFMAN

//Importing the i/o, map, and vector libraries along with the provided files.
#include <iostream>
#include <map>
#include <vector>
#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"

//Declaring a class that inhering the provided base class and declaring prototype for new functions as well as creating a vector for the binary trees created using the class.
class HuffmanTree : public  HuffmanTreeBase {
  public:
    std::string compress(const std::string inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string inputCode, const std::string serializedTree);
    void preorder(std::vector<HuffmanNode*>& p, HuffmanNode* pos) const;
    void serial_postorder(std::string& str, HuffmanNode* pos) const;
  private:
    std::vector<HuffmanNode*> nod;
};
#endif