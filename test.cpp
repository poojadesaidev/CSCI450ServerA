#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

void readFile()
{
  string singleLine;

  ifstream block1("block1.txt");

  while (getline(block1, singleLine))
  {
    cout << singleLine << endl;
  }

  block1.close();
}

string getCreditDebitTotal(string user)
{
  double creditDebitTotal = 0;
  bool userFoundFlag = false;
  string singleLine;

  if (user.empty())
  {
    return "empty";
  }

  ifstream block1("block1.txt");

  while (getline(block1, singleLine))
  {
    cout << singleLine << endl;

    if (!singleLine.empty())
    {
      istringstream stringStream(singleLine);
      string words[3];

      for (int i = 0; i < 3; i++)
      {
        stringStream >> words[i];
      }

      if (words[3].empty())
      {
        return "empty";
      }

      if (!words[0].empty() && words[0].compare(user))
      {
        creditDebitTotal = creditDebitTotal;
      }
    }
  }

  block1.close();

  if (!userFoundFlag)
  {
    return NULL;
  }
  return NULL;
}

int main()
{
  //readFile();
  string s = "9";
  // if (s.empty() || s.compare("empty") == 0)
  // {
  //   cout << "String is empty" << endl;
  // }
  // else
  // {
  //   cout << "String is not empty " << s << endl;
  // }
  int d;
  try
  {
    d = std::stoi(s);
    cout << "Converted Value " + to_string(d);
  }
  catch (...)
  {
    cout << "Cant Convert Value ";
  }
}
