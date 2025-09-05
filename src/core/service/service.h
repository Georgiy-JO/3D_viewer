#ifndef SRC_CORE_SERVICE_SERVICE_H
#define SRC_CORE_SERVICE_SERVICE_H

#include <string>
#include <filesystem>

namespace s21::service
{
    namespace converters
    {
        float DoubleToFloat(const double input);
    }
    namespace character{
        bool IntIsHash(const int& symbol);
        bool IntIsNotEOF(const int& symbol);
    }
    namespace file
    {
        bool IsFileOk(const std::string& file_name, const uintmax_t max_size);
        void RemoveFile(const std::string& file_name);
    }
    
} // namespace s21::service


#endif //SRC_CORE_SERVICE_SERVICE_H