/*
File: Sequencer.cpp
Author: Vy Nguyen
Date: 3-26-23
Section: Lab/Discussion Section 12 David Opie, Lecture Section 10 Dixon
Email: vnguye14@umbc.edu
Description: This program builds all of the functions associated 
with the Strand.h file
*/

#include "Strand.h"
using namespace std; 

// Name: Strand() - Default Constructor
// Desc: Used to build a new empty strand (m_head, m_tail = nullptr and size = 0)
// Preconditions: None
// Postconditions: Creates a new strand with a default name
Strand::Strand()
{
    m_name = "myStrand";
    m_head = nullptr; 
    m_tail = nullptr; 
    m_size = 0; 
}

// Name: Strand(string) - Overloaded Constructor
// Desc: Used to build a new empty strand with the name passed
//       with m_head, m_tail = nullptr; size = 0;
// Preconditions: None
// Postconditions: Creates a new strand with passed name
Strand::Strand(string name)
{
    m_name = name; 
    m_head = nullptr; 
    m_tail = nullptr; 
    m_size = 0; 
}

// Name: ~Strand() - Destructor
// Desc: Used to destruct a strand
// Preconditions: There is an existing strand with at least one node
// Postconditions: Strand is deallocated (including all dynamically allocated nodes)
//                 to have no memory leaks!
Strand::~Strand()
{
    // assigning currNode pointer to m_head (start of LL)
    Node *currNode = m_head;
    //Iterates through and removes each node
    while(currNode != nullptr)
    { 
        m_head = currNode; //sets m_head to curr
        currNode = currNode -> m_next; //moves curr to next node
        delete m_head; //delete m_head;
    }
    // reset all of the static LL pointers
    // set pointers to nullptr, and size of LL to 0
    m_head = nullptr; 
    m_tail = nullptr; 
    m_size = 0; 
}

// Name: InsertEnd
// Desc: Takes in a char. Creates a new node.
//       Inserts node at the end of the strand. Increases size.
// Preconditions: Requires a strand
// Postconditions: Strand is larger.
void Strand::InsertEnd(char data)
{
    Node *newNode = new Node(); // creates new node
    newNode->m_data = data;
    newNode->m_next = nullptr;
    if(m_head == nullptr) // checks if the linked list is empty
    { 
        m_head = newNode; // inserts the new node to the linked list
    }
    else // since the linked list is NOT empty 
    {
        // set a new node to m_head (start of LL)
        Node* currNode = m_head;
        // and while the node is pointed to the next node BUT NOT nullptr (the end)
        while (currNode->m_next != nullptr) 
        {
            // continue pointing currNode to the next node/throughout the LL
            currNode = currNode->m_next;
        }
        // then set newNode to the next node that currNode is pointing to
        currNode->m_next = newNode;
    }
    m_size++; // increments the size of the linked list
}

// Name: GetName()
// Preconditions: Requires a strand
// Postconditions: Returns m_name;
string Strand::GetName()
{
    return m_name; 
}

// Name: GetSize()
// Preconditions: Requires a strand
// Postconditions: Returns m_size;
int Strand::GetSize()
{
    return m_size; 
}

// Name: ReverseSequence
// Preconditions: Reverses the strand
// Postconditions: Strand sequence is reversed in place; nothing returned
void Strand::ReverseSequence()
{
    // initialize new nodes to use in the loop 
    Node *currNode = m_head; 
    Node *prevNode = nullptr; 
    Node *nextNode = nullptr; 

    while (currNode != nullptr) // loop until end of LL
    {
        // store currNode pointing to next 
        nextNode = currNode->m_next; 
        // then reverse currNodes pointer to prevNode
        currNode->m_next = prevNode; 
        // move pointers one position ahead 
        prevNode = currNode;
        currNode = nextNode; 
    }
    m_head = prevNode; 
}

// Name: GetData
// Desc: Returns the data at a specific location in the strand.
//       Iterates to node and returns char.
// Preconditions: Requires a DNA sequence
// Postconditions: Returns a single char from a node
char Strand::GetData(int nodeNum)
{
    // start at the head of LL 
    Node *currNode = m_head;
    // use for-loop to traverse LL until nodeNum index is reached 
    for (int i = 0; i < nodeNum; i++)
    {
        // bounds checker: if currNode is null, its the end of the LL
        if (currNode == nullptr)
        {
            cout << "Error: Current node is NULL - index out of range." << endl; 
        }
        // otherwise, currNode continues to point to the next node 
        else
        {
            currNode = currNode->m_next; 
        }
    }
    // return the char at nodeNum
    return currNode->m_data; 
}
// Name: operator<<
// Desc: Overloaded << operator to return ostream from strand
//       Iterates over the entire strand and builds an output stream
//       (Called like cout << *m_DNA.at(i); in Sequencer)
// Preconditions: Requires a strand
// Postconditions: Returns an output stream (does not cout the output)
ostream &operator<< (ostream &output, Strand &myStrand)
{
    if (myStrand.GetSize() == 0) // strand size checker
    {
        output << "Strand is empty."; 
        return output; 
    }
    else // if LL is populated:
    {   // create new node that is set to the head of LL 
        Node *currNode = myStrand.m_head;
        // traverse LL until the end 
        while (currNode != nullptr)
        {
            output << currNode->m_data; // print out data 
            output << "->"; // along with arrow 
            currNode = currNode->m_next; // then currNode becomes the next node 
        }
        output << "END";
    }
    return output; 
}

