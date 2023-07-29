#include "./headers/header.h"
#include "./headers/contact.h"

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
        std::cin.ignore(1000, '\n');
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

