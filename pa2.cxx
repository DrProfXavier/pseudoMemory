#include <iostream>
#include <string>

using namespace std;
//declarations
int printMenu();

struct node
{
	string data;
	node *next; //pointer to next node
};

class list
{
	//private:
	//*head, *tail;
	public:
	node *head, *tail;
	
	void display();
	void createnode(string value); //standard
	void addProgram(string value, int size, string fit);
	void deleteProgram(string value);
	node* findInsert(int size, string fit/*, string fit*/); //goes in addProgram
	int fragments();
	bool existence(string value);
	
	list()//constructor
	{
		head=NULL;//make head and tail point to null, an empty list 
		tail=NULL;
	}
}programList;

void list::display()
{
	node *temp = new node;
	temp=head;//put a new node in front of head by taking its place
	while(temp!=NULL)//as long as there's a valid pointer to next node
	{
		for (int h = 0; h<4;h++)
		{
			for (int i = 0; i < 8; i++)
			{
			cout << temp->data <<" ";
			temp=temp->next;//set temps address to that of next node to be printed 
			}
			cout<<endl;
		}
	}
}


void list::createnode(string value)
{
	node *temp = new node; //hold onto your hats
	temp->data=value;//address that temp points to(the new node) will have its "data" attribute from "struct node" set to param value 
	temp->next=NULL;
	
	if(head==NULL) //list is empty 
	{
		head = temp;//swap, reset temp
		tail = temp;
		temp = NULL;
	}
	else //list is not empty
	{
		tail->next=temp;//adds to back
		tail=temp;//new tail is new node
	}
}

void list::addProgram(string value, int size, string fit) /*, string fit*/	//Transfer free nodes into data nodes
{	
	int pages;
	int remainder = 0;
	if ((size % 4) > 0) {remainder = 1;}
	pages = (size/4) + remainder;
	node* temp = programList.findInsert(pages, fit);
	
	for (int i = 0; i < pages; i++)
	{
		temp->data = value;
		temp = temp->next;
	}
}

node* list::findInsert(int size, string fit)/*, string fit*/		//will return a pointer to open location
{
	node* iter = head;
	//node* current = NULL;
	node* temp = NULL;
	node* spot = NULL;
	
	int requiredPages = size;
	int spaceCount;
	int potential;
	int max = 33;
	int min = 0;
	
	bool inFrag = false;
	bool bestFit = false;
	bool worstFit = false;
	
	//determine fit method
	if (!fit.compare("best")) 
	{ 
		bestFit = true;
		worstFit = false;
	}
	else 
	{
		bestFit = false;
		worstFit = true;
	}
	
	//for BESTFIT
	while (bestFit)
	{
		for (int i = 0; i < 32; i++)
		{
			if (!inFrag && iter->data == "Free")
			{
				inFrag = true;
				temp = iter;
				spaceCount++;
				iter = iter->next;
			}
			if (inFrag && iter->data == "Free")
			{
				spaceCount++;
				iter=iter->next;
			}
			if ((iter->data == "Free") && (iter->next == NULL))
			{
				inFrag = false;
				spaceCount++;
				if ((spaceCount < max) && (spaceCount > requiredPages))
				{
					potential = spaceCount;
					max = potential;
					spot = temp;
				}
				spaceCount = 0;
				break;
			}
			if ((iter->data != "Free") || (iter->next == NULL))
			{
				inFrag = false;
				if ((spaceCount < max) && (spaceCount > requiredPages))
				{
					potential = spaceCount;
					max = potential;
					spot = temp;
				}
				spaceCount = 0;
				iter = iter->next;
			}
		}
		break;
	}
	
	//WORST OF ALL
	while (worstFit)
	{
		for (int i = 0; i < 32; i++)//(int i = 0; i < 6; i++)
		{
			if (!inFrag && iter->data == "Free")
			{
				inFrag = true;
				temp = iter;
				spaceCount++;
				iter = iter->next;
			}
			if (inFrag && iter->data == "Free")
			{
				spaceCount++;
				iter=iter->next;
			}
			if ((iter->data == "Free") && (iter->next == NULL))
			{
				inFrag = false;
				spaceCount++;
				if ((spaceCount > min) && (spaceCount > requiredPages))
				{
					potential = spaceCount;
					min = potential;
					spot = temp;
				}
				spaceCount = 0;
				break;
			}
			if ((iter->data != "Free") || (iter->next == NULL))
			{
				inFrag = false;
				if ((spaceCount < max) && (spaceCount > requiredPages))
				{
					potential = spaceCount;
					max = potential;
					spot = temp;
				}
				spaceCount = 0;
				iter = iter->next;
			}
		}
		break;
	}
	
	if	(size > max) 
	{
		cout<<"Error, Not enough memory for Program ";
	}

	return spot;
}

int list::fragments()//may return no of fragemts
{
    node *temp = head;
	int noFrags = 0;
	bool inFrag = false;
	
	while (temp->next)
	{
		if (!inFrag && temp->data == "Free")
		{
			noFrags++;
			inFrag = true;
		} 
		if (temp->data != "Free")
		{
			inFrag = false;
		}
		temp = temp->next;
	}
	return noFrags;
}

void list::deleteProgram(string value) //prototype for iterator
{
	node *temp = new node;
	temp = head;//put a new node in front of head by taking its place
	for (int i=0;i<32;i++)//as long as there's a valid pointer to next node
	{
		if (temp->data == value)
		{
			temp->data = "Free";
			
		}
		temp = temp->next;
	}
}

bool existence(string value)
{
	node* check = programList.head;
	bool exists = false;
	
	while (check->next)
	{
		if (check->data == value)
		{
			exists = true;
		} 
		else {exists = false;}
	}
	return exists;
}


int printMenu()
{
	int choice;
	cout << "1. Add program\n"
		 << "2. Kill program\n"
		 << "3. Fragmentation\n"
		 << "4. Print memory\n"
		 << "5. Exit\n\n";
		 cout<<"Choice - ";
	cin >> choice;
	cout<<endl;
	return choice;
}

int main(int argc, char ** argv)
{
	bool isWorking = true;
	int size;
	string name;
	string fit;
	
	if (argv[1] != NULL) 
	{
		string fit = argv[1];
		if (fit.compare("best") == 0)
		{
			fit = "best";
		}
		if	(fit.compare("worst") == 0) 
		{
			fit = "worst";
		}
	}
	
	//Make starting empt list
	int count = 0;	
	while (count < 32) 
	{
		programList.createnode("Free");//freeList.createnode("Free");
		count++;
	}
	
	//Debugging, prints well
	cout << endl;
	cout << "Using "<<fit<<" fit algorithm\n" <<endl;
	
	while (isWorking)
	{
		int choice = printMenu();
		
		switch (choice)
		{
			case 1:
				cout<<"Program name - ";
				cin>>name;
				cout<<endl;
				cout<<"Program size (KB) - ";
				cin>>size;
				cout<<endl;
				if (existence(name))
				{
					cout<<"Error, Program "<<name<<" already running.\n\n";
					
				}
				else{
					programList.addProgram(name, size, fit);//, fit
				}
				break;
			case 2://works
				cout<<"Program name - ";
				cin>>name;
				cout<<endl;
				programList.deleteProgram(name);
				break;
			case 3: 
				int num;
				num = programList.fragments();
				cout << "There are " << num << " Frags \n\n";
				break;
			case 4://basicall done, needs formatting
				programList.display();
				cout << endl;
				break;
			case 5://Done
				isWorking = false;
				break;
			default:
				//error handle
				break;
		}
	}
	return 0;
}
