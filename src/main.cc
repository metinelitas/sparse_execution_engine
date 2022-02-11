#include <iostream>
#include <map>



// Class to represent the nodes of syntax tree
class node
{
public:
    std::string op;
    double val;

    node *left = NULL, *right = NULL;
    node(std::string s)
    {
        op = s;
    }
    node(double v)
    {
        val = v;
    }
};

int eval(node *root)
{
    // empty tree
    if (!root)
        return 0;

    // leaf node i.e, an integer
    if (!root->left && !root->right)
        return root->val;

    double l_val = eval(root->left);
    double r_val = eval(root->right);

    if (root->op == "+")
        return l_val + r_val;

    if (root->op == "*")
        return l_val * r_val;

    return l_val + r_val; // default
}

struct CompareIndexLexicographical {
    bool operator() (const std::pair<int,int> a, std::pair<int,int> b) const {
        if (a.first != b.first)
            return a.first < b.first;
        else
            return a.second < b.second;
    }
};

struct CompareInt {
    bool operator() (const int a, int b) const {
            return a < b;
    }
};

// driver function to check the above program
int main()
{
    std::map <std::pair<int,int>, double, CompareIndexLexicographical> b;
    std::map <std::pair<int,int>, double, CompareIndexLexicographical> c;
    std::map <std::pair<int,int>, double, CompareIndexLexicographical> d;

    
    b.insert({std::make_pair(1,2) , 3});
    b.insert({std::make_pair(2,5) , 7});
    b.insert({std::make_pair(15,15) , 8});

    c.insert({std::make_pair(1,3) , 10});
    c.insert({std::make_pair(1,10) , 7});
    c.insert({std::make_pair(15,15) , 9});
    c.insert({std::make_pair(20,20) , 1});
    
    d.insert({std::make_pair(1,7) , 10});
    d.insert({std::make_pair(2,10) , 7});
    d.insert({std::make_pair(15,15) , 1});
    d.insert({std::make_pair(20,20) , 2});

    // diyelim en ustteki indexi biliyoruz

    // 1,2 



    std::cout << "b \n -------" << std::endl;
    for (auto val : b)
    { 
        std::cout << "index: [" << val.first.first << "] [" << val.first.second << "] Val = " << val.second << std::endl;
    }

    std::cout << "c \n -------" << std::endl;
    for (auto val : c)
    { 
        std::cout << "index: [" << val.first.first << "] [" << val.first.second << "] Val = " << val.second << std::endl;
    }

    std::cout << "d \n -------" << std::endl;
    for (auto val : d)
    { 
        std::cout << "index: [" << val.first.first << "] [" << val.first.second << "] Val = " << val.second << std::endl;
    }


    



/*     {
        double b = 4;
        double c = 5;
        double d = 3;

        // create a syntax tree
        node *root = new node("+");
        root->left = new node("*");
        root->left->left = new node(c);
        root->left->right = new node(d);
        root->right = new node(b);
        std::cout << eval(root) << std::endl;

        delete (root);
    } */
    


    return 0;
}