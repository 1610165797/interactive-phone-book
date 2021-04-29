
#include "Network.h"
#include "misc.h"
#include <fstream>
#include <dirent.h>
#include <limits>

Network::Network(){
    // TODO
    // What should be the initial values for head, tail, and count?
    this->head=NULL;
    this->tail=NULL;
    this->count=0;
}


void Network::push_front(Person* newEntry){
    // TODO
    // Adds a new entry to the front of the LL (where head is pointing)
    if(this->count==0)
    {
    	this->head=newEntry;
    	newEntry->next=NULL;
    	newEntry->prev=this->head;
    	this->tail=newEntry;
    }
    else
    {
    	this->head->prev=newEntry;
    	newEntry->next=this->head;
    	this->head=newEntry;
    	newEntry->prev=head;
    }
    this->count++;
    return;


}


void Network::push_back(Person* newEntry){
    // TODO
    // Adds a new entry to the back of the LL (where tail is pointing)
    if(count==0)
    {
    	this->head=newEntry;
    	newEntry->prev=head;
        newEntry->next=NULL;
        this->tail=newEntry;
    }
    else
    {
    this->tail->next=newEntry;
    newEntry->next=NULL;
    newEntry->prev=tail;
    this->tail=newEntry;
    }
    this->count++;
    return;

}


void Network::printDB(){
    // Already done! 
    cout << "Number of items: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}

Network::~Network(){
    // TODO
    // Delete all the dynamically allocated items
    Person* temp=head;
    while(temp!=NULL){
    	if(temp->next==NULL)
    	{
    		delete temp;
    		break;
    	}
    	temp=temp->next;
    	delete temp->prev;
    }
}


Person* Network::search(Person* searchEntry){
    // TODO
    // Searches the Network to find an entry which has similar attributes as searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Hint: We already implemented the == operator for two Person objects
    // Note: searchEntry is not a Person, but a Person*
    Person* temp=head;
    while(temp!=NULL)
    {
    	if((*searchEntry)==(*temp))
    	{
    		return temp;
    	}
    	temp=temp->next;
    }
    return NULL;
}

Person* Network::search(string fname, string lname, string bd){
    // TODO
    // Search based on fname, lname, and birthdate
    // if found, returns a pointer to it, else returns NULL
    // Note: two ways to implement this:
    // 1st) making a new Person with fname, lname, bdate and and using search(Person*)
    // 2nd) using fname, lname, and bd directly
	Person* temp=new Person(fname,lname,bd);
	Person* result=search(temp);
	delete temp;
	return result;
}

void Network::saveDB(string filename){
    // TODO
    // Saves the netwrok in file <filename>
    // Look at studentDB.db as a template of the format of our database files
    ofstream outfile(filename.c_str());
    Person* temp=this->head;

    while(temp!=NULL)
    {
        temp->write_to_file(outfile);
        temp=temp->next;
    }
    outfile<<"*END-DATABASE\n";
    outfile.close();
}


void Network::loadDB(string filename){
    // TODO
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.db as a template
    // When a new database is being loaded, you need to delete the previous dataset
    Person* temp=head;
    int i=0;
    while(temp!=NULL)
    {
    	if(temp->next==NULL)
    	{
    		delete temp;
    		break;
    	}
    	else
    	{
    		temp=temp->next;
    		delete temp->prev;
    	}
    }

    this->head=NULL;
    this->tail=NULL;
    this->count=0;

    ifstream infile(filename.c_str());
    while(!infile.eof())
    {
        Person* temp=new Person("Default","Default","Default");

        if(temp->read_from_file(infile)==false)
        {
            delete temp;
        }
        else
        {
            if(search(temp)==NULL)
            {
                push_back(temp);
            }
        }
    }
    /*
    string line,f,l,b;
    while(!infile.eof())
    {
    	getline(infile,line,'\n');
    	if(line=="")
    		{break;}
    	for(int i=0;i<line.size();i++)
    	{
    		if(line.substr(i,1)==",")
    		{
    			l=line.substr(0,i);
    			f=line.substr(i+2,line.size()-i-2);
    		}
    	}
    	getline(infile,b,'\n');
    	Person* temp=new Person(f,l,b);
    	if(search(temp)==NULL)
    	{
    		push_back(temp);
    	}
    	getline(infile,line,'\n');
    }
    infile.close();
    */
}

Network::Network(string fileName){
    // TODO
    // Hint: just call loadDB 
    loadDB(fileName);
}

bool Network::remove(string fname, string lname, string bd){
    // TODO
    // remove the entry with matching fname, lname, bd
    // If it exists, returns true, otherwise, returns false
    Person* remove=search(fname,lname,bd);
    if(remove==NULL)
    {
    	return false;
    }
    else
    {
    	if(count==1)
    	{
    		this->head=NULL;
    		this->tail=NULL;
    	}
    	else if(remove==this->head)
    	{
    		this->head=remove->next;
    		remove->next->prev=head;
    	}
    	else if(remove->next==NULL)
    	{
    		remove->prev->next=NULL;
    	}
    	else
    	{
    		remove->prev->next=remove->next;
    		remove->next->prev=remove->prev;
    	}
    	delete remove;
    	this->count--;
    	return true;
    }
    
}

vector<Person*> Network::search(string fname,string lname){
    vector<Person*> list;
    Person* temp=this->head;
    while(temp!=NULL)
    {
        if((fname==(temp->f_name))&&(lname==(temp->l_name)))
        {
            list.push_back(temp);
        }
        temp=temp->next;
    }
    return list;
}

void Network::showMenu(){
    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner");
        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Search & Modify \n";
        cout << "6. Print database \n";
        cout << "7. Send Email \n";
        cout << "0. Quit \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! Quitting ... " << endl;
            return;
        }

        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){ 
            // Already done! 
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            this->saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){ 
            // Already done! 
            cout << "Loading network database \n";
            // Note: we added a nice feature to show the files in current directory
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir ("./")) != NULL) {
                string str;
                while ((ent = readdir (dir)) != NULL) {
                    str = ent->d_name;
                    if (str.size() > 3){
                        if (str.substr(str.size()-3) == ".db")
                            cout << str << endl;
                    }
                }
                closedir (dir);
            }
            cout << "Enter the name of the load file: ";
            cin >> fileName;
            ifstream check(fileName.c_str());
            if (! bool(check))
                cout << "Warning! File does not exist! \n";
            else {
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " items \n";
            }
        }
        else if (opt == 3){
            // TODO
            // Prompt and get the information of a new Person
            // You need to make sure this item does not already exists!
            // If it does not exist, push it to the front of the LL
            string f,l,b;
            cout << "Adding a new item (push front)\n";
            cout << "First name: ";
            getline(cin,f);
            cout << "Last name: ";
            getline(cin,l);
            cout << "Birthdate: ";
            getline(cin,b);
            Person* temp=new Person(f,l,b);
            if(search(temp)==NULL)
            {
            	push_front(temp);
            	temp->add_contact(false);
            	cout<<"Person successfully added! \n";
            }
            else
            {
            	cout<<"Person already exists! \n";
            }

            
        }
        else if (opt == 4){
            // TODO 
            string f,l,b;
            cout << "Removing an item \n";
            cout << "First name: ";
            getline(cin,f);
            cout << "Last name: ";
            getline(cin,l);
            cout << "Birthdate: ";
            getline(cin,b);
            // If found and removed successfully: cout << "Remove Successful! \n";
            // else: cout << "Person not found! \n";
            if(this->remove(f,l,b)==true)
            {
            	cout << "Remove Successful! \n";
            }
            else
            {
            	cout << "Person not found! \n";
            }
        }
        else if (opt==5){
            cout << "Search & Modify \n";
            string f,l;
            cout << "Enter First Name: ";
            getline(cin,f);
            cout << "Enter Last Name: ";
            getline(cin,l);
            vector<Person*>list=search(f,l);
            int index;
            if(list.size()==0)
            {
                cout<<"Person Not Found! \n";
            }
            else if(list.size()==1)
            {
                list[0]->modify();
            }
            else
            {
                for(int i=0;i<list.size();i++)
                {
                    cout<<"["<<i+1<<"]"<<endl;
                    list[i]->print_person();
                }
                cout<<"Choose Person Index: ";
                cin>>index;
                while((index<1)||(index>list.size()))
                {
                    cout<<"Please Input Valid index: ";
                    cin>>index;
                }
                list[index-1]->modify();
            }
        }
        else if (opt==6){
            // TODO 
            cout << "Network Database \n";
            // this should be simple ... 
            this->printDB();
        }
        else if (opt==7){
            // TODO 
            cout << "Send Email \n";

            string f,l;
            cout << "Enter First Name: ";
            getline(cin,f);
            cout << "Enter Last Name: ";
            getline(cin,l);

            vector<Person*>list=search(f,l);
            if(list.size()==0)
            {
                cout<<"Person Not Found! \n";
            }
            else
            {
                int index;
                if(list.size()==1)
                {
                    index=1;
                }
                else
                {
                    for(int i=0;i<list.size();i++)
                    {
                        cout<<"["<<i+1<<"]"<<endl;
                        list[i]->print_person();
                    }
                    cout<<"Choose Person Index: ";
                    cin>>index;
                    while((index<1)||(index>list.size()))
                    {
                        cout<<"Please Input Valid index: ";
                        cin>>index;
                    }
                }
                string addr,subject,content;
                addr=list[index-1]->get_email();
                if(addr=="")
                {
                	cout<<"This person doesn't have an email \n";
                }
            	else
	            {
	            	cin.ignore();
	                cout<<"Email Subject: ";
	                getline(cin,subject);
	                cout<<"Email Content: ";
	                getline(cin,content);
	                sendEmail(addr, subject, content);
	            }
            }

        }

        else if (opt==0){
            // QUIT!
            return;
        }
        else
            cout << "Nothing matched!\n";
        // Don't touch the lines below! :)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.clear();
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}



