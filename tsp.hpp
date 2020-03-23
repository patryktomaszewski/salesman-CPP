
#ifndef SALESMAN_TSP_HPP
#define SALESMAN_TSP_HPP

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <numeric>
#define INF (NAN)

using ulong = unsigned long;
using ivec = std::vector<int>;
using uint = unsigned int;
using rpair = std::pair<double,double>;
using matrix = std::vector<std::vector<double>>;

std :: vector <int > tsp (std::vector<std::vector<double>> cost_matrix );
double get_forbidden_cost();


class TSP_cost_matrix{
public:
    TSP_cost_matrix(matrix cost_matrix) : cost_matrix_(cost_matrix)  {}
    void reduce_row(double row_num);
    void reduce_all_rows();
    void reduce_col(double col_num);
    void reduce_all_cols();
    rpair find_next_path();
    bool is_zero_in_row_col();
    std::vector<std::pair<double,double>> find_zeros();
    double find_min_in_row(double row, double col);
    double find_min_in_col(double row, double col);
    rpair find_max( std::vector<std::pair<double, rpair>> v);
    void reduce_matrix(double row_to_reduce, double col_to_reduce);
    std::vector<int> sort();
    void print_solution();
    void print_matrix();
    bool is_zero_in_row(int row_num);
    bool is_zero_in_col(int col_num);
    double get_size(){return cost_matrix_.size();}
    void last_points();
private:
    double low_bound_ = 0;
    matrix cost_matrix_;
    std::vector<rpair> solution_;

};


#endif //SALESMAN_TSP_HPP
