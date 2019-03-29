#include <cinttypes>
#include <cstddef>
#include <cctype>

#include <iostream>
#include <string>
#include <limits>
#include <sstream>

#include <getopt.h>

#include "passgen.hpp"

using namespace mt::passgen;

int print_help(int argc, char **argv);
int print_version(int argc, char **argv);
generator::alphabet parse_alphabet(const std::string &arg);
std::size_t parse_length(const std::string &arg);

int main(int argc, char **argv) {
  generator gen{ generator::alphabet::ascii };
  std::size_t length{ 64 };
  bool custom_set{ false };
  try {
    option long_opts[]{
      { "help", no_argument, nullptr, 'h' },
      { "version", no_argument, nullptr, 'v' },
      { "alphabet", required_argument, nullptr, 'a' },
      { "length", required_argument, nullptr, 'l' },
      { "custom", required_argument, nullptr, 'c' },
      { nullptr, no_argument, nullptr, 0 }
    };
    const char *opts = "hva:l:c:";
    for (
      int opt = 0;
      (opt = getopt_long(argc, argv, opts, long_opts, nullptr)) != -1;
    ) {
      switch (opt) {
        case 'h': {
          return print_help(argc, argv);
        }
        case 'v': {
          return print_version(argc, argv);
        }
        case 'a': {
          if (!custom_set) {
            gen = generator{ parse_alphabet(optarg) };
          }
          break;
        }
        case 'l': {
          length = parse_length(optarg);
          break;
        }
        case 'c': {
          gen = generator{ optarg };
          custom_set = true;
          break;
        }
        default: {
          throw std::runtime_error{ "Invalid arguments. Try --help" };
        }
      }
    }
    std::cout << gen(length) << std::endl;
  }
  catch (std::exception &err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }
  return 0;
}

#define MT_HELP_TEXT \
"Usage: " << argv[0] << " [OPTION]...\n" \
"Generate passwords.\n" \
"\n" \
"Mandatory arguments to long options are mandatory for short options too.\n" \
"  -h, --help               Disply this help text and exit.\n" \
"  -v, --version            Output version information and exit.\n" \
"  -a, --alphabet=ALPHABET  Use the specified alphabet when generating\n" \
"                             passwords.\n" \
"                             Must be one of: upper, lower, alpha,\n" \
"                             numeric, alphanumeric, symbol, ascii, or\n" \
"                             nospace (defaults ascii).\n" \
"  -l, --length=LENGTH      Generate a password of the specified length\n" \
"                             (defaults to 64).\n" \
"  -c, --custom=ALPHABET    Use a custom alphabet when generating\n" \
"                             passwords. This will override \'a\' if it\n" \
"                             was used.\n" \
"\n" \
"Exit status:\n" \
"  0 if successful.\n" \
"  1 if generation failed.\n" \
"\n" \
"GitHub repo: <https://github.com/gn0mesort/passgen>\n" \
"Written by Alexander Rothman <gnomesort@megate.ch>"

int print_help(int, char **argv) {
  std::cout << MT_HELP_TEXT << std::endl;
  return 0;
}

#undef MT_HELP_TEXT

#ifndef MT_VERSION
#define MT_VERSION "unknown"
#endif

#define MT_VERSION_TEXT \
argv[0] << " version " MT_VERSION

int print_version(int, char **argv) {
  std::cout << MT_VERSION_TEXT << std::endl;
  return 0;
}

#undef MT_VERSION_TEXT

generator::alphabet parse_alphabet(const std::string &arg) {
  std::string tmp{ "" };
  for (const auto &c : arg) {
    tmp += std::tolower(c);
  }
  generator::alphabet r;
  if (tmp == "upper") {
    r = generator::alphabet::upper_case;
  }
  else if (tmp == "lower") {
    r = generator::alphabet::lower_case;
  }
  else if (tmp == "alpha") {
    r = generator::alphabet::alphabetic;
  }
  else if (tmp == "numeric") {
    r = generator::alphabet::numeric;
  }
  else if (tmp == "alphanumeric") {
    r = generator::alphabet::alphanumeric;
  }
  else if (tmp == "symbol") {
    r = generator::alphabet::symbols;
  }
  else if (tmp == "ascii") {
    r = generator::alphabet::ascii;
  }
  else if (tmp == "nospace") {
    r = generator::alphabet::no_space;
  }
  else {
    throw std::runtime_error{ "\"" + arg + "\" is not a valid alphabet." };
  }
  return r;
}

std::size_t parse_length(const std::string &arg) {
  std::istringstream convert{ arg };
  std::size_t r{ 0 };
  convert >> r;
  return r;
}

