#include<iostream>	
#include<string>	
#include<sstream>	/*for storing the data from string to int*/
#include<stdlib.h>	/*for clearing the screen and changing the color of the output*/
int Days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
using namespace std;

class Calender		/*definition of class*/
{
	string input;
	int date, month, year, weekday;
	static string history;
	char ch;
  public:
	/*Operator overloading of ">>" operator to take direct input using object. It is defined outside the class*/
	friend istream & operator >> (istream & din, Calender & date);		
	
	/*Normal member funtion to take input of weekday to find date on that day*/
	void GetDay() 
	{
		cout << "Press 0 for Friday.\nPress 1 for Saturday\nPress 2 for Sunday\nPress 3 for Monday\nPress 4 for Tuesday\nPress 5 for Wednesday\nPress 6 for Thursday.";
		cout << "\nChoose your option: ";
		cin >> weekday;
	}
	
	/*Function to find particular day that falls on the date entered by user*/
	string FindDay() 
	{
		/*int count=0;
		for(int i=1; i<year; i++)
		{
			count+=365;
			if(i%4==0 && i%100!=0)
				count++;
			if(i%400==0)
				count++;
		}
		for(int i=0; i<month-1; i++)
			count+=Days[i];
		count+=date+2;*/
		int count=0;
		count+=year*365;
		count+=((year/4)-(year/100)+(year/400));
		for(int i=0; i<month-1; i++)
			count+=Days[i];
		count+=date+1;
		if(count%7==1)
			return "Saturday";
		else if(count%7==2)
			return "Sunday";
		else if(count%7==3)
			return "Monday";
		else if(count%7==4)
			return "Tuesday";
		else if(count%7==5)
			return "Wednesday";
		else if(count%7==6)
			return "Thursday";
		else
			return "Friday";
	}
	
	/*Function to count number of days from the 1 AD till the date entered by user*/
	int CountDays()
	{
		int count=0;
		count+=year*365;
		count+=((year/4)-(year/100)+(year/400));
		for(int i=0; i<month-1; i++)
			count+=Days[i];
		count+=date-1;
		return count;
	}
	
	/*Function to find the difference between two dates*/
	void Difference(Calender ob)
	{
		int dd=0, mm=0, yy=0;
		if(year!=ob.year)
		{
			if(ob.month!=1)
			{
				for(int i=year+1; i<ob.year; i++)
					mm+=12;
				for(int i=month; i<12; i++)
					mm=mm+1;
				for (int i=1; i<ob.month; i++)
					mm++;
			}
			else if(ob.month==1)
			{
				for(int i=year+1; i<ob.year; i++)
					mm+=12;
				for(int i=month; i<12-1; i++)
					mm=mm+1;
				for (int i=date; i<Days[11]; i++)
				dd++;
				goto jump;
			}
		}
		else 
		{
			for (int i=month; i<ob.month-1; i++)
				mm++;
		}
		for (int i=date; i<Days[ob.month-2]; i++)
				dd++;
		jump:
		for (int i=1; i<=ob.date; i++)
			dd++;
		if(dd>=Days[ob.month-2])
		{
			mm++;
			dd=dd-Days[ob.month-2];
		}
		if(mm>=12)
		{
			yy+=mm/12;
			mm=mm-(12*yy);
		}
		cout << "in months: " << mm+(12*yy) << " month(s) " << dd << " day(s)." <<endl;
		cout << "in years: " << yy << " year(s) " << mm << " month(s) " << dd << " day(s)." <<endl;
	}
	
	/*Function to find all the facts of date entered by the user*/
	void facts()
	{
		cout << "*It is a " << FindDay() << " on this date.\n";
		int count=0;
		for(int i=0; i<month-1; i++)
			count+=Days[i];
		count+=date;
		if(count==1)
			cout << "*It is 1st " << FindDay() << " out of 53.\n";
		if(count%7==0)
			cout << "*It is the " << (count/7) <<"th " << FindDay() << " out of 52.\n";
		else
			cout << "*It is the " << (count/7)+1 <<"th " << FindDay() << " out of 52.\n";
		if (((year % 4 == 0) && (year % 100!= 0)) || (year%400 == 0))
		{
			if(month==2)
				cout << "*This month has " << Days[month-1]+1 << " days.\n";
			else
				cout << "*This month has " << Days[month-1] << " days.\n";
			cout << "*" <<year <<" is a leap year.\n";
			cout << "*It is the " << count << "th day & " << 366-count << " days are left in the year.\n";
		}		
		else
		{
			cout << "*This month has " << Days[month-1] << " days.\n";
			cout << "*" <<year <<" is not a leap year.\n";
			cout << "*It is the " << count << "th day & " << 365-count << " days are left in the year.\n";
		}
	}
	
	/*overloading of "<<" operator to display the data members using directly objects*/
	friend ostream & operator << (ostream & dout, Calender ob);
	
	/*Overloading operator ">" to check whether date 1 is greater than date 2 or not*/
	int operator > (Calender ob)
	{
		if(year == ob.year && month == ob.month && date > ob.date)
			return 1;
		else if(year == ob.year && month > ob.month)
			return 1;
		else if(year > ob.year)
			return 1;
		else 
			return 0;
	}
	
	/*Function to print all the dates in a given interval that fall on a specific day*/
	friend void PrintDate(Calender ob1, Calender ob2);
	
	/*Function to print date of different years*/
	friend void DiffYear(Calender ob1, Calender ob2, int count);
	
	/*Functions to print date of same years*/
	friend void SameYear(Calender ob1, Calender ob2, int count);
	
	/*overloading of "*" operator to exchange the values of date 1 and date 2*/
	friend void operator * (Calender & ob1, Calender & ob2);
	
	/*function to print all the previous commands entered by user*/
	static void ShowHistory()
	{
		cout << "Your inputs were: \n";
		for(int i=0; i<history.size(); i++)
			cout << history[i];
	}
};

/*definition of static data member*/
string Calender	:: history;

/*definition of the friend function*/
istream & operator >> (istream & din, Calender & ob)
{
	cout<<"Enter the date: ";
	din >> ob.input;
	ob.history.append("\n* ");
	ob.history.append(ob.input);
	stringstream ss(ob.input);
	ss >> ob.date >> ob.ch >> ob.month >> ob.ch >> ob.year;
}

/*defition of the operator "*" overloading*/
void operator * (Calender & ob1, Calender & ob2)
{
	int temp = ob1.date;
	ob1.date = ob2.date;
	ob2.date = temp;
	temp = ob1.month;
	ob1.month = ob2.month;
	ob2.month = temp;
	temp = ob1.year;
	ob1.year = ob2.year;
	ob2.year = temp;
}

/*Definition of friend function to Print dates falling on a particular day in an interval*/
void PrintDate(Calender ob1, Calender ob2)
{
	int count=0;
	for(int i=1; i<ob1.year; i++)
	{
		count+=365;
		if (((i % 4 == 0) && (i % 100!= 0)) || (i%400 == 0))
			count++;
	}
	for(int i=0; i<ob1.month-1; i++)
		count+=Days[i];
	count+=ob1.date+1;
	for(int i=ob1.date; i<=Days[ob1.month-1]; i++)
	{
		count++;
		if(count%7==ob1.weekday)
			cout << i << "/" << ob1.month << "/" << ob1.year << endl;
	}
	if(ob1.year!=ob2.year)
	{
		DiffYear(ob1, ob2, count);	
	}
	else if(ob1.year==ob2.year)
	{	
		SameYear(ob1, ob2, count);
	}
}

/*Print dates for different years*/
void DiffYear(Calender ob1, Calender ob2, int count)
{
	for (int i=ob1.month+1; i<=12; i++)
	{
		for(int j=1; j<=Days[i-1]; j++)
		{
			count++;
			if(count%7==ob1.weekday)
			cout << j << "/" << i << "/" << ob1.year << endl;
		}
	}
	for(int i=ob1.year+1; i<ob2.year; i++)
	{
		if (((i % 4 == 0) && (i % 100!= 0)) || (i %400 == 0))
			count++;
		for(int j=1; j<=12; j++)
		{
			for (int k=1; k<=Days[j-1]; k++)
			{
				count++;
				if(count%7==ob1.weekday)
				cout << k << "/" << j << "/" << i << endl;
			}
		}
	}
	for (int i=1; i<ob2.month; i++)
	{
		for(int j=1; j<=Days[i-1]; j++)
		{
			count++;
			if(count%7==ob1.weekday)
			cout << j << "/" << i << "/" << ob2.year << endl;
		}
	}
	for (int i=1; i<=ob2.date; i++)
	{
		count++;
		if(count%7==ob1.weekday)
			cout << i << "/" << ob2.month << "/" << ob2.year << endl;
	}
}

/*Print dates for same year*/
void SameYear(Calender ob1, Calender ob2, int count)
{
	if(ob1.month!=ob2.month)
	{	
		for (int i=ob1.month; i<ob2.month-1; i++)
		{
			for(int j=1; j<=Days[i]; j++)
			{
				count++;
				if(count%7==ob1.weekday)
				cout << j << "/" << i+1 << "/" << ob1.year << endl;
			}
		}
		for (int i=1; i<=ob2.date; i++)
		{
			count++;
			if(count%7==ob1.weekday)
				cout << i << "/" << ob2.month << "/" << ob1.year << endl;
		}
	}		
	else if(ob1.month==ob2.month)
	{
		for(int i=ob1.date; i<ob2.date; i++)
		{
			count++;
			if(count%7==ob1.weekday)
				cout << i << "/" << ob1.month << "/" << ob1.year << endl;
		}
	}
}

ostream & operator << (ostream & dout, Calender ob)
{
	dout << ob.date << "/" << ob.month << "/" << ob.year ;
}

int main()
{
	loop:
	system("cls");
	system("color a");
	cout << "\n*************************Calender Calculator****************************\n";
	int n;
	cout << "\nPress 1 to find day at any date \nPress 2 to find difference between two dates\nPress 3 to find facts of any date\nPress 4 to print dates of particular day in any interval\nPress 5 to see history\nPress 6 to end the program\n";
	cout << "\nChoose your option: ";
	cin >> n;
	Calender date1;
	if(n==1)
	{
		cout << "\nThe date must be of the form dd/mm/yyyy\n";
		cin>>date1;
		cout;
		cout <<"The day on " << date1 << " is " << date1.FindDay()<<endl<<endl;
		system("pause");
		system("cls");
	}
	else if(n==2)
	{
		cout << "\nThe date must be of the form dd/mm/yyyy\n";
		Calender date2;
		cin >> date1;
		cin >> date2;
		if(date1>date2)
			date1*date2;
		cout << "\nThe difference between " << date1.FindDay() << " " << date1 << " & " << date2.FindDay() << " " << date2 <<" is: " <<endl;
		cout << "in hours: " << (date2.CountDays()-date1.CountDays())*24 << " hours." <<endl;
		cout << "in days: " << date2.CountDays()-date1.CountDays() << " days." <<endl;
		date1.Difference(date2);
		cout<<endl;
		system("pause");
		system("cls");
	}
	else if(n==3)
	{
		cout << "\nThe date must be of the form dd/mm/yyyy\n";
		cin >> date1;
		date1.facts();
		cout<<endl;
		system("pause");
		system("cls");
	}
	else if(n==4)
	{
		cout << "\nThe date must be of the form dd/mm/yyyy.\n";
		Calender date2;
		cin >> date1;
		cin >> date2;
		if(date1>date2)
			date1*date2;
		date1.GetDay();
		PrintDate(date1, date2);
		cout<<endl;
		system("pause");
		system("cls");
	}
	else if(n==5)
	{
		date1.ShowHistory();
		cout<<"\n"<<endl;
		system("pause");
		system("cls");
	}
	else if(n==6)
		goto end;
	else
		cout << "\nInvalid Input.\n";
	char ch;
	cout << "\n\nPress \"y\" if you wish to continue else press \"n\" to end the program: ";
	cin >> ch;
	if(ch=='y' || ch=='Y')
		goto loop;
	else
		end:
		cout << "\nThe program is over. Thank you for using.\n";
	return 0;
}
