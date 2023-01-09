//*****************************************************************************************
//Universitatea TRANSILVANIA din Brasov: Facultatea de Inginerie Electrica si Stiinta Calculatoarelor
//Specializare: Inginerie electronica, telecomunicatii si tehnologii informationale
//CONTRIBUITORI:
//Andreea Negru, ETTI, anul I, grupa III
//Catalin Daniel Bradac, ETTI, anul I, grupa I
//Alexandra Andra Berbece, ETTI, anul I, grupa I
//*****************************************************************************************



//***************************************************************
//               Fisierul Header utilizat in proiect
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//***************************************************************
//               Clasele utilizate in proiect
//****************************************************************


class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//functie care preia datele de la utilizator
	void show_account() const;	//functie care afiseaza datele pe ecran
	void modify();	//functie pentru adaugarea de date noi
	void dep(int);	//functie pentru a accepta suma si adaugarea sa la balanta
	void draw(int);	//functie pentru a accepta suma si substragerea sa din balanta principala
	void report() const;	//functie de aranjarea datelor in format tabel
	int retacno() const;	//functie de afisare a numarului de cont
	int retdeposit() const;	//functie de afisare a balantei
	char rettype() const;	//functie de afisare a tipului de cont
};         //clasele se termina aici

void account::create_account()
{
	cout<<"\nIntrodu numarul contului :";
	cin>>acno;
	cout<<"\n\nIntrodu numele detinatorului contului : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nIntrodu tipul contului (C/E) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nIntrodu suma initiala (>=500 pentru Economii >=1000 pentru Cont Curent ) : ";
	cin>>deposit;
	cout<<"\n\n\nCont creat cu succes!";
}

void account::show_account() const
{
	cout<<"\nNumarul de cont : "<<acno;
	cout<<"\nDetinator cont : ";
	cout<<name;
	cout<<"\nTipul contului : "<<type;
	cout<<"\nBalanta contului : "<<deposit;
}


void account::modify()
{
	cout<<"\nNumarul de cont : "<<acno;
	cout<<"\nModifica numele detinatorului de cont : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModifica tipul de cont : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModifica balanta contului : ";
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


//***************************************************************
//    	   Declararea functiilor
//****************************************************************
void write_account();	//functie care scrie datele de la tastatura in fisierul binar
void display_sp(int);	//functie de afisare a detaliilor contului unui utilizator
void modify_account(int);	//functie de modificarea datelor din fisier
void delete_account(int);	//functie de stergere a datelor din fisier
void display_all();		//functie de afisare a tuturor detaliilor unui cont
void deposit_withdraw(int, int); //functie de adaugare/retragere a banilor dintr-un anumit cont
void intro();	//functie a ecranului introductiv

//***************************************************************
//    	 Functiile principale alea programului
//****************************************************************


int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMENIU PRINCIPAL";
		cout<<"\n\n\t01. CREAZA CONT NOU";
		cout<<"\n\n\t02. DEPUNE BANI";
		cout<<"\n\n\t03. RETRAGE BANI";
		cout<<"\n\n\t04. INTEROGHEAZA BALANTA";
		cout<<"\n\n\t05. CONTURILE DISPONIBILE";
		cout<<"\n\n\t06. INCHIDE CONT";
		cout<<"\n\n\t07. MODIFICA CONT";
		cout<<"\n\n\t08. IESIRE";
		cout<<"\n\n\tSelecteaza optiunea dorita (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tIntrodu numarul contului : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tIntrodu numarul contului : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tIntrodu numarul contului : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tIntrodu numarul contului : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tIntrodu numarul contului : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tMultumim pentru utlizarea dBank!";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


//***************************************************************
//    	Functie pentru scrierea in fisier
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fisierul nu poate fi deschis !! Apasa orice tasta...";
		return;
	}
	cout<<"\nDETALII BALANTA\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nNumarul contului nu exista";
}


//***************************************************************
//    	Functie de modificarea datelor din fisier
//****************************************************************

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Fisierul nu poate fi deschis !! Apasa orice tasta...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nIntrodu noile detalii ale contului"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Informatii actualizate";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Informatiile nu au putut fi gasite ";
}

//***************************************************************
//    	Functie de a sterge datele din fisier
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fisierul nu poate fi deschis !! Apasa orice tasta...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tInformatiile au fost sterse..";
}

//***************************************************************
//    Functie de afisare a informatiilor tuturor conturilor
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Fisierul nu poate fi deschis !! Apasa orice tasta...";
		return;
	}
	cout<<"\n\n\t\tLISTA CONTURILOR DISPONIBILE\n\n";
	cout<<"====================================================\n";
	cout<<"Numar Cont      NUME                Tip  Balanta    \n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	Functie de depunere si retragere a sumei
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Fisierul nu poate fi deschis !! Apasa orice tasta...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tDEPUNEREA SUMEI ";
				cout<<"\n\nIntrodu suma depusa: ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tRETRAGEREA SUMEI ";
				cout<<"\n\nIntrodu suma de retragere: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Fonduri Insuficiente";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Informatii Actualizate";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Informatiile nu au putut fi gasite ";
}


//***************************************************************
//    	      Functia de introducere a programului
//****************************************************************


void intro()
{
	cout<<"\n\n\n\t  dbanK";
	cout<<"\n\n\tBine ati venit!";
	cout<<"\n\n\t  Sistemul de management dbanK";
	cout<<"\n\n\n\nCreat de: Andreea Negru, Catalin Daniel Bradac si Alexandra Andra Berbece";
	cout<<"\n\nUniversitatea TRANSILVANIA din Brasov: Facultatea de Inginerie Electrica si Stiinta Calculatoarelor";
	cin.get();
}

//***************************************************************
//    			    Sfarsitul Proiectului
//***************************************************************
