/*
 * File:   main.cpp
 * Author: Raymond Burkholder
 *         raymond@burkholder.net
 *
 * Created on November 30, 2018, 4:28 PM
 */

#include <vector>
#include <iostream>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_rule.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_lit.hpp>

#include <boost/spirit/include/phoenix_operator.hpp>

#define BOOST_SPIRIT_USE_PHOENIX_V3 1

namespace {

namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

//typedef uint8_t mac_t[ 6 ]; // has no operators
//typedef std::array<uint8_t,6> mac_t;  // has no insert
using vMac_t = std::vector<uint8_t>;   // needs to be 6 == sizeof

template<typename Iterator>
struct mac_parser_t: qi::grammar<Iterator, vMac_t()> {

  mac_parser_t(): mac_parser_t::base_type( ruleBytes ) {

    ruleHexDigit = qi::char_( "0-9" )[qi::_val = qi::_1 - '0' ];
    ruleHexLc    = qi::char_( "a-f" )[qi::_val = qi::_1 - 'a' + 10 ];
    ruleHexUc    = qi::char_( "A-F" )[qi::_val = qi::_1 - 'A' + 10 ];
    ruleHex      = ruleHexDigit | ruleHexLc | ruleHexUc;
    ruleByte     = (ruleHex >> ruleHex)[qi::_val = (qi::_1 << 4) + qi::_2];
    ruleBytes    =
         ruleByte >> qi::lit(':')
      >> ruleByte >> qi::lit(':')
      >> ruleByte >> qi::lit(':')
      >> ruleByte >> qi::lit(':')
      >> ruleByte >> qi::lit(':')
      >> ruleByte
      ;
  }

  qi::rule<Iterator, uint8_t()> ruleHexDigit;
  qi::rule<Iterator, uint8_t()> ruleHexLc;
  qi::rule<Iterator, uint8_t()> ruleHexUc;
  qi::rule<Iterator, uint8_t()> ruleHex;
  qi::rule<Iterator, uint8_t()> ruleByte;
  qi::rule<Iterator, vMac_t()>  ruleBytes;

};
}

int main( int argc, char** argv ) {

  const std::string sMac = "10:a0:CD:34:5e:f0";

  vMac_t vResult;
  vResult.reserve( 6 );

  using iterator_type = std::string::const_iterator;
  using mac_parser_string_t = mac_parser_t<iterator_type>;

  mac_parser_string_t parser;

  std::string::const_iterator iter = sMac.begin();
  std::string::const_iterator end  = sMac.end();

  auto result = qi::parse( iter, end, parser, vResult );

  if ( iter == end ) std::cout << "full string matched" << std::endl;

  std::cout << "result=(" << result << "):'" << std::hex;
  for ( uint16_t ch: vResult ) std::cout << ch;
  std::cout << "'" << std::endl;

  return 0;
}

