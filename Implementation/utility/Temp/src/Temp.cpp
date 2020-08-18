#include "../inc/Temp.hpp"


/* 
###########################################
##Template Specialization for OrderBookId##
###########################################
 */

using std:: max;

AVLTree<OrderBookId>::Node::Node(const OrderBookId& newData ):
graph{new Graph<uint32_t ,Graph<uint32_t, Value>>},
bookId{newData.orderBookId},height{0},
right{nullptr},left{nullptr}
{ /* deliberately left blank */}


AVLTree<OrderBookId>::Node::Node(uint32_t newBookId):
graph{new Graph<uint32_t ,Graph<uint32_t, Value>>},
bookId{newBookId},height{0},
right{nullptr},left{nullptr}
{ /* deliberately left blank */}


AVLTree<OrderBookId>::Node* AVLTree<OrderBookId>::makeEmpty(Node *node){
    if(node == nullptr)
        return nullptr;
    
    else{
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return nullptr;
}


AVLTree<OrderBookId>::Node* AVLTree<OrderBookId>::insertNode(Node* node, const OrderBookId& newData){
    
    Node *query= searchNode(node,newData.orderBookId);

    if(query!=nullptr){
        return node;
    }

    /* 1. Perform the normal BST insertion */
    if(node == nullptr)
    {
        Node *temp=new Node(newData);
        return temp;
    }

    if(newData.orderBookId < node->bookId){
        node->left = insertNode(node->left,newData);
    }

    else if(newData.orderBookId > node->bookId){
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


AVLTree<OrderBookId>::Node* AVLTree<OrderBookId>::removeNode(Node* node,uint32_t orderBookId) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(orderBookId < node->bookId)
        node->left = removeNode(node->left,orderBookId);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(orderBookId > node->bookId)
        node->right = removeNode(node->right,orderBookId);
    
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
            node->bookId=temp->bookId;
            //node->AOTree=temp->AOTree;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->bookId);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}


AVLTree<OrderBookId>::Node* AVLTree<OrderBookId>::searchNode(Node* node, uint32_t orderBookId) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->bookId == orderBookId)
        return node;
        
    else if(orderBookId > node->bookId)
        return searchNode(node->right, orderBookId);

    else return searchNode(node->left, orderBookId);

}


AVLTree<OrderBookId>::Node* AVLTree<OrderBookId>::findMin(Node* node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}


AVLTree<OrderBookId>::Node * AVLTree<OrderBookId>::findMax(Node* node) {
    if(node == nullptr)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}


AVLTree<OrderBookId>::Node* AVLTree<OrderBookId>::doBalanced(Node *node){
    
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


AVLTree<OrderBookId>::Node* AVLTree<OrderBookId>::doBalanced(Node *node,const OrderBookId& newData){

    int balance = getBalance(node);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newData.orderBookId < node->left->bookId) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && newData.orderBookId > node->right->bookId) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && newData.orderBookId > node->left->bookId) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && newData.orderBookId < node->right->bookId) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}


AVLTree<OrderBookId>::Node * AVLTree<OrderBookId>::rightRotate(Node *node) 
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


AVLTree<OrderBookId>::Node * AVLTree<OrderBookId>::leftRotate(Node *node) 
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


int AVLTree<OrderBookId>:: getBalance(Node* node){
    if (node == NULL) 
        return 0; 
    return height(node->left) - height(node->right); 
}


int AVLTree<OrderBookId>::height(Node *node) 
{ 
    if (node == nullptr) 
        return 0; 

    return node->height; 
} 


void AVLTree<OrderBookId>::inorder(Node* node)const{
    if(node == nullptr)
        return;

    inorder(node->left);
    cout << node->bookId<<endl;
    inorder(node->right);
}


void AVLTree<OrderBookId>::preorder(Node* node)const{
    if(node == nullptr)
        return;

    cout << node->bookId<<endl;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<OrderBookId>::postorder(Node* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->bookId<<endl;
}


void  AVLTree<OrderBookId>::writeInorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->bookId<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<OrderBookId>::writePreorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->bookId<<endl;


    // then deal with the left subtree
    writePreorder(node->left,outFile);

    // now recur on right subtree 
    writePreorder(node->right,outFile);
}


void  AVLTree<OrderBookId>::writePostorder(Node * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(node->left,outFile);
    
    // now recur on right subtree 
    writePostorder(node->right,outFile);
    
    // then deal with the Node 
    outFile << node->bookId<<endl;

}