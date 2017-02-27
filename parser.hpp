#include <regex>
#include <string>
#include <map>

namespace parser {

class Parser {
public:
  using Param=std::map<std::string,std::string>;  
  
  Parser() { };

  Param& init(std::string& input) {
    p["protocol"] = _get_protocol(input);
    p["host"] =  _get_address(input);
    p["port"] = _get_port(input);
    p["topic"] = _get_topic(input);
  }

  const Param& get() { return p;}

private:
  Param p;
  std::smatch m;

std::string _get_protocol(std::string& s,const std::string& d="kafka") {
  if(std::regex_search (s,m,std::regex("^[A-Za-z]+"))) {
    return std::move(std::string(m[0]));
  }
  return std::move(d);
}
std::string _get_address(std::string& s,const std::string& d="localhost") {
  if (std::regex_search (s,m,std::regex("(\\d+\\.){3}\\d+")))
    return std::move(std::string(m[0]));
  return std::move(d);
}
std::string _get_port(std::string& s,const std::string& d="9092") {
  if (std::regex_search (s,m,std::regex(":\\d+/"))) {
    std::string result(m[0]);
    return std::move( result.substr(0,result.length()-1) );
  }
  return std::move(d);
}
std::string _get_topic(std::string& s,const std::string& d="") {
  std::smatch m;
  if (std::regex_search (s,m,std::regex("[A-Za-z0-9-_:.]*$")))
    return std::move(std::string(m[0]));
  return std::move(d);
}

};

}
