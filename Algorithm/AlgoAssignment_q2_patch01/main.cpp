#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include <time.h>

using namespace std;

/// Macro configuration
#define SEQ_AMT 20
#define SEQ_LEN 1000  // Configurable
#define MER_LEN 15
#define PERCENT 0.2   // Configurable


/// Files related stream.
ifstream DNASeqFile("DNAset.txt");
ofstream result("RESULT.txt");

ofstream odis[16];
ifstream idis[16];

/// counter for specific distance l_mer number.
int disCnt[MER_LEN]; 

/// Initialization
string DNASeq[SEQ_AMT]; // Store DNA sequeues.

/*----------------------------------------------------------------------------*/
/*                                main()                                      */
/*----------------------------------------------------------------------------*/

int main()
{
	clock_t start,finish;
	double totaltime;

  /// Open/Create files to store temprary data at external storage.
  odis[0].open("DIS_00.txt");
  odis[1].open("DIS_01.txt");
  odis[2].open("DIS_02.txt");
  odis[3].open("DIS_03.txt");
  odis[4].open("DIS_04.txt");
  odis[5].open("DIS_05.txt");
  odis[6].open("DIS_06.txt");
  odis[7].open("DIS_07.txt");
  odis[8].open("DIS_08.txt");
  odis[9].open("DIS_09.txt");
  odis[10].open("DIS_10.txt");
  odis[11].open("DIS_11.txt");
  odis[12].open("DIS_12.txt");
  odis[13].open("DIS_13.txt");
  odis[14].open("DIS_14.txt");
  odis[15].open("DIS_15.txt");

  /// Start timing.
  start=clock();

  // Two-dimension matrix to store distance of 2 DNA l-mer.
  int distance [SEQ_LEN+1-MER_LEN][SEQ_LEN+1-MER_LEN];

  /// Read file data to internel storage.
	for(int i=0; i<SEQ_AMT; i++)  
	{
		getline(DNASeqFile, DNASeq[i]);
	}

  /// Sort and calculate distance.
	for(int i=0; i<SEQ_AMT-1; i++)
	{
		for (int j=i+1; j<SEQ_AMT; j++) 
		{	
			for(int t1=0; t1<SEQ_LEN+1-MER_LEN; t1++)
			{
				for(int t2=0 ; t2<SEQ_LEN+1-MER_LEN; t2++)
				{
					int dis=0;

          /// Boundary situations of dynamic scheme programming algorithm.
					if(t1==0 || t2==0)
					{
						for(int temp=0 ; temp<MER_LEN ;temp++)
						{
							if(DNASeq[i][t1+temp]!=DNASeq[j][t2+temp])
							{
								dis++;
							}	
						}
						distance[t1][t2] = dis;
					}

          /// Recursion situations of dynamic programming.
					else
					{
						dis = distance[t1-1][t2-1];
						if(DNASeq[i][t1-1] != DNASeq[j][t2-1])
						{
							dis -= 1;
						}
						if (DNASeq[i][t1+MER_LEN] != DNASeq[j][t2+MER_LEN])
						{
							dis += 1;
						}
						distance[t1][t2] = dis;
					}

          /// Usage of switch/case can produce higher efficiency.
					switch(distance[t1][t2])
					{
                        case 0:
                          odis[0]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[0];
                          break;
                        case 1:
                          odis[1]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[1];
                          break;
                        case 2:
                          odis[2]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[2];
                          break;
                        case 3:
                          odis[3]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[3];
                          break;
                        case 4:
                          odis[4]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[4];
                        case 5:
                          odis[5]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[5];
                          break;
                        case 6:
                          odis[6]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[6];
                          break;
                        case 7:
                          odis[7]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[7];
                          break;
                        case 8:
                          odis[8]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[8];
                          break;
                        case 9:
                          odis[9]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[9];
                          break;
                        case 10:
                          odis[10]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[10];
                          break;
                        case 11:
                          odis[11]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[11];
                          break;
                        case 12:
                          odis[12]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[12];
                          break;
                        case 13:
                          odis[13]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[13];
                          break;
                        case 14:
                          odis[14]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[14];
                          break;
                        case 15:
                          odis[15]<<i<<","<<t1<<"<-->"<<j<<","<<t2<<" : "<<distance[t1][t2]<<endl;
                          ++disCnt[15];
                          break;
					}
				}
			}	
		}
	}	

  /// Flush to external storage.
  for(int i=0; i<MER_LEN; ++i)
  {
    odis[i].flush();
  }

  /// Open sorted temprary files.
  idis[0].open("DIS_00.txt");
  idis[1].open("DIS_01.txt");
  idis[2].open("DIS_02.txt");
  idis[3].open("DIS_03.txt");
  idis[4].open("DIS_04.txt");
  idis[5].open("DIS_05.txt");
  idis[6].open("DIS_06.txt");
  idis[7].open("DIS_07.txt");
  idis[8].open("DIS_08.txt");
  idis[9].open("DIS_09.txt");
  idis[10].open("DIS_10.txt");
  idis[11].open("DIS_11.txt");
  idis[12].open("DIS_12.txt");
  idis[13].open("DIS_13.txt");
  idis[14].open("DIS_14.txt");
  idis[15].open("DIS_15.txt");

  /// Calculate the output amount of 20% least distance l_mer pairs.
	int outputAmt = (SEQ_LEN+1-MER_LEN)*(SEQ_LEN+1-MER_LEN) * (SEQ_AMT*(SEQ_AMT-1)/2) * PERCENT;

  /// Figure out the maximal l_mer distance we need.
  int addition = 0;
  int cnt; // maximal l_mer distance that need.
  for(cnt=0; addition<outputAmt; ++cnt)
  {
    addition += disCnt[cnt];
  }

  /// Fulfill the RESULT.txt file from sorted temprary files.
  int outedAmt = 0;
  string tmpString;
  for(int i=0; i<=cnt; ++i)
  {
    int k=0;
    while(k<disCnt[i] && outedAmt<outputAmt)
    {
      getline(idis[i], tmpString);
      //cout <<tmpString;
      result<<tmpString<<endl;
      ++outedAmt;
      ++k;
    }
  }

  cout<<"=================================================================="<<endl;
  cout<<"See "<<PERCENT<<" minimal l_mer pairs in generated file RESULT.txt"<<endl;
  /// Calculate consuming time.
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
  cout<<"\nCONSUMED_TIME:  "<<totaltime<<" second"<<endl;

	return 0;
}
