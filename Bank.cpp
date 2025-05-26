// ATM with the folowing functionalities:
// Deposit, Withdraw, Balance Inquiry
// User has option to change his/her PIN

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<conio.h>
using namespace std;

class Bank
{
    protected:
    ifstream file1,file2,file3;
    public:

    int file_open_check()
    {
        file1.open("Accounts.txt",ios::in);
        if(!file1)
        {
            cout<<"Contact the Manufacturer (Error Code 101)"<<endl;
            return 0;
        }
        else
        {
            file2.open("PIN.txt",ios::in);
            if(!file2)
            {
                cout<<"Contact the Manufacturer (Error Code 102)"<<endl;
                return 0;
            }
            else
            {
                file3.open("Balance.txt",ios::in);
                if(!file3)
                {
                    cout<<"Contact the Manufacturer (Error Code 103)"<<endl;
                    return 0;
                }
            }
        }
        return 1;
    }

    vector<string> readFromFile(const string &filename) 
    {
        vector<string> data;
        ifstream file(filename);
        if(!file)
        {
            cout<<"Error opening "<<filename<<endl;
            return data;
        }

        string line;
        while(getline(file, line))
        {
            data.push_back(line);
        }
        file.close();
        return data;
    }

    int balance_fetch(int index)
    {
        ifstream file("Balance.txt");
        string line;
        int currentIndex = 0;

        while (getline(file, line))
        {
            if (currentIndex == index)
            {
                return stoi(line);
            }
            ++currentIndex;
        }
    }
};

class User : public Bank
{
    public:

    int user_check(string usr)
    {
        vector<string> Accounts;
        Accounts =  readFromFile("Accounts.txt");

        int length = Accounts.size();
        for(int i=0; i<length ; i++)
        {
            if(usr == Accounts[i])
            {
                return i;
            }
        }
        return -1;
    }

    string user_fetch(int user_index)
    {
        vector<string> Names;
        Names =  readFromFile("Name.txt");

        return Names[user_index];
    }

    bool pin_check(string pin, int user_index)
    {
        vector<string> Pin;
        Pin =  readFromFile("Pin.txt");

        if(pin == Pin[user_index])
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void balance_update(int index, int amount)
    {
        ifstream File("Balance.txt");
        vector<string> Data;
        string data;

        while (getline(File, data))
        {
            Data.push_back(data);
        }
        File.close();

        if (index >= 0 && index < Data.size())
        {
            Data[index] = to_string(amount);
        }

        ofstream outputFile("Balance.txt");
        for(const auto &updatedLine : Data)
        {
            outputFile<<updatedLine<<endl;
        }
    }

    int PIN_change(int index)
    {  
        vector<string> PINs;
        string currentPin, newPin1,newPin2;

        cout << "Enter your Current PIN: ";
        cin >> currentPin;

        PINs = readFromFile("Pin.txt");

        if(index >= 0 && index < PINs.size() && pin_check(currentPin, index))
        {
            while(true)
            {
                cout<<"Enter New PIN: ";
                cin>>newPin1;
                cout<<"Re-Enter New PIN: ";
                cin>>newPin2;

                if(newPin1 == newPin2)
                {
                    PINs[index] = newPin1;
                    ofstream file("Pin.txt");
                    for (const auto& pin : PINs)
                    {
                        file << pin << endl;
                    }
                    cout<<"PIN successfully changed."<<endl;
                    cout<<"\nProgram Exiting"<<endl;
                    cout<<"\t\tThank You for using our Service";
                    break;
                }
                else 
                {
                    cout<<"PINs do not match. Try again."<<endl;
                }
            }
        }
        else 
        {
            cout<<"Incorrect current PIN."<<endl;
        }
    }
};

class Functions : public Bank, public User
{
    public:

    void Interface(int index)
    {
        int choice;
        cout<<"---------- Welcome to ABD BANK ----------\n"<<endl;
        cout<<"\tEnter the desired option below\n"<<endl;
        cout<<"1. Deposit\n2. Withdrawl"<<endl;
        cout<<"3. Balance Inquiry\n4. PIN Change"<<endl;
        cout<<"\nChoice = ";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
            case 1:
            deposit(index);
            break;

            case 2:
            withdraw(index);
            break;

            case 3:
            balance_inquiry(index);
            break;

            case 4:
            PIN_change(index);
            break;
        }
    }

    int deposit(int index)
    {
        int amount;
        cout<<"Note: Amount has to be the multiple of 500"<<endl;
        cout<<"Enter the amount you want to Deposit = ";
        cin>>amount;

        if(amount%500 == 0)
        {
            int fetched_amount = User::balance_fetch(index);
            int new_amount = amount + fetched_amount;
            balance_update(index,new_amount);
        }
        else
        {
            cout<<"Error -- Amount Invalid";
            deposit(index);
        }

        char ch;
        cout<<"Do you want to Perform any other Transaction ? (y/n) = ";
        cin>>ch;
        cout<<endl;

        if(ch == 'y')
        {
            Interface(index);
        }
        else if(ch == 'n')
        {
            cout<<"\nThank You for using our Service";
            getch();
        }
    }

    int withdraw(int index)
    {
        int amount;
        cout<<"Note: Amount has to be the multiple of 500"<<endl;
        cout<<"Enter the amount you want to Withdraw = ";
        cin>>amount;

        if(amount%500 == 0)
        {
            int fetched_amount = User::balance_fetch(index);
            if(amount<fetched_amount)
            {
                int new_amount = fetched_amount - amount;
                balance_update(index,new_amount);
            }
            else
            {
                cout<<"Error -- Insufficient Balance";
                withdraw(index);
            }
        }
        else
        {
            cout<<"Error -- Amount Invalid";
            withdraw(index);
        }

        char ch;
        cout<<"Do you want to Perform any other Transaction ? (y/n) = ";
        cin>>ch;
        cout<<endl;

        if(ch == 'y')
        {
            Interface(index);
        }
        else if(ch == 'n')
        {
            cout<<"\nThank You for using our Service";
            getch();
        }
    }

    void balance_inquiry(int index)
    {
        cout<<"Your Available Balance is = "<<User::balance_fetch(index)<<endl;

        char ch;
        cout<<"Do you want to Perform any other Transaction ? (y/n) = ";
        cin>>ch;
        cout<<endl;

        if(ch == 'y')
        {
            Interface(index);
        }
        else if(ch == 'n')
        {
            cout<<"\nThank You for using our Service";
            getch();
        }
    }
};

int main()
{
    vector<string> Balance{};
    string accno;

    //Class Objects
    Bank obj;
    User usr;
    Functions fn;

    if(obj.file_open_check())
    {
        cout<<"Enter your Account Number = ";
        cin>>accno;

        int user_index = usr.user_check(accno);

        if(user_index != -1)
        {
            //Fetching User details from File
            string name = usr.user_fetch(user_index);
            cout<<"\n\tWelcome "<<name<<endl;

            //Getting PIN from User
            cout<<"Enter your PIN = ";
            string pin;
            cin>>pin;
            
            //Checking PIN size
            while(pin.size() != 4)
            {
                cout<<"Invalid PIN Size"<<endl;
                cout<<"Enter PIN: ";
                cin>>pin;
            }

            //Authenticating PIN from Database
            if(pin.size() == 4)
            {
                int attempts = 0, max_attempts = 3;

                while(attempts < max_attempts)
                {
                    if(usr.pin_check(pin,user_index) == true)
                    {
                        cout<<"PIN Authenticated\n"<<endl;
                        fn.Interface(user_index);
                        break;
                    }
                    else
                    {
                        attempts++;
                        cout<<"Error -- Invalid PIN\t(Remaining Attempts = "<<max_attempts-attempts<<" )"<<endl;
                        cout<<"Enter your PIN: ";
                        string pin;
                        cin>>pin;
                    }
                }
                if(attempts == max_attempts)
                {
                    cout<<"Max Attempts Made (Account Locked)";
                    getch();
                }
            }
        }
        else
        {
            cout<<"User not found"<<endl;
            getch();
        }
    }
    getch();
    
}