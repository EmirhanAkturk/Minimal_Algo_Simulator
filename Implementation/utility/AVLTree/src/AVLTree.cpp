#ifndef _AVLTREE_INL_
#define _AVLTREE_INL_

#include "../include/AVLTree.hpp"

AVLTree<AddOrder> AddOrderTree;
AVLTree<OrderDelete> OrderDeleteTree;
AVLTree<OrderExecuted> OrderExecutedTree;

template<class T>
inline void addMessage(AVLTree<T>& tree,const T& message){
    tree.insert(message);
}

void fileRead(const char * file ){

    ifstream inFile(file);
    while(!inFile.eof()){
        // clock_t start=clock();
        string line=readLine(inFile);
        findValues(line);
    
        // if(line == ";")//tekrar bak
        //         break; */
    }

}

inline string readLine(ifstream& inFile){
    string line;
    inFile>>line;
    return line;
}


void  findValues(const string & line){
    istringstream inString(line);

    int flag=1;
    flag=findColumn(inString,flag,2);
    
    if(flag!=2){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    char c;
    inString>>c;

    switch(c){
        case ADD_ORDER_TYPE: fileAddOrder(inString,flag);
            break;
        
        case ORDER_EXECUTED_TYPE: fileOrderExecute(inString,flag);
            break;

        case ORDER_DELETE_TYPE: fileOrderDelete(inString,flag);
            break;
        
        default:
            cout<<"invalid message type!!\n";
            
    }
        
        
}


int findColumn(istringstream& inString,int flag,int collumn){
    char c;
    while(!inString.eof() && flag<collumn){
        inString>>c;
        if(c==';')
            ++flag;
    }

    return flag;
}


void fileAddOrder(istringstream &inString,int flag){
    
    AddOrder messageA;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageA.orderId;

    flag=findColumn(inString,flag,9);
    if(flag!=9){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageA.orderPrice;

    //AddOrderTree.insert(messageA);
    addMessage(AddOrderTree,messageA);
}


void fileOrderExecute(istringstream &inString,int flag){
    OrderExecuted messageE;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    inString>>messageE.orderId;

    //OrderExecutedTree.insert(messageE);
    addMessage(OrderExecutedTree,messageE);
}


void fileOrderDelete(istringstream &inString,int flag){
    OrderDelete messageD;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    inString>>messageD.orderId;

    //OrderDeleteTree.insert(messageD);
    addMessage(OrderDeleteTree,messageD);
}

/* 
###################################
Template Specialization for AddOrder
###################################
 */


AVLTree<AddOrder>::Node* AVLTree<AddOrder>::makeEmpty(Node *node){
    if(node == nullptr)
        return nullptr;
    
    else{
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return nullptr;
}


AVLTree<AddOrder>::Node * AVLTree<AddOrder>::insertNode(Node * node, const AddOrder& newData){
    
    Node *query= searchNode(node,newData.orderId);

    //if already exist ,check if the price is different
    if(query!=nullptr){
        if(query->orderPrice != newData.orderPrice){
            query->orderPrice=newData.orderPrice;//update price value
        }
        
        return node;
    }

    /* 1. Perform the normal BST insertion */
    if(node == nullptr)
    {
        Node *temp=new Node(newData);
        return temp;
    }

    if(newData.orderId < node->orderId){
        node->left = insertNode(node->left,newData);
    }

    else if(newData.orderId > node->orderId){
        node->right = insertNode(node->right, newData);
    }   
    
    else return node;

    /* 2. Update height of this ancestor Node */
    node->height=max(height(node->left), height(node->right))+1;

    /* 3. Get the balance factor of this ancestor 
    Node to check whether this Node became 
    unbalanced */
    
    return doBalanced(node,newData);
}

AVLTree<AddOrder>::Node* AVLTree<AddOrder>::removeNode(Node* node,uint64_t orderId) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(orderId < node->orderId)
        node->left = removeNode(node->left,orderId);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(orderId > node->orderId)
        node->right = removeNode(node->right,orderId);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node * temp;

            if(node->left == nullptr){
                temp = node->right;
                delete node;
            }
            else{
                temp=node->left;
                delete node;
            }

            // No child case
            if(temp == nullptr){
                temp = node;
                node = nullptr;
            }

            else {// One child case
                node = temp; // Copy the contents of the non-empty child
                temp = nullptr;
            }
            //temp = nullptr;

        }
        else{
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)

            Node * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->orderId=temp->orderId;
            node->orderPrice=temp->orderPrice;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->orderId);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}

AVLTree<AddOrder>::Node* AVLTree<AddOrder>::searchNode(Node* node, uint64_t orderId) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->orderId == orderId)
        return node;
        
    else if(orderId > node->orderId)
        return searchNode(node->right, orderId);

    else return searchNode(node->left, orderId);

}

AVLTree<AddOrder>::Node* AVLTree<AddOrder>::findMin(Node* node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}


AVLTree<AddOrder>::Node * AVLTree<AddOrder>::findMax(Node* node) {
    if(node == nullptr)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}


AVLTree<AddOrder>::Node* AVLTree<AddOrder>::doBalanced(Node *node){
    
    int balance = getBalance(node);
    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && getBalance(node->left)>=0) 
        return rightRotate(node); 

    // Left Right Case 
    if (balance > 1 && getBalance(node->left)<0) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Right Case 
    if (balance < -1 && getBalance(node->right)<=0) 
        return leftRotate(node); 

    // Right Left Case 
    if (balance < -1 && getBalance(node->left)>0) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    /* return the (unchanged) Node pointer */
    return node;

}


AVLTree<AddOrder>::Node* AVLTree<AddOrder>::doBalanced(Node *node,const AddOrder& newData){

    int balance = getBalance(node);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newData.orderId < node->left->orderId) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && newData.orderId > node->right->orderId) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && newData.orderId > node->left->orderId) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && newData.orderId < node->right->orderId) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}


AVLTree<AddOrder>::Node * AVLTree<AddOrder>::rightRotate(Node *node) 
{ 
    Node *x = node->left; 
    Node *T2 = x->right; 

    // Perform rotation 
    x->right = node; 
    node->left = T2; 

    // Update heights 
    node->height = max(height(node->left), 
                    height(node->right)) + 1; 

    x->height = max(height(x->left), 
                    height(x->right)) + 1; 

    // Return new root 
    return x; 
} 


AVLTree<AddOrder>::Node * AVLTree<AddOrder>::leftRotate(Node *node) 
{ 
    Node *y = node->right; 
    Node *x = y->left; 

    // Perform rotation 
    y->left = node; 
    node->right = x; 

    // Update heights 
    node->height = max(height(node->left),	 
                    height(node->right)) + 1; 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 

    // Return new root 
    return y; 
} 

/* void AVLTree<AddOrder>:: fileRead(const char * file ){

    ifstream inFile(file);
    while(!inFile.eof()){
        // clock_t start=clock();
        string line=readLine(inFile);
        findValues(line);
    
        // if(line == ";")//tekrar bak
        //         break; 
    }

} */

int AVLTree<AddOrder>:: getBalance(Node* node){
    if (node == NULL) 
        return 0; 
    return height(node->left) - height(node->right); 
}


int AVLTree<AddOrder>::height(Node *node) 
{ 
    if (node == nullptr) 
        return 0; 

    return node->height; 
} 


void AVLTree<AddOrder>::inorder(Node* node)const{
    if(node == nullptr)
        return;

    inorder(node->left);
    cout << node->orderId<<";"<<node->orderPrice<<endl;
    inorder(node->right);
}


void AVLTree<AddOrder>::preorder(Node* node)const{
    if(node == nullptr)
        return;

    cout << node->orderId<<";"<<node->orderPrice<<endl;;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<AddOrder>::postorder(Node* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->orderId<<";"<<node->orderPrice<<endl;;
}


void  AVLTree<AddOrder>::writeInorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->orderId<<";"<<node->orderPrice<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<AddOrder>::writePreorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->orderId<<";"<<node->orderPrice<<endl;

    // then deal with the left subtree
    writePreorder(node->left,outFile);

    // now recur on right subtree 
    writePreorder(node->right,outFile);
}


void  AVLTree<AddOrder>::writePostorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(node->left,outFile);
    
    // now recur on right subtree 
    writePostorder(node->right,outFile);
    
    // then deal with the Node 
    outFile << node->orderId<<";"<<node->orderPrice<<endl;

}


/* 
###################################
Template Specialization for OrderExecuted
###################################
 */

AVLTree<OrderExecuted>::Node* AVLTree<OrderExecuted>::makeEmpty(Node *node){
    if(node == nullptr)
        return nullptr;
    
    else{
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return nullptr;
}


AVLTree<OrderExecuted>::Node* AVLTree<OrderExecuted>::insertNode(Node* node, const OrderExecuted& newData){
    
    Node *query= searchNode(node,newData.orderId);

    if(query!=nullptr){
        
        return node;
    }

    /* 1. Perform the normal BST insertion */
    if(node == nullptr)
    {
        Node *temp=new Node(newData);
        return temp;
    }

    if(newData.orderId < node->orderId){
        node->left = insertNode(node->left,newData);
    }

    else if(newData.orderId > node->orderId){
        node->right = insertNode(node->right, newData);
    }   
    
    else return node;

    /* 2. Update height of this ancestor Node */
    node->height=max(height(node->left), height(node->right))+1;

    /* 3. Get the balance factor of this ancestor 
    Node to check whether this Node became 
    unbalanced */
    
    return doBalanced(node,newData);
}


AVLTree<OrderExecuted>::Node* AVLTree<OrderExecuted>::removeNode(Node* node,uint64_t orderId) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(orderId < node->orderId)
        node->left = removeNode(node->left,orderId);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(orderId > node->orderId)
        node->right = removeNode(node->right,orderId);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node * temp;

            if(node->left == nullptr){
                temp = node->right;
                delete node;
            }
            else{
                temp=node->left;
                delete node;
            }

            // No child case
            if(temp == nullptr){
                temp = node;
                node = nullptr;
            }

            else {// One child case
                node = temp; // Copy the contents of the non-empty child
                temp = nullptr;
            }
            //temp = nullptr;

        }
        else{
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)

            Node * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->orderId=temp->orderId;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->orderId);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}


AVLTree<OrderExecuted>::Node* AVLTree<OrderExecuted>::searchNode(Node* node, uint64_t orderId) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->orderId == orderId)
        return node;
        
    else if(orderId > node->orderId)
        return searchNode(node->right, orderId);

    else return searchNode(node->left, orderId);

}


AVLTree<OrderExecuted>::Node* AVLTree<OrderExecuted>::findMin(Node* node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}


AVLTree<OrderExecuted>::Node * AVLTree<OrderExecuted>::findMax(Node* node) {
    if(node == nullptr)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}


AVLTree<OrderExecuted>::Node* AVLTree<OrderExecuted>::doBalanced(Node *node){
    
    int balance = getBalance(node);
    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && getBalance(node->left)>=0) 
        return rightRotate(node); 

    // Left Right Case 
    if (balance > 1 && getBalance(node->left)<0) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Right Case 
    if (balance < -1 && getBalance(node->right)<=0) 
        return leftRotate(node); 

    // Right Left Case 
    if (balance < -1 && getBalance(node->left)>0) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    /* return the (unchanged) Node pointer */
    return node;

}


AVLTree<OrderExecuted>::Node* AVLTree<OrderExecuted>::doBalanced(Node *node,const OrderExecuted& newData){

    int balance = getBalance(node);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newData.orderId < node->left->orderId) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && newData.orderId > node->right->orderId) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && newData.orderId > node->left->orderId) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && newData.orderId < node->right->orderId) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}


AVLTree<OrderExecuted>::Node * AVLTree<OrderExecuted>::rightRotate(Node *node) 
{ 
    Node *x = node->left; 
    Node *T2 = x->right; 

    // Perform rotation 
    x->right = node; 
    node->left = T2; 

    // Update heights 
    node->height = max(height(node->left), 
                    height(node->right)) + 1; 

    x->height = max(height(x->left), 
                    height(x->right)) + 1; 

    // Return new root 
    return x; 
} 


AVLTree<OrderExecuted>::Node * AVLTree<OrderExecuted>::leftRotate(Node *node) 
{ 
    Node *y = node->right; 
    Node *x = y->left; 

    // Perform rotation 
    y->left = node; 
    node->right = x; 

    // Update heights 
    node->height = max(height(node->left),	 
                    height(node->right)) + 1; 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 

    // Return new root 
    return y; 
} 


int AVLTree<OrderExecuted>:: getBalance(Node* node){
    if (node == NULL) 
        return 0; 
    return height(node->left) - height(node->right); 
}


int AVLTree<OrderExecuted>::height(Node *node) 
{ 
    if (node == nullptr) 
        return 0; 

    return node->height; 
} 


void AVLTree<OrderExecuted>::inorder(Node* node)const{
    if(node == nullptr)
        return;

    inorder(node->left);
    cout << node->orderId<<endl;
    inorder(node->right);
}


void AVLTree<OrderExecuted>::preorder(Node* node)const{
    if(node == nullptr)
        return;

    cout << node->orderId<<endl;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<OrderExecuted>::postorder(Node* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->orderId<<endl;
}


void  AVLTree<OrderExecuted>::writeInorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->orderId<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<OrderExecuted>::writePreorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->orderId<<endl;

    // then deal with the left subtree
    writePreorder(node->left,outFile);

    // now recur on right subtree 
    writePreorder(node->right,outFile);
}


void  AVLTree<OrderExecuted>::writePostorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(node->left,outFile);
    
    // now recur on right subtree 
    writePostorder(node->right,outFile);
    
    // then deal with the Node 
    outFile << node->orderId<<endl;

}




/* 
###################################
Template Specialization for OrderDelete
###################################
 */

AVLTree<OrderDelete>::Node* AVLTree<OrderDelete>::makeEmpty(Node *node){
    if(node == nullptr)
        return nullptr;
    
    else{
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return nullptr;
}


AVLTree<OrderDelete>::Node* AVLTree<OrderDelete>::insertNode(Node* node, const OrderDelete& newData){
    
    Node *query= searchNode(node,newData.orderId);

    if(query!=nullptr){
        
        return node;
    }

    /* 1. Perform the normal BST insertion */
    if(node == nullptr)
    {
        Node *temp=new Node(newData);
        return temp;
    }

    if(newData.orderId < node->orderId){
        node->left = insertNode(node->left,newData);
    }

    else if(newData.orderId > node->orderId){
        node->right = insertNode(node->right, newData);
    }   
    
    else return node;

    /* 2. Update height of this ancestor Node */
    node->height=max(height(node->left), height(node->right))+1;

    /* 3. Get the balance factor of this ancestor 
    Node to check whether this Node became 
    unbalanced */
    
    return doBalanced(node,newData);
}


AVLTree<OrderDelete>::Node* AVLTree<OrderDelete>::removeNode(Node* node,uint64_t orderId) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(orderId < node->orderId)
        node->left = removeNode(node->left,orderId);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(orderId > node->orderId)
        node->right = removeNode(node->right,orderId);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node * temp;

            if(node->left == nullptr){
                temp = node->right;
                delete node;
            }
            else{
                temp=node->left;
                delete node;
            }

            // No child case
            if(temp == nullptr){
                temp = node;
                node = nullptr;
            }

            else {// One child case
                node = temp; // Copy the contents of the non-empty child
                temp = nullptr;
            }
            //temp = nullptr;

        }
        else{
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)

            Node * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->orderId=temp->orderId;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->orderId);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}


AVLTree<OrderDelete>::Node* AVLTree<OrderDelete>::searchNode(Node* node, uint64_t orderId) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->orderId == orderId)
        return node;
        
    else if(orderId > node->orderId)
        return searchNode(node->right, orderId);

    else return searchNode(node->left, orderId);

}


AVLTree<OrderDelete>::Node* AVLTree<OrderDelete>::findMin(Node* node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}


AVLTree<OrderDelete>::Node * AVLTree<OrderDelete>::findMax(Node* node) {
    if(node == nullptr)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}


AVLTree<OrderDelete>::Node* AVLTree<OrderDelete>::doBalanced(Node *node){
    
    int balance = getBalance(node);
    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && getBalance(node->left)>=0) 
        return rightRotate(node); 

    // Left Right Case 
    if (balance > 1 && getBalance(node->left)<0) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Right Case 
    if (balance < -1 && getBalance(node->right)<=0) 
        return leftRotate(node); 

    // Right Left Case 
    if (balance < -1 && getBalance(node->left)>0) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    /* return the (unchanged) Node pointer */
    return node;

}


AVLTree<OrderDelete>::Node* AVLTree<OrderDelete>::doBalanced(Node *node,const OrderDelete& newData){

    int balance = getBalance(node);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newData.orderId < node->left->orderId) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && newData.orderId > node->right->orderId) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && newData.orderId > node->left->orderId) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && newData.orderId < node->right->orderId) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}


AVLTree<OrderDelete>::Node * AVLTree<OrderDelete>::rightRotate(Node *node) 
{ 
    Node *x = node->left; 
    Node *T2 = x->right; 

    // Perform rotation 
    x->right = node; 
    node->left = T2; 

    // Update heights 
    node->height = max(height(node->left), 
                    height(node->right)) + 1; 

    x->height = max(height(x->left), 
                    height(x->right)) + 1; 

    // Return new root 
    return x; 
} 


AVLTree<OrderDelete>::Node * AVLTree<OrderDelete>::leftRotate(Node *node) 
{ 
    Node *y = node->right; 
    Node *x = y->left; 

    // Perform rotation 
    y->left = node; 
    node->right = x; 

    // Update heights 
    node->height = max(height(node->left),	 
                    height(node->right)) + 1; 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 

    // Return new root 
    return y; 
} 


int AVLTree<OrderDelete>:: getBalance(Node* node){
    if (node == NULL) 
        return 0; 
    return height(node->left) - height(node->right); 
}


int AVLTree<OrderDelete>::height(Node *node) 
{ 
    if (node == nullptr) 
        return 0; 

    return node->height; 
} 


void AVLTree<OrderDelete>::inorder(Node* node)const{
    if(node == nullptr)
        return;

    inorder(node->left);
    cout << node->orderId<<endl;
    inorder(node->right);
}


void AVLTree<OrderDelete>::preorder(Node* node)const{
    if(node == nullptr)
        return;

    cout << node->orderId<<endl;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<OrderDelete>::postorder(Node* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->orderId<<endl;
}


void  AVLTree<OrderDelete>::writeInorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->orderId<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<OrderDelete>::writePreorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->orderId<<endl;

    // then deal with the left subtree
    writePreorder(node->left,outFile);

    // now recur on right subtree 
    writePreorder(node->right,outFile);
}


void  AVLTree<OrderDelete>::writePostorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(node->left,outFile);
    
    // now recur on right subtree 
    writePostorder(node->right,outFile);
    
    // then deal with the Node 
    outFile << node->orderId<<endl;

}

#endif