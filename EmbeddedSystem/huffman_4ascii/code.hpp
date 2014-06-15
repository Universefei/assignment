/* why those is before following #includes ? */
#ifndef CODE_HPP
#define CODE_HPP

#include <map>     // STL map
#include <queue>   // STL queue
#include <fstream> // for class ifstream, ofstream, fstream
#include <cstdint> // ?

#include "node.hpp"
#include "tree.hpp"

class compress
{
   public:
      compress(std::string infile_);
      ~compress();

	  /* Why do not design output file as a data member of class? */
      void write(std::string outfile_);


   private:
      std::ifstream infile;
	  /* histograph, and can be used to construct instance of class tree */
      std::map<char, int> histog;

      // prevent calling of copy-ctor and assignment operator
	  // copy constructor
      compress(const compress &c);
      compress& operator=(const compress &rhs);
};


class decompress
{
   public:
      decompress(std::string file_);
      ~decompress();

      std::string plaintext() const;


   private:
      std::ifstream file;
      uint16_t stream_offset;
      std::string ptext;
      std::map<char, int> histog;

      void getplain(const tree &hc);

      // prevent calling of copy-ctor and assignment operator
      decompress(const decompress &c);
      decompress& operator=(const decompress &rhs);
};



#endif // CODE_HPP
