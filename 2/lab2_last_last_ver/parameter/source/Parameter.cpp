#include "../include/Parameter.hpp"
#include <ios>
#include <ostream>
#include <stdexcept>
#include <string>

#include <iostream>

namespace parameter {

bool Parameter::is_valid(int value) const {
  return value >= Limits::Min && value <= Limits::Max;
}

Parameter::Parameter(std::string name) { this->set_name(name); }

Parameter::Parameter(std::string name, int value) : Parameter(name) {
  this->set_value(value);
}

std::string Parameter::get_name() const { return this->name_; }

void Parameter::set_name(std::string name) {
  if (name.empty())
    throw std::invalid_argument("Name of Parameter is empty.");
  this->name_ = name;
}

int Parameter::get_value() const { return this->value_; }

void Parameter::set_value(int value) {
  if (is_valid(value) == false)
    throw std::invalid_argument("Value of Parameter is out of range.");
  this->value_ = value;
}

int generate_random(int low_edge, int high_edge) {
  srand(time(NULL));
  int num = low_edge + rand() % (high_edge - low_edge + 1);
  return num;
}

bool Parameter::check_with_complexity(int complexity) const {
  int d_20_value = generate_random(D_20::MinValue, D_20::MaxValue);
  bool result = true;
  if (d_20_value == D_20::MinValue) {
    return false;
  } else if (d_20_value == D_20::MaxValue) {
    return true;
  } else {
    result = (this->value_ + d_20_value >= complexity);
  }
  return result;
}

bool Parameter::check_with_benefit(int complexity) const {
  int d_20_value = std::max(generate_random(D_20::MinValue, D_20::MaxValue),
                            generate_random(D_20::MinValue, D_20::MaxValue));
  bool result = true;
  if (d_20_value == D_20::MinValue) {
    return false;
  } else if (d_20_value == D_20::MaxValue) {
    return true;
  } else {
    result = (this->value_ + d_20_value >= complexity);
  }
  return result;
}

bool Parameter::check_with_interference(int complexity) const {
  int d_20_value = std::min(generate_random(D_20::MinValue, D_20::MaxValue),
                            generate_random(D_20::MinValue, D_20::MaxValue));
  bool result = true;
  if (d_20_value == D_20::MinValue) {
    return false;
  } else if (d_20_value == D_20::MaxValue) {
    return true;
  } else {
    result = (this->value_ + d_20_value >= complexity);
  }
  return result;
}

Parameter &Parameter::operator+=(int changing) {
  if (is_valid(this->value_ + changing) == false)
    throw std::invalid_argument("Value of Parameter is out of range.");
  this->value_ += changing;
  return *this;
}

std::ostream &operator<<(std::ostream &s, const Parameter &param) {
  s << param.name_ << " " << param.value_;
  return s;
}

std::istream &operator>>(std::istream &s, Parameter &param) {
  std::string name;
  int value;
  s >> name >> value;
  if (s.good()) {
    if (name.empty() != false && param.is_valid(value) != false) {
      param.name_ = name;
      param.value_ = value;
    } else {
      s.setstate(std::ios::failbit);
    }
  }
  return s;
}

} // namespace parameter
