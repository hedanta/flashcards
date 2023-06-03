#include "card_learner.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::wstring, std::wstring>;
using CardsContainer = std::vector<Flashcard>;

void CardLearner::EraseCurrentCard() {
  study_deck_.pop_back();
}

Flashcard CardLearner::GetCard() {
  int deck_size = CardLearner::GetDeckSize();
  Flashcard card;

  if (deck_size > 0) {
    card = study_deck_.back();
  }

  return card;
}

std::vector<std::wstring> CardLearner::GetAllDecks() {
  return cards.GetAllDecks();
}

void CardLearner::SetCurrentDeck(std::wstring& deck_name) {
  deck_name_ = deck_name;
  study_deck_ = cards.GetDeck(cards.GetDeckId(deck_name));
}

const bool CardLearner::CheckUserAnswer(std::wstring& user_ans, std::wstring& card_ans) {
  return user_ans == card_ans;
}