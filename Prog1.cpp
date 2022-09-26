#include <iostream>
#include <fstream>
#include "timer.h" 
#include "myList.h"
#include "node.h"


using namespace std;
using std::cout;

//functions
string cleanWord(string wordD);
int skipped = 0;


myList<string> dictionaryList;
myList<string> bookList;


int main()
{

    Timer tim;
    
 
    //reading the dictionary
    int dictionarySize = 0;
    string tmp;
    ifstream dictFile;
    dictFile.open("dict.txt");
    
    while(dictFile >> tmp)
    {
        tmp = cleanWord(tmp);
        dictionaryList.insert(tmp);
        dictionarySize++;
    }
    



    
    //starting the time
    tim.Start();
    

    
    //reading the book file and comparing to the dictionary
    string btmp;
    ifstream bookFile;

    bookFile.open("book.txt");
    int misspelled = 0;
    int matchNum = 0;
    int comp;
    double long matchComp = 0;
    double long missComp = 0; 
    double long tempComp = 0;

    while(bookFile >> btmp) 
    {
        btmp = cleanWord(btmp);
        if(!isalpha(btmp[0]))
        {
            skipped++;
        }
        else if(!isblank(btmp[0]))
        {
            skipped++;
        }
        else
        {
            comp = dictionaryList.find(btmp, tempComp);
            if(comp == 1)
            {
                matchNum++;
                matchComp += tempComp;
            }
            else if(comp != 1)
            {
                missComp += tempComp;
                misspelled++;
                bookList.insert(btmp);
            }
            tempComp = 0;
        }

    }

    tim.Stop();

    cout << "dictionary Size: " << dictionarySize << "\n";
    cout << "Done checking and these are the results \n";
    cout << " Finished in time: " << tim.Time() << "\n";
    cout << " There are: " << matchNum << " words found in the dictionary\n";
    cout << matchComp  << " compares. Average : " << matchComp/matchNum << "\n";
    cout << "There are " << misspelled << "words NOT found in the dictionary\n"; 
    cout << missComp  << " compares. Average: " << missComp/misspelled << "\n";
    cout << "There are " << skipped << " words not checked.";
    
    
    
    
    //writing to the misspelled file
    string tempMiss;
    ofstream missFile;
    missFile.open("misspelled.txt");
    int tracker = 0;
    
    while(!bookList.isEmpty())
    {
        tracker++;
        tempMiss = bookList.frontMod();
        missFile << tempMiss << "\n";
    }
    
    missFile.close();
    
    dictionaryList.~myList();
    bookList.~myList();
    

}

string cleanWord(string word)
{
    string cleanW = "";
    for(int i =0; i< word.size(); i++)
    {
        if(isupper(word[i]))
        {
            word[i] = tolower(word[i]);
        }
        if(isalnum(word[i]))
        {
            cleanW = cleanW + word[i];
        }
        else if(word[i] == '\'')
        {
            cleanW = cleanW + word[i];
        }
    }
    
    //return word;
    return cleanW;
};

