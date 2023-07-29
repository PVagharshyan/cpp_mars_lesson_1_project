#include "./headers/header.h"
#include "./headers/contact.h"

//friend methods

std::istream& operator>> (std::istream& in, Contact& obj) {
    do{
        std::cout << "name, lastname: ";
        getline(in, obj.name);
    }while (!obj.check_name());
    do{
        std::cout << "phon number(+374): ";
        in >> obj.phon_number;
    }while (!obj.check_phon_number());
    do{
        std::cout << "email: ";
        in >> obj.email;
    }while (!obj.check_email()); 
    return in;
}

std::ostream& operator<< (std::ostream& out, const Contact& obj) {
    out << "name: ";
    out << obj.name << std::endl;
    out << "phone number: ";
    out << obj.phon_number << std::endl;
    out << "email: "; 
    out << obj.email << std::endl;
    return out;
}

//initialisation of functions

std::vector<std::string> split (std::string str, char ch) {
    std::vector<std::string> result = {};
    std::string current_word = "";
    for (int i = 0;i < str.length();++i){
        if (str[i] != ch){
            current_word += str[i];
        }
        else {
            if (current_word != "")
                result.push_back(current_word);
            current_word = "";
        }
    }
    if (current_word != "")
        result.push_back(current_word);
    return result;
}

int exist (const std::vector<Contact>& v, const Contact& obj) {
    for (int i = 0;i < v.size();++i) { 
        if (v[i] == obj) {
            return i;
        }
    }
    return -1;
}

