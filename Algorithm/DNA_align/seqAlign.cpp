#include <iostream>
#include <iomanip>

#define MAXLEN 40
using namespace std;

char solutionMatrix[MAXLEN+1][MAXLEN+1];    // store visual emulation path
int  dynamicMatrix[MAXLEN+1][MAXLEN+1];     // store optimil alignment

int main()
{

  string foo; // input string1;
  string bar; // input string2

  int fooLen;
  int barLen;
  
  /// Input from standard IO
  /// ======================

  cout<<"Input the first DNA sequeue (Maximal length: 40 )"<<endl;
  cin >> foo;
  cout<<"Input the second DNA sequeue (Maximal length: 40 )"<<endl;
  cin >> bar;

  fooLen = foo.length();
  barLen = bar.length();

  /// Construct dynammicMatrix[][] and solutionMatrix[][].
  /// ===================================================
  
  // Boundary situation initialization
  for(int i=0; i<=fooLen; ++i)
  {
    dynamicMatrix[barLen][i]=2*(fooLen - i);
    solutionMatrix[barLen][i] = '-';
  }
  
  for(int i=0; i<=barLen; ++i)
  {
    dynamicMatrix[i][fooLen]=2*(barLen - i);
    solutionMatrix[i][fooLen] = '|';
  }

  // Common situation utilizing recursion approach
  int down, right, diagonal;
  for(int verCnt = barLen-1; verCnt>=0; --verCnt)
  {
    for(int horCnt = fooLen-1; horCnt>=0; --horCnt)
    {
      // calculate the penalties  of 3 methods 
      down = dynamicMatrix[verCnt+1][horCnt] + 2; // from down
      right = dynamicMatrix[verCnt][horCnt+1] + 2; // from right
      if(foo[horCnt] == bar[verCnt])
      {
        diagonal = dynamicMatrix[verCnt+1][horCnt+1] + 0; // from diagonal
      }
      else
      {
        diagonal = dynamicMatrix[verCnt+1][horCnt+1] + 1;
      }

      // find out optimil alignment direction.
      if(diagonal <= right && diagonal <= down)
      {
        dynamicMatrix[verCnt][horCnt] = diagonal;
        solutionMatrix[verCnt][horCnt] = '\\';
        continue;
      }
      if(right < diagonal && right < down)
      {
        dynamicMatrix[verCnt][horCnt] = right;
        solutionMatrix[verCnt][horCnt] = '-';
        continue;
      }
      if(down < right && down < diagonal)
      {
        dynamicMatrix[verCnt][horCnt] = down;
        solutionMatrix[verCnt][horCnt] = '|';
        continue;
      }

    }
  }
  
  /// Output into standard IO
  /// =======================
  
  // dynamicMatirx printer
  cout<<"==============================================="<<endl;
  cout<<"dynamic matrix"<<endl;
  for(int verIdx=0; verIdx<=barLen; ++verIdx)
  {
    for(int horIdx=0; horIdx<=fooLen; ++horIdx)
    {
      cout<<setfill('0')<<setw(3)<<dynamicMatrix[verIdx][horIdx]<<" ";
    }
    cout<<endl;
  }

  // solutionMatrix printer
  cout<<endl;
  cout<<"==============================================="<<endl;
  cout<<"solution matrix"<<endl;
  for(int verIdx=0; verIdx<=barLen; ++verIdx)
  {
    for(int horIdx=0; horIdx<=fooLen; ++horIdx)
    {
      cout<<" "<<solutionMatrix[verIdx][horIdx]<<"  ";
    }
    cout<<endl;
  }

  return 0;
}

