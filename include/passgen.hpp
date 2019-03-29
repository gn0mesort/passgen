#ifndef MT_PASSGEN_PASSGEN_HPP
#define MT_PASSGEN_PASSGEN_HPP

#include <cstddef>

#include <random>
#include <fstream>
#include <string>

namespace mt::passgen {
  class random_engine {
  public:
    using result_type = std::default_random_engine::result_type;
    constexpr result_type max() const;
    constexpr result_type min() const;
    result_type operator()();
  private:
    std::ifstream m_urandom{ "/dev/urandom", std::ios::binary };
  };

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
    std::string m_alphabet{ "" };
    random_engine m_random{ };
  };
}

#endif
