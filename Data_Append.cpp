#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<set>

using namespace std;

int main()
{
    int n;

    fstream file1, file2, file3, file4;
    
    // Open Accounts.txt
    file1.open("Accounts.txt", ios::in | ios::app);
    if(!file1)
    {
        cout<<"Account's File opening Error!"<<endl;
        return 0;
    }
    
    // Open Pin.txt
    file2.open("Pin.txt", ios::app);
    if(!file2)
    {
        cout<<"PIN File opening Error!"<<endl;
        return 0;
    }
    
    // Open Balance.txt
    file3.open("Balance.txt", ios::app);
    if(!file3)
    {
        cout<<"Balance File opening Error!"<<endl;
        return 0;
    }
    
    // Open Name.txt
    file4.open("Name.txt", ios::app);
    if(!file4)
    {
        cout<<"Name File opening Error!"<<endl;
        return 0;
    }

    // Read existing account numbers into a set
    set<string> existing_accounts;
    string temp_account;
    while (file1>>temp_account)
    {
        existing_accounts.insert(temp_account);
    }
    file1.close();

    cout<<"How many Accounts do you want to add? ";
    cin>>n;

    vector<string> account_no(n);
    vector<string> PIN(n);
    vector<string> Balance(n);
    vector<string> Name(n);

    // Reopen Accounts.txt for appending new data
    file1.open("Accounts.txt", ios::app);

    for(int i = 0; i < n; ++i)
    {
        while(true) 
        {
            cout<<"Enter Account Number "<<i + 1<<": ";
            cin>>account_no[i];
            if(existing_accounts.find(account_no[i]) != existing_accounts.end())
            {
                cout<<"Account number already exists! Please enter a different account number."<<endl;
            }
            else
            {
                existing_accounts.insert(account_no[i]);
                file1<<account_no[i]<<"\n";
                break;
            }
        }
    }

    for(int i = 0; i < n; ++i)
    {
        cout<<"Enter Pin "<<i + 1<<": ";
        cin>>PIN[i];
        file2<<PIN[i]<<"\n";
    }

    for(int i = 0; i < n; ++i)
    {
        cout<<"Enter Balance "<<i + 1<<": ";
        cin>>Balance[i];
        file3<<Balance[i]<<"\n";
    }

    for(int i = 0; i < n; ++i)
    {
        cout<<"Enter Name "<<i + 1<<": ";
        cin>>Name[i];
        file4<<Name[i]<<"\n";
    }

    file1.close();
    file2.close();
    file3.close();
    file4.close();

    return 0;
}
