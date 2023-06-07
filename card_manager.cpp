#include "card_manager.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::wstring, std::wstring>;
using CardsContainer = std::vector<Flashcard>;

CardManager::CardManager() = default;

CardManager::~CardManager() = default;

void CardManager::EraseCurrentCard() {
  study_deck_.pop_back();
}

Flashcard CardManager::GetCard() {
  Flashcard card;

  if (GetDeckSize() > 0) {
    card = study_deck_.back();
  }

  return card;
}

std::wstring CardManager::GetDeckName() {
  return cards.GetNameFromId(deck_id_); 
}

std::wstring CardManager::GetDeckNameFromId(std::string& deck_id) {
  return cards.GetNameFromId(deck_id);
}

const int CardManager::GetDeckSize() {
  return study_deck_.size(); 
}

std::string CardManager::GetDeckId() {
  return deck_id_;
}

std::wstring CardManager::GetQuestion() {
  return GetCard().first; 
}

std::wstring CardManager::GetAnswer() {
  return GetCard().second; 
}

void CardManager::SetCurrentDeck(std::string& deck_id) {
  deck_id_ = deck_id;
  study_deck_ = cards.GetDeck(deck_id_);
}

const bool CardManager::CheckUserAnswer(std::wstring& user_ans, std::wstring& card_ans) {
  return user_ans == card_ans;
}