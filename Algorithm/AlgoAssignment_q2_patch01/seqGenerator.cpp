#include <iostream>
#include <cstdlib>
#include <fstream>

#define LEN 1000
#define AMT 20

using namespace std;

ofstream genFile("DNAset.txt");
char Element[4] = {
  'A',
  'G',
  'C',
  'T'
};

int main()
{

  srand(9);

  int amt = 0;
  int randIndex;
  while(amt < AMT)
  {
    for(int i=0; i<LEN; ++i)
    {
      randIndex = rand()%4;
      genFile<<Element[randIndex];
    }
    genFile<<"\n";

    ++amt;
  }

  return 0;

}
