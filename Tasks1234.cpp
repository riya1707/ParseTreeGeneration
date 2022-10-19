#include<bits/stdc++.h>
using namespace std;

class TreeNode
{
  public:
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

string toPrefix(string infix){
    string prefix;
    stack<char> prestack;
    reverse(infix.begin(), infix.end());

    for(int i=0; i<infix.length(); i++){
        if(isalpha(infix[i])  || infix[i]=='~'){
            prefix.push_back(infix[i]);
        }
        else if(infix[i]=='('){
            while(!(prestack.top()==')')){
                prefix.push_back(prestack.top());
                prestack.pop();
            }
            prestack.pop();
        }
        else{
            prestack.push(infix[i]);
        }
    }

    while(!prestack.empty()){
        prefix.push_back(prestack.top());
        prestack.pop();
    }
    reverse(prefix.begin(), prefix.end());

    return prefix;
}

TreeNode* prefixtoParse(string prefix, int &idx, vector<TreeNode*> &arr){
    TreeNode* root=new TreeNode(prefix[idx]);
    arr.push_back(root);
    //cout<< "Pushin: "<< root->data<<endl;

    if(isalpha(prefix[idx]) || idx==prefix.length()){
        return root;
    }

    if(prefix[idx]=='~'){
        idx++;
        root->right= prefixtoParse(prefix, idx, arr);
        //cout<< "right to negation "<<root->right->data<< " "<< idx<<endl;
    }
    else {
        idx++;
        root->left= prefixtoParse(prefix, idx, arr);
        //cout<< "root->left "<<root->left->data<< " "<< idx<<endl;
        idx++;
        root->right= prefixtoParse(prefix, idx, arr);
        //cout<< "root->right "<<root->right->data<< " "<< idx<<endl;
    }

    return root;
}

void infixTrav(TreeNode* root){
    if(root==NULL)
    return;

    infixTrav(root->left);
    cout<<root->data<<" ";
    infixTrav(root->right);
}

int heightOfParse(TreeNode* root){
    if(root==NULL){
        return 0;
    }

    return 1+max(heightOfParse(root->left), heightOfParse(root->right));
}

int main(){
    string infix;
    cout<<"Enter completely paranthesized infix string\n";
    cin >> infix;

    string prefix=toPrefix(infix);

    cout << "Prefix string:\n" << prefix<<endl;
    vector<TreeNode*> arr;
    int initVal=0;

    TreeNode* parseTree= prefixtoParse(prefix, initVal, arr);

    cout<< "Infix traversal of parse tree: ";
    infixTrav(arr[0]);

    cout<< endl << "Height of the parse tree: " << heightOfParse(arr[0]);

    return 0;
}