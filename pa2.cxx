#include <iostream>
#include <string>
using namespace std;

struct node
{
	int kilos[4] = {0,0,0,0}; //node data, 0 represent empty Kilo
	string data;
	node *next; //pointer to next node
};

class list
{
	private:
	node *head, *tail; 
	public:
	void display();
	void insert_start(string name, int size);
	
	list()//constructor
	{
		head=NULL;//make head and tail point to null, an empty list 
		tail=NULL;
	}
};

void list::display()
{
	node *temp = new node;
	temp=head;//put a new node in front of head by taking its place
	while(temp!=NULL)//as long as there's a valid pointer to next node
	{
		cout << temp->data <<"\t";
		for (int i=0;i<4;i++) 
		{
			cout<< temp->kilos[i] << ", ";
		} //prints the "kilo slots"
		if (temp->kilos[0] == 0) {cout<<"free";}
		
		temp=temp->next;//set temps address to that of next node to be printed 
	}
	

}

void list::insert_start(string name, int size)
{
	node *temp=new node;
	temp->data=name;
	temp->next=head;
	head = temp;
	
	for (int i=0; i<size; i++)
	{
		temp->kilos[i] = 1;
	}
}

int main(int argc, char ** argv)
{
	list obj;
	obj.insert_start("P1", 3);
	
	obj.display();	
	
	return 0;
}

