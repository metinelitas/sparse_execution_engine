#include <iostream>
#include <map>

using index_t = std::pair<int, int>;

using composite_t = std::map<index_t, double>;

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
    node(composite_t &&data)
    {
        this->data = data;
    }
};

composite_t sparse_sum(const composite_t& lhs, const composite_t& rhs)
{
    composite_t result;
    composite_t::const_iterator lhs_it = lhs.begin();
    composite_t::const_iterator rhs_it = rhs.begin();
    index_t max_index = std::make_pair(INT_MAX, INT_MAX);
    index_t lhs_index;
    index_t rhs_index;

    while (true)
    {
        lhs_index = lhs_it->first;
        rhs_index = rhs_it->first;

        if (lhs_it == lhs.end())
            lhs_index = max_index;

        if (rhs_it == rhs.end())
            rhs_index = max_index;

        if ((lhs_index == max_index) && (rhs_index == max_index))
            break;

        if (lhs_index < rhs_index)
        {
            result[lhs_index] = lhs_it->second;
            lhs_it++;
        }
        else if (lhs_index == rhs_index)
        {
            result[lhs_index] = lhs_it->second + rhs_it->second;
            lhs_it++;
            rhs_it++;
        }
        else if (lhs_index > rhs_index)
        {
            result[rhs_index] = rhs_it->second;
            rhs_it++;
        }
    }

    return result;
}

composite_t sparse_multiply(const composite_t& lhs, const composite_t& rhs)
{
    composite_t result;
    composite_t::const_iterator lhs_it = lhs.begin();
    composite_t::const_iterator rhs_it = rhs.begin();
    index_t max_index = std::make_pair(INT_MAX, INT_MAX);
    index_t lhs_index;
    index_t rhs_index;

    while (true)
    {
        lhs_index = lhs_it->first;
        rhs_index = rhs_it->first;

        if (lhs_it == lhs.end())
            lhs_index = max_index;

        if (rhs_it == rhs.end())
            rhs_index = max_index;

        if ((lhs_index == max_index) && (rhs_index == max_index))
            break;

        if (lhs_index < rhs_index)
        {
            lhs_it++;
        }
        else if (lhs_index == rhs_index)
        {
            result[lhs_index] = lhs_it->second * rhs_it->second;
            lhs_it++;
            rhs_it++;
        }
        else if (lhs_index > rhs_index)
        {
            rhs_it++;
        }
    }

    return result;
}

composite_t eval_expression_tree(node *root)
{
    composite_t result;

    if (!root)
        return result;

    if (!root->left && !root->right)
        return root->data;

    composite_t l_val = eval_expression_tree(root->left);
    composite_t r_val = eval_expression_tree(root->right);

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

void printParamter(const composite_t& param) 
{
    for (auto x : param)
    {
        std::cout << "index: [" << x.first.first << "][" << x.first.second << "]\t Val = " << x.second << std::endl;
    }
}

int main()
{
    composite_t b;
    composite_t c;
    composite_t d;

    b.insert({std::make_pair(0,0), 728.49});
    b.insert({std::make_pair(1,0), 599.27});
    b.insert({std::make_pair(1,1), 833.81});
    b.insert({std::make_pair(1,2), 919.39});
    b.insert({std::make_pair(1,3), 688.53});
    b.insert({std::make_pair(1,4), 643.26});
    b.insert({std::make_pair(1,5), 227.8});
    b.insert({std::make_pair(1,6), 863.85});
    b.insert({std::make_pair(2,0), 277.14});
    b.insert({std::make_pair(2,1), 281.43});
    c.insert({std::make_pair(0,0), 707.53});
    c.insert({std::make_pair(1,0), 156.0});
    c.insert({std::make_pair(1,1), 649.25});
    c.insert({std::make_pair(1,2), 800.6});
    c.insert({std::make_pair(1,3), 762.59});
    d.insert({std::make_pair(0,0), 822.69});
    d.insert({std::make_pair(0,1), 269.2});


    std::cout << "b \n -------" << std::endl;
    printParamter(b);
    std::cout << "c \n -------" << std::endl;
    printParamter(c);
    std::cout << "d \n -------" << std::endl;
    printParamter(d);

    // create an expression tree
    node *root = new node("+");
    root->left = new node("*");
    root->left->left = new node(std::move(c));
    root->left->right = new node(std::move(d));
    root->right = new node(std::move(b));

    composite_t result = eval_expression_tree(root);

    std::cout << "result \n -------" << std::endl;
    printParamter(result);

    delete (root);

    return 0;
}