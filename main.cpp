//Name: Tanner Tracy
//Assignment: Homework 1
//Class: Hoenigman - CSCI 2270

//includes and namespace declaration
#include <iostream>
#include <fstream>
using namespace std;

//definition of struct
struct item
{
    bool status;
    int price;
    string type;
    bool sold;
};


int main(int argc, const char * argv[])
{
    //variable declaration
    const int arraysize = 100;
    
    string line;
    int soldarraycount = 0;
    int itemarraycount = 0;
    int soldindex = 0;
    int count = 0;
    
    item itemarray[arraysize];
    item soldarray[arraysize];
    
    //opening file
    ifstream infile;
    infile.open(argv[1]);
    
    //check if the file properly opens
    if (infile.is_open())
    {
        //read in the lines from the data
        for(int i=0;getline(infile, line); i++)
        {
            item temp;
            count++; //add 1 to count for each time a line is read in
            
            //split the line into two strings in order to read in three data types
            int index = line.find(',');
            string splitstring = line.substr(index+2, 100);
            int index2 = splitstring.find(',');
            
            
            string itemtype = line.substr(0,index);
            string itemstatus = splitstring.substr(0,index2);
            string itemprice = splitstring.substr(index2+2, 100);
            
            //declare the item types for the current line
            temp.type = itemtype;
            if (itemstatus == "wanted")
            {
                temp.status = 0;
            }
            else if (itemstatus == "for sale")
            {
                temp.status = 1;
            }
            temp.price = stoi(itemprice);
            temp.sold = 0;
            
            //search the array for a match with the current item
            for (int j=0; j<itemarraycount ; j++)
            {
                count++; //add one count for each time it searches the array
                if (temp.status)
                {
                    if (temp.type == itemarray[j].type)
                    {
                        if (temp.status != itemarray[j].status)
                        {
                            if ( itemarray[j].price >= temp.price)
                            {
                                if (!temp.sold)
                                {
                                    temp.sold = 1;
                                    soldindex = j;
                                    count++; //add one count for each time it shifts the array
                                }
                            }
                        }
                    }
                }
                
                else
                {
                    if (temp.type == itemarray[j].type)
                    {
                        if (temp.status != itemarray[j].status)
                        {
                            if ( itemarray[j].price <= temp.price)
                            {
                                if (!temp.sold)
                                {
                                    temp.sold = 1;
                                    soldindex = j;
                                    count++; //add one count for each time it shifts the array
                                }
                            }
                        }
                    }
                    
                }
            }
            
            //if the item is declared as sold, add it too the soldarray, remove the other sold item from the itemarray, and shift the itemarray based on the removed item.
            if (temp.sold)
            {
                if (temp.status)
                {
                    soldarray[soldarraycount] = temp;
                }
                else
                {
                    soldarray[soldarraycount] = itemarray[soldindex];
                }
                soldarraycount++;
                itemarraycount = itemarraycount - 1;
                for (int j=0; j<i; j++)
                {
                    if (j > soldindex)
                    {
                        
                        itemarray[j-1] = itemarray[j];
                    }
                    
                }
            }
            //else add the item to the itemarray
            else
            {
                itemarray[itemarraycount] = temp;
                itemarraycount++;
            }
        }
    }
    
    //output
    for (int i=0; i<soldarraycount; i++)
    {
        cout << soldarray[i].type << ' ' << soldarray[i].price << endl;
    }
    
    cout << '#' << endl;
    
    for (int i=0; i<itemarraycount; i++)
    {
        if (itemarray[i].status)
        {
            cout << itemarray[i].type << ", for sale, " << itemarray[i].price << endl;
        }
        else
        {
            cout << itemarray[i].type << ", wanted, " << itemarray[i].price << endl;
        }
    }
    
    cout << '#' << endl;
    cout << "operations:" << count << endl;
    return 0;
}