#include "passgen.hpp"

#include <limits>
#include <algorithm>

namespace mt::passgen {
  constexpr random_engine::result_type random_engine::max() const {
    return std::numeric_limits<result_type>::max();
  }

  constexpr random_engine::result_type random_engine::min() const {
    return std::numeric_limits<result_type>::min();
  }

  random_engine::result_type random_engine::operator()() {
    result_type r;
    m_urandom.read(reinterpret_cast<char*>(&r), sizeof(result_type));
    return r;
  }

  generator::generator(const alphabet abc) {
    switch (abc) {
      case alphabet::upper_case: {
        m_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        break;
      }
      case alphabet::lower_case: {
        m_alphabet = "abcdefghijklmnopqrstuvwxyz";
        break;
      }
      case alphabet::alphabetic: {
        m_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz";
        break;
      }
      case alphabet::numeric: {
        m_alphabet = "0123456789";
        break;
      }
      case alphabet::alphanumeric: {
        m_alphabet = "0123456789"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz";
        break;
      }
      case alphabet::symbols: {
        m_alphabet = " !\"#$%&\'()*+,-/:;<=>?@[\\]^_`{|}~";
        break;
      }
      case alphabet::ascii: {
        m_alphabet = " !\"#$%&\'()*+,-/:;<=>?@[\\]^_`{|}~"
                     "0123456789"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz";
        break;
      }
      case alphabet::no_space: {
        m_alphabet = "!\"#$%&\'()*+,-/:;<=>?@[\\]^_`{|}~"
                     "0123456789"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz";
        break;
      }
    }
    std::shuffle(m_alphabet.begin(), m_alphabet.end(), m_random);
  }

  generator::generator(const std::string &abc) :
  m_alphabet{ abc } {
    std::shuffle(m_alphabet.begin(), m_alphabet.end(), m_random);
  }

  std::string generator::operator()(const std::size_t length) {
    std::string r;
    r.resize(length);
    for (auto &c : r) {
      c = m_alphabet[m_random() % m_alphabet.size()];
    }
    return r;
  }
}
