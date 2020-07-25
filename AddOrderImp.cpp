#include "AddOrderImp.h"

bool  AddOrderImp:: searchMessage(const string & line){
    istringstream sin(line);//sin ile string içinde gezilecek
    int flag=1;//1. sütündan başlanacak
    auto findColumn=[&flag,&sin](int collumn){//istenilen sütün bulunur
        char c;
        while(!sin.eof() && flag<collumn){
            sin>>c;
            if(c==';')
                ++flag;
        }
    };

    char messageType;
    findColumn(2);
    sin>>messageType;

    if(messageType=='A'){
        
        findColumn(4);
        sin>>orderId;
        findColumn(9);
        sin>>orderPrice;

        return true;
    }

    else return false;
       
}

void AddOrderImp::print(){
    cout<<orderId<<" "<<orderPrice<<endl;
}

Node* BinarySearchTree:: addNewNode(uint64_t newOrderId, uint64_t newOrderPrice){
    Node* newNode = new Node();
	newNode->orderId = newOrderId;
    newNode->orderPrice=newOrderPrice;
	newNode->left = newNode->right = nullptr;

    return newNode;
}

Node* BinarySearchTree::insertNode(Node* rootPtr,uint64_t orderId, uint64_t orderPrice){
    if(rootPtr==nullptr){//
        rootPtr=addNewNode(orderId,orderPrice);
        this->rootPtr=rootPtr;
        return rootPtr;
    }

    else if(orderPrice <= rootPtr->orderId){
        rootPtr->left = insertNode(rootPtr->left,orderId,orderPrice);
    }

    else{
        rootPtr->right = insertNode(rootPtr->right,orderId,orderPrice);
    }

    this->rootPtr=rootPtr;
    return rootPtr;
}

Node* BinarySearchTree::searchNode(Node* rootPtr,uint64_t orderId)const{
    if(rootPtr==nullptr || rootPtr->orderId == orderId) 
        return rootPtr;
    
    if(orderId<rootPtr->orderId)
        return searchNode(rootPtr->left,orderId);
    
    return searchNode(rootPtr->right, orderId);
}

/* 
Node* BinarySearchTree::searchNode(Node* rootPtr,uint32_t orderPrice)const{
    if(rootPtr==nullptr || rootPtr->orderId == orderPrice) 
        return rootPtr;
    
    if(orderPrice<rootPtr->orderId)
        return searchNode(rootPtr->left,orderPrice);
    
    return searchNode(rootPtr->right, orderPrice);
}
 */

Node* BinarySearchTree::minValueNode(Node* node)const{

    Node* current = node; 

	/* loop down to find the leftmost leaf */
	while (current && current->left != nullptr) 
		current = current->left; 

	return current; 

}

Node* BinarySearchTree::maxValueNode(Node* node)const{
    
    Node* current = node; 

	/* loop down to find the rightmost leaf */
	while (current && current->right != nullptr) 
		current = current->right; 

	return current; 
}

Node* BinarySearchTree::deleteNode(Node* rootPtr, uint64_t orderId) {
    //base case
    if(rootPtr==nullptr) return rootPtr;

    // If the key to be deleted is smaller than the root's key, 
	// then it lies in left subtree 
    if(orderId < rootPtr->orderId)    
        rootPtr->left = deleteNode(rootPtr->left, orderId);
    
    // If the key to be deleted is greater than the root's key, 
	// then it lies in right subtree 
    else if (orderId > rootPtr->orderId)
            rootPtr->right=deleteNode(rootPtr->right,orderId);
            
    // if key is same as root's key, then This is the node 
	// to be deleted 
    else{
        // node with only one child or no child 
        if(rootPtr->left == nullptr){
            Node* temp= rootPtr->right;
            delete rootPtr;
            return temp;
        }
        else if(rootPtr->right == nullptr){
            Node* temp = rootPtr->left;
            delete rootPtr;
            return temp;
        }

        // node with two children: Get the inorder successor (smallest 
		// in the right subtree)
        Node* temp = minValueNode(rootPtr->right);

        // Copy the inorder successor's content to this node 
        rootPtr->orderId = temp->orderId;

        // Delete the inorder successor 
        rootPtr->right = deleteNode(rootPtr->right, temp->orderId);

    }

    return rootPtr; 
}

void fileRead(ifstream &inFile, BinarySearchTree &tree){
    string line;
    AddOrderImp messageA;
    while(inFile>>line){
        messageA.searchMessage(line);
        
        //tree.setRoot( tree.insertNode(tree.getRoot(), messageA.getOrderId(),messageA.getOrderPrice()));
        tree.insertNode(tree.getRoot(), messageA.getOrderId(),messageA.getOrderPrice());
        if(line == ";")//tekrar bak
            break;
    }

}

void BinarySearchTree:: writePostorder(Node * rootPtr,ofstream &outFile)const{
    if (rootPtr == nullptr)
		return;

	// first recur on left subtree 
	writePostorder(rootPtr->left,outFile);

	// then recur on right subtree 
	writePostorder(rootPtr->right,outFile);

	// now deal with the node 
	outFile << rootPtr->orderId <<";"<<rootPtr->orderPrice<<endl;
}

void BinarySearchTree:: writeInorder(Node * rootPtr,ofstream & outFile)const{
    if(rootPtr == nullptr)
        return;
    
    // first recur on left subtree 
	writeInorder(rootPtr->left,outFile);

	// then deal with the node 
	outFile << rootPtr->orderId <<";"<<rootPtr->orderPrice<<endl;

	// now recur on right subtree 
	writeInorder(rootPtr->right,outFile);
    
}

void BinarySearchTree::printPostorder(Node * rootPtr)const{
    if (rootPtr == nullptr)
		return;

	// first recur on left subtree 
	printPostorder(rootPtr->left);

	// then recur on right subtree 
	printPostorder(rootPtr->right);

	// now deal with the node 
	cout << rootPtr->orderId <<";"<<rootPtr->orderPrice<<endl;
}

void BinarySearchTree::printInorder(Node * rootPtr)const{
    if(rootPtr == nullptr)
        return;
    
    // first recur on left subtree 
	printInorder(rootPtr->left);

	// then deal with the node 
	cout << rootPtr->orderId <<";"<<rootPtr->orderPrice<<endl;

	// now recur on right subtree 
	printInorder(rootPtr->right);
    
}