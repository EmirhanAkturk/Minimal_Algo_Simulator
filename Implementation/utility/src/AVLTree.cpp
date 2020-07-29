#include "../include/AVLTree.h"

node* AVLTree::makeEmpty(node* t) {
    if(t == nullptr)
        return nullptr;
    
    else{
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    return nullptr;
}

int AVLTree::height(node *t) 
{ 
    if (t == nullptr) 
        return 0; 

    return t->height; 
} 

int AVLTree::getBalance(node *t) 
{ 
    if (t == NULL) 
        return 0; 
    return height(t->left) - height(t->right); 
} 

node* AVLTree::doBalanced(node *t,uint64_t newOrderId){

    int balance = getBalance(t);

    // If this node becomes unbalanced, then 
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

node* AVLTree::doBalanced(node *t){
    
    int balance = getBalance(t);
    // If this node becomes unbalanced, then 
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

    /* return the (unchanged) node pointer */
    return t;

}

node* AVLTree::newNode(uint64_t newOrderId,uint32_t newOrderPrice) 
{ 
    node* temp = new node; 

    temp->orderId = newOrderId; 
    temp->orderPrice = newOrderPrice; 

    temp->height=0;
    temp->left = nullptr; 
    temp->right = nullptr; 

    return temp; 
}  
    

node* AVLTree::insert( node* t,uint64_t newOrderId,uint32_t newOrderPrice)
{
    node* query= find(t,newOrderId);

    if(query!=nullptr){
        if(query->orderPrice!=newOrderPrice){
            query->orderPrice=newOrderPrice;
        }

        return t;
    }

    /* 1. Perform the normal BST insertion */
    if(t == nullptr)
    {
        return (newNode(newOrderId,newOrderPrice));
    }

    if(newOrderId < t->orderId){
        t->left = insert(t->left,newOrderId,newOrderPrice);
    }

    else if(newOrderId > t->orderId){
        t->right = insert(t->right, newOrderId, newOrderPrice);
    }   
    
    else return t;

    /* 2. Update height of this ancestor node */
    t->height=max(height(t->left), height(t->right))+1;

    /* 3. Get the balance factor of this ancestor 
    node to check whether this node became 
    unbalanced */
    
    return doBalanced(t,newOrderId);
    /* return the (unchanged) node pointer */
    //return t;
}

node * AVLTree::rightRotate(node *t) 
{ 
    node *x = t->left; 
    node *T2 = x->right; 

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

node * AVLTree::leftRotate(node *x) 
{ 
    node *y = x->right; 
    node *T2 = y->left; 

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
node* AVLTree::Insert(node* root, uint64_t newOrderId,uint32_t newOrderPrice) 
{  
    // Create a new Node containing 
    // the new element 
    node* newnode = newNode(newOrderId,newOrderPrice); 

    // Pointer to start traversing from root and 
    // traverses downward path to search 
    // where the new node to be inserted 
    node* x = root; 

    // Pointer y maintains the trailing 
    // pointer of x 
    node* y = nullptr; 

    while (x != nullptr) { 
        y = x; 
        if (newOrderId < x->orderId) 
            x = x->left; 
        else
            x = x->right; 
    } 

    // If the root is nullptr i.e the tree is empty 
    // The new node is the root node 
    if (y == nullptr) 
        y = newnode; 

    // If the new key is less then the leaf node key 
    // Assign the new node to be its left child 
    else if (newOrderId < y->orderId) 
        y->left = newnode; 

    // else assign the new node its right child 
    else
        y->right = newnode; 

    // Returns the pointer where the 
    // new node is inserted 
    return y; 
} 
*/

node* AVLTree::findMin(node* t)
{
    if(t == nullptr)
        return nullptr;
    else if(t->left == nullptr)
        return t;
    else
        return findMin(t->left);
}

node* AVLTree::findMax(node* t) {
    if(t == nullptr)
        return nullptr;
    else if(t->right == nullptr)
        return t;
    else
        return findMax(t->right);
}

node* AVLTree::remove(node* t,uint64_t orderId) {
    
    
    
    if(t == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(orderId < t->orderId)
        t->left = remove(t->left,orderId);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(orderId > t->orderId)
        t->right = remove(t->right,orderId);
    
    // if value is same as root's value, then This is the node
    // to be deleted
    else 
    {   
        // node with only one child or no child
        if( (t->left == nullptr) || (t->right == nullptr) ) {
            
            node * temp;

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
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)

            node * temp = findMin(t->right);

            // Copy the inorder successor's data to this node
            t->orderId=temp->orderId;
            t->orderPrice=temp->orderPrice;

            // remove the inorder successor
            t->right=remove(t->right,temp->orderId);

        }
    }
    
    // If the tree had only one node then return
    if(t==nullptr)
        return t;

    t->height = max(height(t->left), height(t->right))+1;

    return doBalanced(t);
}

void  AVLTree::writeInorder(node * rootPtr,ofstream & outFile)const{
    if(rootPtr == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(rootPtr->left,outFile);

    // then deal with the node 
    outFile << rootPtr->orderId <<";"<<rootPtr->orderPrice<<endl;

    // now recur on right subtree 
    writeInorder(rootPtr->right,outFile);
}

void AVLTree::inorder(node* t) {
    if(t == nullptr)
        return;
    inorder(t->left);
    cout << t->orderId << ";"<<t->orderPrice<<endl;
    inorder(t->right);
}

node* AVLTree::find(node* t, uint64_t orderId) {
    if(t == nullptr)
        return nullptr;
    
    else if(t->orderId==orderId)
        return t;
        
    else if(orderId > t->orderId)
        return find(t->right, orderId);

    else return find(t->left, orderId);

}