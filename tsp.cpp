#include "tsp.hpp"


double get_forbidden_cost(){ return NAN; }



bool TSP_cost_matrix::is_zero_in_row(int row_num){
    for(std::size_t i =0 ;i<cost_matrix_.size();i++){
        if(cost_matrix_[row_num][i]==0){
            return true;
        }

    }
    return false;
}

bool TSP_cost_matrix::is_zero_in_col(int col_num){
    for(std::size_t i =0 ;i<cost_matrix_.size();i++){
        if(cost_matrix_[i][col_num]==0){
            return true;
        }

    }
    return false;
}

bool TSP_cost_matrix::is_zero_in_row_col() {
    for(size_t i =0;i<cost_matrix_.size();i++){
        if(is_zero_in_row(i)==false){
            return false;
        }
    }
    for(size_t i =0;i<cost_matrix_.size();i++){
        if(is_zero_in_col(i)==false){
            return false;
        }
    }
    return true;
}
double TSP_cost_matrix::find_min_in_row(double row, double col){
    std::vector<double>v;
    for(size_t i = 0;i<cost_matrix_.size();i++){
        if(!std::isnan(cost_matrix_[row][i]) && i != col){
            v.push_back(cost_matrix_[row][i]);
        }


    }
    auto min =(*std::min_element(v.begin(),v.end()));
    return min;
}



double TSP_cost_matrix::find_min_in_col(double row, double col) {
    std::vector<double>v;
    for(size_t i = 0;i<cost_matrix_.size();i++){
        if(!std::isnan(cost_matrix_[i][col]) && i!=row){
            v.push_back(cost_matrix_[i][col]);
        }
    }
    auto min =(*std::min_element(v.begin(),v.end()));
    return min;
}




void TSP_cost_matrix::reduce_row(double row_num) {


    std::vector<double> min_vec;
    for (std::size_t i = 0; i < cost_matrix_.size(); i++) {

        min_vec.push_back(cost_matrix_[row_num][i]);

    }
    min_vec.erase(
            std::remove_if(std::begin(min_vec), std::end(min_vec), [](const auto &value) { return std::isnan(value); }),
            std::end(min_vec));
    auto min = (*std::min_element(min_vec.begin(), min_vec.end()));
    low_bound_ += min;

    for (std::size_t j = 0; j < cost_matrix_.size(); j++) {


        cost_matrix_[row_num][j] -= min;



    }
}
void TSP_cost_matrix::reduce_all_rows(){
    for(std::size_t i =0 ;i<cost_matrix_.size();i++){
        reduce_row(i);
    }
}


void TSP_cost_matrix::reduce_col(double col_num){
    std::vector<double> min_vec;
    for(std::size_t i = 0; i<cost_matrix_.size(); i++){

        min_vec.push_back(cost_matrix_[i][col_num]);

    }
    min_vec.erase(std::remove_if(std::begin(min_vec),std::end(min_vec),[](const auto& value) { return std::isnan(value); }),std::end(min_vec));
    auto min =(*std::min_element(min_vec.begin(),min_vec.end()));
    low_bound_ += min;

    for(std::size_t j =0;j<cost_matrix_.size();j++){


        cost_matrix_[j][col_num] -= min;



    }
}

void TSP_cost_matrix::reduce_all_cols(){
    for(std::size_t i =0 ;i<cost_matrix_.size();i++){
        reduce_col(i);
    }
}






rpair TSP_cost_matrix::find_next_path() {
    std::vector<std::pair<double, rpair>> path;
    std::vector<std::pair<double,double>> lista_zer = find_zeros();


    for(auto i : lista_zer){
        std::pair<double,rpair>pre_path = std::make_pair(0,i);
        path.push_back(pre_path);
    }

    for(auto& i :path){

        auto sum = find_min_in_row(i.second.first,i.second.second)+find_min_in_col(i.second.first,i.second.second);
        i.first = sum;
    }


    auto added_to_solution = find_max(path);

    return added_to_solution;

}

std::vector<std::pair<double,double>> TSP_cost_matrix::find_zeros() {
    std::vector<std::pair<double,double>>zerujace_pary;
    for(std::size_t i=0;i < cost_matrix_.size();i++){
        for(std::size_t j=0;j < cost_matrix_.size();j++){
            if(cost_matrix_[i][j] == 0){

                zerujace_pary.push_back(std::make_pair(i,j));

            }

        }

    }
    return zerujace_pary;
}

rpair TSP_cost_matrix::find_max( std::vector<std::pair<double, rpair>>v){

    double start_value = v[0].first;

    rpair start_pair = v[0].second;

    for(auto elem : v){

        if(elem.first>start_value){
            start_value = elem.first;

            start_pair = elem.second;

        }

    }

    solution_.push_back(start_pair);
    return start_pair;

}


void TSP_cost_matrix::reduce_matrix(double row_to_reduce, double col_to_reduce){
    for(size_t i =0;i<cost_matrix_.size();i++){
        for(size_t j =0;j<cost_matrix_.size();j++){
            if(i==row_to_reduce || j==col_to_reduce){
                cost_matrix_[i][j]=NAN;
            }
        }
    }
    cost_matrix_[col_to_reduce][row_to_reduce] = NAN;
}

std::vector<int> TSP_cost_matrix::sort(){
    std::vector<rpair> new_solution;
    rpair helper;
    std::vector<int>sorted_solution;


    for(std::size_t i =0;i<solution_.size();i++){

        if(i ==0){
            new_solution.push_back(solution_[0]);
        }
        helper = new_solution[i];
        for(std::size_t j =0;i<solution_.size();j++){
            if(helper.second==solution_[j].first){
                new_solution.push_back(solution_[j]);
                break;
            }
        }
    }


    for (int i = 0; i < new_solution.size(); i++) {

        sorted_solution.push_back(new_solution[i].first+1);

    }
    return sorted_solution;
}

void TSP_cost_matrix::last_points(){
    std::vector<double>row_indices;
    std::vector<double>col_indices;


    if(!is_zero_in_row_col()){
        reduce_all_rows();
    }
    if(!is_zero_in_row_col()){
        reduce_all_cols();
    }

    for(std::size_t i =0;i<cost_matrix_.size();i++){
        for(std::size_t j =0;j<cost_matrix_.size();j++){
            if(!std::isnan(cost_matrix_[i][j]) ){


                row_indices.push_back(i);

                col_indices.push_back(j);
            }
        }
    }
    std::vector<double>single_row_indices;
    std::vector<double>single_col_indices;
    for (auto elem : row_indices){
        if (std::count(single_row_indices.begin(), single_row_indices.end(), elem))
            continue;
        else
            single_row_indices.push_back(elem);
    }

    for (auto elem : col_indices){
        if (std::count(single_col_indices.begin(), single_col_indices.end(), elem))
            continue;
        else

            single_col_indices.push_back(elem);
    }

    if (std::isnan(cost_matrix_[single_row_indices[0]][single_col_indices[0]])) {
        solution_.push_back({single_row_indices[0],single_col_indices[1]});
        solution_.push_back({single_row_indices[1],single_col_indices[0]});
    }
    if (std::isnan(cost_matrix_[single_row_indices[0]][single_col_indices[1]])) {
        solution_.push_back({single_row_indices[0],single_col_indices[0]});
        solution_.push_back({single_row_indices[1],single_col_indices[1]});
    }
    if (std::isnan(cost_matrix_[single_row_indices[1]][single_col_indices[0]])) {
        solution_.push_back({single_row_indices[0],single_col_indices[0]});
        solution_.push_back({single_row_indices[1],single_col_indices[1]});
    }
    if (std::isnan(cost_matrix_[single_row_indices[1]][single_col_indices[1]])) {
        solution_.push_back({single_row_indices[0],single_col_indices[1]});
        solution_.push_back({single_row_indices[1],single_col_indices[0]});
    }

}



std :: vector <int > tsp (std::vector<std::vector<double>> cost_matrix ){
    std::vector<int>final_path;
    std::size_t i =0 ;
    TSP_cost_matrix helper = TSP_cost_matrix(cost_matrix);

    rpair max_elem;

    while (i < helper.get_size()){

        if(!helper.is_zero_in_row_col() ) {

            helper.reduce_all_rows();


        }

        if(!helper.is_zero_in_row_col()){
            helper.reduce_all_cols();

        }


        max_elem = helper.find_next_path();
        helper.reduce_matrix(max_elem.first,max_elem.second);
        if(i==helper.get_size() - 3) {helper.last_points();  break;}
        i++;
    }

    final_path = helper.sort();

    return final_path;


}

