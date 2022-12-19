/*
Name: Arsalan Farrokhi U97331543, Kevin Tran U56161476
*/
#include "Huffman.hpp"

//Defining a class for preorder travers that gets a reference to a vector of huffmannode pointers and a current position.
void HuffmanTree::preorder(std::vector<HuffmanNode*>& p, HuffmanNode* pos) const{
  //adds the character from the position to the back of the vector.
  if(pos->getCharacter() != 0)
    p.push_back(pos);
  //recursively call the function for the two nodes.
  if(pos->left != nullptr){
    preorder(p, pos->left);    
  }
  if(pos->right != nullptr ){
    preorder(p, pos->right);
  }
}

//A function that traverses in postorder through the position and adds the serial representation of the tree to the string.
void HuffmanTree::serial_postorder(std::string& str, HuffmanNode* pos) const{
  //recursively call the function for the left child.
  if(pos->left != nullptr){
    serial_postorder(str, pos->left);    
  }
  //recursively call the function for the right child.
  if(pos->right != nullptr ){
    serial_postorder(str, pos->right);
  }
  //if the position is a branch -> add "B".
  if(pos->getCharacter() == 0){
    str+="B";
  }
  //Add "L" and the character if the position is a leaf.
  else{
    str+="L";
    str+=(pos->getCharacter());
  }
}

//Compression function
std::string HuffmanTree::compress(const std::string inputStr){
  
  //making a frequency dictionary.
  std::map<char, int> freqtab;
  for(auto i : inputStr){
    freqtab[i]++;
  }
  
  //inserting the dictionary values into the heapqueue 
  HeapQueue<HuffmanNode*, HuffmanNode::Compare> HQ;
  for(auto i : freqtab){
    HuffmanNode* temp = new HuffmanNode(i.first, i. second);
    HQ.insert(temp);
  }
  
  //Compressing the nodes into a binary tree
  while(HQ.size()!= 1){
    
    HuffmanNode* L = HQ.min();
    HQ.removeMin();
    HuffmanNode* R = HQ.min();
    HQ.removeMin();
    HuffmanNode* branch = new HuffmanNode(0, (int) (L->getFrequency())+(int)(R->getFrequency()), nullptr, L, R);
    L->parent = branch;
    R->parent = branch;
    HQ.insert(branch);
    
  }

  //Getting a vector of positions in a preorder traverser
  std::vector<HuffmanNode*> p;
  preorder(p, HQ.min());
  
  //making a dictionary of binary represenations of each character
  std::map<char, std::string> binary;
  
  //filling the dictionary with the values
  for(auto each : p){
    HuffmanNode* ptr = each;
    while(!(ptr->isRoot())){
      if(ptr == (ptr->parent->right)){
        binary[each->getCharacter()] = "1" + binary[each->getCharacter()];
      }
      else{
        binary[each->getCharacter()] = "0" + binary[each->getCharacter()];
      }
      ptr = ptr->parent;
    }
    
  }
  //getting the output
  std::string output;
  for(auto letter : inputStr){
    output += binary[letter];
  }
  //updating the binary tree that we got after the compression
  nod.push_back(HQ.min());
  
  return output;
}

//function to serialize the tree
std::string HuffmanTree::serializeTree() const {
      //calling a recursive function on the binary tree to get the postorder representation of the tree
      std::string output;
      HuffmanNode* pos = nod.back();
      serial_postorder(output, pos);
      return output;
      }


//decompressing the code and the tree
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){
 
  //Recreating the binary tree in a postorder manner
  HuffmanNode* pos = new HuffmanNode(serializedTree[1], 0);
  HuffmanNode* temp;
  for(int i = 2; i < serializedTree.length(); i++){
    if(serializedTree[i] == 'L'){
      i++;
      if(pos->parent == nullptr){
        temp = new HuffmanNode(0, 0);
        temp->left = pos;
        pos->parent = temp;
        temp = new HuffmanNode(serializedTree[i], 0, pos->parent, nullptr, nullptr);
        pos->parent->right = temp;
        pos = temp;
      }
      else if(pos == pos->parent->right){
        temp = new HuffmanNode(0, 0, pos->parent, pos, nullptr);
        pos->parent->right = temp;
        pos->parent = temp;
        temp = new HuffmanNode( serializedTree[i], 0, pos->parent, nullptr, nullptr);
        pos->parent->right = temp;
        pos = temp;
      }
    }
    else{
      pos = pos->parent;
    }
  }
  //Making the string from the code from the arguments using the binary tree creading in the previous step
  temp = pos;
  std::string output;
  for(auto i : inputCode){
    i=='0'?temp = temp->left: temp = temp->right;
    if(temp->isLeaf()){
      output+=temp->getCharacter();
      temp = pos;
    }
  }
  //returning the string
  return output;
}