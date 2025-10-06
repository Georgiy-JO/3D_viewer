#ifndef SRC_CORE_SERVICE_SERVICE_H
#define SRC_CORE_SERVICE_SERVICE_H

#include <filesystem>
#include <string>

namespace service {
namespace converters {
float DoubleToFloat(const double input);
}
namespace character {
bool IntIsHash(const int& symbol);
bool IntIsNotEOF(const int& symbol);
}  // namespace character
namespace file {
bool IsFileOk(const std::string& file_name, const uintmax_t max_size);
void RemoveFile(const std::string& file_name);
}  // namespace file

}  // namespace service

#endif  // SRC_CORE_SERVICE_SERVICE_H