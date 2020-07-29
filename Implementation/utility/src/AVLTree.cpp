#include "../include/AVLTree.h"

Node* AVLTree::makeEmpty(Node* t) {
    if(t == nullptr)
        return nullptr;
    
    else{
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    return nullptr;
}

int AVLTree::height(Node *t) 
{ 
    if (t == nullptr) 
        return 0; 

    return t->height; 
} 

int AVLTree::getBalance(Node *t) 
{ 
    if (t == NULL) 
        return 0; 
    return height(t->left) - height(t->right); 
} 

Node* AVLTree::doBalanced(Node *t,uint64_t newOrderId){

    int balance = getBalance(t);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newOrderId < t->left->orderId) 
        return rightRotate(t); 

    // Right Right Case 
    if (balance < -1 && newOrderId > t->right->orderId) 
        return leftRotate(t); 

    // Left Right Case 
    if (balance > 1 && newOrderId > t->left->orderId) 
    { 
        t->left = leftRotate(t->left); 
        return rightRotate(t); 
    } 

    // Right Left Case 
    if (balance < -1 && newOrderId < t->right->orderId) 
    { 
        t->right = rightRotate(t->right); 
        return leftRotate(t); 
    } 

    return t;
}

Node* AVLTree::doBalanced(Node *t){
    
    int balance = getBalance(t);
    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && getBalance(t->left)>=0) 
        return rightRotate(t); 

    // Left Right Case 
    if (balance > 1 && getBalance(t->left)<0) 
    { 
        t->left = leftRotate(t->left); 
        return rightRotate(t); 
    } 

    // Right Right Case 
    if (balance < -1 && getBalance(t->right)<=0) 
        return leftRotate(t); 

    // Right Left Case 
    if (balance < -1 && getBalance(t->left)>0) 
    { 
        t->right = rightRotate(t->right); 
        return leftRotate(t); 
    } 

    /* return the (unchanged) Node pointer */
    return t;

}

// Node* AVLTree::newNode(uint64_t newOrderId,uint32_t newOrderPrice) 
// { 
//     Node* temp = new Node; 

//     temp->orderId = newOrderId; 
//     temp->orderPrice = newOrderPrice; 

//     temp->height=0;
//     temp->left = nullptr; 
//     temp->right = nullptr; 

//     return temp; 
// }  
    

Node* AVLTree::insertNode( Node* t,uint64_t newOrderId,uint32_t newOrderPrice)
{
    Node* query= find(t,newOrderId);

    if(query!=nullptr){
        if(query->orderPrice!=newOrderPrice){
            query->orderPrice=newOrderPrice;
        }

        return t;
    }

    /* 1. Perform the normal BST insertion */
    if(t == nullptr)
    {
        Node *temp=new Node(newOrderId,newOrderPrice);
        return temp;
    }

    if(newOrderId < t->orderId){
        t->left = insertNode(t->left,newOrderId,newOrderPrice);
    }

    else if(newOrderId > t->orderId){
        t->right = insertNode(t->right, newOrderId, newOrderPrice);
    }   
    
    else return t;

    /* 2. Update height of this ancestor Node */
    t->height=max(height(t->left), height(t->right))+1;

    /* 3. Get the balance factor of this ancestor 
    Node to check whether this Node became 
    unbalanced */
    
    return doBalanced(t,newOrderId);
    /* return the (unchanged) Node pointer */
    //return t;
}

Node * AVLTree::rightRotate(Node *t) 
{ 
    Node *x = t->left; 
    Node *T2 = x->right; 

    // Perform rotation 
    x->right = t; 
    t->left = T2; 

    // Update heights 
    t->height = max(height(t->left), 
                    height(t->right)) + 1; 

    x->height = max(height(x->left), 
                    height(x->right)) + 1; 

    // Return new root 
    return x; 
} 

Node * AVLTree::leftRotate(Node *x) 
{ 
    Node *y = x->right; 
    Node *T2 = y->left; 

    // Perform rotation 
    y->left = x; 
    x->right = T2; 

    // Update heights 
    x->height = max(height(x->left),	 
                    height(x->right)) + 1; 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 

    // Return new root 
    return y; 
} 

/*  
Node* AVLTree::Insert(Node* root, uint64_t newOrderId,uint32_t newOrderPrice) 
{  
    // Create a new Node containing 
    // the new element 
    Node* newNode = newNode(newOrderId,newOrderPrice); 

    // Pointer to start traversing from root and 
    // traverses downward path to search 
    // where the new Node to be inserted 
    Node* x = root; 

    // Pointer y maintains the trailing 
    // pointer of x 
    Node* y = nullptr; 

    while (x != nullptr) { 
        y = x; 
        if (newOrderId < x->orderId) 
            x = x->left; 
        else
            x = x->right; 
    } 

    // If the root is nullptr i.e the tree is empty 
    // The new Node is the root Node 
    if (y == nullptr) 
        y = newNode; 

    // If the new key is less then the leaf Node key 
    // Assign the new Node to be its left child 
    else if (newOrderId < y->orderId) 
        y->left = newNode; 

    // else assign the new Node its right child 
    else
        y->right = newNode; 

    // Returns the pointer where the 
    // new Node is inserted 
    return y; 
} 
*/

Node* AVLTree::findMin(Node* t)
{
    if(t == nullptr)
        return nullptr;
    else if(t->left == nullptr)
        return t;
    else
        return findMin(t->left);
}

Node* AVLTree::findMax(Node* t) {
    if(t == nullptr)
        return nullptr;
    else if(t->right == nullptr)
        return t;
    else
        return findMax(t->right);
}

Node* AVLTree::removeNode(Node* t,uint64_t orderId) {
    
    
    
    if(t == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(orderId < t->orderId)
        t->left = removeNode(t->left,orderId);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(orderId > t->orderId)
        t->right = removeNode(t->right,orderId);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (t->left == nullptr) || (t->right == nullptr) ) {
            
            Node * temp;

            if(t->left == nullptr){
                temp = t->right;
                delete t;
            }
            else{
                temp=t->left;
                delete t;
            }

            // No child case
            if(temp == nullptr){
                temp = t;
                t = nullptr;
            }

            else {// One child case
                t = temp; // Copy the contents of the non-empty child
                temp = nullptr;
            }
            //temp = nullptr;

        }
        else{
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)

            Node * temp = findMin(t->right);

            // Copy the inorder successor's data to this Node
            t->orderId=temp->orderId;
            t->orderPrice=temp->orderPrice;

            // remove the inorder successor
            t->right=removeNode(t->right,temp->orderId);

        }
    }
    
    // If the tree had only one Node then return
    if(t==nullptr)
        return t;

    t->height = max(height(t->left), height(t->right))+1;

    return doBalanced(t);
}

void  AVLTree::writeInorder(Node * rootPtr,ofstream & outFile)const{
    if(rootPtr == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(rootPtr->left,outFile);

    // then deal with the Node 
    outFile << rootPtr->orderId <<";"<<rootPtr->orderPrice<<endl;

    // now recur on right subtree 
    writeInorder(rootPtr->right,outFile);
}

void  AVLTree::writePreorder(Node * rootPtr,ofstream & outFile)const{
    if(rootPtr == nullptr)
        return;
    
    // first recur on node
    outFile << rootPtr->orderId <<";"<<rootPtr->orderPrice<<endl;

    // then deal with the left subtree
    writePreorder(rootPtr->left,outFile);

    // now recur on right subtree 
    writePreorder(rootPtr->right,outFile);
}

void  AVLTree::writePostorder(Node * rootPtr,ofstream & outFile)const{
    if(rootPtr == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(rootPtr->left,outFile);
    
    // now recur on right subtree 
    writePostorder(rootPtr->right,outFile);
    
    // then deal with the Node 
    outFile << rootPtr->orderId <<";"<<rootPtr->orderPrice<<endl;

}

void AVLTree::inorder(Node* t) {
    if(t == nullptr)
        return;
    inorder(t->left);
    cout << t->orderId << ";"<<t->orderPrice<<endl;
    inorder(t->right);
}

void AVLTree::preorder(Node* t) {
    if(t == nullptr)
        return;
    
    cout << t->orderId << ";"<<t->orderPrice<<endl;
    inorder(t->left);
    inorder(t->right);
}

void AVLTree::postorder(Node* t) {
    if(t == nullptr)
        return;
    
    inorder(t->left);
    inorder(t->right);
    cout << t->orderId << ";"<<t->orderPrice<<endl;
}

Node* AVLTree::find(Node* t, uint64_t orderId) {
    if(t == nullptr)
        return nullptr;
    
    else if(t->orderId==orderId)
        return t;
        
    else if(orderId > t->orderId)
        return find(t->right, orderId);

    else return find(t->left, orderId);

}