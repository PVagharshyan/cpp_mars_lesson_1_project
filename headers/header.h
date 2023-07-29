#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Contact class declaration

class Contact;

//declaration of functions

std::vector<std::string> split(std::string, char);
int exist (const std::vector<Contact>&, const Contact&);
