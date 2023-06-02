#include "CardManager.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::string, std::string>;
using CardsContainer = std::vector<Flashcard>;

// чтение из json
const json CardManager::ReadFromCardsFile() {
  std::ifstream cards_file;
  cards_file.exceptions(std::ifstream::badbit);

  json data;

  try {
    cards_file.open(path_to_file_);
    data = json::parse(cards_file);
  }

  catch (std::ifstream::failure& e) {
    std::cerr << "Exception opening/reading file" << std::endl;
  }

  cards_file.close();
  return data;
}

// запись в json
const void CardManager::WriteToCardsFile(json& data) {
  std::ofstream cards_edit;
  cards_edit.exceptions(std::ofstream::badbit);

  try {
    cards_edit.open(path_to_file_);
    cards_edit << std::setw(2) << data << std::endl;
  }

  catch (std::ofstream::failure const &e) {
    std::cerr << "Exception opening/writing to file" << std::endl;
  }

  cards_edit.close();
}

const int CardManager::RandomNum(const int& max_n) {
  std::random_device random;
  std::mt19937 gen(random());
  std::uniform_int_distribution<> dis(0, max_n);

  int num = dis(gen);

  return num;
}

const int CardManager::EncodeName(std::string& deck_name) {
	return RandomNum(RandomNum(12345));
}

// создание колоды
const void CardManager::CreateDeck(std::string& deck_name) {
  json data = ReadFromCardsFile();

  // setting deck id
  bool found = false;
  for (auto& it : data["decks"].items()) {
    if (it.key() == deck_name && !found) {
      std::cerr << "This deck already exists!" << std::endl;
      found = true;
    }
  }

  if (!found) {
    int deck_enc = EncodeName(deck_name);
    json edits = { std::make_pair(deck_name, deck_enc) };
    data["decks"].insert(edits.begin(), edits.end());
  }

  WriteToCardsFile(data);
}

const int CardManager::GetDeckId(std::string& deck_name) {
  json data = ReadFromCardsFile();

  for (auto& it : data["decks"].items()) {
    if (it.key() == deck_name) {
      return it.value();
    }
  }
}

CardsContainer CardManager::GetDeck(const int& deck_id) {
	std::ifstream file;
    file.exceptions(std::ifstream::badbit);

    CardsContainer deck{};

    try {
      file.open("cards.json");
      json data = json::parse(file);

      for (auto& el : data["cards"].items()) {
        for (auto& deck_el : el.value()["deck"].items()) {
          if (deck_el.value() == deck_id) {
            deck.push_back(std::make_pair( el.value()["question"], el.value()["answer"] ));
          }
        }
      }

      std::random_device rd;
      std::mt19937 g(rd());
      
      std::shuffle(deck.begin(), deck.end(), g);
    }

    catch (std::ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }

    file.close();
    return deck;
}

std::vector<std::string> CardManager::GetAllDecks() {
  json data = ReadFromCardsFile();

  std::vector<std::string> decks;

  for (auto& it : data["decks"].items()) {
    decks.push_back(it.key());
  }

  return decks;
}

// добавление карточки в колоду
const void CardManager::AddToDeck(int card_id, int deck_id) {
  json data = ReadFromCardsFile();

  bool found = false;
  for (auto& it : data["cards"][card_id]["deck"].items()) {
    if (it.value() == deck_id && !found) {
      std::cerr << "The card is already in the deck!" << std::endl;
      found = true;
    }
  }

  if (!found) {
    data["cards"][card_id]["deck"].push_back(deck_id);
  }

  WriteToCardsFile(data);
}

// удаление карточки из колоды
const void CardManager::RemoveFromDeck(int card_id, int deck_id) {
  json data = ReadFromCardsFile();

  // количество колод, в которых есть карточка
  int deck_count = data["cards"][card_id]["deck"].size();

  // ищем индекс колоды, чтобы стереть её
  for (int deck_idx = 0; deck_idx < deck_count; deck_idx += 1) {
    if (data["cards"][card_id]["deck"][deck_idx] == deck_id) {
      data["cards"][card_id]["deck"].erase(deck_idx);
      break;
    }
  }

  WriteToCardsFile(data);
}

const void CardManager::RenameDeck(std::string previous_name, std::string new_name) {
  json data = ReadFromCardsFile();

  const auto deck_it = data.find(previous_name);
  if (deck_it != data.end()) {
    std::swap(data[new_name], *deck_it);
    data.erase(deck_it);
  }
  
  WriteToCardsFile(data);
}