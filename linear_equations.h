#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdlib>
#include <algorithm>
using namespace std;

#ifndef Linear_Equations_H_
#define Linear_Equations_H_
class Linear_equations{
    protected:
    int equations_num;
    vector<string> equations;
    vector<string> formatted_equations;
    vector<string> variables;
    vector<vector<float>> coefficients;
    vector<float> constants ;
    
    public:
    Linear_equations();
    void set_nummber_of_equations(int _equations_num);
    int get_nummber_of_equations();
    void set_equation(string _equation);
    vector<string> get_equations();
    void modify_all_equations();
    void find_variable_names(string _eq);
    void find_coefficients(string _eq);
    void find_constants(string _eq);
    void format_equations(int eq_index);
};
#endif