
#include "Date.h"

Date::Date(){
	// Already done!
	// cout << "Default constructor called! " << endl;
	day = 1;
	month = 1;
	year = 1970;
}


Date::Date(int day, int month, int year){
	// Already done! 
	// cout << "Constructor with integer arguments is called!" << endl;
	set_date(day, month, year);
}


Date::Date(string str){
	// Already done! 
	// input format is M/D/YYYY
	// cout << "Constructor wtih string argument is called" << endl;
	set_date(str); 
}


bool Date::operator==(const Date& rhs){
	// TODO
	if((this->year==rhs.year)&&(this->month==rhs.month)&&(this->day==rhs.day))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Date::operator!=(const Date& rhs){
	// TODO
	return(!(*(this)==rhs));
}

bool Date::operator < (const Date& rhs){
	// TODO
	if(this->year<rhs.year)
	{
		return true;
	}
	else if(this->year>rhs.year)
	{
		return false;
	}
	else
	{
		if(this->month<rhs.month)
		{
			return true;
		}
		else if(this->month>rhs.month)
		{
			return false;
		}
		else
		{
			if(this->day<rhs.day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool Date::operator > (const Date& rhs){
	// TODO
	if((*(this)!=rhs)&&(!(*(this)<rhs)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Date::check_date(int day, int month, int year){
	// TODO -- you did this in Lab3
	// Leap years are those years divisible by 4, except for century years which are not divisible by 400. 
	if (day<1 | day > 31)
		return false;
	if((month<1)||(month>12))
		return false; 
	if((month==4)||(month==6)||(month==9)||(month==11))
	{
		if (day>30)
			return false;
	}
	else if(month==2)
	{
		if(day>29)
			return false;
	}
	if(!(((abs(year)%400)==0)||(((abs(year)%4)==0)&&(abs(year)%100)!=0)))
	{
		if((month==2)&&(day>28))
		{
			return false;
		}
	}
	return true;
}

bool Date::check_valid(string str){
	int c=0;
	bool r=true;
	int sec=0;
	if(str.size()<5)
	{
		return false;
	}
	for(int i=0;i<str.size();i++)
	{
		if(str.substr(i,1)=="/")
		{
			if(i==0)
			{
				return false;
			}
			else if(i==str.size()-1)
			{
				return false;
			}
			c++;
			if(c==2)
			{
				sec=i;
			}
		}
	}
	if(c!=2)
	{
		return false;
	}

	return r;

}

bool Date::set_date(string str){
	// TODO
	// input format should be M/D/YYYY
	// You may use these prompts
	// cout << "Error! Invalid date!" << endl;
	// cout << "Date set to default!" << endl;
	int pre=0;
	int cur=0;
	if(check_valid(str)==false)
	{
		this->day=1;
		this->month=1;
		this->year=1970;
		return false;
	}
	while(str.substr(cur,1)!="/")
	{
		cur++;
	}
	month=atoi(str.substr(pre,cur-pre).c_str());
	cur++;
	pre=cur;
	while(str.substr(cur,1)!="/")
	{
		cur++;
	}
	day=atoi(str.substr(pre,cur-pre).c_str());
	pre=cur+1;
	year=atoi(str.substr(pre,str.size()-pre).c_str());
	if(!(check_date(this->day,this->month,this->year)))
	{
		this->day=1;
		this->month=1;
		this->year=1970;
		return false;
	}
	else
	{
		return true;
	}
}


bool Date::set_date(int day, int month, int year){
	// Already done!
	// returns a true if operation successful, or false if unsuccessful
	// understand why we used "this" statement in this method
	if (check_date(day, month, year)){
		this->day = day;
		this->month = month;
		this->year = year;
		return true;
	}
	else {
		cout << "Error! Invalid date!" << endl;
		cout << "Date set to default!" << endl;
		this->day = 1;
		this->month = 1;
		this->year = 1970;
		return false;
	}
}
string Date::convert(int month){
	switch(month)
	{
        case 1:return "Jan";
        case 2:return "Feb";
        case 3:return "Mar";
        case 4:return "Apr";
        case 5:return "May";
        case 6:return "Jun";
        case 7:return "Jul";
        case 8:return "Aug";
        case 9:return "Sep";
        case 10:return "Oct";
        case 11:return "Nov";
        case 12:return "Dec";
	}

}

void Date::print_date(string type){
	// TODO
	// Different types for print, are: 
	// "M/D/YYYY"
	// "Month D, YYYY"
	// "D-Month-YYYY"
	// otherwise, cout << "Wrong print type!" << endl;
	MONTH_TYPE x;

	if(type=="M/D/YYYY")
	{
		cout<<month<<"/"<<day<<"/"<<year<<endl;
	}
	else if(type=="Month D, YYYY")
	{
		cout<<convert(month)<<" "<<day<<", "<<year<<endl;
	}
	else if(type=="D-Month-YYYY")
	{
		cout<<day<<"-"<<convert(month)<<"-"<<year<<endl;
	}
	else
	{
		cout << "Wrong print type!" << endl;
	}
}

string Date::get_date(){
	// Already done!
	ostringstream ss;
	ss << month << "/" << day << "/" << year; 
	string str = ss.str();
	return str;
}