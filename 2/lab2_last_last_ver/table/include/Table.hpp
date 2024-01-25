#ifndef TABLE_HPP
#define TABLE_HPP

#include "../../parameter/include/Parameter.hpp"

#include <istream>
#include <ostream>
#include <string>

namespace table {

/**
 * @brief Class representing a table.
 */
class Table {

private:
  int size_; ///< Size of the table
  parameter::Parameter *data_; ///< Data stored in the table

public:
  /**
   * @brief Default constructor for Table.
   */
  Table() = default;

  /**
    * @brief Constructor creating a table with specified names and size.
    * @param names Array of names
    * @param size Size of the table
    * @throws std::invalid_argument if array of names is empty.
    * @throws std::invalid_argument if name of parameter is empty.
    */
  Table(std::string *names, int size);


  /**
   * @brief Constructor creating a table with a single name and value.
   * @param name Name of the parameter
   * @param value Value of the parameter
   */
  Table(std::string name, int value);

  /**
   * @brief Copy constructor for Table.
   * @param other Another Table object to be copied
   */
  Table(const Table &other);

  /**
   * @brief Move constructor for Table.
   * @param other Another Table object to be moved
   */
  Table(Table &&other);

  /**
   * @brief Destructor for Table.
   */
  ~Table() { delete[] this->data_; }

  /**
   * @brief Copy assignment operator for Table.
   * @param other Another Table object to be assigned
   * @return Reference to the assigned object
   */
  Table &operator=(const Table &other);

  /**
   * @brief Move assignment operator for Table.
   * @param other Another Table object to be moved
   * @return Reference to the moved object
   */
  Table &operator=(Table &&other) noexcept;

  /**
   * @brief Overloaded subscript operator to access a parameter by name.
   * @param name Name of the parameter
   * @return Reference to the parameter with the given name
   */
  parameter::Parameter &operator[](std::string name);

  /**
   * @brief Overloaded function call operator to check parameter with complexity and mode.
   * @param param Parameter to check
   * @param complexity Complexity value
   * @param mode Mode of check
   * @return true if the check is successful, false otherwise
   */
  bool operator()(const parameter::Parameter &param, int complexity,
                  parameter::Modes mode);


  /**
   * @brief Overloaded addition assignment operator to add a new parameter to the table.
   * @param new_param New parameter to be added
   * @return Reference to the modified Table
   */
  Table &operator+=(const parameter::Parameter &new_param);

  /**
   * @brief Sorts the table by names.
   */
  void sort_by_names();

  /**
   * @brief Retrieves the parameter with the maximum value for the given names.
   * @param name Array of names
   * @param size Size of the array
   * @return The parameter with the maximum value
   * @throws std::invalid_argument if array is empty
   */
  parameter::Parameter get_max(std::string *name, int size);

  /**
   * @brief Overloaded output operator for Table objects.
   * @param s Output stream
   * @param table Table object to output
   * @return Output stream
   */
  friend std::ostream &operator<<(std::ostream &s, const Table &table);

  /**
   * @brief Overloaded input operator for Table objects.
   * @param s Input stream
   * @param other Table object for input
   * @return Input stream
   */
  friend std::istream &operator>>(std::istream &s, Table &other);
};

} // namespace table

#endif
