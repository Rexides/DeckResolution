#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace po = boost::program_options;
namespace pt = boost::property_tree;

struct Card {
  uint success;
  uint failure;
  Card(uint s, uint f) {
    success = s;
    failure = f;
  }
};

class Deck {
public:

  void addCard(Card& card){
    _cards.push_back(card);
  }

  void suffle() {
    std::random_shuffle(_cards.begin(), _cards.end());
  }

  Card draw() {
    Card card = _cards.back();
    _cards.pop_back();
    return card;
  }

private:
  typedef std::vector<Card> vector_card;
  vector_card _cards;

};

void loadDeck(std::string deck_file, Deck& deck) {
  pt::ptree deck_desc;
  pt::read_json(deck_file, deck_desc);

  for (auto& c : deck_desc.get_child("cards")) {
    uint amount = c.second.get("amount", 1);
    uint success = c.second.get("success", 0);
    uint failure = c.second.get("failure", 0);
    Card card(success, failure);
    for (int i = 0; i < amount; i++) {
      deck.addCard(card);
    }
  }
}

int main(int argc, char* argv[]) {
  po::options_description desc("Options");
  desc.add_options()
  ("deck", po::value<std::string>(), "The JSON file describing the deck(s) you want to use")
  ;
  po::variables_map options;
  po::store(po::parse_command_line(argc, argv, desc), options);

  Deck deck;
  loadDeck(options["deck"].as<std::string>(), deck);
  deck.suffle();
  
  return 0;
}