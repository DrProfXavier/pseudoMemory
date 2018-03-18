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
	
	list()//constructor
	{
		head=NULL;//make head and tail point to null, an empty list 
		tail=NULL;
	}
} /*freeList,*/ programList;

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
	/*same goes for the pointer, assign temp's destination address to 
	 * next, the node's pointer, becasue it is the tail, points to null,
	 */ 
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
	node* temp = programList.findInsert(pages, fit);//,fit
	//node* temp = head;
	
	for (int i = 0; i < pages; i++)
	{
		temp->data = value;
		temp = temp->next;
	}
}

node* list::findInsert(int size, string fit)/*, string fit*/		//will return a pointer to open location
{
	node* spot = new node;//should point to beginning of chosen frag
	node* temp = head;//itereator start
	node* nodeArr[32];//array with number
	
	int spaceNeeded = size;
	int possibleSpaces = programList.fragments();//number of fragments
	int spacesArr[possibleSpaces] = {0};//array of fragments
	int spaceSize = 0;
	int targetSize;


	bool bestFit = false;
	bool worstFit = false;
	bool inFrag = false;

	//best or worst fit
	if (!fit.compare("best")) { 
		bestFit = true;
		worstFit = false;
	}
	else {
		bestFit = false;
		worstFit = true;
	}
	
	//fill "node* nodeArr" with each node
	for (int count=0; count<32; count++)
	{
		nodeArr[count] = temp;
		temp = temp->next;
	}

    //will fill spacesArr with fragment sizes
	int j = 1;//index of spacesArr
	while (j <= possibleSpaces) //while indexs < size of spacesArr
	{
		for (int i = 0; i < 32; i++)//temp->next
		{
			if (!inFrag && nodeArr[i]->data == "Free")
			{
				inFrag = true;
				spaceSize++;
			} 
			if (inFrag && nodeArr[i]->data =="Free")
			{
				spaceSize++;
			} 
			if (nodeArr[i]->data != "Free")
			{
				inFrag = false;
				if (spaceSize > 0)
				{
					spacesArr[j] = spaceSize;
					spaceSize = 0;
				}
			}
			j++;
		}
	}

	//depending on fit method
	if (bestFit) 
	{
		int min = 0;
		for(int i=0; i<possibleSpaces; i++)
		{
			if((spacesArr[i]<min) && (spacesArr[i]>spaceNeeded))
			{
				min = spacesArr[i];
			}
		}
		targetSize = min;
	}
	
	if (worstFit) 
	{
		int max = 0;
		for(int i=0; i<possibleSpaces; i++)
		{
			if((spacesArr[i]>max) && (spacesArr[i]>spaceNeeded))
			{
				max = spacesArr[i];
			}
		}
		targetSize = max;
	}
	 
	/*find the matching fragment space based on best or worst fit.
	 * Once the copmleted fragment is found, return [index-spaceSize]
	 * as start point "spot"
	 */
	int fragIndex = 1; //wtf is space??
	while (fragIndex <= possibleSpaces) 
	{
		for (int i = 0; i < 32; i++)//temp->next
		{
			if (!inFrag && nodeArr[i]->data == "Free")
			{
				inFrag = true;
				spaceSize++;
			} 
			else if (inFrag && nodeArr[i]->data =="Free")
			{
				spaceSize++;
			} 
			else if (nodeArr[i]->data != "Free")
			{
				inFrag = false;
				fragIndex++;
				if (spaceSize == targetSize)
				{
					spot = nodeArr[i - spaceSize -1];
					break;
				}
				spaceSize = 0;
			}
		}
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
	//create 32 FREE pages in empty list
	int count = 0;
	string fit = "best";//FOR TESTING, CHANGE TO CHECK ARGS
	
	while (count < 32) {
	programList.createnode("Free");//freeList.createnode("Free");
	count++;
	}
	
	//Debugging, prints well
	cout << endl;
	cout << "Using best fit algorithm\n" <<endl;
	
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
				programList.addProgram(name, size, fit);//, fit
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
