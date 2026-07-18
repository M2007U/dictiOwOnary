#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

#include "FOwOFunctions.cpp"

using namespace std;

int POwO_vector_BinarySearch(vector<string>& inVector , string inString, bool inUseLength, bool inDebug)
{
    //will return -1 if string does not exist, else will return index

    if (inVector.size() == 0)
    {
        return -1;
    }
    else
    {
        int PinL = 0;
        int PinR = (int)inVector.size();

        while (PinL < PinR)
        {
            int PinM = PinL + (PinR - PinL) / 2;
            if (inDebug)
            {
                cout << "LMR:" << PinL << "," << PinM << "," << PinR << endl;
            }
            
            //base on lenth first
            if (inVector[PinM].length() < inString.length() && inUseLength)
            {
                PinL = PinM + 1;
            }
            else if (inString.length() < inVector[PinM].length() && inUseLength)
            {
               PinR = PinM ;
            }
            else if (inVector[PinM] < inString) //then string
            {
                PinL = PinM + 1;
            }
            else if (inString < inVector[PinM])
            {
                PinR = PinM;
            }
            else if (inVector[PinM].length() == inString.length() && inVector[PinM] == inString)
            {
                //found match
                PinL = PinM;
                PinR = PinM;
                return PinM;
            }
        }

        return -1; //if the flow managed to reach here, this mean that the text does not exist
        
    }
      
}

void POwO_vector_BinaryInsert(vector<string>& inVector , string inString , bool inUseLength, bool inDebug)
{
    if (inVector.size() == 0)
    {
        inVector.push_back(inString);
    }
    else
    {
        int PinL = 0;
        int PinR = (int)inVector.size();
        bool willInsert = true;

        while (PinL < PinR)
        {
            int PinM = PinL + (PinR - PinL) / 2;
            if (inDebug)
            {
                cout << "LMR:" << PinL << "," << PinM << "," << PinR << endl;
            }

            //base on lenth first
            if (inVector[PinM].length() < inString.length() && inUseLength)
            {
                PinL = PinM + 1;
            }
            else if (inString.length() < inVector[PinM].length() && inUseLength)
            {
               PinR = PinM ;
            }
            else if (inVector[PinM] < inString) //then string
            {
                PinL = PinM + 1;
            }
            else if (inString < inVector[PinM])
            {
                PinR = PinM;
            }
            else if (inVector[PinM].length() == inString.length() && inVector[PinM] == inString)
            {
                //found match
                PinL = PinM;
                PinR = PinM;
                willInsert = false;
            }
        }

        if (willInsert)
        {
            inVector.insert(inVector.begin() + PinL, inString);
        }
        
    }
    
}

int main ()
{
    FOwO fowo;
    vector<string> StringList = {};
    string USERinput = "";
    bool FLAG_Debug = false;

    getline(cin,USERinput);

    while(USERinput != "/exit")
    {
        cout << fowo.strOwOng.shOwOrthand.ColorText("b") <<  ">";
        //cin.ignore();
        getline(cin,USERinput);
        cout << fowo.strOwOng.shOwOrthand.ColorText("d");

        if (USERinput == "/help" || USERinput == "/h")
        {
            cout << fowo.strOwOng.shOwOrthand.ColorText("g") << fowo.cOwOut.GenerateTable<string>({"Commands","what it does ?"},{16,75}, {'l','l'},
            {
                "/print all","print all words in the list",
                "/clr","clear the screen",
                "/read doc","read all words from a txt file",
                "/print doc","generate a txt file with all words in the list",
                "/search","search for a word and return it's index",

                "/del","delete a word at a certain index",
                "/delList","delete all words that appears in a certain txt file from the list",
                "/delAll","delete all words from te list",

                "/flag debug","switch between debug mode or not"
            },'-',' ') << fowo.strOwOng.shOwOrthand.ColorText("d") << endl;
        }
        else if (USERinput == "/print all")
        {
            int temp_columnCount = 0;
            fowo.cOwOut.PromptForNumber<int>("column count ? : ", temp_columnCount);

            int temp_columnWidth = 0;
            fowo.cOwOut.PromptForNumber<int>("column width ? : ", temp_columnWidth);

            cout << fowo.strOwOng.shOwOrthand.ColorText("g") ;

            for(int i = 0 ; i < StringList.size() ; i++)
            {
                cout << "(" << right << setfill(' ') << setw(5) << i << ") : " << setw(temp_columnWidth) << setfill(' ') << left << StringList[i];
                
                if ((i+1) % temp_columnCount == 0)
                {
                    cout << endl;
                }
            }

            cout << fowo.strOwOng.shOwOrthand.ColorText("d") << endl;


        }
        else if (USERinput == "/clr")
        {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
        else if (USERinput == "/read doc" || USERinput == "/rd")
        {
            string temp_fileName = "";
            string temp_isOrdered = "";

            fowo.cOwOut.PromptUserStrings({&temp_fileName, &temp_isOrdered},{"filename ? : ","is ordered ? y/n :"});

            ifstream ReaderOwO(temp_fileName);

            if (!ReaderOwO.is_open())
            {
                cout << fowo.cOwOut.ConsoleQuick("r","nope, can't find file QwQ>") << endl;
            }
            else
            {
                string temp_line = "";

                if (temp_isOrdered == "y")
                {
                    while( getline(ReaderOwO, temp_line))
                    {
                        if (temp_line != "")
                        {
                            StringList.push_back(temp_line);
                        }
                    }
                }
                else
                {
                    while( getline(ReaderOwO, temp_line))
                    {
                        if (temp_line != "")
                        {
                            POwO_vector_BinaryInsert(StringList, temp_line, false, FLAG_Debug);
                        }
                    }
                }

                cout << fowo.cOwOut.ConsoleQuick("g","file read : " + temp_fileName) << endl;

                
            }
        }
        else if (USERinput == "/print doc" || USERinput == "/pd")
        {
            cout << "filename ? : ";
            string temp_fileName = "";
            getline(cin,temp_fileName);

            ofstream WriterOwO(temp_fileName);
            if (!WriterOwO.is_open())
            {
                cout << "can't write file QAQ" << endl;
            }
            else
            {
                for(int i = 0 ; i < StringList.size() ; i ++)
                {
                    WriterOwO << StringList[i] << "\n";
                }
            }
            WriterOwO.close();
        }
        else if (USERinput == "/search" || USERinput == "/sr")
        {
            string temp_SearchString = "";
            fowo.cOwOut.PromptUserStrings({&temp_SearchString},{"search string ? : "});

            cout << fowo.strOwOng.shOwOrthand.ColorText("g") << "searched index : " << POwO_vector_BinarySearch(StringList, temp_SearchString, false, FLAG_Debug) << fowo.strOwOng.shOwOrthand.ColorText("d") << endl;
        }
        else if (USERinput == "/del")
        {
            int temp_catchIndex = -1;
            cout << "index ? : " ;
            cin >> temp_catchIndex;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 🔥 ONLY HERE
            if (0 <= temp_catchIndex && temp_catchIndex < StringList.size())
            {
                StringList.erase( StringList.begin() + temp_catchIndex );
                cout << "removed item index : " << temp_catchIndex << endl; 
            }
            else
            {
                cout << "index out of range" << endl;
            }
        }
        else if (USERinput == "/delList")
        {
            cout << "filename ? : ";
            string temp_fileName = "";
            getline(cin,temp_fileName);

            ifstream ReaderOwO(temp_fileName);

            if (!ReaderOwO.is_open())
            {
                cout << "nope, can't find file QwQ>" << endl;
            }
            else
            {
                string temp_line = "";
                while( getline(ReaderOwO, temp_line))
                {
                    int temp_catchIndex = POwO_vector_BinarySearch(StringList, temp_line, false, FLAG_Debug);

                    if (temp_catchIndex > -1)
                    {
                        StringList.erase( StringList.begin() + temp_catchIndex );
                        cout << "removed item : " << temp_line << endl;
                    }
                }                
            }
        }
        else if (USERinput == "/delAll")
        {
            StringList.clear();
            cout << "string list cleared, all clean" << endl;
        }
        else if (USERinput == "/exit")
        {
            cout << "ok bye OwO/" << endl;
        }
        else if (USERinput == "/flag debug")
        {
            string temp_userInput = "";

            fowo.cOwOut.PromptUserStrings({&temp_userInput},{"set flag Debug to (0/1) ?"});

            if (temp_userInput == "0")
            {
                FLAG_Debug = false;
                cout << fowo.cOwOut.ConsoleQuick("g","FLAG_Debug is now false") << endl;
            }
            else if (temp_userInput == "1")
            {
                FLAG_Debug = true;
                cout << fowo.cOwOut.ConsoleQuick("g","FLAG_Debug is now true") << endl;
            }
            else
            {
                cout << fowo.cOwOut.ConsoleQuick("r","0 or 1 ? FLAG not set") << endl;
            }
        }
        else if (USERinput.at(0) == '/')
        {
            cout << fowo.strOwOng.shOwOrthand.ColorText("r") << "unrecognized command" << fowo.strOwOng.shOwOrthand.ColorText("d") << endl;
        }
        else
        {
            POwO_vector_BinaryInsert(StringList, USERinput, false, FLAG_Debug);
        }

        cout << endl;
    }
    
}