#include <iostream>
#include <algorithm>
#include <vector>
#include "../../OOP/List/List.h"

struct Leader
{
    int key;
    int incomeEdgeCount = 0;
    List<Leader*> trailers;

    Leader(int key)
        : key(key)
    {}
    operator int() const
    {
        return key;
    }
};

List<Leader*> buildGraph(const std::vector<std::pair<int, int>>& edges)
{
    List<Leader*> graph;

    for (const std::pair<int, int>& edge : edges)
    {
        Leader* tail = nullptr;
        for (Leader* leader : graph)
        {
            if (leader->key == edge.first)
            {
                tail = leader;
                break;
            }
        }

        if (!tail)
        {
            tail = new Leader(edge.first);
            graph.append(tail);
        }

        Leader* head = nullptr;
        for (Leader* leader : graph)
        {
            if (leader->key == edge.second)
            {
                head = leader;
                break;
            }
        }

        if (!head)
        {
            head = new Leader(edge.second);
            graph.append(head);
        }

        head->incomeEdgeCount++;
        tail->trailers.headInsert(head);
    }

    return graph;
}

void printGraph(const List<Leader*>& graph)
{
    for (const Leader* leader : graph)
    {
        for (const Leader* trailer : leader->trailers)
        {
            std::cout << "(" << leader->key << ", " << trailer->key << ")\n";
        }
    }
}

bool sort(const List<Leader*>& graph, std::vector<int> &result)
{
    List<Leader*> newGraph;
    for (int i = 0; i < graph.size(); ++i)
    {
        if (!graph[i]->incomeEdgeCount)
        {
            newGraph.append(graph[i]);
        }
    }
    if (!newGraph.size())
    {
        return false;
    }
    Leader *p = newGraph[0];
    while (newGraph.size())
    {
        p = *newGraph.begin();
        for (int j = 0 ; j < p->trailers.size(); ++j)
        {
            --p->trailers[j]->incomeEdgeCount;
            if (!p->trailers[j]->incomeEdgeCount)
            {
                newGraph.append(p->trailers[j]);
            }
        }
        result.push_back(p->key);
        newGraph.headErase();
    }
    if (result.size() != graph.size())
    {
        return false;
    }
    return true;
}

int main()
{
    List<Leader*> graph = buildGraph({
        {2, 1},
        {4, 5},
        {5, 1},
        {5, 3},
        {6, 2},
        {6, 3},
        {6, 5},
        {7, 1},
    });
    std::vector<int> result;
    bool sorted = sort(graph, result);
    if (!sorted)
    {
        std::cout << "Graph has cycle, no answer\n";
    }
    else
    {
        for (int i = 0; i < result.size(); ++i)
        {
            std::cout << result[i];
        }
    }

    for (Leader* leader : graph)
    {
        delete leader;
    }

    return 0;
}

