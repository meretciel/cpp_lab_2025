//
// Created by ryan on 6/12/24.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <utility>
#include <filesystem>


using std::string;

namespace Graph {
    using AdjacentMatarix = std::vector<std::vector<int>>;

    class SimpleGraph {
    public:
        size_t n;
        std::filesystem::path output_dir;

    private:
        std::vector<std::vector<int>> neighbors_;
        std::vector<int> visit_time_;
        std::vector<int> low_point_;
        int time_ = 0;


    public:
        explicit SimpleGraph(size_t n): n(n), visit_time_(n), low_point_(n){};
        SimpleGraph(size_t n, AdjacentMatarix&& adj_matrix):
            n(n), neighbors_{std::move(adj_matrix)}, visit_time_(n), low_point_(n) {};

        void set_neighbors(AdjacentMatarix&& other) {
            neighbors_ = std::move(other);
        }

        void save() const {
            std::stringstream ss;
            ss << "graph_" << time_ << ".txt";
            std::filesystem::path output_path{output_dir / ss.str()};
            std::ofstream out_stream{output_path};

            for (int item : visit_time_) {
                out_stream << item << " ";
            }

            out_stream << "\n";

            for (int item : low_point_) {
                out_stream << item << " ";
            }
            out_stream << "\n";
            out_stream.close();
        }
    };
}


int main(int argc, char* argv[]) {

    string line;
    std::ifstream input_file("/home/ryan/workspace/tmp/graph_1.txt");
    getline(input_file, line);
    const int n_int = std::stoi(line);
    assert(n_int > 0);
    const size_t n = static_cast<size_t>(n_int);

    std::vector<std::vector<int>> neighbors{n + 1, std::vector<int>{}};

    for (int i = 1; i <= n; ++i) {
        getline(input_file, line);
        string token;
        std::stringstream ss{line};
        while (getline(ss, token, ',')) {
            neighbors.at(i).push_back(std::stoi(token));
        }
    }
    input_file.close();

    std::cout << n << '\n';
    for (int i = 1; i <= n; ++i) {
        for (auto item : neighbors.at(i)) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    Graph::SimpleGraph graph{n, std::move(neighbors)};
    graph.output_dir = "/home/ryan/workspace/tmp/graph_output";
    graph.save();

    return 0;
}