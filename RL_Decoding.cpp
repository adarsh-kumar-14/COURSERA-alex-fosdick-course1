// C++ Program for RUN LENGTH DECODING

#include<iostream>
#include <fstream>
using namespace std;

// Linked list node
struct node {
    char data;
    node* next;
};

// Function to add a new node to the Linked List
node* add(char data)
{
    node* newnode = new node;
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

// Function to decode the linked list
string RLD(node* head)
{
	node* p = head;
	string res = "";
	int count;

	// While there are nodes left
	while (p) {
		// To store the count by which the current
		// character needs to be repeated
		count = 0;

		// Get the current character
		char c = p->data;
		if (p->next) {
			node* temp = p->next;

			// If current node is a digit
			if (temp && temp->data >= '0' && temp->data <= '9')
            {
				// Generate the integer from
				// the consecutive digits
				while (temp && temp->data >= '0' && temp->data <= '9') {
					count = count * 10 + (temp->data - '0');
					temp = temp->next;
				}
				p = temp;
			}
			else {
				count = 1;
				p = p->next;
			}
		}
		else {
			count = 1;
			p = p->next;
		}

		// Repeat the character count times
		for (int i = 0; i < count; i++) {
			res += c;
		}
	}

	ofstream filestream("test_out_out.txt",ios::app);
    if (filestream.is_open())
    {
        filestream << res;
    }
    else
    {
        cout <<"File opening is fail.";
    }
	filestream<<"\n";
    filestream.close();

	return res;
}

node* string_to_linkedList(string text, node* head)
{
    head = add(text[0]);
    node* curr = head;

    // curr pointer points to the current node
    // where the insertion should take place
    for (int i = 1; i < text.size(); i++) {
        curr->next = add(text[i]);
        curr = curr->next;
    }
    return head;
}

// Driver code
int main()
{
    string text;
    ifstream filestream("test_out.txt");
    if (filestream.is_open())
    {
      cout<<"\nDATA IN OUTPUT TEXT FILE\n";
      while ( getline (filestream,text) )
      {
          cout << text <<endl;
          node* head = NULL;
          head = string_to_linkedList(text, head);
          RLD(head);
      }
      filestream.close();
    }
    else {
      cout << "Input File opening has failed."<<endl;
    }
    ifstream file("test_out_out.txt");
    if (file.is_open())
    {
        cout<<"\nDATA IN FINAL OUTPUT TEXT FILE\n";
        while ( getline (file,text) )
        {
          cout << text <<endl;
        }
        file.close();
    }
    else {
      cout << "Output File opening has failed."<<endl;
    }
	return 0;
}


