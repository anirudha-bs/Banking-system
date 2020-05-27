// C++ banking system

#include<iostream>
#include<fstream>

using namespace std;

class account
{
	int acno,pin[4];
	char name[50];
	int balance;
public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	int retacno() const;
	int retbalance() const;
  int* retpin();
};

void hashing(int *c)
{
for(int i=0;i<3;i++)
  c[i]=(c[i]*2713)%1277;
}

void account::create_account()
{
	cout<<"\nEnter The account No. : ";
	cin>>acno;
  cout<<"\nEnter the 4 digit pin number(space seperated) : ";
  for(int i=0;i<4;i++)
    cin>>pin[i];
  hashing(pin);
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The Initial amount(>=500 and >=1000) : ";
	cin>>balance;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
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
	cin.ignore();
	cin.getline(name,50);
}

void account::dep(int x)
{
	balance+=x;
}

void account::draw(int x)
{
	balance-=x;
}

int account::retacno() const
{
	return acno;
}

int account::retbalance() const
{
	return balance;
}

int* account::retpin()
{
  return pin;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void balance_withdraw(int, int);

int main()
{
	char ch;
	int ac;
	do
	{
		cout<<"\n\nMAIN MENU";
		cout<<"\n\n01. NEW ACCOUNT";
		cout<<"\n\n02. DEPOSIT AMOUNT";
		cout<<"\n\n03. WITHDRAW AMOUNT";
		cout<<"\n\n04. DISPLAY ACCOUNT DETAILS";
		cout<<"\n\n05. CLOSE AN ACCOUNT";
		cout<<"\n\n06. MODIFY AN ACCOUNT";
		cout<<"\n\n07. EXIT";
		cout<<"\n\nSelect Your Option (1-7) : ";
		cin>>ch;
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\nEnter The account No. : "; cin>>ac;
			balance_withdraw(ac, 1);
			break;
		case '3':
			cout<<"\n\nEnter The account No. : "; cin>>ac;
			balance_withdraw(ac, 2);
			break;
		case '4':
			cout<<"\n\nEnter The account No. : "; cin>>ac;
			display_sp(ac);
			break;
		case '5':
			cout<<"\n\nEnter The account No. : "; cin>>ac;
			delete_account(ac);
			break;
		 case '6':
			cout<<"\n\nEnter The account No. : "; cin>>ac;
			modify_account(ac);
			break;
		 case '7':
			cout<<"\n\nThank you for using C++ banking system ";
			break;
		 default :cout<<"Please enter a valid option ";
		}
		cin.ignore();
		cin.get();
	}while(ch!='7');
	return 0;
}

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("banking.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void display_sp(int n)
{
	account ac;
  int upin[4],*pin;
	bool flag=false;
	ifstream inFile;
	inFile.open("banking.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile could not be open !!";
		return;
	}
  cout<<"\nEnter the pin no : ";
  for(int i=0;i<4;i++)
     cin>>upin[i];
  hashing(upin);
  pin=ac.retpin();

  while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n && pin[0]==upin[0] && pin[1]==upin[1] && pin[2]==upin[2] && pin[3]==upin[3])
		{
      cout<<"\nBALANCE DETAILS\n";
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\nAccount number does not exist";
}


void modify_account(int n)
{
  int upin[4],*pin;
	bool found=false;
	account ac;
	fstream File;
	File.open("banking.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"\nFile could not be open !!";
		return;
	}
  cout<<"\nEnter the pin no : ";
  for(int i=0;i<4;i++)
    cin>>upin[i];
  hashing(upin);
  pin=ac.retpin();

	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n && pin[0]==upin[0] && pin[1]==upin[1] && pin[2]==upin[2] && pin[3]==upin[3])
		{
			ac.show_account();
			cout<<"\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n Record Not Found ";
}

void delete_account(int n)
{
	account ac;
  int upin[4],*pin;
	ifstream inFile;
	ofstream outFile;
	inFile.open("banking.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !!";
		return;
	}
  cout<<"\nEnter the pin no : ";
  for(int i=0;i<4;i++)
     cin>>upin[i];
  hashing(upin);
  pin=ac.retpin();

	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n && pin[0]==upin[0] && pin[1]==upin[1] && pin[2]==upin[2] && pin[3]==upin[3])
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("banking.dat");
	rename("Temp.dat","banking.dat");
	cout<<"\nRecord Deleted ..";
}

void balance_withdraw(int n, int option)
{
	int amt,upin[4],*pin;
	bool found=false;
	account ac;
	fstream File;
	File.open("banking.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !!";
		return;
	}
  cout<<"\nEnter the pin no : ";
  for(int i=0;i<4;i++)
     cin>>upin[i];
  hashing(upin);
  pin=ac.retpin();

	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n && pin[0]==upin[0] && pin[1]==upin[1] && pin[2]==upin[2] && pin[3]==upin[3])
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\nTO DEPOSITE AMOUNT ";
				cout<<"\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\nTO WITHDRAW AMOUNT ";
				cout<<"\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retbalance()-amt;
				if(bal<500)
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\nBalance updated";
			found=true;
	  }
  }
	File.close();
	if(found==false)
		cout<<"\nRecord Not Found ";
}
