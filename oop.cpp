/*
Index Number : CODSE202F-001
Name         : K. H. P. SENALANKARA

Program Name : Bank Management System
*/

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

class Bank_Account
{
protected:

    string account_number,first_name,last_name,user_name,password,account_type,balance,amount;
    int bbalance;

    int convert(string data)
    {
        int num;
        num = stoi(data); //converting string type variable to integer type variable
        return num;

        /*
        This function is used to convert string type variable to integer type and return int type variable to calling statement
        */
    }

    void Get_User_Data()
    {
        cout<<"ENTER ACCOUNT NUMBER >> ";cin>>account_number;
        cout<<"ENTER FIRST NAME     >> ";cin>>first_name;
        cout<<"ENTER LAST NAME      >> ";cin>>last_name;
        cout<<"ENTER USER NAME      >> ";cin>>user_name;
        cout<<"ENTER PASSWORD       >> ";cin>>password;
        cout<<"AMOUNT               >> RS.";cin>>amount;

        /*
        This function is used to get user data when creating a new bank account
        */
    }

    void ac_store()
    {
        fstream user_file,users;
        users.open("user_details.csv",ios::app);
        if(users.is_open())
        {
            users<<user_name<<","<<password<<"\n";
            users.close();
        }

        else
        {
            users.close();
            users.open("user_details.csv",ios::out);
            users<<user_name<<","<<password<<"\n";
            users.close();
        }
        user_file.open(user_name+".csv",ios::out);
        user_file<<account_number<<","<<first_name<<","<<last_name<<","<<user_name<<","<<password<<","<<account_type<<","<<amount;
        user_file.close();
        user_file.open(user_name+"Transactions.csv",ios::out); //creating transactions file
        user_file.close();
        system("cls");
        cout<<endl<<setw(35) <<"ACCOUNT CREATED SUCCESSFULLY !!"<<endl<<endl;

        /*
        This function used to store user entered data in to a file.
        If "user_details.csv" is present in the location of this c++ file, It will open and write if not it will create a new file called user_details.csv

        This function also create a new file for a single user.
        Name of the file = User Name of user + ".csv" file type
        */
    }

    string login()
    {
        string uuser_name,ppassword;
        int fail;
        cout<<"ENTER YOUR USER NAME >> ";cin>>uuser_name;
        cout<<"ENTER YOUR PASSWORD >> ";cin>>ppassword;
        system("cls");

        fstream get_data;
        get_data.open("user_details.csv",ios::in);
        string uname,passw;
        while(get_data.good())
        {
            getline(get_data,uname,',');
            getline(get_data,passw,'\n');
            if(uuser_name == uname)
            {
                if(ppassword == passw)
                {
                    cout<<endl<<"NOTIFICATION: SUCCESSFULLY LOGIN !!"<<endl;
                    return uuser_name;
                    break;
                }
                else
                {
                    cout<<endl<<"PASSWORD NOT WORKING !!"<<endl;
                    break;
                }
            }
            else
            {
                fail = 1;
            }
        }
        if(fail == 1)
        {
            system("cls");
            cout<<endl<<"NOTIFICATION: USER NAME NOT FOUND !!"<<endl;
            return "LOGIN FAIL";
        }
        get_data.close();

        /*
        This function is used to login to already created bank account,
        This function will return user name of user to calling statement
        */
    }

    string show_details(string user_name,float interest_rate)
    {
        fstream get_file_data;
        get_file_data.open(user_name+".csv",ios::in);
        if(get_file_data.is_open())
        {
            getline(get_file_data,account_number,',');
            getline(get_file_data,first_name,',');
            getline(get_file_data,last_name,',');
            getline(get_file_data,user_name,',');
            getline(get_file_data,password,',');
            getline(get_file_data,account_type,',');
            getline(get_file_data,amount);

            int bbalance = convert(amount);
            bbalance = (bbalance * interest_rate/100) + bbalance;

            cout<<endl<<endl<<setw(60)<<"-- Your Account Details ---"<<endl<<endl;
            cout<<"\t"<<"-----------------------------------------------------------------------------------------------"<<endl<<endl;
            cout<<setw(50) <<"ACCOUNT NUMBER    : "<<account_number<<endl;
            cout<<setw(50) <<"ACCOUNT TYPE      : "<<account_type<<endl;
            cout<<setw(50) <<"ACCOUNT USER NAME : "<<user_name<<endl;
            cout<<setw(50) <<"USER FULL NAME    : MR."<<first_name<<" "<<last_name<<endl<<endl;
            cout<<setw(50) <<"ACCOUNT BALANCE   : RS."<<convert(amount)<<endl;
            cout<<setw(50) <<"INTEREST RATE     :"<<interest_rate<<"%"<<endl<<endl;
            cout<<"\t"<<"-----------------------------------------------------------------------------------------------"<<endl;
            cout<<setw(60) <<"NEXT MONTH BALANCE WILL BE (INTEREST RATE : "<<interest_rate<<"%): "<<(bbalance)<<endl;
            cout<<"\t"<<"-----------------------------------------------------------------------------------------------"<<endl;

            get_file_data.close();

            return Account_Fuctions(user_name); //Account Functions + user want to logout from user's account?
        }
        else
        {
            system("cls");
            cout<<"USER NAME NOT FOUND !!"<<endl<<endl<<"MAKE SURE TO CREATE A NEW ACCOUNT FIRST !! "<<endl<<endl<<"OR"<<endl<<endl<<"TRY AGAIN WITH A DIFFERENT USER NAME !!"<<endl<<endl;
        }

        /*
        This function used to show user details. Read From User's File
        This function also call -> Account_Fuctions | also return Account_Fuctions to calling statement
        */
    }

    string Account_Fuctions(string use_name)
    {
        string acc_functions[6] = {"EDIT ACCOUNT DETAILS","ADD MONEY","WITHDRAW MONEY","VIEW TRANSACTIONS","DELETE BANK ACCOUNT","LOGOUT"};
        int acc;
        for(acc = 0;acc<6;acc++)
        {
            cout<<endl<<setw(25)<<"("<<(acc+1)<<") "<<acc_functions[acc];
        }

        cout<<endl<<endl<<"ENTER A NUMBER >> ";cin>>acc;
        if(acc == 1)
        {
            edit_account_details(use_name);
            return "Refresh";
        }

        else if (acc == 2)
        {
            string money_status;
            money_status = edit_account_details(use_name,"Add Money");
            return money_status;
        }

        else if (acc == 3)
        {
            string balance;
            balance = edit_account_details(use_name,"Withdraw Money");
            return balance; // data about account
        }
        else if(acc == 4)
        {
            string view;
            view = Show_All_Transactions(use_name);
            return view;
        }
        else if (acc == 5)
        {
            string del;
            del = delete_bank_account(use_name);
            return del;
        }
        else if (acc == 6)
        {
            system("cls");
            cout<<"LOGOUT SUCCESSFULLY"<<endl;
            return "Logout"; //returning "Logout" string to calling statement | user want to logout from this account
        }
        else
        {
            cout<<"SOME THING WENT WRONG";
        }

        /*
        Showing Available functions like ["Edit Account Details","Add Money","Withdraw Money","Logout"]
        return "Logout" to calling statement if user want to logout from this account

        1->edit account details
        2->add money
        3->withdraw money
        4->logout
        */
    }

    void edit_account_details(string uuser_name)
    {
        string new_first_name,new_last_name,new_balance;char user_choise;
        fstream edit_acc,c_ac;

        edit_acc.open(uuser_name+".csv",ios::in);

        if(edit_acc.is_open())
        {
            while(edit_acc.good())
            {
                getline(edit_acc,account_number,',');
                getline(edit_acc,first_name,',');
                getline(edit_acc,last_name,',');
                getline(edit_acc,user_name,',');
                getline(edit_acc,password,',');
                getline(edit_acc,account_type,',');
                getline(edit_acc,amount);

                new_first_name = first_name;new_last_name = last_name;new_balance = amount;
                edit_acc.close();
            }
        int no;
        cout<<endl<<setw(60)<<"ONLY FIRST NAME, LAST NAME, BALANCE EDITABLE !!!"<<endl<<endl;
        cout<<"\t"<<"[1] - FIRST NAME"<<endl;
        cout<<"\t"<<"[2] - LAST NAME"<<endl;
        cout<<"\t"<<"[3] - BALANCE NAME"<<endl<<endl;
        cout<<"SELECT AN NUMBER YOU WANT TO EDIT >> ";cin>>no;

        if(no == 1)
        {
            cout<<endl<<"\t"<<"EDITING THE FIRST NAME !!"<<endl<<endl;
            cout<<"ENTER YOUR NEW FIRST NAME >> ";cin>>new_first_name;
        }

        else if(no == 2)
        {
            cout<<endl<<"\t"<<"EDITING THE LAST NAME !!"<<endl<<endl;
            cout<<"ENTER YOUR NEW LAST NAME >> ";cin>>new_last_name;
        }

        else if(no == 3)
        {
            cout<<endl<<"\t"<<"EDITING ACCOUNT BALANCE !!"<<endl<<endl;
            cout<<"ENTER YOUR NEW BALANCE AMOUNT >> ";cin>>new_balance;
        }

        cout<<endl<<endl<<"DO YOU WANT TO SAVE CHANGES? IN YOUR ACCOUNT (Y/N) >> ";cin>>user_choise;
        if(user_choise == 'y')
        {

                c_ac.open(uuser_name+".csv",ios::out);
                c_ac<<account_number<<","<<new_first_name<<","<<new_last_name<<","<<uuser_name<<","<<password<<","<<account_type<<","<<new_balance;
                c_ac.close();
                system("cls");
                cout<<endl<<"NOTIFICATION: ACCOUNT DETAILS EDITED SUCCESSFULLY !!";
        }

        else
        {
            system("cls");
            cout<<endl<<endl<<"NOTIFICATION: NO ACCOUNT DETAILS CHANGED !! ";
        }
    }
    /*
    This function is used to edit bank account details
    1->edit user's first name
    2->edit user's last name
    3->edit user's balance
    */
    }
    string edit_account_details(string uuser_name,string User_choise) // Add Money | Withdraw Money
    {
        int new_user_amount,current_account_balance,user_val;
        string cc_balance;char user_choise;
        fstream edit_acc,c_ac;
        edit_acc.open(uuser_name+".csv",ios::in);

        if(edit_acc.is_open())
        {
            while(edit_acc.good())
            {
                getline(edit_acc,account_number,',');
                getline(edit_acc,first_name,',');
                getline(edit_acc,last_name,',');
                getline(edit_acc,user_name,',');
                getline(edit_acc,password,',');
                getline(edit_acc,account_type,',');
                getline(edit_acc,amount);

                edit_acc.close();

                cc_balance = amount;
                current_account_balance = convert(cc_balance);


            }
        cout<<"ENTER >> RS.";cin>>new_user_amount;

        if(User_choise == "Add Money")
        {
            cout<<endl<<endl<<"DO YOU WANT TO ADD "<<new_user_amount<<" TO YOUR ACCOUNT ? (Y/N) >> ";cin>>user_choise;
            if(user_choise == 'y')
            {
                user_val = new_user_amount;
                new_user_amount = current_account_balance + new_user_amount;

                c_ac.open(uuser_name+".csv",ios::out);
                c_ac<<account_number<<","<<first_name<<","<<last_name<<","<<uuser_name<<","<<password<<","<<account_type<<","<<new_user_amount;
                c_ac.close();
                c_ac.open(uuser_name+"Transactions.csv",ios::app);
                c_ac<<"YOUR BANK ACCOUNT HAS CREDITED "<<user_val<<" SUCCESSFULLY"<<endl;
                c_ac.close();
                system("cls");
                cout<<endl<<"MONEY ADDED SUCCESSFULLY !!";
                return "Money Added";
            }
            else
            {
                system("cls");
                cout<<endl<<endl<<"NOTIFICATION: MONEY ADDED FAIL !!";
                c_ac.open(uuser_name+"Transactions.csv",ios::app);
                c_ac<<"YOUR BANK ACCOUNT HAS BEEN DEBITED "<<user_val<<" FAIL"<<endl;
                c_ac.close();
                return "Refresh"; //used to show account details
            }
        }
        else if(User_choise == "Withdraw Money")
        {
            cout<<endl<<endl<<"DO YOU WANT TO WITHDRAW "<<new_user_amount<<" FROM YOUR ACCOUNT ? (Y/N) >> ";cin>>user_choise;
            if(user_choise == 'y')
            {

                if(current_account_balance >= new_user_amount)
                {
                    user_val = new_user_amount;
                    new_user_amount = current_account_balance - new_user_amount;
                    c_ac.open(uuser_name+".csv",ios::out);
                    c_ac<<account_number<<","<<first_name<<","<<last_name<<","<<uuser_name<<","<<password<<","<<account_type<<","<<new_user_amount;
                    c_ac.close();
                    c_ac.open(uuser_name+"Transactions.csv",ios::app);
                    c_ac<<"YOUR BANK ACCOUNT HAS DEBITED "<<user_val<<" SUCCESSFULLY"<<endl;
                    c_ac.close();
                    system("cls");
                    cout<<endl<<"MONEY WITHDRAW SUCCESSFULLY !!";
                    return "Refresh";
                }
                else
                {
                    system("cls");
                    cout<<"NOTIFICATION: INSUFFICIENT AMOUNT IN YOUR BANK ACCOUNT !! "<<endl;
                    return "Insufficient";
                }
            }
            else
            {
                system("cls");
                cout<<endl<<endl<<"NOTIFICATION: MONEY WITHDRAW FAIL !!";

                c_ac.open(uuser_name+"Transactions.csv",ios::app);
                c_ac<<"YOUR BANK ACCOUNT HAS DEBITED "<<user_val<<" FAIL"<<endl;
                c_ac.close();
                return "Refresh"; //used to show account details
            }
        }
        else
        {
            cout<<"SOMETHING WENT WRONG !!";
        }
    }
    /*
    This function used to add money / withdraw money from bank account
    if User_choise = Add Money to bank account , This function working for adding money
    if User_choise = withdraw money from bank account, This function for withdraw money

    update in user's file
    */
    }
    string Show_All_Transactions(string user_name)
    {
        string line;
        char user_choise = 'n';
        ifstream get_trans;
        get_trans.open(user_name + "Transactions.csv");
        if(get_trans.is_open())
        {
            system("cls");
            while(get_trans.good())
            {
                getline(get_trans,line,'\n');
                cout<<line<<endl;
            }
            cout<<endl<<"EXIT (Y) >>";cin>>user_choise;
            if(user_choise == 'y')
            {
                system("cls");
                return "view";
            }
        }

        /*
        Showing All Transactions - open file (User's name + Transactions) .csv File
        */
    }
    string delete_bank_account(string user_name)
    {
        char yn;
        cout<<"DO YOU WANT TO DELETE YOUR BANK ACCOUNT? (Y / N) >> ";cin>>yn;
        if(yn == 'y')
        {
            string tuser_name,tpassword,user_entered_password;
            fstream user_data,temp,user_files;
            user_data.open("user_details.csv",ios::in);
            temp.open("user_details_temp.csv",ios::out);
            if(user_data.is_open())
            {
                cout<<endl<<"ENTER YOUR ACCOUNT PASSWORD : ";cin>>user_entered_password;
                cout<<endl<<endl;
                while(user_data.good())
                {
                    getline(user_data,tuser_name,',');
                    getline(user_data,tpassword,'\n');

                    if(user_name == tuser_name)
                    {
                        if(user_entered_password == tpassword)
                        {
                            user_files.open(user_name + ".csv" , ios::out);
                            user_files<<"THIS BANK ACCOUNT HAS BEEN DELETED !!";
                            user_files.close();
                            user_files.open(user_name + "Transactions.csv",ios::out);
                            user_files<<"NO TRANSACTION DETAILS [THIS BANK ACCOUNT HAS BEEN DELETED !!]";
                            user_files.close();

                            system("cls");
                            cout<<endl<<"\t"<<"YOUR BANK ACCOUNT "<<user_name<<" NOW HAS BEEN DELETED SUCCESSFULLY !!"<<endl;
                            cout<<"\t"<<"ALL YOUR ACCOUNT TRANSACTIONS WERE DELETED SUCCESSFULLY !!"<<endl;
                            cout<<"\t"<<"YOU ARE NOW LOGOUT FROM THE BANK ACCOUNT SUCCESSFULLY !!"<<endl<<endl;
                        }
                    }
                    else
                    {
                        temp<<tuser_name<<","<<tpassword<<"\n";
                    }
                }
                temp.close();
                user_data.close();
            }

            temp.open("user_details_temp.csv",ios::in);
            user_data.open("user_details.csv",ios::out);
            if(temp.is_open())
            {
                while(temp.good())
                {
                    getline(temp,tuser_name,',');
                    getline(temp,tpassword,'\n');

                    user_data<<tuser_name<<","<<tpassword<<"\n";
                }
                temp.close();
                user_data.close();

                temp.open("user_details_temp.csv",ios::out);
                temp<<"TEMP FILE FOR DELETING BANK ACCOUNT";
                temp.close();
                return "delete";
            }
        }
        else
        {
            system("cls");
            cout<<endl<<endl<<"NOTIFICATION: NO ACCOUNT DETAILS CHANGED !! ";
            return "Refresh";
        }

    }
};

class Savings_Account : public Bank_Account
{
private:
    float interest_rate;
    string user_name;
public:
    Savings_Account()
    {
        interest_rate = 3;
        account_type = "SAVINGS ACCOUNT";
    }
    ~Savings_Account()
    {
        cout<<"END OF EXECUTION !!";
    }
    void Create_New_User()
    {
        cout<<endl<<"|+| CREATING A NEW SAVINGS ACCOUNT !!"<<endl<<endl;
        Get_User_Data();
        ac_store();
    }
    void call_same()
    {
        show_ac_details();
    }
    string show_ac_details()
    {
        string log;
        log = show_details(user_name,interest_rate);
        if (log == "Logout")
        {
            return "Logout";
        }
        else if(log == "delete")
        {
            return "Logout";
        }
        else if (log == "Insufficient")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (log == "Refresh")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (log == "Money Added")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (log == "view")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (user_name == "LOGIN FAIL")
        {
            Login_To_Savings_Account();
            return "Logout";
        }
        call_same();
    }
    void Login_To_Savings_Account()
    {
        user_name = login();
    }
/*
This sub class is used to control savings account user's data

->create accounts
->login to savings account
->logout from savings account
->edit savings account details
->automatically set interest_rate to savings account

*/
};

class Current_Account : public Bank_Account
{
private:
    float interest_rate;
    string user_name;
public:
    Current_Account()
    {
        interest_rate = 3;
        account_type = "CURRENT ACCOUNT";
    }
    ~Current_Account()
    {
        cout<<"END OF EXECUTION !!";
    }
    void Create_New_User()
    {
        cout<<endl<<"|+| CREATING A NEW CURRENT ACCOUNT !!"<<endl<<endl;
        Get_User_Data();
        ac_store();
    }
    void call_same()
    {
        show_ac_details();
    }
    string show_ac_details()
    {
        string log;
        log = show_details(user_name,interest_rate);
        if (log == "Logout")
        {
            return "Logout";
        }
        else if(log == "delete")
        {
            return "Logout";
        }
        else if (log == "Insufficient")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (log == "Refresh")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (log == "Money Added")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (log == "view")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (user_name == "LOGIN FAIL")
        {
            Login_To_Savings_Account();
            return "Logout";
        }
        call_same();
    }
    void Login_To_Savings_Account()
    {
        user_name = login();
    }
/*
This sub class used to control current account user's data
->create accounts
->login to current account
->logout from current account
->edit current account details
->automatically set interest_rate to current account
*/
};

class Fixed_Account : public Bank_Account
{
private:
    float interest_rate;
    string user_name;
public:
    Fixed_Account()
    {
        interest_rate = 3;
        account_type = "FIXED ACCOUNT";
    }
    ~Fixed_Account()
    {
        cout<<"END OF EXECUTION !!";
    }
    void Create_New_User()
    {
        cout<<endl<<"|+| CREATING A NEW FIXED ACCOUNT !!"<<endl<<endl;
        Get_User_Data();
        ac_store();
    }
    void call_same()
    {
        show_ac_details();
    }
    string show_ac_details()
    {
        string log;
        log = show_details(user_name,interest_rate);
        if (log == "Logout")
        {
            return "Logout";
        }
        else if(log == "delete")
        {
            return "Logout";
        }
        else if (log == "Insufficient")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (log == "Refresh")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (log == "Money Added")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (log == "view")
        {
            log = show_details(user_name,interest_rate);
        }
        else if (user_name == "LOGIN FAIL")
        {
            Login_To_Savings_Account();
            return "Logout";
        }
        call_same();
    }
    void Login_To_Savings_Account()
    {
        user_name = login();
    }
/*

This sub class used to control Fixed account user's data
->create accounts
->login to fixed account
->logout from fixed account
->edit fixed account details
->automatically set interest_rate for fixed account

*/

};

int main()
{
    int number,ac_type;
    string acc_types[3] = {"SAVINGS ACCOUNT","CURRENT ACCOUNT","FIXED ACCOUNT"};

    cout<<setw(60)<< " -- BANK MANAGEMENT SYSTEM --" <<endl<<endl<<endl;
    cout<<setw(60)<< "[+] 1.CREATE A BANK ACCOUNT"<<endl;
    cout<<setw(60)<< "[+] 2.LOGIN TO BANK ACCOUNT"<<endl;
    cout<<setw(60)<< "[+] 3.EXIT                 "<<endl;
    cout<<"ENTER NUMBER >> ";cin>>number;
    system("cls");


    if(number == 1) //create a new bank account
    {
        cout<<setw(65)<<"[ CREATE A NEW BANK ACCOUNT ]"<<endl<<endl;
        cout<<setw(60)<<"------ ACCOUNT TYPES ------"<<endl<<endl;
        int x;
        for(x=0;x<3;x++)
        {
            cout<<setw(35)<<"[+] "<<x+1<<"."<<acc_types[x]<<endl;
        }
        cout<<endl<<"[CREATE] ENTER ACCOUNT TYPE >> ";cin>>ac_type;
        if(ac_type == 1)
        {
            Savings_Account x;
            x.Create_New_User();
            main();
        }
        else if (ac_type == 2)
        {
            Current_Account x;
            x.Create_New_User();
            main();
        }
        else if (ac_type == 3)
        {
            Fixed_Account x;
            x.Create_New_User();
            main();
        }
        else
        {
            cout<<"INVALID INPUT, PLEASE TRY AGAIN !!";
        }
    }
    else if(number == 2) //login
    {
        int w_ac;
        int x;
        cout<<setw(50)<<"[ --- LOGIN --- ]"<<endl<<endl;
        cout<<setw(65)<<" [ -- SELECT YOUR ACCOUNT TYPE --] "<<endl<<endl;
        for(x=0;x<3;x++)
        {
            cout<<setw(35)<<"[+] "<<x+1<<"."<<acc_types[x]<<endl;
        }

        cout<<endl<<"[LOG IN] ENTER YOUR ACCOUNT TYPE >> ";cin>>w_ac;

        if(w_ac == 1) //savings account login
        {
            string log;
            Savings_Account Acc;
            Acc.Login_To_Savings_Account();
            log = Acc.show_ac_details();

            if(log == "Logout")
            {
                main();
            }
        }
        else if(w_ac == 2) //current account login
        {
            string log;
            Current_Account Acc;
            Acc.Login_To_Savings_Account();
            log = Acc.show_ac_details();

            if(log == "Logout")
            {
                main();
            }
        }
        else if(w_ac == 3) //fixed account login
        {
            string log;
            Fixed_Account Acc;
            Acc.Login_To_Savings_Account();
            log = Acc.show_ac_details();

            if(log == "Logout")
            {
                main();
            }
        }
        else
        {
            cout<<"SOMETHING WENT WRONG !!"<<endl;
            main();
        }
    }
    else if(number == 3)
    {
        cout<<endl<<"EXIT FROM THE PROGRAM SUCCESSFULLY !!"<<endl<<endl;
        system("exit");
    }
    else
    {
        cout<<endl<<"INVALID NUMBER, PLEASE TRY AGAIN !!"<<endl<<endl;
        system("exit");
    }
    return 0;
/*
Showing Menus | Getting User Input |

Select sub class type (account type)

exit from program
*/
}
