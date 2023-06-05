#include "card_learner.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::wstring, std::wstring>;
using CardsContainer = std::vector<Flashcard>;

void CardLearner::EraseCurrentCard() {
  study_deck_.pop_back();
}

Flashcard CardLearner::GetCard() {
  Flashcard card;

  if (GetDeckSize() > 0) {
    card = study_deck_.back();
  }

  return card;
}

std::wstring CardLearner::GetDeckName() { 
  return cards.GetNameFromId(deck_id_); 
}

std::wstring CardLearner::GetDeckNameFromId(std::string& deck_id) {
  return cards.GetNameFromId(deck_id);
}

const int CardLearner::GetDeckSize() { 
  return study_deck_.size(); 
}

std::string CardLearner::GetDeckId() {
  return deck_id_;
}

void CardLearner::SetCurrentDeck(std::string& deck_id) {
  deck_id_ = deck_id;
  study_deck_ = cards.GetDeck(deck_id_);
}

const bool CardLearner::CheckUserAnswer(std::wstring& user_ans, std::wstring& card_ans) {
  return user_ans == card_ans;
}