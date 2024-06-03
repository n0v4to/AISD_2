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
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        if (!has_vertex(from) || !has_vertex(to)) {
            return;
        }

        adjacency_list[from].push_back(Edge(from, to, d))
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        if (!has_vertex(from) || !has_vertex(to)) {
            return false;
        }

        auto& edges = adjacency_list[from];
        auto it = std::remove_if(edges.begin(), edges.end(),
            [to](const Edge& e) { return e.to == to; });

        if (it != edges.end()) {
            edges.erase(it, edges.end());
            return true;
        }

        return false;
    }

    bool remove_edge(const Edge& e) {
        return remove_edge(e.from, e.to);
    } //c учетом расстояния

    bool has_edge(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from)) {
            return false;
        }

        for (const auto& edge : adjacency_list.at(from)) {
            if (edge.to == to) {
                return true;
            }
        }

        return false;
    }

    bool has_edge(const Edge& e) const {
        return has_edge(e.from, e.to);
    } //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex) {
        if (!has_vertex(vertex)) {
            return std::vector<Edge>();
        }

        return adjacency_list.at(vertex);
    }

    size_t order() const {
        return adjacency_list.size();
    }//порядок

    size_t degree(const Vertex& v) const {
        if (!has_vertex(v)) {
            return 0;
        }

        return adjacency_list.at(v).size();
    } //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        std::unordered_map<Vertex, Distance> distance;
        std::unordered_map<Vertex, Vertex> predecessor;

        for (const auto& pair : adjacency_list) {
            distance[pair.first] = std::numeric_limits<Distance>::max();
            predecessor[pair.first] = pair.first;
        }

        distance[from] = 0;

        for (size_t i = 0; i < order() - 1; ++i) {
            for (const auto& pair : adjacency_list) {
                const Vertex& u = pair.first;
                for (const Edge& edge : pair.second) {
                    const Vertex& v = edge.to;
                    Distance new_distance = distance[u] + edge.distance;
                    if (new_distance < distance[v]) {
                        distance[v] = new_distance;
                        predecessor[v] = u;
                    }
                }
            }
        }

        std::vector<Edge> path;
        for (Vertex v = to; v != from; v = predecessor[v]) {
            Vertex u = predecessor[v];
            for (const Edge& edge : adjacency_list[u]) {
                if (edge.to == v) {
                    path.push_back(edge);
                    break;
                }
            }
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

    //обход
    std::vector<Vertex> walk(const Vertex& start_vertex) const {
        std::vector<Vertex> result;
        std::unordered_set<Vertex> visited;

        depth_first_search(start_vertex, visited, result);

        return result;
    }

    void depth_first_search(const Vertex& current_vertex, std::unordered_set<Vertex>& visited, std::vector<Vertex>& result) const {
        visited.insert(current_vertex);
        result.push_back(current_vertex);

        for (const Edge& edge : adjacency_list.at(current_vertex)) {
            if (visited.find(edge.to) == visited.end()) {
                depth_first_search(edge.to, visited, result);
            }
        }
    }
};
