#include <iostream>
#include <map>

using index_t = std::pair<int,int>;

using composite_t = std::map <index_t, double>;

class node
{
public:
    std::string op;
    composite_t data;

    node *left = NULL, *right = NULL;
    node(std::string s)
    {
        op = s;
    }
    node(composite_t&& data)
    {
        this->data = data;
    }
};


struct SparseExecutionEngine {

    composite_t sparse_sum(composite_t lhs , composite_t rhs)
    {
        composite_t result;

        for (auto l : lhs)
        {
            result[l.first] = l.second;
        }

        for (auto r : rhs)
        {
            result[r.first] += r.second;
        }
    
        return result;
    }

    composite_t sparse_multiply(composite_t lhs , composite_t rhs)
    {
        composite_t result;
        // we need matching indexes
        for (auto l : lhs)
        {
            auto r = rhs.find(l.first);
            if (r != rhs.end())
            {
                result.insert({l.first, l.second * r->second});
            }
        }

        return result;

    }

    composite_t eval(node *root)
    {
        composite_t result;

        if (!root)
            return result;

        if (!root->left && !root->right)
            return root->data;

        composite_t l_val = eval(root->left);
        composite_t r_val = eval(root->right);

        if (root->op == "+")
        {
            return sparse_sum(l_val, r_val);       
        }

        if (root->op == "*")
        {
            return sparse_multiply(l_val, r_val);
        }

        return sparse_sum(l_val, r_val); // default
    }

};



// driver function to check the above program
int main()
{
    
    composite_t b;
    composite_t c;
    composite_t d;
    
    b.insert({std::make_pair(1,2) , 3});
    b.insert({std::make_pair(2,5) , 7});
    b.insert({std::make_pair(15,15) , 8});

    // c.insert({std::make_pair(1,2) , 10});
    c.insert({std::make_pair(1,3) , 10});
    c.insert({std::make_pair(1,10) , 7});
    c.insert({std::make_pair(15,15) , 9});
    c.insert({std::make_pair(20,20) , 1});
    
    d.insert({std::make_pair(1,7) , 10});
    d.insert({std::make_pair(2,10) , 7});
    d.insert({std::make_pair(15,15) , 100});
    d.insert({std::make_pair(20,20) , 2});


    {
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

    }

        SparseExecutionEngine engine = SparseExecutionEngine();


        // create an expression tree
        node *root = new node("+");
        root->left = new node("*");
        root->left->left = new node(std::move(c));
        root->left->right = new node(std::move(d));
        root->right = new node(std::move(b));
        
        composite_t result = engine.eval(root);

        std::cout << "result \n -------" << std::endl;
        for (auto val : result)
        { 
            std::cout << "index: [" << val.first.first << "] [" << val.first.second << "] Val = " << val.second << std::endl;
        }

        delete (root);


    return 0;
}