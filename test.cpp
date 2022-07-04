#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <list>

using namespace std;

int writeToFile(string text)
{
  fstream block1;

  block1.open("block1.txt", ios_base::app | ios_base::in);
  if (block1.is_open())
  {
    block1 << text << endl;
    return 0;
  }
  else
  {
    return -1;
  }
  block1.close();
}

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

string decode(string encodedString)
{

  int n = encodedString.length();

  // declaring character array
  char original_char_array[n + 1];
  char encoded_char_array[n + 1];

  // copying the contents of the
  // string to char array
  strcpy(encoded_char_array, encodedString.c_str());

  for (int i = 0; i < n + 1; i++)
  {
    char c = encoded_char_array[i];
    cout << encoded_char_array[i] << endl;
    if (isdigit(c))
    {
      c = c - 3;
      if (c < 48)
      {
        c = c + 10;
      }
    }
    else if (isalpha(c))
    {
      c = c - 3;

      if ((c < 97 && c > 90) || c < 65)
      {
        c = c + 26;
      }
    }
    original_char_array[i] = c;
  }

  string s = original_char_array;

  return s;
  // cout << s << s.length() << endl;
}

string getCreditDebitTotal(string user)
{
  int creditDebitTotal = 0;
  bool userFoundFlag = false;
  string singleLine;

  if (user.empty())
  {
    return "empty";
  }

  ifstream block1("block1.txt");

  while (getline(block1, singleLine))
  {
    if (!singleLine.empty())
    {
      istringstream stringStream(singleLine);
      string words[4];

      for (int i = 0; i < 4; i++)
      {
        stringStream >> words[i];
      }

      if (words[3].empty())
      {
        return "empty";
      }
      int d;
      try
      {
        string decodedValue = decode(words[3]);
        d = stoi(decodedValue);
      }
      catch (...)
      {
        return "empty";
      }

      if (!words[1].empty() && words[1].compare(user) == 0)
      {
        userFoundFlag = true;
        creditDebitTotal = creditDebitTotal - d;
      }

      if (!words[2].empty() && words[2].compare(user) == 0)
      {
        userFoundFlag = true;
        creditDebitTotal = creditDebitTotal + d;
      }
    }
  }

  block1.close();

  if (!userFoundFlag)
  {
    return "empty";
  }
  return to_string(creditDebitTotal);
}

int getMaxSerialNumber()
{
  int maxSer = 0;
  string singleLine;

  ifstream block1("block1.txt");

  while (getline(block1, singleLine))
  {
    if (!singleLine.empty())
    {
      istringstream stringStream(singleLine);
      string currSrStr;
      stringStream >> currSrStr;
      int currSr = stoi(currSrStr);
      if (maxSer < currSr)
      {
        maxSer = currSr;
      }
    }
  }

  block1.close();
  return maxSer;
}
struct Player
{
  int id;
  string name;
  Player(int playerId, string playerName) : id(playerId), name(playerName)
  {
  }
  bool operator<(const Player &playerObj) const
  {
    return id < playerObj.id;
  }
};

int main()
{
  //readFile();
  string s = "log 16 Rolyhu Dol 399";
  // if (s.empty() || s.compare("empty") == 0)
  // {
  //   cout << "String is empty" << endl;
  // }
  // else
  // {
  //   cout << "String is not empty " << s << endl;
  // }
  // int d;
  // try
  // {
  //   d = stoi(s);
  //   cout << "Converted Value " + to_string(d);
  // }
  // catch (...)
  // {
  //   cout << "Cant Convert Value ";
  // }
  // string result = getCreditDebitTotal(s);

  // if (result.empty())
  // {
  //   cout << "Could not find user" << endl;
  // }

  // if (result.compare("empty") == 0)
  // {
  //   cout << "Could not find user" << endl;
  // }

  // int bal = 1000 + stoi(result);
  // cout << "Balance is " << bal << endl;

  // cout << "Max Serial Number is " + to_string(getMaxSerialNumber()) << endl;
  // cout << decode(s) << endl;
  // string w = "15 lsdhf kjhfdsd 80";
  // writeToFile(w);

  // istringstream stringStream(s);
  // string trnstnSingle;
  // string trnstnComplete = "";
  // stringStream >> trnstnSingle;
  // while (stringStream >> trnstnSingle)
  // {
  //   trnstnComplete = trnstnComplete + trnstnSingle + " ";
  // }
  // size_t end = trnstnComplete.find_last_not_of(" ");
  // trnstnComplete = (end == std::string::npos) ? "" : trnstnComplete.substr(0, end + 1);
  // cout << trnstnComplete + "end" << endl;

  // int randomNumber;

  // srand((unsigned)time(0));
  // randomNumber = rand();
  // int randomServName = (randomNumber % 3) + 1;

  // cout << randomNumber << endl;
  // cout << randomServName << endl;
  list<Player> listofPlayers;
  listofPlayers.push_back(Player(6, "Pooja"));
  listofPlayers.push_back(Player(22, "Sid"));
  listofPlayers.push_back(Player(3, "Cheeki"));
  listofPlayers.push_back(Player(43, "Baba"));
  listofPlayers.push_back(Player(30, "Chuglu"));
  listofPlayers.push_back(Player(2, "Chaafu"));
  listofPlayers.sort();
  for (Player &p : listofPlayers)
  {
    cout << p.id << " " << p.name << endl;
  }
}
