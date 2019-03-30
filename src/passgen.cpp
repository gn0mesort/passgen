#include "passgen.hpp"

#include <limits>
#include <algorithm>

namespace mt::passgen {
  std::random_device generator::m_random{ "/dev/urandom" };

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
