#include<fstream.h>
#include<stdio.h>
#include<string.h>               //Header files
#include<conio.h>
#include<stdlib.h>
#include<process.h>
class admin
 {
  char password[40];

  public: admin()
			  {strcpy(password,"qwerty");}
			 int count()
			  {return strlen(password);}
			 int check_pass(char pass[])
			  {
				if(strcmp(password,pass)==0)
				  return 1;
				else return 0;
           }

 };
class vlib
{
 int movie_code;
 char movie_title[20];
 char director[20];
 char actor[10];
 char actress[10];
 float prices;
 int no_of_copies;
 int no_issued;

 public:
		  vlib()
		  {
			no_issued=0;           //Constructor
		  }
		  void assign();
		  void input_for_modification();
		  void issue(char m_name[20]);
		  void rent_cd(char m_name[60]);
		  char* get_moviename()
		  {
			return movie_title;      //Function to return Movie Title
		  }
		  int get_code()
		  {
			return movie_code;     //Function to return Movie Code
		  }
		  void display_det();
		  void display_list();
		  void disp_full_det();
};
void vlib::assign()
{
 cout<<"Enter the movie code:\n";
  cin>>movie_code;
 cout<<"Enter the movie name:\n";
  gets(movie_title);
 cout<<"Enter the director:\n";
  gets(director);
 cout<<"Enter the actor:\n";         //Function to Enter the details of a movie
  gets(actor);
 cout<<"Enter the actress:\n";
  gets(actress);
 cout<<"Enter the no.of copies available:\n";
  cin>>no_of_copies;
 cout<<"Enter the no.of copies issued:\n";
  cin>>no_issued;
}


void vlib::input_for_modification()
{
 cout<<"Enter the movie code:\n";
  cin>>movie_code;
 cout<<"Enter the movie name:\n";
  gets(movie_title);
 cout<<"Enter the director:\n";      //Function to Modify the various details
  gets(director);
 cout<<"Enter the actor:\n";
  gets(actor);
 cout<<"Enter the actress:\n";
  gets(actress);
}


void vlib::issue(char m_name[60])
{
 char ch;
 do
 {
  cout<<"Enter the no.of DVD's of "<<m_name<<" you want to issue:\n";
	cin>>no_issued;

	  if((no_of_copies)>=(no_issued))
	  {
		no_of_copies-=no_issued;
		 cout<<no_issued<<"DVDs";
		if(no_issued>1)
		 cout<<" 's has been issued \n";   //Function to issue the DVD's
		break;
	 }
	 else
	 {
	  cout<<" Sorry!!Not enough DVD's available\n";
	  cout<<" Do you want to issue less DVD's ???";
	  cin>>ch;
	}
 }
 while((ch=='y')||(ch=='Y'));
}


void vlib::rent_cd(char m_name[60])
{
	int num;
	cout<<"\n Enter the no.f DVD's of "<<m_name<<" you want to return :\n";
	cin>>num;

	no_of_copies+=num;
	no_issued-=num;
	cout<<endl<<num<<"DVD";
													 //Function to return the DVS's
	if(num>1)
	 cout<<" 's have been returned \n";
	else
	 cout<<"  has been returned \n";
}


void vlib::display_det()
{
	cout<<"\nMovie code : "<<movie_code<<endl;
	cout<<"Movie name : ";
	puts(movie_title);
	cout<<"Movie director : ";
	puts(director);           //Function to display the details of the movie
	cout<<"Movie actor : ";
	puts(actor);
	cout<<"Movie actress : ";
	puts(actress);
	cout<<endl;

}
void vlib::display_list()
{
	cout<<endl;
	cout<<"MOVIE CODE   :"<<movie_code<<endl;
	cout<<"MOVIE TITLE  :"<<movie_title; //Function to display the list of movies

}
void vlib::disp_full_det()
{
	cout<<"\n The movie code : "<<movie_code<<endl;
	cout<<"Movie title : ";
	puts(movie_title);
	cout<<"The director of movie : ";
	puts(director);
	cout<<"The actor of movie : ";
	puts(actor);                 //Function to display the complete details of the movie
	cout<<"The actress of movie : ";
	puts(actress);
	cout<<"The no.of copies available : "<<no_of_copies<<endl;
	cout<<"The no.of copies issued : "<<no_issued<<endl<<endl;
}


void createfile()
{
	ofstream fout("vlib.dat",ios::binary);
	vlib v;
	char ch;
	do
	{
		cout<<"Enter your record \n\n";
		v.assign();                         //create movie record
		fout.write((char*)&v,sizeof(v));
		cout<<"Do you want to enter more \n";
		cin>>ch;
		cout<<endl;
	}
	while((ch=='y')||(ch=='Y'));
	fout.close();

}
void display_full_det()
{
	ifstream fin("vlib.dat",ios::binary);
	vlib v;
	fin.read((char*)&v,sizeof(v));
	while(fin)
	{                                    //Function to display the full details
		v.disp_full_det();
		fin.read((char*)&v,sizeof(v));

	}
	fin.close();
}


void append()
{
	ofstream fout("vlib.dat",ios::binary|ios::app);
	vlib v;
	char ch;
	do
	{
		cout<<"Enter the movie record :\n";
		v.assign();
		fout.write((char*)&v,sizeof(v));    //Function to append a new record
		cout<<"Do you want to continue ??";
		cin>>ch;
	}
	while((ch=='y')||(ch=='Y'));
	fout.close();
}


void insertion()
{
	fstream file1,file2;
	vlib v,vnew;
	file1.open("vlib.dat",ios::binary|ios::in);
	file2.open("vlibnew.dat",ios::binary|ios::out);

	cout<<"Insert the movie record :\n\n";
	vnew.assign();

	int insert=0;
	file1.read((char*)&v,sizeof(v));
	while(file1)                      //Function to insert a new record
	{
		if(vnew.get_code()<v.get_code()&& (!insert))
		{
			 file2.write((char*)&vnew,sizeof(vnew));
			 insert++;
		}
		file2.write((char*)&v,sizeof(v));
		file1.read((char*)&v,sizeof(v));
	}
		if(!insert)
		file2.write((char*)&vnew,sizeof(vnew));
		file1.close();
		file2.close();

		remove("vlib.dat");
		rename("vlibnew.dat","vlib.dat");
}

void deletion()
{
 fstream file1,file2;
 vlib v;
 int code;
 cout<<"\nEnter the movie code whose record you want to delete:";
 cin>>code;


 file1.open("vlib.dat",ios::binary|ios::in);
 file2.open("vlibnew.dat",ios::binary|ios::out);
 int del=0;
 while(file1.read((char*)&v,sizeof(v)))
 {
  if(v.get_code()!=code)              //Function to delete a record
	file2.write((char*)&v,sizeof(v));
  else
	del++;
  }
  if(!del)
  cout<<"Movie record not found\n";
  else
  cout<<"\nMovie record deleted\n";

  file1.close();
  file2.close();

  remove("vlib.dat");
  rename("vlibnew.dat","vlib.dat");
  }


  void modify()
  {
	 fstream file("vlib.dat",ios::in|ios::out|ios::binary);
	 vlib v;
	 int code;
	 cout<<"Enter the movie code to be modified\n";
	 cin>>code;

	 int found=0;
	 long pos=sizeof(vlib);

	 file.read((char*)&v,sizeof(v));

	 while(file &&(!found))
	  {
		  if(v.get_code()==code)
		  {
			 found ++;                  //Function to Modify the details
			 cout<<"New Record\n";
			 v.input_for_modification();
			 file.seekp(-pos,ios::cur);
			 file.write((char*)&v,sizeof(v));
			 break;
			 }
			 file.read((char*)&v,sizeof(v));
	  }
	  if(!found)
		cout<<"Movie record not found for editing\n";
	  file.close();
	  }


	  void display_records()
	  {ifstream fin("vlib.dat",ios::binary);
	  vlib v;
	  fin.read((char*)&v,sizeof(v));
	  while(fin)
	  {                             //Function to display the records
	  v.display_det();
	  fin.read((char*)&v,sizeof(v));
	  }
	  fin.close();
	  }


	 void display_list()
	 {
		ifstream fin("vlib.dat",ios::binary);
		vlib v;
		 fin.read((char*)&v,sizeof(v));
		 while(fin)
		{                             //Function to display the list
		 v.display_list();
		 fin.read((char*)&v,sizeof(v));
		 }
		 fin.close();
	 }

 void issue_cd()
		{
		fstream file("vlib.dat",ios::in|ios::out|ios::binary);
		vlib v;
		int code;
		cout<<"\nEnter the movie code you want to rent\n";
		cin>>code;

		int found=0;
		char m_name[60];
		long pos=sizeof(vlib);
		file.read((char*)&v,sizeof(v));
		while(file&&!found)
		 {
		 if(v.get_code()==code)         //Function to issue a dvd
		  {
			  found ++;
			  strcpy(m_name,v.get_moviename());
			  v.issue(m_name);
			  file.seekp(-pos,ios::cur);
			  file.write((char*)&v,sizeof(v));
			  break;
			  }
			  file.read((char*)&v,sizeof(v));
		  }

		 if(found==0)
		 cout<<"Wrong code entered\n";
		 file.close();
		 }


void return_cd()
{
fstream file("vlib.dat",ios::in|ios::out|ios::binary);
vlib v;
int code;
cout<<"\nEnter the movie code that you want to return\n";
cin>>code;
int found=0;
char m_name[60];
long pos=sizeof(vlib);
file.read((char*)&v,sizeof(v));
while(file&&!found)
{
  if(v.get_code()==code)
	 {                                 //Function to return a DVD
	  found++;
	  strcpy(m_name,v.get_moviename());

	  v.rent_cd(m_name);
	  file.seekp(-pos,ios::cur);
	  file.write((char*)&v,sizeof(v));
	  break;
	  }
	  file.read((char*)&v,sizeof(v));
	  }
	  if(found==0)
	  cout<<"Wrong Code\n";
	  file.close();
	  }

  int admin_login()
	{
	 char pass[6];
	 int i=0;char ch;
	 admin a;
	 ifstream fin("Administrator.dat",ios::binary);
	 fin.read((char*)&a, sizeof(a));
	 fin.close();
	 cout<<"\n\nPlease Enter The Six Digit Password\n\n";
	 do
	  {
		ch=getch();
		if(ch=='\b')
		 {
		  if(i!=0)
			{
			 i--;
			 cout<<"\b";
			}
		 }
		else
		 {
		  pass[i++]=ch;
		  cout<<"*";
		 }
	  }while(i!=a.count());
	 pass[i]='\0';
	 if(a.check_pass(pass)==1)
		{cout<<"\n\nWELCOME\n\n";
		 return 1;                  //Function for entering a password
		}
	 else
		{cout<<"\n\nWRONG PASSWORD!!\n\n";
		 return 0;
      }
  }
  void main()
  {
	 {
	  admin a;
	  ofstream fout("Administrator.dat",ios::binary);
	  fout.write((char*)&a, sizeof(a));
	  fout.close();
	 }
		int c,c1,c2;
		char a,b,d;
	  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	 cout<<"*******************JUST ADDD POPCORN*****************************\n";
	 cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	 cout<<"\nBuy the latest DVDs & intoxicate yourself into the majestic world of Movies \n";
	 cout<<"                                     && Ofcourse,JUST ADDD POPCORN TO IT!!!!!!\n\n\n\n";



	 do
	  {
		cout<<"\n1:If you are a Customer,Please Press 1\n";
		cout<<"2:If you are the Admin, Please Press 2\n";
		cout<<"3:If you want to View the Contact Card,Please Press 3\n";
		cout<<"4:If you want to Exit,Please Press 4\n";
		cin>>c;


		switch(c)
		{
		 case 1: do
					 {
					 cout<<"\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
					 cout<<"\n############CUSTOMER MENU#############\n";
					 cout<<"1.View the list of Movie DVDs\n";
					 cout<<"2.View the list of movie DVDs with all the details\n";
					 cout<<"3.Rent a movie DVD\n";
					 cout<<"4.Return a movie DVD\n";
					 cout<<"5.Exit from menu\n";
					 cin>>c1;
		 switch(c1)
		 {
		  case 1:cout<<"    MOVIE LIST    \n";
					display_list();
					break;
		  case 2:cout<<"    MOVIE DETAILS   \n";
					display_records();
					break;
		  case 3:display_list();
					 issue_cd();
					 break;
		  case 4: display_list();
					 return_cd();
					 break;
		  case 5: cout<<"\nExiting from the menu\n";
					 break;
		  }
		  cout<<"\nDo you want to return to MOVIE MENU?\n";
		  cin>>a;
		  }
		  while(a=='y');
		  break;

  case 2: if(admin_login())
			 do
			 { cout<<"\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
				cout<<"\n@@@@@ADMIN MENU@@@@@@@@\n";
			  cout<<"\n1.Create Movie Records\n";
			  cout<<"2.Append Records\n";
			  cout<<"3.Display Movie Records\n";
			  cout<<"4.Insert a Movie Record\n";
			  cout<<"5.Delete a Movie Record\n";
			  cout<<"6.Modify an existing movie record\n";
			  cout<<"7.Exit\n";
			  cin>>c2;
		switch(c2)
		  {
		case 1: createfile();
					break;
		case 2: append();
				  break;
		case 3: cout<<"MOVIE MENU\n";
				  display_full_det();
				  break;
		case 4: insertion();
				  break;
		case 5: deletion();
				  break;
		case 6: modify();
				  break;
		case 7:cout<<"Exiting\n";
				 break;
		}
		cout<<"\nDo you want to return to MOVIE MENU again?\n";
		cin>>b;
		}
		  while(b=='y');
		  break;
  case 3: cout<<"\\\\\CONTACT CARD\\\\\\\\\\\n\n\n";
			  cout<<"/////////////////////////////////////////////////////";
			  cout<<endl;
			 cout<<"///!!!!!!!!!!!!!JUST ADDD POPCORN!!!!!!!!!!!!!!!! ///\n";
			 cout<<"///   The ultimate place for MOVIE LOVERS!!      /// \n";

			 cout<<"///   ADDRESS:: Shop 23,Ground Floor, FUN MALL   ///  \n";
			 cout<<"///             Lajpat Nagar,New Delhi           ///  \n";
			 cout<<"///   CONTACT:: 9910254141(Aditya Chaudhary)     ///\n";
			 cout<<"///             9745874598(Abhijit Anand)        ///\n";
			 cout<<"//    E-MAIL ::adityachd123@gmail.com            ///\n";
			 cout<<"///   ALWAYZZ READY TO SERVE YOU!!!!!            ///\n";
			 cout<<"/////////////////////////////////////////////////////";
			 cout<<"\n\n";
			 break;
  case 4:cout<<"Exiting";
			  exit(0);
			  break;

	}
	cout<<"\nDo you want to continue AND return to the Main Menu(Y/y)";
	cin>>d;
	}
	while((d=='y')||(d=='Y'));
		 }

