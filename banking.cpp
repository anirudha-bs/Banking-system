#include <iostream>

using namespace std;
static int getacno=100;

void spin_hash(int *c)
{
int val=263,mod=73,i;
for(i=0;i<3;i++)
  c[i]=(c[i]*263)%73;
}

class account {
private:
  string name;
  float balance;

public:
  int acno,m,pin[3];
  void create_acc();
  void show_acc() const;
  void deposit(int);
  void withdraw(int);
  void modify();
  void hashing(int*);

};

 void account::hashing(int *c)
{
 int val=263,mod=73,i;
 for(i=0;i<3;i++)
   c[i]=(c[i]*263)%73;
}


  void account::create_acc()
{
  cout<<"\nEnter The Name of The account Holder : ";
  cin>>name;
  cout<<"\nEnter The Initial amount deposit amount for your savings account: ";
	cin>>balance;
  acno=getacno;
  cout<<"\nEnter 4 digit secret pin seperated by space - ";
  for(int i=0;i<3;i++)
      cin>>pin[i];
  hashing(pin);
  cout<<"\nAccount Created..";
  cout<<"\nYour account number is - "<<getacno++;
  cout<<"\nYour pin number is - ";
  for(int i=0;i<3;i++)
      cout<<pin[i];
}

void account::show_acc() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nBalance amount : "<<balance;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin>>name;
	cout<<"\nModify Balance amount : ";
	cin>>balance;
}


void account::deposit(int x)
{
	balance+=x;
  cout<<"\nAmount deposited =  "<<x;
  cout<<"\nCurrent balance =  "<<balance;
}

void account::withdraw(int x)
{
	balance-=x;
  cout<<"\nAmount withdraw =  "<<x;
  cout<<"\nCurrent balance =  "<<balance;
}

int main()
{
  int choice,n,accno,amt,flag=0,spin[3];
  cout<<"\n\t\t\tC++ BANK";
  cout<<"\n\nEnter the number of accounts to be created"<<endl;
  cin>>n;
  account a[n];
  for(int i=0;i<n;i++)
    a[i].create_acc();

   do
	{
    cout<<"\n\n\t\tMAIN MENU";
		cout<<"\n\t\t01. DEPOSIT AMOUNT";
		cout<<"\n\t\t02. WITHDRAW AMOUNT";
		cout<<"\n\t\t03. BALANCE ENQUIRY";
		cout<<"\n\t\t04. MODIFY AN ACCOUNT";
		cout<<"\n\t\t05. EXIT";
		cout<<"\n\t\tSelect Your Option (1-5) : ";
		cin>>choice;
    if(choice==5)
      goto ex;

    cout<<"\n\nEnter your account number - ";
    cin>>accno;
    cout<<"\nEnter your secret pin - ";
    for(int i=0;i<3;i++)
        cin>>spin[i];
    spin_hash(spin);
    cout<<spin;
    for(int i=0;i<n;i++)
    {
       if((a[i].acno==accno)&&(a[i].pin[i]!=spin[i]))
         flag=-1;
    }

    if(flag==-1)
   {
      cout<<"\nAccount number or pin is wrong";
      continue;
    }

    switch(choice)
		{
		case 1:
      cout<<"\nEnter the amount to be deposited";
      cin>>amt;
			a[accno-100].deposit(amt);
			break;

    case 2:
      cout<<"\nEnter the amount to be withdrawn";
      cin>>amt;
      a[accno-100].withdraw(amt);
      break;

  	case 3:
			a[accno-100].show_acc();
			break;

    case 4:
				a[accno-100].modify();
		  	break;

ex: case 5:
			cout<<"\nThank you for using C++ bank";
			break;

    default :cout<<"\nPlease enter a valid option";
		}

 }while(choice!=5);

  return 0;
}
