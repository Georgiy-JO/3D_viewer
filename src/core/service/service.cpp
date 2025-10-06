#include "service.h"

namespace service::file {
bool IsFileOk(const std::string& file_name, const uintmax_t max_size) {
  std::filesystem::path file_path(file_name);
  return std::filesystem::exists(file_path) &&
         std::filesystem::file_size(file_path) > 0 &&
         std::filesystem::file_size(file_path) < max_size;
}

void RemoveFile(const std::string& file_name) {
  std::filesystem::path file_path(file_name);
  std::filesystem::remove(file_path);
}
}  // namespace service::file

namespace service::character {
bool IntIsHash(const int& symbol) {
  return IntIsNotEOF(symbol) && symbol == '#';
}
bool IntIsNotEOF(const int& symbol) { return symbol != EOF; }
}  // namespace service::character

namespace service::converters {
float DoubleToFloat(const double input) {
  if (input >= static_cast<double>(std::numeric_limits<float>::max()))
    return std::numeric_limits<float>::max();
  else if (input <= static_cast<double>(std::numeric_limits<float>::lowest()))
    return std::numeric_limits<float>::lowest();
  else if (input > 0 &&
           input <= static_cast<double>(std::numeric_limits<float>::min()))
    return std::numeric_limits<float>::min();
  else if (input < 0 && input >= static_cast<double>(
                                     std::numeric_limits<float>::min() * (-1)))
    return std::numeric_limits<float>::min() * (-1);
  else
    return static_cast<float>(input);
}
}  // namespace service::converters
