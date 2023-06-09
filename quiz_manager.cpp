#include "quiz_manager.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::wstring, std::wstring>;
using CardsContainer = std::vector<Flashcard>;

QuizManager::QuizManager() = default;

QuizManager::QuizManager(std::string& deck_id)
: cards{}
, deck_id_{ deck_id }
, study_deck_{ cards.GetDeck(deck_id_) }
, current_card_{}
{};

QuizManager::~QuizManager() = default;

void QuizManager::EraseCurrentCard() {
  study_deck_.pop_back();
}

std::string QuizManager::GetCurrentDeckId() {
  return deck_id_;
}

std::wstring QuizManager::GetDeckNameFromId(std::string& deck_id) {
  return cards.GetDeckNameFromId(deck_id);
}

std::wstring QuizManager::GetCurrentDeckName() {
  return cards.GetDeckNameFromId(deck_id_);
}

Flashcard QuizManager::GetCard() {
  Flashcard card;

  if (GetCurrentDeckSize() > 0) {
    card = study_deck_.back();
  }

  return card;
}

const int QuizManager::GetCurrentDeckSize() {
  return study_deck_.size(); 
}

std::wstring QuizManager::GetQuestion() {
  return GetCard().first; 
}

std::wstring QuizManager::GetAnswer() {
  return GetCard().second; 
}

void QuizManager::SetCurrentDeck(std::string& deck_id) {
  deck_id_ = deck_id;
  study_deck_ = cards.GetDeck(deck_id_);
}

const bool QuizManager::CheckUserAnswer(std::wstring& user_ans, std::wstring& card_ans) {
  return user_ans == card_ans;
}