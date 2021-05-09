
#include "Person.h"
#include <limits>

Person::Person()
{
    set_person();
}

Person::Person(string fname, string lname, string bdate)
{
    this->f_name=fname;
    this->l_name=lname;
    this->birthdate=new Date(bdate);
    receive=1;
    p=0.5;
}


Person::~Person()
{
    delete birthdate;
}


void Person::set_person()
{
    delete birthdate;
	cout << "First Name: ";
    getline(cin,this->f_name);
	cout << "Last Name: ";
    getline(cin,this->l_name);
    cout << "Birthdate (M/D/YYYY): ";
    string x;
    getline(cin,x);
    this->birthdate=new Date(x);
    this->add_contact();
    receive=1;
    p=0.5;
}


bool Person::operator==(const Person& rhs)
{
    if((this->f_name==rhs.f_name)&&(this->l_name==rhs.l_name)&&((*(this->birthdate))==(*(rhs.birthdate))))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Person::operator!=(const Person& rhs)
{
    return (!(*(this)==rhs));
}


void Person::print_person(bool add)
{
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
	for(int i=0;i<contacts.size();i++)
	{
		if(add==true)
		{
			cout<<"["<<i+1<<"] ";
		}
        cout<<contacts[i]->get_contact()<<endl;
	}
}

void Person::add_contact(bool add)
{
    string state,type;
    string a,b;
    while(1)
    {

    	if(add==true)
    	{
    		state="Y";
    		add=false;
    	}
    	else
    	{
    		cout<<"Adding More Contact? (Y/N) ";
	        getline(cin,state);
	    }
        if(state=="Y")
        {
            cout<<"Enter \"Email\", \"Phone\", or \"SocialNetwork\": ";
            getline(cin,type);
            if(type=="Email")
            {
            	cout<<"Enter "<<type<<"'s type: ";
	            getline(cin,a);
	            cout<<"Enter "<<a<<"'s value: ";
	            getline(cin,b);
            	ContactInfo* p=new Email(a,b);
                contacts.push_back(p);
            }
            else if(type=="Phone")
            {
            	cout<<"Enter "<<type<<"'s type: ";
	            getline(cin,a);
	            cout<<"Enter "<<a<<"'s value: ";
	            getline(cin,b);
            	ContactInfo* p=new Phone(a,b);
                contacts.push_back(p);
            }
            else if(type=="SocialNetwork")
            {
            	cout<<"Enter "<<type<<"'s type: ";
	            getline(cin,a);
	            cout<<"Enter "<<a<<"'s value: ";
	            getline(cin,b);
            	ContactInfo* p=new SNAccount(a,b);
                contacts.push_back(p);
            }
        }
        else if(state=="N")
        {
            return;
        }
        else
        {
        }

    }
}

void Person::remove_contact() 
{

	while(1)
	{
		if(this->contacts.size()==0)
		{
			cout<<"This person has no contact\n";
			return;
		}

        string state;
        this->print_person(true);
        cout<<"Enter removal index or quit: ";
		getline(cin,state);
		if(quit(state))
		{
            return;
		}
		else if((0<atoi(state.c_str()))&&((this->contacts.size()+1)>atoi(state.c_str())))
		{
            cout<<"Confirm Removal? (Y/N) ";
            string confirm;
            getline(cin,confirm);
            if(confirm=="Y")
            {
                this->contacts.erase(contacts.begin()+atoi(state.c_str())-1);
                cout<<"Removal Confirmed\n";
            }
            else
            {
                
            }
		}
        else
        {

        }
	}
}

void Person::write_to_file(ofstream& outfile)
{
	outfile<<"*START-PERSON\n";
	outfile<<l_name<<", "<<f_name<<endl;
	outfile<<this->birthdate->get_date()<<endl;
	for(int i=0;i<contacts.size();i++)
	{
		outfile<<this->contacts[i]->get_contact(true)<<endl;
	}
	outfile<<"*END-PERSON\n";
}

bool Person::read_from_file(ifstream& infile)
{
	string buffer;
	getline(infile,buffer);
    if(buffer.find("*START-PERSON")==std::string::npos)
    {
        return false;
    }
	getline(infile,buffer);
	this->l_name=buffer.substr(0,buffer.find(","));
	this->f_name=buffer.substr(buffer.find(",")+2);
	getline(infile,buffer);
	this->birthdate=new Date(buffer);
	while(true)
	{
		getline(infile,buffer);
        if(buffer.find("*END-PERSON")!=std::string::npos)
        {
            return true;
        }
		string type=buffer.substr(buffer.find("(")+1,buffer.find(")")-buffer.find("(")-1);
		string value=buffer.substr(buffer.find(")")+2,buffer.size()-buffer.find(")")-2);
		if(buffer.find("Phone")!=std::string::npos)
		{
			ContactInfo* p=new Phone(type,value);
            contacts.push_back(p);
		}
		else if(buffer.find("Email")!=std::string::npos)
		{
			ContactInfo* p=new Email(type,value);
			contacts.push_back(p);
		}
		else if(buffer.find("SocialNetwork")!=std::string::npos)
		{
			ContactInfo* p=new SNAccount(type,value);
			contacts.push_back(p);
		}
	}
}

void Person::modify()
{
    
    while(true)
    {
	    cout<<"[1] Edit first name\n";
	    cout<<"[2] Edit last name\n";
	    cout<<"[3] Edit birthdate\n";
	    cout<<"[4] Remove contact information\n";
	    cout<<"[5] Add contact information\n";
	    cout<<"Select a Command Number or quit: ";
        string buffer;
	    cin>>buffer;
        cin.ignore();
    	if(quit(buffer))
    	{
    		break;
    	}
        switch(atoi(buffer.c_str()))
        {
            case 1: cout<<"Enter First Name: ";getline(cin,this->f_name);break;
            case 2: cout<<"Enter Last Name: ";getline(cin,this->l_name);break;
            case 3: cout<<"Enter Birthdate: ";getline(cin,buffer);this->birthdate->set_date(buffer);break;
            case 4: this->remove_contact();break;
            case 5: this->add_contact();break;
        }

        
    }
    return;
}

string Person::get_email()
{
    vector<ContactInfo*>email;
    for(int i=0;i<this->contacts.size();i++)
    { 
        if(this->contacts[i]->get_contact(true).find("Email")!=std::string::npos)
        {
            email.push_back(this->contacts[i]);
        }
    }
    if(email.size()==0)
    {
        return "";
    }
    else if(email.size()==1)
    {
        return email[0]->get_contact();
    }
    else
    {
        for(int i=0;i<email.size();i++)
        {
            cout<<i+1<<". "<<email[i]->get_contact()<<endl;
        }
        cout<<"Enter Email Index: ";
        int ind;
        cin>>ind;
        return email[ind-1]->get_contact();
    }
}

string Person::get_all_emails()
{
    string e="";
    for(int i=0;i<this->contacts.size();i++)
    { 
        if(this->contacts[i]->get_contact(true).find("Email")!=std::string::npos)
        {
            string temp=this->contacts[i]->get_contact();
            temp=temp.substr(temp.find(")")+2);
            e=e+" "+temp;
        }
    }
    if(e=="")
    {
    	return "";
    }
    else
    {
    	return e.substr(1);
    }
}

void Person::send_ad(map <string,int> ad)
{

	string emails=this->get_all_emails();
    string ad_name=choose_ad(ad);
    if((emails.size()==0)||(ad_name.size()==0))
    {
        return;
    }
    else
    {
    	string content="Dear "+this->f_name+" "+this->l_name+", \n\n"+"This is an advertisement from "+ad_name+".\n\n"+"Best Regards,\n\n"+ad_name;
        receive++;
        sendEmail(emails,ad_name,content);
        cout<<ad_name<<" ad sent to "<<f_name<<" "<<l_name<<". Is this ad relevent? (Y/N) ";
        string i;
        cin>>i;
        if(i=="Y")
        {
        }
        else
        {
           this->avoid.push_back(ad_name);
        }
    }
}

string Person::choose_ad(map <string,int> ad)
{

    auto temp=ad.begin();
    float sum=0;
    for(auto it=temp;it!=ad.end();++it)
    {
        sum+=it->second;
        if(find(avoid.begin(),avoid.end(),it->first)==end(avoid))
        {
        	if((temp->second)<(it->second))
        	{
        		temp=it;
        	}
        }
    }
    sum/=ad.size();
    if(receive==10)
    {
        p=float(avoid.size())/receive;
        if(p*temp->second>50*sum)
        {
            return temp->first;
        }
        else
        {
            return "";
        }
    }
    else
    {
    	return temp->first;
    }
}
