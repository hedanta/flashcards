﻿#include <quiz/quiz_manager.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>

namespace {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
}

QuizManager::QuizManager() = default;

QuizManager::QuizManager(const std::string& deck_id)
  : cards{}
  , deck_id_{ deck_id }
  , study_deck_{ cards.GetShuffledDeck(deck_id_) }
  , current_card_{}
{};

void QuizManager::EraseCurrentCard() {
  study_deck_.pop_back();
}

const DeckContainer QuizManager::LoadAllDecks() {
  return cards.GetAllDecks();
}

const std::string QuizManager::GetCurrentDeckId() {
  return deck_id_;
}

const std::wstring QuizManager::GetDeckNameFromId(const std::string& deck_id) {
  return cards.GetDeckNameFromId(deck_id);
}

const std::wstring QuizManager::GetCurrentDeckName() {
  return cards.GetDeckNameFromId(deck_id_);
}

const Flashcard QuizManager::GetCard() {
  Flashcard card;

  if (GetCurrentDeckSize() > 0) {
    card = study_deck_.back();
  }

  return card;
}

const CardsWithId QuizManager::GetCardsList() {
  std::string deck_id = "0";
  return cards.GetCardsList(deck_id);
}

const CardsWithId QuizManager::GetCurrentCardsList() {
  return cards.GetCardsList(deck_id_);
}

const int QuizManager::GetCurrentDeckSize() {
  return study_deck_.size();
}

const std::wstring QuizManager::GetQuestion() {
  return GetCard().first;
}

const std::wstring QuizManager::GetAnswer() {
  return GetCard().second;
}

void QuizManager::SetCurrentDeck(const std::string& deck_id) {
  deck_id_ = deck_id;
  study_deck_ = cards.GetShuffledDeck(deck_id_);
}

const void QuizManager::RenameCurrentDeck(const std::string& deck_id, const std::wstring& new_name) {
  cards.RenameDeck(deck_id, new_name);
}

const void QuizManager::AddToDeck(const int& card_id, const std::string& deck_id) {
  cards.AddToDeck(card_id, deck_id);
}

const void QuizManager::RemoveFromDeck(const int& card_id, const std::string& deck_id) {
  cards.RemoveFromDeck(card_id, deck_id);
}

const bool QuizManager::CheckUserAnswer(const std::wstring& user_ans, const std::wstring& card_ans) {
  return user_ans == card_ans;
}

const void QuizManager::CreateDeck(const std::wstring& deck_name) {
  cards.CreateDeck(deck_name);
}

const void QuizManager::DeleteDeck(const std::string& deck_id) {
  cards.DeleteDeck(deck_id);
}