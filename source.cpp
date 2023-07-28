#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Contact class declaration

class Contact;

//declaration of functions

std::vector<std::string> split(std::string, char);
int exist (const std::vector<Contact>&, const Contact&);

//Contact class initialisation 

class Contact{
private:
    std::string name;
    std::string phon_number;
    std::string email;
public: 
    Contact();
    bool check_name () const;
    bool check_phon_number () const;
    bool check_email() const;
    void set_contact(std::string, std::string, std::string);
    std::string get_name() const;
    std::string get_phon_number() const;
    std::string get_email() const;
    bool operator== (const Contact&) const;
    friend std::istream& operator>> (std::istream&, Contact&);
    friend std::ostream& operator<< (std::ostream&, const Contact&);
};

int main() {
    while (true) {
        
        //db all items appear in 'contacts'
        
        std::vector<Contact> contacts = {};
        std::string file_name = "db.txt";
        std::ifstream file;
        file.open(file_name);
        if (!file.is_open()) {
            std::cout << "Error: file not found please create following file(db.txt)" << std::endl;
            std::cout << "Warning: it's important that it's empty or it won't work properly" << std::endl;
            return 0;
        }
        else {
            std::string current_name = "";
            std::string current_phon_number = "";
            std::string current_email = "";
            Contact current_contact;
            while(std::getline(file, current_name)) { 
                std::getline(file, current_phon_number);
                std::getline(file, current_email);
                current_contact.set_contact(current_name, current_phon_number, current_email);   
                contacts.push_back(current_contact);
            }
        }
        char command = 0; 
        std::cout << "create(c), delete(d), search(s) exit(e)" << std::endl;
        std::string command_str = "";
        std::cin >> command_str;
        if (command_str.length() == 1 && (command_str[0] == 'c' || command_str[0] == 'd' || command_str[0] == 's' || command_str[0] == 'e')) {
            if (command_str[0] == 'c') {
                Contact current_contact;
                std::cin >> current_contact;
                if (exist(contacts, current_contact) != -1) {
                    std::cout << "Error: this data already exists" << std::endl; 
                    file.close();
                    continue;
                }
                contacts.push_back(current_contact);
            }
            else if (command_str[0] == 'd') {
                Contact deleting_contact;
                std::cin >> deleting_contact;
                if (exist(contacts, deleting_contact) == -1) {
                    std::cout << "Error: this cannot be deleted as it does not exist" << std::endl;
                    file.close();
                    continue;
                }
                contacts.erase(contacts.begin() + exist(contacts, deleting_contact));
            }
            else if (command_str[0] == 's') {
                Contact searched_contact;
                std::cin >> searched_contact;
                bool search_flag = false;
                for (int i = 0;i < contacts.size();++i) {
                    if (contacts[i] == searched_contact) {
                        std::cout << searched_contact;
                        search_flag = true;
                        break;
                    }
                }
                if (!search_flag) std::cout << "Error: The data you are looking for is not found" << std::endl;
            }
            else if (command_str[0] == 'e') {
                std::cout << "Thank you for using our app․:)" << std::endl;
                file.close();
                return 0;
            }
            else {
                std::cout << "Error: There is no such command, please follow the informational message that is given at the beginning of the request" << std::endl;
            }
        }
        file.close();
        std::ofstream update_file;
        update_file.open(file_name);
        for (int i = 0;i < contacts.size();++i) {
            update_file << contacts[i].get_name() << std::endl;
            update_file << contacts[i].get_phon_number() << std::endl;
            update_file << contacts[i].get_email() << std::endl;
        }
        update_file.close();
    }
    return 0;
}

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

