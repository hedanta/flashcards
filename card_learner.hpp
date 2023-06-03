#include "card_manager.hpp"

#include <nlohmann/json.hpp>

#include <codecvt>
#include <random>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::wstring, std::wstring>;
using CardsContainer = std::vector<Flashcard>;

namespace {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
}

class CardLearner {
private:
  CardManager cards;
  std::wstring deck_name_{Converter.from_bytes("All")};
  CardsContainer study_deck_{ cards.GetDeck(cards.GetDeckId(deck_name_)) };
  Flashcard current_card_;

public:
  CardLearner() = default;

  CardLearner(std::wstring& deck_name)
    : cards{}
    , deck_name_{deck_name}
    , study_deck_{ cards.GetDeck(cards.GetDeckId(deck_name)) }
    , current_card_{}
  {};

  ~CardLearner() = default;
  
  std::wstring GetDeckName() { return deck_name_; }
  const int GetDeckSize() {  return study_deck_.size();  }
  std::vector<std::wstring> GetAllDecks();
  void SetCurrentDeck(std::wstring& deck_name);

  Flashcard GetCard();

  std::wstring GetQuestion() { return GetCard().first; }
  std::wstring GetAnswer() { return GetCard().second; }

  const bool CheckUserAnswer(std::wstring& user_ans, std::wstring& card_ans);
  void EraseCurrentCard();
};