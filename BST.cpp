#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* Right, * Left;

    Node(int data)
    {
        this->data = data;
        Right = Left = NULL;
    }
};


class Tree
{
    Node* Root;
public:
    Tree()
    {
        Root = NULL;
    }
    void addNode(int data)
    {
        Node* node = new Node(data);
        if (Root == NULL)
        {
            Root = node;
        }
        else
        {
            Node* current = Root;
            Node* parent = NULL;

            while (current != NULL)
            {
                parent = current;
                if (data > current->data)
                {
                    current = current->Right;
                }
                else
                {
                    current = current->Left;
                }
            }
            if (data > parent->data)
            {
                parent->Right = node;
            }
            else
            {
                parent->Left = node;
            }
        }
    }

    Node* SearchBST(int data) 
    {
        if (Root == NULL)
        {
            return Root;
        }
        else
        {
            Node* CurrentRoot = Root;
            while (CurrentRoot != NULL)
            {
                if (CurrentRoot->data == data)
                {
                    return CurrentRoot;
                }
                else if(data < CurrentRoot->data)
                {
                    CurrentRoot = CurrentRoot->Left;
                }
                else
                {
                    CurrentRoot = CurrentRoot->Right;
                }
            }
            return NULL;
        }
    }
    Node* FindMin(Node* Current)
    {
        if (Current == NULL)
        {
            return NULL;
        }
        else if (Current->Left == NULL)
        {
            return Current;
        }
        else
        {
            return FindMin(Current->Left);
        }
    }
    
    Node* FindMax(Node* Current)
    {
        if (Current == NULL)
        {
            return NULL;
        }
        else if (Current->Right == NULL)
        {
            return Current;
        }
        else
        {
            return FindMax(Current->Right);
        }
    }

    void DisplayMinMax()
    {
        Node* min = FindMin(Root);
        cout << min->data << endl;
        Node* max = FindMax(Root);
        cout << max->data << endl;
    }

    int FindParent(int data)
    {
        if (Root == NULL || Root->data == data)
        {
            return NULL;
        }
        else
        {
            Node* Current = Root;
            Node* Parent = Root;
            while (Current)
            {
                if (Current->data == data)
                {
                    return Parent->data;
                }
                else if (data < Current->data)
                {
                    Parent = Current;
                    Current = Current->Left;
                }
                else
                {
                    Parent = Current;
                    Current = Current->Right;
                }
            }
        }
    }
    

    Node* DeleteNode(Node* node, int data)
    {
        if (node == NULL)
        {
            return NULL;
        }
        if (data < node->data)
        {
            node->Left = DeleteNode(node->Left, data);
        }
        else if(data > node->data)
        {
            node->Right = DeleteNode(node->Right, data);
        }
        else
        {
            // leaf node
            if (node->Left == NULL && node->Right == NULL)
            {
                delete node;
                node = NULL;
            }

            // one child on left
            else if (node->Left != NULL && node->Right == NULL)
            {
                node->data = node->Left->data;
                delete node->Left;
                node->Left = NULL;
            }
            // one child on right
            else if(node->Right != NULL && node->Left == NULL)
            {
                node->data = node->Right->data;
                delete node->Right;
                node->Right = NULL;
            }
            else
            {
                Node* Max = FindMax(node->Left);
                node->data = Max->data;
                node->Left = DeleteNode(node->Left, Max->data);
            }
        }
        return node;
    }

    Node* Delete(int data)
    {
        return DeleteNode(this->Root, data);
    }

    void DisplayNodesInOrder(Node* node)
    {
        if (node == NULL) return;
        DisplayNodesInOrder(node->Left);
        cout << node->data << "\t";
        DisplayNodesInOrder(node->Right);
    }

    void TraverseInOrder()
    {
        DisplayNodesInOrder(Root);
    }
    
    void DisplayNodesPreOrder(Node* node)
    {
        if (node == NULL) return;
        cout << node->data << "\t";
        DisplayNodesPreOrder(node->Left);
        DisplayNodesPreOrder(node->Right);
    }

    void TraversePreOrder()
    {
        DisplayNodesPreOrder(Root);
    }

    void DisplayNodesPostOrder(Node* node)
    {
        if (node == NULL) return;
        DisplayNodesPreOrder(node->Left);
        DisplayNodesPreOrder(node->Right);
        cout << node->data << "\t";
    }

    void TraversePostOrder()
    {
        DisplayNodesPostOrder(Root);
    }
};

int main()
{
    Tree BST;
    BST.addNode(4);
    BST.addNode(2);
    BST.addNode(5);
    BST.addNode(1);
    BST.addNode(3);
    BST.addNode(6);

    BST.TraverseInOrder();
    cout << endl;
    BST.TraversePreOrder();
    cout << endl;
    BST.TraversePostOrder();
    cout << endl;

    cout << BST.SearchBST(5) << endl;

    BST.DisplayMinMax();
    cout << endl;

    cout << BST.FindParent(2) << endl;

    BST.Delete(2);
    BST.TraverseInOrder();
    cout << endl;
}
