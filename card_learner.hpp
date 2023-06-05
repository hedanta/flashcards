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
public:
  CardManager cards;

private:
  std::string deck_id_{ "0" };
  CardsContainer study_deck_{ cards.GetDeck(deck_id_) };
  Flashcard current_card_;

public:
  CardLearner() = default;

  CardLearner(std::string& deck_id)
    : cards{}
    , deck_id_{deck_id}
    , study_deck_{ cards.GetDeck(deck_id_) }
    , current_card_{}
  {};

  ~CardLearner() = default;
  
  void SetCurrentDeck(std::string& deck_id);

  std::wstring GetDeckName();
  std::wstring GetDeckNameFromId(std::string& deck_id);
  std::string GetDeckId();
  const int GetDeckSize();
  Flashcard GetCard();
  std::wstring GetQuestion() { return GetCard().first; }
  std::wstring GetAnswer() { return GetCard().second; }

  const bool CheckUserAnswer(std::wstring& user_ans, std::wstring& card_ans);

  void EraseCurrentCard();
};