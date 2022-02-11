#include <iostream>
#include <map>

using index_t = std::pair<int,int>;

using param_t = std::map <index_t, double>;

class node
{
public:
    std::string op;
    param_t data;

    node *left = NULL, *right = NULL;
    node(std::string s)
    {
        op = s;
    }
    node(param_t&& data)
    {
        this->data = data;
    }
};


struct SparseExecutionEngine {





    // Return the next tuple greater or equal to a given tuple
    param_t::iterator Search(index_t index, param_t )
    {

    }


   





    param_t sparse_sum(param_t left , param_t right)
    {
        double result = 0;

        // start from the lowest index of left - right 
        index_t start = min(left.begin()->first, right.begin()->first);


        param_t::iterator it_left = left.begin();
        param_t::iterator it_right = right.begin();

        index_t left_index = it_left->first;
        index_t right_index = it_right->first;

        if (left_index == right_index)
        {
            result = it_left->second + it_right->second;
        }


    }

    param_t sparse_multiply(param_t left , param_t right)
    {

    }

    // param_t eval(node *root)
    // {
    //     if (!root)
    //         return nullptr;

    //     if (!root->left && !root->right)
    //         return root->data.at(current_index);

    
    //     param_t l_val = eval(root->left);
    //     param_t r_val = eval(root->right);

    //     if (root->op == "+")
    //     {
    //         return sparse_sum(l_val, r_val);       
    //     }

    //     if (root->op == "*")
    //     {
    //         return sparse_multiply(l_val, r_val);
    //     }

    //     return sparse_sum(l_val, r_val); // default
    // }

};



param_t::iterator foo(param_t p)
{
    return p.begin();
}

// driver function to check the above program
int main()
{
    
    param_t b;
    param_t c;
    param_t d;


    b.insert({std::make_pair(15,15) , 8});
    b.insert({std::make_pair(1,2) , 3});
    b.insert({std::make_pair(2,5) , 7});

    c.insert({std::make_pair(1,2) , 10});
    c.insert({std::make_pair(1,3) , 10});
    c.insert({std::make_pair(1,10) , 7});
    c.insert({std::make_pair(15,15) , 9});
    c.insert({std::make_pair(20,20) , 1});
    
    d.insert({std::make_pair(1,7) , 10});
    d.insert({std::make_pair(2,10) , 7});
    d.insert({std::make_pair(15,15) , 1});
    d.insert({std::make_pair(20,20) , 2});

    SparseExecutionEngine engine = SparseExecutionEngine();

    // param_t a = engine.sparse_sum(b,c);

    param_t::iterator it = foo(b);

    std::cout << it->second << std::endl;



    // {
    //     std::cout << "b \n -------" << std::endl;
    //     for (auto val : b)
    //     { 
    //         std::cout << "index: [" << val.first.first << "] [" << val.first.second << "] Val = " << val.second << std::endl;
    //     }

    //     std::cout << "c \n -------" << std::endl;
    //     for (auto val : c)
    //     { 
    //         std::cout << "index: [" << val.first.first << "] [" << val.first.second << "] Val = " << val.second << std::endl;
    //     }

    //     std::cout << "d \n -------" << std::endl;
    //     for (auto val : d)
    //     { 
    //         std::cout << "index: [" << val.first.first << "] [" << val.first.second << "] Val = " << val.second << std::endl;
    //     }

    // }



        // create an expression tree
        // node *root = new node("+");
        // root->left = new node("*");
        // root->left->left = new node(std::move(c));
        // root->left->right = new node(std::move(d));
        // root->right = new node(std::move(b));
        // std::cout << eval(root) << std::endl;

        // delete (root);

    


    return 0;
}