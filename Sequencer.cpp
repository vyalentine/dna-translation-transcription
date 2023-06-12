/*
File: Sequencer.cpp
Author: Vy Nguyen
Date: 3-26-23
Section: Lab/Discussion Section 12 David Opie, Lecture Section 10 Dixon
Email: vnguye14@umbc.edu
Description: This program builds all of the functions associated 
with the Sequencer.h file
*/

#include "Sequencer.h"
using namespace std; 


// Name: Sequencer (constructor)
// Desc: Creates a new sequencer to hold one or more DNA/mRNA strands make of
//       multiples of three nucleotides
// Preconditions:  Populates m_fileName from passed information from call
//                 For example: ./proj3 proj3_data1.txt
// Postconditions: A sequencer created to populate DNA/mRNA strands
Sequencer::Sequencer(string fileName)
{
  m_fileName = fileName; 
}

// Name:  Sequencer (destructor)
// Desc: Deallocates all dynamic aspects of a Sequencer
// Preconditions: There are an existing DNA/mRNA strand(s) (linked list)
// Postconditions: All vectors are cleared of DNA and mRNA strands
//                 Indicates that the strands have been deallocated
Sequencer::~Sequencer()
{
  cout << "Deleting DNA Strands. " << endl; 
  cout << "Deleting mRNA Strands. " << endl; 
  // delete all the dyanmic mem in both vectors
  // by traversing through each vector based on its
  // size and deleting the LLs (passed into Strand destructor)
  int dnaVectSize;
  dnaVectSize = (int) m_DNA.size(); 
  for (int i = 0; i < dnaVectSize; i++)
  {
    delete m_DNA.at(i); 
  }

  int mRNAVectSize;
  mRNAVectSize = (int) m_mRNA.size(); 
  for (int i = 0; i < mRNAVectSize; i++)
  {
    delete m_mRNA.at(i); 
  }
}

// Name: StartSequencing
// Desc: Calls ReadFile and continually calls mainmenu until the user exits
// Preconditions: m_fileName has been populated
// Postconditions: m_DNA has been populated (after ReadFile concludes)
void Sequencer::StartSequencing()
{
  ReadFile(); 
  while (MainMenu() != 5) { MainMenu(); }
}

// Name: DisplayStrands
// Desc: Displays each strand in both mDNA and mRNA
//       Displays numbered type (For example, DNA 1) then the name of the strand.
//       Finally displays the strand with arrows between each nucleotide
// Preconditions: At least one linked list is in mDNA (may have mRNA)
// Postconditions: Displays DNA strand from one of the vectors
void Sequencer::DisplayStrands()
{
  // need to cast the size of vectors for it to return as int
  int dnaVectSize; 
  dnaVectSize = (int) m_DNA.size(); 

  // iterate through the vectors mDNA and mRNA that holds the strands (LLs)
  // first, display the DNA strands vector  
  for (int i = 0; i < dnaVectSize; i++)
  {
    // checks to see if the LL is empty
    if(m_DNA.at(i)->GetSize() == 0) 
    { 
      cout << "The DNA strand is empty." << endl; // output if it is empty
    }
    else
    {
      // output DNA number and name of organism
      cout << "DNA " << i + 1 << endl; 
      cout << "***" << m_DNA.at(i)->GetName() << "***" << endl; 
      cout << *m_DNA.at(i) << endl;
    }
  }

  //repeat the following steps for mRNA vector 
  int mRNAVectSize;
  mRNAVectSize = (int) m_mRNA.size(); 
  for (int i = 0; i < mRNAVectSize; i++)
  {
    // checks to see if the LL is empty
    // use at() for bounds checking
    if(m_mRNA.at(i)->GetSize() == 0) 
    { 
      cout << "The mRNA strand is empty." << endl; // output if it is empty
    }
    else{
      // output DNA number and name of organism
      cout << "mRNA" << i + 1 << endl; 
      cout << "***" << m_mRNA.at(i)->GetName() << "***" << endl; 
      cout << *m_mRNA.at(i) << endl;
    }
  }
}


// Name: ReadFile
// Desc: Reads in a file of DNA strands that has the name on one line then
//       the sequence on the next
//       All sequences will be an indeterminate length (always evenly divisible by three though).
//       There are an indeterminate number of sequences in a file.
//       Hint: Read in the entire sequence into a string then go char
//       by char until you hit a new line break. Then insert to the m_DNA vector
// Preconditions: Valid file name of characters (Filled with a name and then A, T, G, or C)
// Postconditions: Populates each DNA strand and puts in m_DNA
void Sequencer::ReadFile()
{
  string nameOfStrand = ""; // store the name of the organism 
  string sequence = ""; // store the organism's DNA sequence 
  ifstream sequenceFileHandler(m_fileName); // open file 
  while ((getline(sequenceFileHandler, nameOfStrand, ',')) and getline(sequenceFileHandler, sequence))
  {
    Strand *myStrand = new Strand(nameOfStrand); // create a strand pointer object
    // another loop that interates through the sequence string length: 
    for (int i = 0; i < (int) sequence.length(); i++)
    {
      // if the char at the index is NOT a comma or endline, 
      // insert it into the LL 
      if ((sequence[i] != '\0') and (sequence[i] != ','))
      {
        myStrand->InsertEnd(sequence[i]); 
      }
    }
    // then insert newstrand into the DNA vector
    m_DNA.push_back(myStrand); 
  }

  cout << "Opened File. " << endl; 
  cout << (int) m_DNA.size() << " strand(s) loaded. " << endl; 
  sequenceFileHandler.close(); 
}

// Name:  MainMenu
// Desc: Displays the main menu and manages exiting.
//       Returns 5 if the user chooses to quit, else returns 0
// Preconditions: m_DNA populated
// Postconditions: Indicates the user has quit the program
int Sequencer::MainMenu()
{
  // do while that manages the main menue and its options 
  int userChoice; 
  do
  {
    // show main menu and get user choice
    cout << "What would you like to do?: " << endl
        << "1. Display Strands " << endl
        << "2. Reverse Strand " << endl
        << "3. Transcribe DNA to mRNA " << endl
        << "4. Translate mRNA to Amino Acids " << endl
        << "5. Quit " << endl; 
    cin >> userChoice; 

    // checks to see if between 1 and 5
    if (userChoice < 1 || userChoice > 5)
    {
      cout << "Please choose again (1-5)." << endl;
      continue; // go down to the next iteration of main menu 
    }
    // switch for the userChoice options/functions
    switch (userChoice) 
    {
    case 1:
      DisplayStrands();
      break;

    case 2:
      ReverseSequence();
      break;

    case 3:
      Transcribe();
      break;

    case 4:
      Translate();
      break;

    case 5:
      break; // exit the loop
    }
  }while (userChoice != 5); 

  if (userChoice != 5)
  {
    return 0; 
  }

  else
  {
    cout << "Exiting program. " << endl; 
    return 5; 
  }
}

// Name: ChooseDNA
// Desc: Asks the user to choose one strand to use from loaded DNA strands
// Preconditions: Populated m_DNA
// Postconditions: Returns index of chosen strand
int Sequencer::ChooseDNA()
{
  // dnaChoice is 1 by default if there is only one DNA strand
  int dnaChoice = 1; 
  int dnaVectSize;
  dnaVectSize = (int) m_DNA.size(); 

  // if there are more than one DNA strands: 
  if (dnaVectSize > 1)
  {
    // ask user which strand they want then store that in a int var 
    cout << "Which DNA strand do you want to work with?" << endl; 
    cout << "Choose 1 - " << dnaVectSize << endl; 
    cin >> dnaChoice; 

    // user input validation 
    while ((dnaChoice < 1) || (dnaChoice > dnaVectSize ))
      {
        cout << "Please choose again." << endl; 
        cout << "Which DNA strand do you want to work with?" << endl; 
        cout << "Choose 1 - " << m_DNA.size() << endl; 
        cin >> dnaChoice; 
      }
  }

  // decrement by 1 before returning 
  return --dnaChoice;
}

// Name: ChooseMRNA
// Desc: Asks the user to choose one strand to use from translated mRNA strands
// Preconditions: Populated m_mRNA
// Postconditions: Returns index of chosen strand
int Sequencer::ChooseMRNA()
{
  // ask user which strand they want then store that in a int var 
  int mRNAChoice = 1; 
  int mRNAVectSize;
  mRNAVectSize = (int) m_mRNA.size(); 
  
  // if there are more than one mRNA strands: 
  if (mRNAVectSize > 1)
  {
  cout << "Which mRNA strand do you want to work with?" << endl; 
  cout << "Choose 1 - " << mRNAVectSize << endl; 
  cin >> mRNAChoice; 

  // user input validation 
  while ((mRNAChoice < 1) || (mRNAChoice > mRNAVectSize ))
    {
      cout << "Please choose again." << endl; 
      cout << "Which mRNA strand do you want to work with?" << endl; 
      cout << "Choose 1 - " << m_mRNA.size() << endl; 
      cin >> mRNAChoice; 
    }
  }

  // decrement by 1 before returning 
  return --mRNAChoice;
}

// Name: ReverseSequence
// Desc: User chooses to reverse either DNA or mRNA to reverse
//       Then calls either ChooseDNA or ChooseMRNA which returns index of strand
//       Calls ReverseStrand on chosen location
// Preconditions: Populated m_DNA or m_mRNA
// Postconditions: Reverses a specific strand replacing in place
void Sequencer::ReverseSequence()
{
  int strandChoice; 
  cout << "Which type of strand to reverse?" << endl
  << "1. DNA" << endl
  << "2. mRNA" << endl; 
  cin >> strandChoice; 

  //user input val: if strandChoice is not 1 or 2 
  while ((strandChoice < 1) || (strandChoice > 2))
  {
    cout << "Please choose again." << endl; 
    cout << "Which type of strand to reverse?" << endl
    << "1. DNA" << endl
    << "2. mRNA" << endl; 
    cin >> strandChoice; 
  }

  if (strandChoice == 1) // if user chooses to reverse DNA strand
  {
      // allow user to choose which mRNA to reverse by calling ChooseDNA
      // then pass returned index into ReverseSeq function
      int dnaChoice = ChooseDNA(); 
      m_DNA.at(dnaChoice)->ReverseSequence(); 
      dnaChoice += 1; // add by one for the cout statement 
      cout << "Done reversing DNA " << dnaChoice << "'s Strand!" << endl; 
  }

  else if (strandChoice == 2) // if user chooses to reverse mRNA strand
  {
    // if the mRNA vector is empty, prompt user to transcribe DNA first
    if (int(m_mRNA.size()) == 0) 
    { 
      cout << "No mRNA to reverse; Transcribe DNA first." << endl; 
    }
    // if there are mRNA to reverse:
    // allow user to choose which mRNA to reverse by calling ChooseMRNA 
    // then pass returned index into ReverseSeq function
    else 
    { 
      int mRNAChoice = ChooseMRNA(); 
      m_mRNA.at(mRNAChoice)->ReverseSequence();
      mRNAChoice += 1; // add by one for the cout statement 
      cout << "Done reversing mRNA " << mRNAChoice << "'s Strand!" << endl; 
    }
  }

}

// Name: Transcribe
// Desc: Iterates through each DNA strand in m_DNA to transcribe to m_mRNA
// A->U, T->A, C->G, G->C (DNA to mRNA)
// Can be called multiple times (will result in multiple mRNA strands)
// Puts the transcribed mRNA strand into m_mRNA
// Note: if this function is called more than once on the same strands of DNA,
// it will add duplicate strands into m_mRNA!
// Preconditions: Populated m_DNA
// Postconditions: Transcribes each strand of m_DNA to m_mRNA
void Sequencer::Transcribe()
{
  int dnaVectSize; 
  dnaVectSize = (int) m_DNA.size(); 
  // iterate through the vector mDNA that holds the DNA strands (LLs) using nested for-loops 
  // first for-loop iterates through the size of m_DNA vector
  for (int i = 0; i < dnaVectSize; i++)
  {
    // checks to see if the LL at an indice within the vector is empty
    if(m_DNA.at(i)->GetSize() == 0) 
    {
      cout << "ERROR: The DNA strand is empty." << endl; // output if it is empty
    }

    else // otherwise, if LL is NOT empty 
    {
      // creating a new empty mRNA strand pointer object
      // along with a char var for the nucleotides in each LL 
      Strand *newMRNAStrand = new Strand(m_DNA.at(i)->GetName());   
      char mRNAnucleotide; 
      int dnaLLSize = m_DNA.at(i)->GetSize(); // get size of LL at index of vector 

      // 1) second for-loop iterates through the size of each LL in the m_DNA vector
      // 2) pass the indexes of the LL to access char, which is passed into GetData()
      // for comparison, and then change mRNAnucleotide var into corresponding letter 
      for (int j = 0; j < dnaLLSize; j++)
      {
        // basically: if the node at index j of the DNA LL, within this DNA vector, corresponds to a letter
        // this is what the mRNAnucleotide would be 
        if (m_DNA.at(i)->GetData(j) == 'A') { mRNAnucleotide = 'U'; }

        else if (m_DNA.at(i)->GetData(j) == 'T') { mRNAnucleotide = 'A'; }

        else if (m_DNA.at(i)->GetData(j) == 'C') { mRNAnucleotide = 'G'; }
        
        else if (m_DNA.at(i)->GetData(j) == 'G') { mRNAnucleotide = 'C'; }
        
        // insert the new nucleotide at the end of the newMRNAStrand LL 
        newMRNAStrand->InsertEnd(mRNAnucleotide); 
      }
      // new mRNAStrand LL is inserted into m_mRNA vector
      m_mRNA.push_back(newMRNAStrand); 
    }
  }
  cout << dnaVectSize << " strand(s) of DNA successfully transcribed into new mRNA strands! " << endl; 
}

// Name: Translate
// Desc: Iterates through a chosen mRNA strand and converts to amino acids
// For every three nucleotides in strand, passes them three at a time to Convert
// Displays each amino acid but does not store the amino acids in the class
// Preconditions: Populated m_mRNA
// Postconditions: Translates a specific strand of mRNA to amino acids
void Sequencer::Translate()
{
    // if the mRNA vector is empty 
    // prompt user to transcribe DNA first 
    if (m_mRNA.size() == 0) 
    { 
      cout << "No mRNA to translate; Transcribe DNA first." << endl; 
    }
    else
    {
      //allow user to choose which mRNA to translate by calling ChooseMRNA
      int mRNAChoice = ChooseMRNA(); 
      // calculate the size of the chosen mRNA LL 
      int mRNAChoiceSize = m_mRNA.at(mRNAChoice)->GetSize(); 
      // display name of strand
      cout << "***" << m_mRNA.at(mRNAChoice)->GetName() << "***" << endl; 
      for (int i = 0; i < mRNAChoiceSize; i ++)
      {
        if (i % 3 == 0) // checks if the current index is a multiple of 3 using mod 
        {
          // local constants that are passed into GetData to access the three letter groups 
          const int FIRST_LETTER = 0;
          const int SECOND_LETTER = 1;
          const int THIRD_LETTER = 2; 
          // make a string out of every three chars by calling GetData() three times
          // and adding the chars to an empty string, then pass string to Convert()
          char nucleotide1 = m_mRNA.at(mRNAChoice)->GetData(i + FIRST_LETTER);
          char nucleotide2 = m_mRNA.at(mRNAChoice)->GetData(i + SECOND_LETTER);
          char nucleotide3 = m_mRNA.at(mRNAChoice)->GetData(i + THIRD_LETTER);
          string trinucleotide = ""; 
          trinucleotide += nucleotide1;
          trinucleotide += nucleotide2; 
          trinucleotide += nucleotide3; 
          cout << trinucleotide << "->" << Convert(trinucleotide) << endl; 
        }
      }
      mRNAChoice += 1; // increment by one for the cout statement 
      cout << "Done translating mRNA " << mRNAChoice << "'s Strand! " << endl; 

    }
}

// Name: Convert (Provided)
// Desc: Converts codon (three nodes) into an amino acid
// Preconditions: Passed exactly three U, A, G, or C
// Postconditions: Returns the string name of each amino acid
string Sequencer::Convert(const string trinucleotide){
  if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))
    return ("Isoleucine");
  else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA")||
	  (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG"))
    return ("Leucine");
  else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
	  (trinucleotide=="GUA")||(trinucleotide=="GUG"))
    return ("Valine");
  else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))
    return ("Phenylalanine");
  else if((trinucleotide=="AUG"))
    return ("Methionine (START)");
  else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))
    return ("Cysteine");
  else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
	  (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");
  else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
	  (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");
  else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
	  (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");
  else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
	  (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");
  else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
	  (trinucleotide=="UCA")||(trinucleotide=="UCG")||
	  (trinucleotide=="AGU")||(trinucleotide=="AGC"))
    return ("Serine");
  else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
    return ("Tyrosine");
  else if((trinucleotide=="UGG"))
    return ("Tryptophan");
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");
  else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))
    return ("Asparagine");
  else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))
    return ("Histidine");
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");
  else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))
    return ("Aspartic acid");
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");
  else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
	  (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");
  else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"))
    return ("Stop");
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}
