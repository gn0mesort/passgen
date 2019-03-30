#ifndef MT_PASSGEN_PASSGEN_HPP
#define MT_PASSGEN_PASSGEN_HPP

#include <cstddef>

#include <random>
#include <fstream>
#include <string>

namespace mt::passgen {
  class generator {
  public:
    enum class alphabet {
      upper_case,
      lower_case,
      alphabetic,
      numeric,
      alphanumeric,
      symbols,
      ascii,
      no_space
    };

    generator(const alphabet abc);
    generator(const std::string &abc);
    std::string operator()(const std::size_t length);
  private:
    static std::random_device m_random;

    std::string m_alphabet{ "" };
  };
}

#endif
