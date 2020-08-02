#ifndef _AVLTREE_INL_
#define _AVLTREE_INL_

/* 
###################################
Template Specialization for AddOrder
###################################
 */


Node<AddOrder>* AVLTree<AddOrder>::makeEmpty(Node<AddOrder> *node){
    if(node == nullptr)
        return nullptr;
    
    else{
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return nullptr;
}


Node<AddOrder>* AVLTree<AddOrder>::insertNode(Node<AddOrder>* node, const AddOrder& newData){
    
    Node<AddOrder> *query= searchNode(node,newData.orderId);

    if(query!=nullptr){
        if(query->data.orderPrice != newData.orderPrice){
            query->data.orderPrice=newData.orderPrice;
        }

        return node;
    }

    /* 1. Perform the normal BST insertion */
    if(node == nullptr)
    {
        Node<AddOrder> *temp=new Node<AddOrder>(newData);
        return temp;
    }

    if(newData.orderId < node->data.orderId){
        node->left = insertNode(node->left,newData);
    }

    else if(newData.orderId > node->data.orderId){
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

Node<AddOrder>* AVLTree<AddOrder>::removeNode(Node<AddOrder>* node,const AddOrder& data) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(data.orderId < node->data.orderId)
        node->left = removeNode(node->left,data);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(data.orderId > node->data.orderId)
        node->right = removeNode(node->right,data);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node<AddOrder> * temp;

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

            Node<AddOrder> * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->data=temp->data;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->data);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}

Node<AddOrder>* AVLTree<AddOrder>::removeNode(Node<AddOrder>* node,uint64_t orderId) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(orderId < node->data.orderId)
        node->left = removeNode(node->left,orderId);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(orderId > node->data.orderId)
        node->right = removeNode(node->right,orderId);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node<AddOrder> * temp;

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

            Node<AddOrder> * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->data=temp->data;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->data);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}


Node<AddOrder>* AVLTree<AddOrder>::searchNode(Node<AddOrder>* node, const AddOrder& data) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->data.orderId == data.orderId)
        return node;
        
    else if(data.orderId > node->data.orderId)
        return searchNode(node->right, data);

    else return searchNode(node->left, data);

}

Node<AddOrder>* AVLTree<AddOrder>::searchNode(Node<AddOrder>* node, uint64_t orderId) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->data.orderId == orderId)
        return node;
        
    else if(orderId > node->data.orderId)
        return searchNode(node->right, orderId);

    else return searchNode(node->left, orderId);

}


Node<AddOrder>* AVLTree<AddOrder>::findMin(Node<AddOrder>* node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}


Node<AddOrder> * AVLTree<AddOrder>::findMax(Node<AddOrder>* node) {
    if(node == nullptr)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}


Node<AddOrder>* AVLTree<AddOrder>::doBalanced(Node<AddOrder> *node){
    
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


Node<AddOrder>* AVLTree<AddOrder>::doBalanced(Node<AddOrder> *node,const AddOrder& newData){

    int balance = getBalance(node);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newData.orderId < node->left->data.orderId) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && newData.orderId > node->right->data.orderId) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && newData.orderId > node->left->data.orderId) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && newData.orderId < node->right->data.orderId) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}


Node<AddOrder> * AVLTree<AddOrder>::rightRotate(Node<AddOrder> *node) 
{ 
    Node<AddOrder> *x = node->left; 
    Node<AddOrder> *T2 = x->right; 

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


Node<AddOrder> * AVLTree<AddOrder>::leftRotate(Node<AddOrder> *node) 
{ 
    Node<AddOrder> *y = node->right; 
    Node<AddOrder> *x = y->left; 

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


int AVLTree<AddOrder>:: getBalance(Node<AddOrder>* node){
    if (node == NULL) 
        return 0; 
    return height(node->left) - height(node->right); 
}


int AVLTree<AddOrder>::height(Node<AddOrder> *node) 
{ 
    if (node == nullptr) 
        return 0; 

    return node->height; 
} 


void AVLTree<AddOrder>::inorder(Node<AddOrder>* node)const{
    if(node == nullptr)
        return;

    inorder(node->left);
    cout << node->data.orderId<<";"<<node->data.orderPrice<<endl;
    inorder(node->right);
}


void AVLTree<AddOrder>::preorder(Node<AddOrder>* node)const{
    if(node == nullptr)
        return;

    cout << node->data.orderId<<";"<<node->data.orderPrice<<endl;;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<AddOrder>::postorder(Node<AddOrder>* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->data.orderId<<";"<<node->data.orderPrice<<endl;;
}


void  AVLTree<AddOrder>::writeInorder(Node<AddOrder> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->data.orderId<<";"<<node->data.orderPrice<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<AddOrder>::writePreorder(Node<AddOrder> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->data.orderId<<";"<<node->data.orderPrice<<endl;

    // then deal with the left subtree
    writePreorder(node->left,outFile);

    // now recur on right subtree 
    writePreorder(node->right,outFile);
}


void  AVLTree<AddOrder>::writePostorder(Node<AddOrder> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(node->left,outFile);
    
    // now recur on right subtree 
    writePostorder(node->right,outFile);
    
    // then deal with the Node 
    outFile << node->data.orderId<<";"<<node->data.orderPrice<<endl;

}



/* 
###################################
Template Specialization for OrderExecute
###################################
 */

Node<OrderExecute>* AVLTree<OrderExecute>::makeEmpty(Node<OrderExecute> *node){
    if(node == nullptr)
        return nullptr;
    
    else{
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return nullptr;
}


Node<OrderExecute>* AVLTree<OrderExecute>::insertNode(Node<OrderExecute>* node, const OrderExecute& newData){
    
    Node<OrderExecute> *query= searchNode(node,newData);

    if(query!=nullptr){
        if(query->data.orderId != newData.orderId){
            query->data=newData;
        }

        return node;
    }

    /* 1. Perform the normal BST insertion */
    if(node == nullptr)
    {
        Node<OrderExecute> *temp=new Node<OrderExecute>(newData);
        return temp;
    }

    if(newData.orderId < node->data.orderId){
        node->left = insertNode(node->left,newData);
    }

    else if(newData.orderId > node->data.orderId){
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


Node<OrderExecute>* AVLTree<OrderExecute>::removeNode(Node<OrderExecute>* node,const OrderExecute& data) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(data.orderId < node->data.orderId)
        node->left = removeNode(node->left,data);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(data.orderId > node->data.orderId)
        node->right = removeNode(node->right,data);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node<OrderExecute> * temp;

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

            Node<OrderExecute> * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->data=temp->data;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->data);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}


Node<OrderExecute>* AVLTree<OrderExecute>::removeNode(Node<OrderExecute>* node,uint64_t orderId) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(orderId < node->data.orderId)
        node->left = removeNode(node->left,orderId);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(orderId > node->data.orderId)
        node->right = removeNode(node->right,orderId);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node<OrderExecute> * temp;

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

            Node<OrderExecute> * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->data=temp->data;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->data);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}

Node<OrderExecute>* AVLTree<OrderExecute>::searchNode(Node<OrderExecute>* node, const OrderExecute& data) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->data.orderId == data.orderId)
        return node;
        
    else if(data.orderId > node->data.orderId)
        return searchNode(node->right, data);

    else return searchNode(node->left, data);

}

Node<OrderExecute>* AVLTree<OrderExecute>::searchNode(Node<OrderExecute>* node, uint64_t orderId) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->data.orderId == orderId)
        return node;
        
    else if(orderId > node->data.orderId)
        return searchNode(node->right, orderId);

    else return searchNode(node->left, orderId);

}


Node<OrderExecute>* AVLTree<OrderExecute>::findMin(Node<OrderExecute>* node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}


Node<OrderExecute> * AVLTree<OrderExecute>::findMax(Node<OrderExecute>* node) {
    if(node == nullptr)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}


Node<OrderExecute>* AVLTree<OrderExecute>::doBalanced(Node<OrderExecute> *node){
    
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


Node<OrderExecute>* AVLTree<OrderExecute>::doBalanced(Node<OrderExecute> *node,const OrderExecute& newData){

    int balance = getBalance(node);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newData.orderId < node->left->data.orderId) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && newData.orderId > node->right->data.orderId) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && newData.orderId > node->left->data.orderId) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && newData.orderId < node->right->data.orderId) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}


Node<OrderExecute> * AVLTree<OrderExecute>::rightRotate(Node<OrderExecute> *node) 
{ 
    Node<OrderExecute> *x = node->left; 
    Node<OrderExecute> *T2 = x->right; 

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


Node<OrderExecute> * AVLTree<OrderExecute>::leftRotate(Node<OrderExecute> *node) 
{ 
    Node<OrderExecute> *y = node->right; 
    Node<OrderExecute> *x = y->left; 

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


int AVLTree<OrderExecute>:: getBalance(Node<OrderExecute>* node){
    if (node == NULL) 
        return 0; 
    return height(node->left) - height(node->right); 
}


int AVLTree<OrderExecute>::height(Node<OrderExecute> *node) 
{ 
    if (node == nullptr) 
        return 0; 

    return node->height; 
} 


void AVLTree<OrderExecute>::inorder(Node<OrderExecute>* node)const{
    if(node == nullptr)
        return;

    inorder(node->left);
    cout << node->data.orderId<<endl;
    inorder(node->right);
}


void AVLTree<OrderExecute>::preorder(Node<OrderExecute>* node)const{
    if(node == nullptr)
        return;

    cout << node->data.orderId<<endl;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<OrderExecute>::postorder(Node<OrderExecute>* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->data.orderId<<endl;;
}


void  AVLTree<OrderExecute>::writeInorder(Node<OrderExecute> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->data.orderId<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<OrderExecute>::writePreorder(Node<OrderExecute> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->data.orderId<<endl;

    // then deal with the left subtree
    writePreorder(node->left,outFile);

    // now recur on right subtree 
    writePreorder(node->right,outFile);
}


void  AVLTree<OrderExecute>::writePostorder(Node<OrderExecute> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(node->left,outFile);
    
    // now recur on right subtree 
    writePostorder(node->right,outFile);
    
    // then deal with the Node 
    outFile << node->data.orderId<<endl;

}




/* 
###################################
Template Specialization for OrderDelete
###################################
 */

Node<OrderDelete>* AVLTree<OrderDelete>::makeEmpty(Node<OrderDelete> *node){
    if(node == nullptr)
        return nullptr;
    
    else{
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return nullptr;
}


Node<OrderDelete>* AVLTree<OrderDelete>::insertNode(Node<OrderDelete>* node, const OrderDelete& newData){
    
    Node<OrderDelete> *query= searchNode(node,newData);

    if(query!=nullptr){
        if(query->data.orderId != newData.orderId){
            query->data=newData;
        }

        return node;
    }

    /* 1. Perform the normal BST insertion */
    if(node == nullptr)
    {
        Node<OrderDelete> *temp=new Node<OrderDelete>(newData);
        return temp;
    }

    if(newData.orderId < node->data.orderId){
        node->left = insertNode(node->left,newData);
    }

    else if(newData.orderId > node->data.orderId){
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


Node<OrderDelete>* AVLTree<OrderDelete>::removeNode(Node<OrderDelete>* node,const OrderDelete& data) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(data.orderId < node->data.orderId)
        node->left = removeNode(node->left,data);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(data.orderId > node->data.orderId)
        node->right = removeNode(node->right,data);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node<OrderDelete> * temp;

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

            Node<OrderDelete> * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->data=temp->data;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->data);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}

Node<OrderDelete>* AVLTree<OrderDelete>::removeNode(Node<OrderDelete>* node,uint64_t orderId) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(orderId < node->data.orderId)
        node->left = removeNode(node->left,orderId);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(orderId > node->data.orderId)
        node->right = removeNode(node->right,orderId);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node<OrderDelete> * temp;

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

            Node<OrderDelete> * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->data=temp->data;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->data);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}

Node<OrderDelete>* AVLTree<OrderDelete>::searchNode(Node<OrderDelete>* node, const OrderDelete& data) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->data.orderId == data.orderId)
        return node;
        
    else if(data.orderId > node->data.orderId)
        return searchNode(node->right, data);

    else return searchNode(node->left, data);

}


Node<OrderDelete>* AVLTree<OrderDelete>::searchNode(Node<OrderDelete>* node, uint64_t orderId) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->data.orderId == orderId)
        return node;
        
    else if(orderId > node->data.orderId)
        return searchNode(node->right, orderId);

    else return searchNode(node->left, orderId);

}

Node<OrderDelete>* AVLTree<OrderDelete>::findMin(Node<OrderDelete>* node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}


Node<OrderDelete> * AVLTree<OrderDelete>::findMax(Node<OrderDelete>* node) {
    if(node == nullptr)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}


Node<OrderDelete>* AVLTree<OrderDelete>::doBalanced(Node<OrderDelete> *node){
    
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


Node<OrderDelete>* AVLTree<OrderDelete>::doBalanced(Node<OrderDelete> *node,const OrderDelete& newData){

    int balance = getBalance(node);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newData.orderId < node->left->data.orderId) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && newData.orderId > node->right->data.orderId) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && newData.orderId > node->left->data.orderId) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && newData.orderId < node->right->data.orderId) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}


Node<OrderDelete> * AVLTree<OrderDelete>::rightRotate(Node<OrderDelete> *node) 
{ 
    Node<OrderDelete> *x = node->left; 
    Node<OrderDelete> *T2 = x->right; 

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


Node<OrderDelete> * AVLTree<OrderDelete>::leftRotate(Node<OrderDelete> *node) 
{ 
    Node<OrderDelete> *y = node->right; 
    Node<OrderDelete> *x = y->left; 

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


int AVLTree<OrderDelete>:: getBalance(Node<OrderDelete>* node){
    if (node == NULL) 
        return 0; 
    return height(node->left) - height(node->right); 
}


int AVLTree<OrderDelete>::height(Node<OrderDelete> *node) 
{ 
    if (node == nullptr) 
        return 0; 

    return node->height; 
} 


void AVLTree<OrderDelete>::inorder(Node<OrderDelete>* node)const{
    if(node == nullptr)
        return;

    inorder(node->left);
    cout << node->data.orderId<<endl;
    inorder(node->right);
}


void AVLTree<OrderDelete>::preorder(Node<OrderDelete>* node)const{
    if(node == nullptr)
        return;

    cout << node->data.orderId<<endl;

    preorder(node->left);
    preorder(node->right);
}


void AVLTree<OrderDelete>::postorder(Node<OrderDelete>* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->data.orderId<<endl;;
}


void  AVLTree<OrderDelete>::writeInorder(Node<OrderDelete> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->data.orderId<<endl;
    // now recur on right subtree 
    writeInorder(node->right,outFile);
}


void  AVLTree<OrderDelete>::writePreorder(Node<OrderDelete> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->data.orderId<<endl;

    // then deal with the left subtree
    writePreorder(node->left,outFile);

    // now recur on right subtree 
    writePreorder(node->right,outFile);
}


void  AVLTree<OrderDelete>::writePostorder(Node<OrderDelete> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(node->left,outFile);
    
    // now recur on right subtree 
    writePostorder(node->right,outFile);
    
    // then deal with the Node 
    outFile << node->data.orderId<<endl;

}

#endif