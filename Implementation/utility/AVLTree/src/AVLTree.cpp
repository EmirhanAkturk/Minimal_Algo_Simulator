#ifndef _AVLTREE_CPP_
#define _AVLTREE_CPP_

#include "../inc/AVLTree.hpp"

using std:: max;

/* 
###################################
Template Specialization for Seconds
###################################
 */

AVLTree<Seconds>::Node* AVLTree<Seconds>::makeEmpty(Node *node){
    if(node == nullptr)
        return nullptr;
    
    else{
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return nullptr;
}


AVLTree<Seconds>::Node* AVLTree<Seconds>::insertNode(Node* node, const Seconds& newData){
    
    Node *query= searchNode(node,newData.timestamp);

    if(query!=nullptr){
        
        return node;
    }

    /* 1. Perform the normal BST insertion */
    if(node == nullptr)
    {
        Node *temp=new Node(newData);
        return temp;
    }

    if(newData.timestamp < node->timestamp){
        node->left = insertNode(node->left,newData);
    }

    else if(newData.timestamp > node->timestamp){
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


AVLTree<Seconds>::Node* AVLTree<Seconds>::removeNode(Node* node,uint32_t timestamp) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(timestamp < node->timestamp)
        node->left = removeNode(node->left,timestamp);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(timestamp > node->timestamp)
        node->right = removeNode(node->right,timestamp);
    
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
            node->timestamp=temp->timestamp;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->timestamp);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}


AVLTree<Seconds>::Node* AVLTree<Seconds>::searchNode(Node* node, uint32_t timestamp) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->timestamp == timestamp)
        return node;
        
    else if(timestamp > node->timestamp)
        return searchNode(node->right, timestamp);

    else return searchNode(node->left, timestamp);

}


AVLTree<Seconds>::Node* AVLTree<Seconds>::findMin(Node* node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}


AVLTree<Seconds>::Node * AVLTree<Seconds>::findMax(Node* node) {
    if(node == nullptr)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}


AVLTree<Seconds>::Node* AVLTree<Seconds>::doBalanced(Node *node){
    
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


AVLTree<Seconds>::Node* AVLTree<Seconds>::doBalanced(Node *node,const Seconds& newData){

    int balance = getBalance(node);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newData.timestamp < node->left->timestamp) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && newData.timestamp > node->right->timestamp) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && newData.timestamp > node->left->timestamp) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && newData.timestamp < node->right->timestamp) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}


AVLTree<Seconds>::Node * AVLTree<Seconds>::rightRotate(Node *node) 
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


AVLTree<Seconds>::Node * AVLTree<Seconds>::leftRotate(Node *node) 
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


int AVLTree<Seconds>:: getBalance(Node* node){
    if (node == NULL) 
        return 0; 
    return height(node->left) - height(node->right); 
}


int AVLTree<Seconds>::height(Node *node) 
{ 
    if (node == nullptr) 
        return 0; 

    return node->height; 
} 


void AVLTree<Seconds>::inorder(Node* node)const{
    if(node == nullptr)
        return;

    inorder(node->left);
    cout << node->timestamp<<endl;
    inorder(node->right);
}


void AVLTree<Seconds>::preorder(Node* node)const{
    if(node == nullptr)
        return;

    cout << node->timestamp<<endl;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<Seconds>::postorder(Node* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->timestamp<<endl;
}


void  AVLTree<Seconds>::writeInorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->timestamp<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<Seconds>::writePreorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->timestamp<<endl;


    // then deal with the left subtree
    writePreorder(node->left,outFile);

    // now recur on right subtree 
    writePreorder(node->right,outFile);
}


void  AVLTree<Seconds>::writePostorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(node->left,outFile);
    
    // now recur on right subtree 
    writePostorder(node->right,outFile);
    
    // then deal with the Node 
    outFile << node->timestamp<<endl;

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
            query->timestamp=newData.timestamp;//update timestamp value
            query->nanosecond=newData.nanosecond;//update nanosecond value
            query->quantity=newData.quantity;//update quantity value
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
            node->timestamp=temp->timestamp;
            node->nanosecond=temp->nanosecond;
            node->orderId=temp->orderId;
            node->quantity=temp->quantity;
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
    cout<< node->timestamp<<";"<< node->nanosecond<<";"<<node->orderId<<";"
        <<node->quantity<<";"<<node->orderPrice<<endl;
    inorder(node->right);
}


void AVLTree<AddOrder>::preorder(Node* node)const{
    if(node == nullptr)
        return;

    cout<< node->timestamp<<";"<< node->nanosecond<<";"<<node->orderId<<";"
        <<node->quantity<<";"<<node->orderPrice<<endl;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<AddOrder>::postorder(Node* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout<< node->timestamp<<";"<< node->nanosecond<<";"<<node->orderId<<";"
        <<node->quantity<<";"<<node->orderPrice<<endl;
    
}


void  AVLTree<AddOrder>::writeInorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->timestamp<<";"<<node->nanosecond<<";"<<node->orderId<<";"
            <<node->quantity<<";"<<node->orderPrice<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<AddOrder>::writeItrPreorder(Node * root,ofstream & outFile)const{
    
    if (root == NULL) 
       return; 
  
    // Create an empty stack and push root to it 
    std::stack<Node *> nodeStack; 
    nodeStack.push(root); 
  
    /* Pop all items one by one. Do following for every popped item 
       a) print it 
       b) push its right child 
       c) push its left child 
    Note that right child is pushed first so that left is processed first */
    while (nodeStack.empty() == false) 
    { 
        // Pop the top item from stack and print it 
        Node *node = nodeStack.top(); 

        outFile << node->timestamp<<";"<<node->nanosecond<<";"<<node->orderId<<";"
                <<node->quantity<<";"<<node->orderPrice<<endl;

        nodeStack.pop(); 
  
        // Push right and left children of the popped node to stack 
        if (node->right) 
            nodeStack.push(node->right); 
        if (node->left) 
            nodeStack.push(node->left); 
    } 
}

void  AVLTree<AddOrder>::writePreorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->timestamp<<";"<<node->nanosecond<<";"<<node->orderId<<";"
            <<node->quantity<<";"<<node->orderPrice<<endl;

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
    outFile << node->timestamp<<";"<<node->nanosecond<<";"<<node->orderId<<";"
            <<node->quantity<<";"<<node->orderPrice<<endl;

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
            node->nanosecond=temp->nanosecond;
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
    cout <<node->nanosecond<<";"<<node->orderId<<endl;
    inorder(node->right);
}


void AVLTree<OrderExecuted>::preorder(Node* node)const{
    if(node == nullptr)
        return;

    cout <<node->nanosecond<<";"<<node->orderId<<endl;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<OrderExecuted>::postorder(Node* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout <<node->nanosecond<<";"<<node->orderId<<endl;
}


void  AVLTree<OrderExecuted>::writeInorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile <<node->nanosecond<< ";"<<node->orderId<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<OrderExecuted>::writePreorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile <<node->nanosecond<< ";"<<node->orderId<<endl;

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
    outFile <<node->nanosecond<< ";"<<node->orderId<<endl;

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
            node->nanosecond=temp->nanosecond;
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
    cout << node->nanosecond<< ";" <<node->orderId<<endl;
    inorder(node->right);
}


void AVLTree<OrderDelete>::preorder(Node* node)const{
    if(node == nullptr)
        return;

    cout << node->nanosecond<< ";" <<node->orderId<<endl;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<OrderDelete>::postorder(Node* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->nanosecond<< ";" <<node->orderId<<endl;
}


void  AVLTree<OrderDelete>::writeInorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->nanosecond<< ";"<<node->orderId<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<OrderDelete>::writePreorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->nanosecond<< ";"<<node->orderId<<endl;


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
    outFile << node->nanosecond<< ";"<<node->orderId<<endl;

}

#endif