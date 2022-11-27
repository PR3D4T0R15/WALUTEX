#pragma once
#include "curl/curl.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <iostream>
#include "window_functions.h"

int getDataFromServer();
int updateArray(std::string);