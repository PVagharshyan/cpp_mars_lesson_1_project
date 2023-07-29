#include "./headers/header.h"
#include "./headers/contact.h"
//Contact methods

Contact::Contact() 
    : name(""), phon_number(""), email("")
{}

bool Contact::check_name () const {
    std::vector<std::string> splited_str = split(name, ' ');
    if (splited_str.size() != 2) {
        std::cout << "Error: The name must contain two words: first name and last name." << std:: endl;
        return false;
    }
    return true;
}

bool Contact::check_phon_number () const {
    std::string code = "+374";
    for (int i = 0;i < code.length();++i){
        if (code[i] != phon_number[i]){
            std::cout << "Error: Number must begin with +374";
            return false;
        }
    }
    if (phon_number.length() != 12) {
        std::cout << "Error: generally Armenian numbers contain 12 symbols" << std::endl;
        return false;
    }
    for (int i = 4;i < phon_number.length();++i) {
        int current_number = (int)phon_number[i] - (int)'0'; 
        if (!(current_number <= 9 && current_number >= 0)) {
            std::cout << "Error: the number cannot contain any symbols other than numbers except for the first + sign" << std::endl;
            return false;
        }
    }
    return true; 
}

bool Contact::check_email () const {
    if (email[email.length() - 1] == '@' || email[0] == '@'){
        std::cout << "Error: cannot start or end with @ sign." << std::endl;
    }
    std::vector<std::string> splited_str = split(email, '@');
    if (splited_str.size() != 2) {
        std::cout << "Error: the specified address contains more than one @ sign." << std::endl;
        return false;
    }
    std::vector<std::string> splited_site = split(splited_str[1], '.');
    if (splited_site.size() != 2) {
        std::cout << "Error: respectively the address site is not specified correctly" << std::endl;
        return false;
    }
    return true; 
}

void Contact::set_contact (std::string n, std::string p, std::string e) {
    name = n;
    phon_number = p;
    email = e;
}

std::string Contact::get_name () const {
    return name;
}
std::string Contact::get_phon_number() const {
    return phon_number;
}
std::string Contact::get_email() const {
    return email;
}

bool Contact::operator== (const Contact& obj) const{
    return (
            obj.name == name &&
            obj.phon_number == phon_number &&
            obj.email == email
           );
}
