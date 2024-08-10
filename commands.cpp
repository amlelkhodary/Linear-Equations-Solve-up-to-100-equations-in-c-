#include "commands.h"
bool Commands::command_starts_with(const string &str, const string &sub_str){
    for(int i=0; i<sub_str.length(); i++){
        if(str[i] != sub_str[i])
            return false;
    }
    return true;
}
int Commands::num_vars(){
    return variables.size();
}

string Commands::equation(int eq_num){
    return formatted_equations[eq_num-1];
}

vector<float> Commands::column (string var_name){
    int i;
    for(i=0; i<variables.size(); i++){
        if(variables[i]==var_name)
            break;
    }
    vector<float> column;
    for(vector<float> vec : coefficients){
        column.push_back(vec[i]);
    }
    return column;
}

string Commands::add (int eq1_num, int eq2_num){
    vector<float> adding;
    for(int i=0; i<variables.size(); i++){
        adding.push_back(coefficients[eq1_num-1][i]+coefficients[eq2_num-1][i]);
    }
    ostringstream oss;
    for(int i=0; i<variables.size(); i++){
        if(adding[i] != 0){
            if(adding[i] > 0 && i==0)
                oss<<adding[i];
            else if(adding[i] > 0 && i!=0)
                oss<<"+"<<adding[i];
            else if(adding[i] < 0)
                oss<<adding[i];
            oss<<variables[i];
        }
    }
    int constant = constants[eq1_num-1] + constants[eq2_num-1];
    oss<<"="<<constant;
    return oss.str();
}
string Commands::subtract (int eq1_num, int eq2_num){
    vector<float> subtracting;
    for(int i=0; i<variables.size(); i++){
        subtracting.push_back(coefficients[eq1_num-1][i]-coefficients[eq2_num-1][i]);
    }
    ostringstream oss;
    for(int i=0; i<variables.size(); i++){
        if(subtracting[i] != 0){
            if(subtracting[i] > 0 && i==0)
                oss<<subtracting[i];
            else if(subtracting[i] > 0 && i!=0)
                oss<<"+"<<subtracting[i];
            else if(subtracting[i] < 0)
                oss<<subtracting[i];
            oss<<variables[i];
        }
    }
    int constant = constants[eq1_num-1] - constants[eq2_num-1];
    oss<<"="<<constant;
    return oss.str();
}
string Commands::substitute (string var_name, int eq1_num, int eq2_num){
    vector<float> coeff_before_substitution;
    vector<float> coeff_after_substitution;
    float const_before_substitution;
    float const_after_substitution;
    float var_coeff;
    string substituted_string;
    ostringstream oss;
    int var_num;
    for(var_num=0; var_num<variables.size(); var_num++){
        if(variables[var_num] == var_name)
            break;
    }
    var_coeff = coefficients[eq1_num-1][var_num];
    if(var_coeff !=0){
        for(int i=0; i<coefficients[eq1_num-1].size(); i++){
            coeff_before_substitution.push_back(coefficients[eq1_num-1][i]/var_coeff);
        }
        for(int i=0; i<coefficients[eq2_num-1].size(); i++){
            coeff_after_substitution.push_back(coefficients[eq2_num-1][i]+coeff_before_substitution[i]);
        }
        const_before_substitution = constants[eq1_num-1]/var_coeff;
        const_after_substitution = constants[eq2_num-1] + const_before_substitution;

        for(int i=0; i<coeff_after_substitution.size(); i++){
            if(coeff_after_substitution[i] != 0){
                if(coeff_after_substitution[i] > 0 && i==0)
                    oss<<coeff_after_substitution[i];
                else if(coeff_after_substitution[i] > 0 && i!=0)
                    oss<<"+"<<coeff_after_substitution[i];
                else if(coeff_after_substitution[i] < 0)
                    oss<<coeff_after_substitution[i];
                oss<<variables[i];
            }
        }
        oss<<"="<<const_after_substitution;
        return oss.str();
    }
    else{
        return formatted_equations[eq2_num];
    }
}
vector<vector<float>> Commands::cramer_matrix_coeff(){
    return coefficients;
}
vector<vector<float>> Commands::cramer_matrix_coeff_of_var (string var_name){
    vector<vector<float>> coeff_of_var;
    vector<float> column_vec;
    int var_num;
    for(var_num=0; var_num<variables.size(); var_num++){
        if(variables[var_num] == var_name)
            break;
    }
    for(int i=0; i<coefficients.size(); i++){
        for(int j=0; j<coefficients[0].size(); j++){
            if(j == var_num)
                column_vec.push_back(constants[i]);
            else
                column_vec.push_back(coefficients[i][j]);
        }
        coeff_of_var.push_back(column_vec);
        column_vec.clear();
    }
    return coeff_of_var;
}
float Commands::calculate_determinant(vector<vector<float>> matrix){
    float determinant = 1.0;
    
    for(int i = 0; i < matrix.size(); i++) {
        float pivot = matrix[i][i];
        if (pivot == 0) {
            return 0;
        }
        
        for(int j = i + 1; j < matrix.size(); j++) {
            float factor = matrix[j][i] / pivot;
            for(int k = i; k < matrix[i].size(); k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
        determinant *= pivot;
    }
    return determinant;
}

float Commands::cramer_matrix_determinant_value() {
    vector<vector<float>> cramer_matrix = coefficients; 
    matrix_determinant = calculate_determinant(cramer_matrix);
    return matrix_determinant;
}

vector<float> Commands::solve(){
    for(int i=0; i< coefficients.size(); i++){
        vector<vector<float>> cramer_matrix = coefficients;
        for(int j=0; j<coefficients[0].size(); j++){
            cramer_matrix[j][i] = constants[j];
        }
        equations_solve.push_back(calculate_determinant(cramer_matrix)/matrix_determinant);
    }
    return equations_solve;
}