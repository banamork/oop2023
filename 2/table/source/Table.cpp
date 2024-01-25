#include "../include/Table.hpp"
#include <algorithm>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <tuple>
#include <type_traits>

namespace table {

Table::Table(std::string *names, int size) {
  if (names == nullptr)
    throw std::invalid_argument("Array of names is empty.");
  parameter::Parameter *data = new parameter::Parameter[size];
  for (int i = 0; i < size; i++) {
    if (names[i].empty()) {
      delete[] data;
      throw std::invalid_argument("Name of parameter is empty.");
    }
    data[i] = parameter::Parameter{names[i]};
  }
  this->data_ = data;
}

Table::Table(std::string name, int value) {
  parameter::Parameter param{name, value};
  this->size_ = 1;
  this->data_ = new parameter::Parameter[this->size_];
  this->data_[0] = param;
}

Table::Table(const Table &other) {
  delete[] this->data_;
  this->size_ = other.size_;
  if (other.data_) {
    std::copy(other.data_, other.data_ + other.size_, this->data_);
  } else {
    this->data_ = nullptr;
  }
}

Table::Table(Table &&other) {
  std::swap(this->data_, other.data_);
  std::swap(this->size_, other.size_);
}

Table &Table::operator=(const Table &other) {
  if (this != &other) {
    delete[] this->data_;
    this->size_ = other.size_;
    if (other.data_) {
      std::copy(other.data_, other.data_ + other.size_, this->data_);
    } else {
      this->data_ = nullptr;
    }
  }
  return *this;
}

Table &Table::operator=(Table &&other) noexcept {
  if (this != &other) {
    std::swap(this->data_, other.data_);
    std::swap(this->size_, other.size_);
  }
  return *this;
}

parameter::Parameter &Table::operator[](std::string name) {
  int result;
  for (int i = 0; i < this->size_; i++) {
    if (this->data_[i].get_name() == name) {
      result = i;
      break;
    }
  }
  return this->data_[result];
}

bool Table::operator()(const parameter::Parameter &param, int complexity,
                       parameter::Modes mode) {
  bool result = true;

  if (mode == parameter::Modes::Complexity)
    result = param.check_with_complexity(complexity);
  else if (mode == parameter::Modes::Benefit)
    result = param.check_with_benefit(complexity);
  else
    result = param.check_with_interference(complexity);

  return result;
}

Table &Table::operator+=(const parameter::Parameter &newparam) {
  int new_size = this->size_++;
  parameter::Parameter *new_data = new parameter::Parameter[new_size];
  std::copy(this->data_, this->data_ + this->size_, new_data);

  this->size_ = new_size;
  delete[] this->data_;

  this->data_ = new_data;

  return *this;
}

bool comp(const parameter::Parameter &a, const parameter::Parameter &b) {
  return a.get_name() < b.get_name();
}

void Table::sort_by_names() {
  std::sort(this->data_, this->data_ + this->size_, comp);
}

parameter::Parameter Table::get_max(std::string *names, int size) {
  if (size == 0 || names == nullptr) {
    throw std::invalid_argument("Empty array");
  }
  parameter::Parameter result;
  int max_val = -100000;
  for (int i = 0; i < size; i++) {
    parameter::Parameter &param = (*this)[names[i]];
    if (max_val < param.get_value()) {
      result = param;
    }
  }
  return result;
}

std::ostream &operator<<(std::ostream &s, const Table &table) {
  for (int i = 0; i < table.size_; i++) {
    s << table.data_[i] << '\n';
  }
  return s;
}

std::istream &operator>>(std::istream &s, Table &table) {
  int size;
  s >> size;
  if (s.good()) {
    if (size > 0) {
      parameter::Parameter p;
      s >> p;
      table += p;
    }
  }
  return s;
}

} // namespace table
