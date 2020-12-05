// C++ Program for RUN LENGTH ENCODING

#include<iostream>
#include <fstream>
using namespace std;

// A linked list node
struct Node {
	char data;
	struct Node* next;
	Node(int x)
	{
		data = x;
		next = NULL;
	}
};

// Function to append nodes to a list
void append(struct Node* head_ref, char new_data)
{
	struct Node* new_node = new Node(new_data);

	struct Node* last = head_ref;

	if (head_ref == NULL) {
		head_ref = new_node;
		return;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;
	return;
}

// Function to write into text file
void writeList(Node* node)
{
    ofstream filestream("test_out.txt",ios::app);
	while (node != NULL) {
        if (filestream.is_open())
        {
            filestream << node->data;
        }
        else
        {
            cout <<"File opening is fail.";
        }
        node = node->next;
	}
	filestream<<"\n";
    filestream.close();
}

// Function to encode the list
void RLE(Node* head)
{
	// Pointer used to traverse through
	// all the nodes in the list
	Node* p = head;

	// List to store the encoded message
	Node* temp = new Node(p->data);

	// Store the first character in c
	char c = p->data;
	p = p->next;

	// Count to count the number of
	// continuous elements
	int count = 1;

	// Taverse through all the
	// elements in the list
	while (p != NULL) {

		// Store the current character in x
		char x = p->data;

		// If the characters are same
		if (c == x)
			// Increment count
			count++;
		// Else
		else {

			// If the count is greater than 1
			if (count > 1) {

				// Append the count to list
				if (count > 9)
					append(temp, '0' + (count / 10));

				append(temp, '0' + (count % 10));
			}

			// Reset the count
			count = 1;

			// Add the next character
			// to the list
			append(temp, x);

			// Take the character to check as
			// the current character
			c = x;
		}
		p = p->next;
	}

	// Add the final count
	if (count >1)
		append(temp, '0' + count);

	// Write the list
	writeList(temp);
}

// Main Function
int main()
{
    string srg;
    ifstream filestream("test_in.txt");
    if (filestream.is_open())
    {
      cout<<"\nDATA IN INPUT TEXT FILE\n";
      while ( getline (filestream,srg) )
      {
          cout << srg <<endl;

          // Creating the linked list
          Node* head = new Node(srg[0]);
          head->next = new Node(srg[1]);
	      head->next->next = new Node(srg[2]);
          head->next->next->next = new Node(srg[3]);
          head->next->next->next->next = new Node(srg[4]);
	      head->next->next->next->next->next = new Node(srg[5]);
          head->next->next->next->next->next->next = new Node(srg[6]);
          RLE(head);
      }
    filestream.close();
    }
    else {
      cout << "Input File opening has failed."<<endl;
    }


    ifstream file("test_out.txt");
    if (file.is_open())
    {
        cout<<"\nDATA IN OUTPUT TEXT FILE\n";
        while ( getline (file,srg) )
        {
          cout << srg <<endl;
        }
        file.close();
    }
    else {
      cout << "Output File opening has failed."<<endl;
    }
	return 0;
}

