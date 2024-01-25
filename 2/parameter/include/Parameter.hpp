#ifndef PARAMETER_HPP
#define PARAMETER_HPP

#include <ostream>
#include <string>

namespace parameter {

enum D_20 : int { MinValue = 1, MaxValue = 20 };

enum Limits : int { Min = 1, Max = 20 };

enum class Modes {
  Complexity,
  Benefit,
  Interference,
};

class Parameter {
private:
  std::string name_;
  int value_ = Limits::Min;

  /**
   * @brief Check whether the given value is valid
   * @param value The value to be checked
   * @return True if the value is valid, false otherwise
   */
  bool is_valid(int value) const;

public:

  /**
   * @brief Default constructor for Parameter
   */
  Parameter() = default;

  /**
   * @brief Constructor with name
   * @param name The name of the parameter
   */
  explicit Parameter(std::string name);

  /**
   *  @brief Constructor with name and value
   * @param name The name of the parameter
   * @param value The value of the parameter
   */
  Parameter(std::string name, int value);

  /**
   *  @brief Get the name of the parameter
   * @return The name of the parameter
   */
  std::string get_name() const;

  /**
   * @brief Set the name of the parameter
   * @param name The name to be set
   * @throws std::invalid_argument if string is empty
   */
  void set_name(std::string name);


  /**
   * @brief Get the value of the parameter
   * @return The value of the parameter
   */
  int get_value() const;

  /**
   * @brief Set the value of the parameter
   * @param value The value to be set
   * @throws std::invalid_argument if you have gone beyond the borders
   */
  void set_value(int value);

  /**
   * @brief Check with a complexity value
   * @param complexity The complexity value to be checked
   * @return True if the check is successful, false otherwise
   */
  bool check_with_complexity(int complexity) const;

  /**
   * @brief Check with a benefit value
   * @param benefit The benefit value to be checked
   * @return True if the check is successful, false otherwise
   */
  bool check_with_benefit(int complexity) const;

  /**
   * @brief Check with an interference value
   * @param interference The interference value to be checked
   * @return True if the check is successful, false otherwise
   */
  bool check_with_interference(int complexity) const;

  /**
   * @brief Overloaded operator to add a value to the parameter
   * @param changing The value to be added
   * @return A reference to the modified parameter
   * @throws std::invalid_argument if you have gone beyond the borders
   */
  Parameter &operator+=(int changing);

  /**
   * @brief Output stream operator overloading for Parameter
   * @param s The output stream
   * @param param The parameter to be output
   * @return The output stream
   */
  friend std::ostream &operator<<(std::ostream &s, const Parameter &param);

  /**
    * @brief Input stream operator overloading for Parameter
    * @param s The input stream
    * @param param The parameter to be input
    * @return The input stream
    */
  friend std::istream &operator>>(std::istream &s, Parameter &param);
};
} // namespace parameter
#endif
