#include "CardManager.hpp"

#include <nlohmann/json.hpp>

#include <random>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::string, std::string>;
using CardsContainer = std::vector<Flashcard>;

class CardLearner {
private:
  CardManager cards;
  std::string deck_name_{ "All" };
  CardsContainer study_deck_{ cards.GetDeck(cards.GetDeckId(deck_name_)) };
  Flashcard current_card_;

public:
  CardLearner() = default;

  CardLearner(std::string& deck_name)
    : cards{}
    , deck_name_{deck_name}
    , study_deck_{ cards.GetDeck(cards.GetDeckId(deck_name)) }
    , current_card_{}
  {};

  ~CardLearner() = default;
  
  const int GetDeckSize() {  return study_deck_.size();  }
  std::vector<std::string> GetAllDecks();
  void SetCurrentDeck(std::string& deck_name);

  Flashcard GetCard();

  const bool CheckUserAnswer(std::string& user_ans, std::string& card_ans);
  void EraseCurrentCard();
};