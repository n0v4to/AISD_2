#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <limits>

#define EPSILON 1e-10
#define INF 1e9


template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;

        Edge(const Vertex& f, const Vertex& t, const Distance& d) : from(f), to(t), distance(d) {}
    };

private:
    std::vector<Vertex> _vertices;
    std::unordered_map<Vertex, std::vector<Edge>> _edges;
public:
    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex& v) const {
        return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
    }

    void add_vertex(const Vertex& v) {
        if (!has_vertex(v)) {
            _vertices.push_back(v);
            _edges[v] = std::vector<Edge>();
        }
    }

    bool remove_vertex(const Vertex& v) {
        auto it = std::find(_vertices.begin(), _vertices.end(), v);
        if (it == _vertices.end()) {
            return false;
        }

        _vertices.erase(it);
        _edges.erase(v);

        for (auto& pair : _edges) {
            auto& edges = pair.second;
            edges.erase(std::remove_if(edges.begin(), edges.end(),
                [v](const Edge& e) { return e.to == v; }), edges.end());
        }

        return true;
    }

    std::vector<Vertex> vertices() const {
        return _vertices;
    }


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        if (!has_vertex(from) || !has_vertex(to)) {
            return;
        }

        _edges[from].push_back(Edge(from, to, d));
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        if (!has_edge(from, to))
            return false;
        auto& edges = _edges.at(from);

        edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& e) { return (e.from == from) && (e.to == to); }), edges.end());

        return true;    
    }

    bool remove_edge(const Edge& e) {
        if (!has_edge(e))
            return false;
        auto& edges = _edges.at(e.from);

        edges.erase(std::remove_if(edges.begin(), edges.end(), [e](const Edge& edge)
            { return (e.from == edge.from) && (e.to == edge.to) && (e.distance == edge.distance); }), edges.end());

        return true;
    } //c учетом расстояния

    bool has_edge(const Vertex& from, const Vertex& to) const {
        for (const auto& edges : _edges) {
            for (const auto& edge : edges.second) {
                if (edge.from == from && edge.to == to) {
                    return true;
                }
            }
        }
        return false;
    }

    bool has_edge(const Edge& e) const {
        auto& edges = _edges.at(e.from);
        for (const auto& edge : edges)
            if (edge.to == e.to && std::abs(edge.weight - e.weight) < EPSILON)
                return true;
        return false;
    } //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex) {
        if (!has_vertex(vertex)) {
            return std::vector<Edge>();
        }

        return _edges.at(vertex);
    }

    size_t order() const {
        return _vertices.size();
    }//порядок

    size_t degree(const Vertex& v) const {
        size_t count = 0;
        for (const auto& edges : _edges) {
            for (const auto& edge : edges.second) {
                if (edge.from == v || edge.to == v) {
                    count++;
                }
            }
        }
        return count;
    } //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        std::unordered_map<Vertex, Distance> distance;
        std::unordered_map<Vertex, Vertex> predecessor;

        for (const auto& v : _vertices) {
            distance[v] = INF;
        }
        distance[from] = 0;

        for (size_t i = 0; i < _vertices.size() - 1; ++i) {
            for (const auto& vertex : _vertices) {
                for (const auto& edge : _edges.at(vertex)) {
                    if (distance[edge.from] + edge.distance < distance[edge.to]) {
                        distance[edge.to] = distance[edge.from] + edge.distance;
                        predecessor[edge.to] = edge.from;
                    }
                }
            }
        }

        for (const auto& vertex : _vertices) {
            for (const auto& edge : _edges.at(vertex)) {
                if (distance[edge.from] + edge.distance < distance[edge.to]) {
                    throw std::runtime_error("Отрицательный цикл обнаружен");
                }
            }
        }

        std::vector<Edge> path;
        Vertex cur = to;
        while (cur != from) {
            for (const auto& edge : _edges.at(predecessor[cur])) {
                if (edge.to == cur) {
                    path.push_back(edge);
                    break;
                }
            }
            cur = predecessor[cur];
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    Distance length_shortest_path(const Vertex& from, const Vertex& to) const {
        std::vector<Edge> edges = shortest_path(from, to);
        Distance len = 0;
        for (const auto& edge : edges) {
            len += edge.distance;
        }
        return len;
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

        for (const Edge& edge : _edges.at(current_vertex)) {
            if (visited.find(edge.to) == visited.end()) {
                depth_first_search(edge.to, visited, result);
            }
        }
    }

    Vertex find_optimal_warehouse() const {
        Distance min_max_distance = std::numeric_limits<Distance>::max();
        Vertex optimal_warehouse;

        for (const auto& pair : vertices()) {
            Distance max_distance = 0;

            for (const auto& pair2 : vertices()) {
                if (pair != pair2) {
                    Distance distance = length_shortest_path(pair, pair2);
                    max_distance = std::max(max_distance, distance);
                }
            }

            if (max_distance < min_max_distance) {
                min_max_distance = max_distance;
                optimal_warehouse = pair;
            }
        }

        return optimal_warehouse;
    }

    void print_edges() const {
        std::cout << "Edges: " << std::endl;
        for (const Vertex& vertex : _vertices) {
            for (const Edge& edge : _edges.at(vertex)) {
                std::cout << edge.from << " -> " << edge.to << "(" << edge.distance << ")" << std::endl;
            }
        }
    }
};
