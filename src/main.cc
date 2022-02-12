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

composite_t sparse_sum(composite_t lhs, composite_t rhs)
{
    composite_t result;
    composite_t::iterator lhs_it = lhs.begin();
    composite_t::iterator rhs_it = rhs.begin();
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

composite_t sparse_multiply(composite_t lhs, composite_t rhs)
{
    composite_t result;
    composite_t::iterator lhs_it = lhs.begin();
    composite_t::iterator rhs_it = rhs.begin();
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

int main()
{
    composite_t b;
    composite_t c;
    composite_t d;

    b.insert({std::make_pair(1, 2), 3.1});
    b.insert({std::make_pair(2, 5), 7.1});
    b.insert({std::make_pair(15, 15), 8.1});

    c.insert({std::make_pair(1, 3), 10.1});
    c.insert({std::make_pair(1, 10), 7.1});
    c.insert({std::make_pair(15, 15), 9.2});
    c.insert({std::make_pair(20, 20), 1.3});

    d.insert({std::make_pair(1, 7), 10.2});
    d.insert({std::make_pair(2, 10), 7.5});
    d.insert({std::make_pair(15, 15), 100.6});
    d.insert({std::make_pair(20, 20), 2.7});

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

    // create an expression tree
    node *root = new node("+");
    root->left = new node("*");
    root->left->left = new node(std::move(c));
    root->left->right = new node(std::move(d));
    root->right = new node(std::move(b));

    composite_t result = eval_expression_tree(root);

    std::cout << "result \n -------" << std::endl;
    for (auto val : result)
    {
        std::cout << "index: [" << val.first.first << "] [" << val.first.second << "] Val = " << val.second << std::endl;
    }

    delete (root);

    return 0;
}