#include "../parser.h"
#include <fstream>

namespace s21::inbound_model::parser {
  using namespace service_functions;

Parser::Parser(Model3D& model_,const std::string& file_name_):m_model(model_),m_file_name(file_name_){}

void Parser::SetFileName(const std::string& file_name_){
  m_file_name=file_name_;
}

void Parser::SetModelRef(Model3D& model_){
  m_model=model_;
}

std::string Parser::GetFilename() const{
  return m_file_name;
}

Model3D& Parser::GetModelRef(){
  return m_model;
}

Model3D& Parser::ParseIt() {
  std::ifstream ifs(m_file_name);
  if (!ifs.is_open()) {
    ModelNormalizer();
    throw std::ios_base::failure("File not found: " + m_file_name);
  }
  auto prefix_array = CreatePrefixArray();
  std::string line{""};
  bool prefix_o_flag = false;

  while (std::getline(ifs, line)) {
    LSpaceChTrim(line);
    for (size_t i = 0; line.size() != 0 && !IsHash(line[0]) && i < prefix_array.size(); i++) {
      if (LineStartsWithPrefix(line, prefix_array[i])) {
        line.erase(0, prefix_array[i].length());
        if (prefix_array[i] == "v")
          PrefixV(line);
        else if (prefix_array[i] == "f")
          PrefixF(line);
        else if (prefix_array[i] == "l")
          PrefixL(line);
        else if (prefix_array[i] == "p")
          PrefixP(line);
        else if (prefix_array[i] == "o")
          prefix_o_flag |= PrefixO(line);
        break;
      }
    }
  }
  if (!prefix_o_flag){
    std::string new_name= m_file_name;
    new_name.erase((new_name.size() - 4), 4);
    new_name.erase(
        new_name.begin(),
        (std::find_if(new_name.rbegin(), new_name.rend(), [](int ch) {
          return IsSlash(ch);
        })).base());
    ModelNameSetter(new_name);
  } 
  ifs.close();

  ModelNormalizer();
  return m_model;
}

void Parser::ModelNormalizer() {
  m_model.CenterScale();
  // m_model.AddSingleVertEdges();  // may become needed
  m_model.ManageEdges();
}

}   //s21::inbound_model::parser