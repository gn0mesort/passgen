#ifndef MT_PASSGEN_PASSGEN_HPP
#define MT_PASSGEN_PASSGEN_HPP

/**
 * @mainpage passgen
 * 
 * `passgen` is a password generation utility for Linux based operating
 * systems. It is made up of a [simple driver program](@ref main.cpp) and
 * a [generator](@ref mt::passgen::generator) object. `passgen` does make an
 * effort to ensure that generated passwords are unpredictable but it is
 * not intended to be treated as an infallible security tool.
 */

#include <cstddef>

#include <random>
#include <fstream>
#include <string>

namespace mt::passgen {
  /**
   * @brief A password generator.
   *
   * `generator` is a function-like object which generates sequences
   * of pseudo-random characters. Each seqeunce is based on an alphabet
   * (either a standard one or a custom alphabet one) which is provided to the
   * constructor. Regardless of how it is provided the alphabet will be
   * shuffled to make the mapping of random bytes to characters less
   * predictable.
   */
  class generator {
  public:

    /**
     * @brief An enumeration of standard generator alphabets.
     */
    enum class alphabet {
      /**
       * Uppercase latin characters A-Z.
       */
      upper_case,

      /**
       * Lowercase latin characters a-z.
       */
      lower_case,

      /**
       * Uppercase and lowercase latin characters.
       */
      alphabetic,

      /**
       * Arabic numerals 0-9.
       */
      numeric,

      /**
       * Alphabetic and numeric combined.
       */
      alphanumeric,

      /**
       * All typographical symbols from the ASCII set (including space).
       */
      symbols,

      /**
       * The full ASCII set.
       */
      ascii,

      /**
       * The full ASCII set except the space character.
       */
      no_space
    };

    /**
     * @brief Constructs a generator using an [alphabet](@ref alphabet)
     * value.
     *
     * @param abc The built in alphabet to select for use.
     */
    explicit generator(const alphabet abc);

    /**
     * @brief Constructs a generator using a custom alphabet.
     *
     * @param abc A string containing a custom alphabet to use.
     */
    explicit generator(const std::string &abc);

    /**
     * @brief Generate a password with the given length.
     *
     * @param length The length of the password string to generate.
     * @return The string representation of the generated password.
     */
    std::string operator()(const std::size_t length);
  private:
    /**
     * std::random_device is PROBABLY a secure generator on whatever system
     * you are using. However, the standard doesn't require it be secure or
     * even random. Using libstdc++ this is just a wrapper around RDRAND
     * (if supported) or /dev/urandom (if otherwise specified or RDRAND is
     * unsupported). I have opted to specify /dev/urandom. If this code is
     * compiled on Windows the token ("/dev/urandom") will in all likelihood
     * be ignored and you will get a Windows implementation (which is, to my
     * knowledge, also secure).
     *
     * You may wish to see https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/src/c%2B%2B11/random.cc#L91
     * for more information on how std::random_device is implented.
     */
    static std::random_device m_random;

    std::string m_alphabet{ "" };
  };
}

#endif
