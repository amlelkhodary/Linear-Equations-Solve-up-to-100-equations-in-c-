#include "linear_equations.h"

Linear_equations::Linear_equations(){}

void Linear_equations::set_nummber_of_equations(int _equations_num){
    equations_num = _equations_num ;
}

int Linear_equations::get_nummber_of_equations(){
    return equations_num;
}

void Linear_equations::set_equation(string _equation){
    equations.push_back(_equation);
}

vector<string> Linear_equations::get_equations(){
    return equations;
}

void Linear_equations::modify_all_equations(){
    for(string eq : equations){
        if(variables.size() < equations_num)
            find_variable_names(eq);
        sort(variables.begin(),variables.end());
        auto duplicated = unique(variables.begin(), variables.end()); 
        variables.erase(duplicated, variables.end());
    }
    
    while(variables.size() > equations_num){
        variables.pop_back();
    }
    // for(string val : variables){
    //     cout<<val<<endl;
    // }
    for(string eq : equations){
        find_coefficients(eq);
    }
    // for(vector<float> val:coefficients){
    //     for(float val2:val){
    //         cout<<val2<<" ";
    //     }
    //     cout<<endl;
    // }
    for(string eq : equations){
        find_constants(eq);
    }
    for(int i=0; i<equations.size();i++){
        format_equations(i);
    }
}

void Linear_equations::find_variable_names(string _eq){
    int char_count = 0 ;
    istringstream iss(_eq);
    string var;
    string num;
    vector<int> var_num;
    float coeff;
    char ch;
    bool names_contain_int = false;
    vector<string> variable_names;
    bool string_ok = true;
    while(iss>>ch){   
        char_count++;
        if(isalpha(ch)){
            var.push_back(ch);
            string_ok = false;
        }
        else if(isdigit(ch) && !string_ok){
            names_contain_int = true;
            num.push_back(ch); 
        }
        else if (ch == '+' || ch == '-' || ch == '=' || char_count == _eq.size()){ 
            if(!var.empty()){
                variable_names.push_back(var);
                var_num.push_back(stof(num));
                num.clear();
                var.clear();
            }
            string_ok = true;
        }
    }
    if(!names_contain_int){
        sort(variable_names.begin(),variable_names.end());
    }
    else{
        sort(var_num.begin(),var_num.end());
        for(int i=0; i<variable_names.size(); i++){
            string var_num_to_str = to_string(var_num[i]) ;
            for(int j=0; j<var_num_to_str.length(); j++){
                variable_names[i].push_back(var_num_to_str[j]);
            }
        }
    }
    for(string variable : variable_names){
        variables.push_back(variable);
    } 
}

void Linear_equations::find_coefficients(string _eq){
    int char_count = 0 ;
    char last_sign = '0';
    char last_char = '0';
    istringstream iss(_eq);
    string coeff;
    string var_name;
    char ch;
    float eq_coeff[equations_num] = {0};
    bool is_RHS = false;
    while(iss>>ch){
        char_count ++ ;
        if(isdigit(ch)){
            if(var_name.empty())
                coeff.push_back(ch);
            else
               var_name.push_back(ch); 
        }
        else if(isalpha(ch) ){
            var_name.push_back(ch);
            if((last_char == '0' || last_char == '+' || last_char == '-' || last_char == '=') && coeff.empty()){
                char c = 1+'0';
                coeff.push_back(c);
            }
        }
        if (ch == '+' || ch == '-' || ch == '=' || char_count == _eq.size()){ 
            if(!coeff.empty() && !var_name.empty()){
                for(int i=0; i<variables.size(); i++){
                    if(variables[i] == var_name){
                        if(!is_RHS){
                            if(last_sign == '-' )
                                eq_coeff[i]-=stof(coeff);
                            else
                                eq_coeff[i]+=stof(coeff);
                        }
                        else{
                            if(last_sign == '+' || last_sign == '=')
                                eq_coeff[i]-=stof(coeff);
                            else if (last_sign == '-')
                                eq_coeff[i]+=stof(coeff);
                        }
                    }
                }
            }
            last_sign = ch;
            coeff.clear();
            var_name.clear();
        }
        last_char = ch;
        if(last_char == '=') is_RHS = true;
    }
    vector<float> vec(eq_coeff, eq_coeff + equations_num);
    coefficients.push_back(vec);
    
    // for(float val : vec){
    //     cout<<val<<" ";
    // }
    // cout<<endl;
}

void Linear_equations::find_constants(string _eq){
    float constant = 0.0;
    int char_count = 0;
    istringstream iss(_eq);
    string num;
    string var;
    char ch;
    bool is_RHS = false;
    char last_sign;
    while(iss>>ch){
        char_count++;
        if(isdigit(ch)){
            num.push_back(ch);
        }
        else if(isalpha(ch)){
            var.push_back(ch);
        }
        if (ch == '+' || ch == '-' || ch == '=' || char_count == _eq.size()){
            if(empty(var) && !empty(num)){
                // cout<<"ch = "<<ch<<endl;
                if(!is_RHS){
                    if(last_sign == '-')
                        constant+=stof(num);
                    else
                        constant-=stof(num);         
                }
                else{
                    if(last_sign == '+' || last_sign == '=')
                        constant+=stof(num);
                    else if (last_sign == '-')
                        constant-=stof(num);
                }
            }
            var.clear();
            num.clear();
            last_sign = ch;
        }
        if(ch == '=') is_RHS = true;
    }
    // cout<<constant<<endl;
    constants.push_back(constant);
}

void Linear_equations::format_equations(int eq_index){
    ostringstream oss;
    for(int i=0; i<variables.size(); i++){
        if(coefficients[eq_index][i] != 0){
            if(coefficients[eq_index][i] > 0 && i==0)
                oss<<coefficients[eq_index][i];
            else if(coefficients[eq_index][i] > 0 && i!=0)
                oss<<"+"<<coefficients[eq_index][i];
            else if(coefficients[eq_index][i] < 0)
                oss<<coefficients[eq_index][i];
            oss<<variables[i];
        }
    }
    oss<<"="<<constants[eq_index];
    string result = oss.str();
    formatted_equations.push_back(result);
    cout<<result<<endl;
}