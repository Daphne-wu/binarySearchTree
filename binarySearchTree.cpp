//Daphne Wu 
//This program creates binary trees :)
#include <iostream>
#include <cstring>


// In general, make sure that you can add, remove, and print in any order. I should be able to add five numbers, remove a couple of them, print the tree, add a couple more, print the tree, delete one, etc.

// Visual shows binary search tree correctly:  10 points

// Numbers are entered correctly:  10 points

// Numbers are removed correctly:  10 points

// Can ask the tree if a number is contained in it. (Search): 5 points


using namespace std;


// a struct for node more accessible
struct Node {
    int data;
    Node* right;
    Node* left;
};

//function prototypes
void sortArray(int array[], int size);
void visual(Node* root, int spacing);
bool search(Node* root, int value, bool &result);
Node* addNode(Node* root, int value);
void sortArray(int array[], int size);
Node* removeNode(Node* root, int value);
Node* minValueNode(Node* root);

int main () {

	int inputNumbers;
	char* input = new char();
	int array[100];
	memset(array, -1, 100);

	cout << "Good morning/afternoon/evening! Here we create binary trees :). How would you like to input numbers? Type: 'FILE' or 'CONSOLE'" << endl;
	cin.getline(input, 80, '\n');
	cout << "How many numbers would you like to input into the tree?" << endl;
	cin >> inputNumbers;
	cin.get();


	//if the user wants to enter by console (manual input) then do the following
	if (strcmp(input, "CONSOLE") == 0) {
		// int number;
		//read in every number inputed
		cout << "Enter " << inputNumbers << " number's seperated by a space." << endl;
		for (int i = 0; i < inputNumbers; i++) {
			cin >> array[i];
		}
		cin.get();
		//used to check input
		// for (int i = 0; i < inputNumbers; i++) {
		// 	cout << array[i];
		// }
 	}
 	else if (strcmp(input, "FILE") == 0) {
 		cout << "Enter the file name. Currently available: 'inputNumbers.txt'" << endl;
 		char file[20];
 		cin.getline(file, 20, '\n');
 		//read file ant input into array
 		FILE* pFile = NULL;
        pFile = fopen(file, "r");
        if (pFile == NULL)
        {
            cout << "Error in opening the file Numbers.txt";
            return 0;
        }

        //store ints seperated by space into the integer array
        int index = 0;
        char line[1000];
        while(fgets(line, 1000, pFile)) { //read the line of the file
        	char* buffer = new char[20];
        	memset(buffer, '\0', 20); //set the buffer to the null character
        	int position = 0;
        	while (buffer != NULL) {
        		buffer = strchr(line + position, ' '); //finds first occurance of the space ands stores it in buffer
        		if (buffer != NULL) { //when there is a returned value to the buffer
	        		char lineBuffer[20]; 
	        		memset(lineBuffer, '\0', 20); //set the linebuffer to the null character
	        		strncpy(lineBuffer, line + position, sizeof(line - buffer)); //copy the string of whats before the occurance of the space into the lineBuffer, (line - buffer is where the information is stored (occurance))
	        		array[index++] = stoi(lineBuffer); //store the integer into the array at specified index
	        		position = (buffer-line) + 1; //move to the next position and repeat
	        	}

        	}
        }
 	}
 	  // else they didnt type a proper command, boo!
    else {
        cout << "Oops! You entered something incorrectly! :( Try again! :D";
        return 0;
    }
    
    //create the binary tree 
    Node* root = NULL;
    for (int i = 0; i < inputNumbers; i++) {
        root = addNode(root, array[i]);
    }

   	bool running = true;

   	while (running) {
   		cout << "What would you like to do? Enter: 'ADD', 'REMOVE', 'SEARCH', 'PRINT', 'QUIT'. " << endl;
   		cin.getline(input, 80, '\n');
   		//if they want to add
   		if (strcmp(input, "ADD") == 0) {
   			int number;
   			cout << "Enter the number you would like to add: ";
   			cin >> number;
   			cin.get();
   			//add node
   			root = addNode(root, number);
   			//print tree
   			visual(root, 0);
   		}
   		// if they would like to remove a node
      	else if (strcmp(input, "REMOVE") == 0) {
          	int number;
          	cout << "Enter the number would you like to remove: ";
          	cin >> number;
          	cin.get();
          	// remove function is called
          	root = removeNode(root, number);
          	// tree is printed
          	visual(root, 0);
     	}
     	else if (strcmp(input, "SEARCH") == 0) {
     		int number;
     		bool result = false;
     		cout << "Enter the number would you like to search: ";
     		cin >> number;
     		cin.get();
     		//return if found
     		 if (search(root, number, result) == true) {
              	cout << "This number is in the binary tree!" << endl;
              	visual(root, 0);
          	}
          	//otherwise tell user not found
          	else {
              	cout << "Whoops! Looks like that number isn't in the tree" << endl;
          	}
      	}
     	else if (strcmp(input, "PRINT") == 0) {
     		//print tree
     		visual(root, 0);
     	}
	     // else they want to quit the program
	     else if (strcmp(input, "QUIT") == 0) {
	        running = false;
	    }
 	 }
  		cout << "Thanks!";

  return 0;
}

//prints 2d binary tree using spaces to sepreate in between (sideways)
void visual(Node* root, int spacing) {
	if (root != NULL) {
        spacing = spacing + 10;
        visual(root->right, spacing);
        cout << endl;
        for (int i = 10; i < spacing; i++) {
            cout << " ";
        }
        cout << root->data << endl;
        visual(root->left, spacing);
    }
}

//function to add nodes
Node* addNode(Node* root, int value) {
	//if no node in tree insert it as root
	if (root == NULL) {
		Node* node = new Node();
		node->data = value;
		return node;
	}
	else {
		if (value < root->data) {
			root->left = addNode(root->left, value);
		}
		else {
			root->right = addNode(root->right, value);
		}
	}
	return root;
}
//function to return the smallest node in a subtree
Node* minValueNode(Node* root) {
    Node* current = root;
    while (current != NULL && current->left != NULL) {
        current = current->left;
    }
    return current;
}
//function to remove node
Node* removeNode(Node* root, int value) {
	//if tree is empty then stop
	if (root == NULL) {
		return root;
	}
	if (value < root->data) {
		root->left = removeNode(root->left, value);
	}
	else if (value > root->data) {
		root->right = removeNode(root->right, value);
	}
	//otherwise the value to be delete is found 
	else {
		//if doesnt have left child, then only need to save right child to temp and delete (at a specified root/node to be deleted)
		if (root->left == NULL) {
			Node* temp = root->right;
			delete root;
			return temp;
		}
		//otherwise save left child and delete
		else if (root->right == NULL) {
			Node* temp = root->right;
            delete root;
            return temp;
		}
		else {
		//other case is that it has two children
			//find smallest value in the subtreee
			Node* temp = minValueNode(root->right);
			//copy the smallest child's data into the root data 
			root->data = temp->data;
			//delete successor
			root->right = removeNode(root->right, temp->data);
		}
	}
	return root;

}

//recursively run though the different roots of the tree to determine whether the value is in the tree
bool search(Node* root, int value, bool &result) {
	//if value is larger than the root then goes to the right, otherwise goes to the left
	if (root != NULL) {
		if (root->data == value) {
			result = true;
		}
		else if (root->data < value) {
			search(root->right, value, result);
		}
		else {
			search(root->left, value, result);
		}
	}
	return result;
}

//sorts array smallest to largest
void sortArray(int array[], int size) {
	for (int i = 0; i < size; i++) {
		for(int j = i + 1; j < size; j++) {
			if (array[i] > array[j]) {
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}


