#include <iostream>
#include <torch/torch.h>
#include <vector>
#include <stdexcept>

using namespace std;

#define N int8_t

torch::Tensor ALU(torch::Tensor t1, torch::Tensor t2, string op)
{
    torch::Tensor *Result = new torch::Tensor;
    //___ADDITION__(may require changing vector size)
    if (op == "+")
    {
        if (t1.sizes() != t2.sizes())
        {
            throw std::invalid_argument("Shapes Mismatch" + (char32_t)((int)t1.sizes()[0]) + ',' + (char32_t)t1.sizes()[1] + '!=' + (char32_t)(int)t2.sizes()[0] + ',' + (char32_t)(int)t2.sizes()[1]);
        }
        std::vector<vector<int8_t>> *tempouter = new vector<vector<int8_t>>();

        for (int i = 0; i < t1.sizes()[0]; i++)
        {

            for (int j = 0; j < (int)t1.sizes()[1]; j++)
            {
                std::vector<int8_t> *temp = new vector<int8_t>();
                (*temp).push_back(t1[i][j].item<int8_t>() + t2[i][j].item<int8_t>());
                (*tempouter).push_back((*temp));
                delete temp;
            }
        }

        vector<vector<int8_t>> t = *tempouter;
        delete tempouter;
        // Printing Vectors
        //  for (int k = 0; k < t.size(); k++)
        //  {
        //      for (int l = 0; l < t[0].size(); l++)
        //      {
        //          cout << t[k][l];
        //      }
        //      cout << '\n';
        //  }

        std::vector<int8_t> flat_vector;
        for (const auto &inner_vector : t)
        {
            flat_vector.insert(flat_vector.end(), inner_vector.begin(), inner_vector.end());
        }
        return (torch::tensor(flat_vector, torch::kInt32)).view({t1.sizes()[0], t1.sizes()[1]});
    }

    else if (op == "-")
    {
        if (t1.sizes() != t2.sizes())
        {
            throw std::invalid_argument("Shapes Mismatch" + (char32_t)((int)t1.sizes()[0]) + ',' + (char32_t)t1.sizes()[1] + '!=' + (char32_t)(int)t2.sizes()[0] + ',' + (char32_t)(int)t2.sizes()[1]);
        }
        std::vector<vector<int8_t>> *tempouter = new vector<vector<int8_t>>();

        for (int i = 0; i < t1.sizes()[0]; i++)
        {

            for (int j = 0; j < (int)t1.sizes()[1]; j++)
            {
                std::vector<int8_t> *temp = new vector<int8_t>();
                (*temp).push_back(t1[i][j].item<int8_t>() - t2[i][j].item<int8_t>());
                (*tempouter).push_back((*temp));
                delete temp;
            }
        }

        vector<vector<int8_t>> t = *tempouter;
        delete tempouter;
        // Printing Vectors
        //  for (int k = 0; k < t.size(); k++)
        //  {
        //      for (int l = 0; l < t[0].size(); l++)
        //      {
        //          cout << t[k][l];
        //      }
        //      cout << '\n';
        //  }

        std::vector<int8_t> flat_vector;
        for (const auto &inner_vector : t)
        {
            flat_vector.insert(flat_vector.end(), inner_vector.begin(), inner_vector.end());
        }
        return (torch::tensor(flat_vector, torch::kInt32)).view({t1.sizes()[0], t1.sizes()[1]});
    }

    else if (op == "mat_mul")
    {
        vector<vector<int>> *temp = new vector<vector<int>>;

        for (int i = 0; i < t2.sizes()[1]; i++)
        {
            vector<int> *row = new vector<int>;

            for (int j = 0; j < t1.sizes()[0]; j++)
            {
                int *sum = new int;

                for (int k = 0; k < t1.sizes()[0]; k++)
                {
                    *sum = *sum + (t1[i][k].item<N>() * t2[k][i].item<N>());
                }
                row[i][j] = *sum;
                delete sum;
            }
            temp->push_back((*row));
            delete row;
        }

        std::vector<int8_t> flat_vector;
        for (const auto &inner_vector : *temp)
        {
            flat_vector.insert(flat_vector.end(), inner_vector.begin(), inner_vector.end());
        }
        delete temp;
        return (torch::tensor(flat_vector, torch::kInt32)).view({t1.sizes()[1], t1.sizes()[0]});
    }
}

int main()
{

    torch::Tensor tensor1 = torch::randn({4, 1});
    torch::Tensor tensor2 = torch::randn({4, 1});
    tensor1 = tensor1.to(torch::kInt8);
    tensor2 = tensor2.to(torch::kInt8);

    cout << tensor1 << '\n'
         << tensor2 << '\n'
         << ALU(tensor1, tensor2, "+") << '\n';

    return 0;
}