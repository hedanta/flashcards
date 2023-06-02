#include "CardLearner.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::string, std::string>;
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

std::vector<std::string> CardLearner::GetAllDecks() {
  return cards.GetAllDecks();
}

void CardLearner::SetCurrentDeck(std::string& deck_name) {
  deck_name_ = deck_name;
  study_deck_ = cards.GetDeck(cards.GetDeckId(deck_name));
}

const bool CardLearner::CheckUserAnswer(std::string& user_ans, std::string& card_ans) {
  return user_ans == card_ans;
}