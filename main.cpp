#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<map>
#include<algorithm>
#include "linear_equations.h"
#include "commands.h"
using namespace std;
int main(){
    Linear_equations equation;
    Commands command;
    ifstream file ("I:/CPP_Training/projects/linear_equation_project/equations.txt");
    string line;
    vector<string> equations;
    if (getline(file, line)) {
        command.set_nummber_of_equations(stoi(line));
        for(int eq_index = 0; eq_index < command.get_nummber_of_equations() ; eq_index++){
            getline(file, line);
            command.set_equation(line);
        }
        command.modify_all_equations();
        while(getline(file, line)){
            cout<<"--------------------------------------  "<<line<<endl;
            if(command.command_starts_with(line,"num_vars")){
                cout<<command.num_vars()<<endl;
            }
            else if(command.command_starts_with(line,"equation")){
                string cmd = "equation";
                int eq_num = 0;
                istringstream iss(line);
                if (iss>>cmd>>eq_num)
                    cout<<command.equation(eq_num)<<endl;
            }  
            else if(command.command_starts_with(line,"column")){
                string cmd = "column";
                string variable_name;
                istringstream iss(line);
                if(iss>>cmd>>variable_name){
                    vector<float> column_coeff = command.column(variable_name) ;
                    for(float val : column_coeff){
                        cout<<val<<endl;
                    }
                }
            }
            else if(command.command_starts_with(line,"add")){
                string cmd = "add";
                int eq_num_1 ;
                int eq_num_2 ;
                istringstream iss(line);
                if(iss>>cmd>>eq_num_1>>eq_num_2)
                    cout<<command.add(eq_num_1,eq_num_2)<<endl;
            }
            else if(command.command_starts_with(line,"subtract")){
                string cmd = "subtract";
                int eq_num_1 ;
                int eq_num_2 ;
                istringstream iss(line);
                if(iss>>cmd>>eq_num_1>>eq_num_2)
                    cout<<command.subtract(eq_num_1,eq_num_2)<<endl;
            }
            else if(command.command_starts_with(line,"substitute")){
                string cmd = "substitute" ;
                string variable_name;
                int eq_num_1 ;
                int eq_num_2 ;
                istringstream iss(line);
                if(iss>>cmd>>variable_name>>eq_num_1>>eq_num_2)
                    cout<<command.substitute(variable_name,eq_num_1,eq_num_2)<<endl;
            }
            else if(command.command_starts_with(line,"D_value")){
                cout<<command.cramer_matrix_determinant_value()<<endl;
            }
            else if(command.command_starts_with(line,"D")){
                string cmd = "D" ;
                string variable_name;
                istringstream iss(line);
                if(iss>>cmd>>variable_name){
                    vector<vector<float>> coeff = command.cramer_matrix_coeff_of_var(variable_name);
                    for(vector<float> vec : coeff){
                        for(float val : vec){
                            cout<<val<<" ";
                        }
                        cout<<endl;
                    }
                }
                else{
                    vector<vector<float>> coeff = command.cramer_matrix_coeff();
                    for(vector<float> vec : coeff){
                        for(float val : vec){
                            cout<<val<<" ";
                        }
                        cout<<endl;
                    }
                }
            }
                
            else{
                vector<float> vec = command.solve() ;
                for(float val : vec){
                    cout<<val<<endl;
                }
            }      
        }
    }
    return 0;
}