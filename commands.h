#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdlib>
#include "linear_equations.h"
using namespace std;
#ifndef Commannds_H_
#define Commannds_H_
class Commands : public Linear_equations{
    float matrix_determinant;
    vector<float> equations_solve;

    public:
    bool command_starts_with(const string &str, const string &sub_str);
    int num_vars();
    string equation(int eq_num);
    vector<float> column (string var_name);
    string add (int eq1_num, int eq2_num);
    string subtract (int eq1_num, int eq2_num);
    string substitute (string var_name, int eq1_num, int eq2_num);
    vector<vector<float>> cramer_matrix_coeff();
    vector<vector<float>> cramer_matrix_coeff_of_var (string var_name);
    float calculate_determinant(vector<vector<float>> matrix);
    float cramer_matrix_determinant_value ();
    vector<float> solve();
};
#endif