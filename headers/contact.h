#pragma once

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
