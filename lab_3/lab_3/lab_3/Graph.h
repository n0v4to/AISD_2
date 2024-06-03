#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>


template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;
        
        Edge(const Vertex& f, const Vertex& t, const Distance& d) : from(f), to(t), distance(d) {}
    }


    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex& v) const {
        return adjacency_list.find(v) != adjacency_list.end();
    }

    void add_vertex(const Vertex& v) {
        if (!has_vertex(v)) {
            adjacency_list[v] = std::vector<Edge>();
        }
    }

    bool remove_vertex(const Vertex& v) {
        if (!has_vertex(v)) {
            return false;
        }

        adjacency_list.erase(v);

        for (auto& pair : adjacency_list) {
            auto& edges = pair.second;
            edges.erase(std::remove_if(edges.begin(), edges.end(),
                [v](const Edge& e) { return e.to == v; }), edges.end());
        }

        return true;
    }

    std::vector<Vertex> vertices() const {
        std::vector<Vertex> result;
        for (const auto& pair : adjacency_list) {
            result.push_back(pair.first);
        }
        return result;
    }


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& from, const Vertex& to,
        const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); //c учетом расстояния
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e) const; //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //порядок 
    size_t degree(const Vertex& v) const; //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex)const;
};
