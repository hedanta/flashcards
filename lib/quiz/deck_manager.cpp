#include <quiz/deck_manager.hpp>

#include <algorithm>
#include <codecvt>
#include <iostream>
#include <fstream>
#include <random>

namespace {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
}

DeckManager::DeckManager() = default;

const json DeckManager::ReadFromCardsFile() {
  setlocale(LC_ALL, "ru");
  std::ifstream cards_file;
  cards_file.exceptions(std::ifstream::badbit);

  json data;

  try {
    cards_file.open(path_to_file_);
    data = json::parse(cards_file);
  }

  catch (std::ifstream::failure& e) {
    throw std::ifstream::badbit;
  }

  cards_file.close();
  return data;
}

const void DeckManager::WriteToCardsFile(const json& data) {
  std::ofstream cards_edit;
  cards_edit.exceptions(std::ofstream::badbit);

  try {
    cards_edit.open(path_to_file_);
    cards_edit << std::setw(2) << data << std::endl;
  }

  catch (std::ofstream::failure const &e) {
    throw std::ofstream::badbit;
  }

  cards_edit.close();
}

 int DeckManager::RandomNum(int& max_n) {
  std::random_device random;
  std::mt19937 gen(random());
  std::uniform_int_distribution<> dis(0, max_n);

  int num = dis(gen);

  return num;
}

std::string DeckManager::EncodeName(const std::wstring& deck_name) {
  int max_n = 12345;
	return std::to_string(RandomNum(max_n));
}

const void DeckManager::CreateDeck(const std::wstring& deck_name) {
  json data = ReadFromCardsFile();

  bool found = false;
  std::wstring w_deck;
  for (auto& it : data["decks"].items()) {
    w_deck = Converter.from_bytes(it.value());

    if (w_deck == deck_name && !found) {
      std::cerr << "This deck already exists!" << std::endl;
      found = true;
    }
  }

  if (!found) {
    std::string deck_enc = EncodeName(deck_name);
    std::string deck_name_utf = Converter.to_bytes(deck_name);
    json edits = { std::make_pair(deck_enc, deck_name_utf) };
    data["decks"].insert(edits.begin(), edits.end());
  }

  WriteToCardsFile(data);
}

const std::wstring DeckManager::GetNameFromId(const std::string& deck_id) {
  json data = ReadFromCardsFile();

  std::wstring deck_name = L"";

  for (auto& it : data["decks"].items()) {
    if (deck_id == it.key()) {
      deck_name = Converter.from_bytes(it.value());
      break;
    }
  }

  return deck_name;
}

const CardsContainer DeckManager::GetShuffledDeck(const std::string& deck_id) {
	std::ifstream file;
    file.exceptions(std::ifstream::badbit);

    CardsContainer deck{};

    try {
      file.open("cards.json");
      json data = json::parse(file);

      for (auto& el : data["cards"].items()) {
        std::wstring w_quest = Converter.from_bytes(el.value()["question"]);
        std::wstring w_ans = Converter.from_bytes(el.value()["answer"]);

        for (auto& deck_el : el.value()["deck"].items()) {
          if (deck_el.value() == deck_id) {
            deck.push_back(std::make_pair(w_quest, w_ans));
          }
        }
      }
    }

    catch (std::ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);

    file.close();
    return deck;
}

const CardsWithId DeckManager::GetCardsList(const std::string& deck_id) {
  std::ifstream file;
  file.exceptions(std::ifstream::badbit);

  CardsWithId cards_list{};

  try {
    file.open("cards.json");
    json data = json::parse(file);

    for (auto& el : data["cards"].items()) {
      const int card_id = el.value()["id"];
      std::wstring w_quest = Converter.from_bytes(el.value()["question"]);

      for (auto& deck_el : el.value()["deck"].items()) {
        if (deck_el.value() == deck_id) {
          cards_list.push_back(std::make_pair(card_id, w_quest));
        }
      }
    }
  }

  catch (std::ifstream::failure& e) {
    std::cerr << "Exception opening/reading file" << std::endl;
  }

  file.close();
  return cards_list;
}


const DeckContainer DeckManager::GetAllDecks() {
  json data = ReadFromCardsFile();

  std::vector<std::pair<std::string, std::wstring>> decks;
  std::wstring w_deck;

  for (auto& it : data["decks"].items()) {
    w_deck = Converter.from_bytes(it.value());
    decks.push_back(std::make_pair(it.key(), w_deck));
  }

  return decks;
}

const std::wstring DeckManager::GetDeckNameFromId(const std::string& deck_id) {
  return GetNameFromId(deck_id);
}

const void DeckManager::AddToDeck(const int& card_id, const std::string& deck_id) {
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

const void DeckManager::RemoveFromDeck(const int& card_id, const std::string& deck_id) {
  json data = ReadFromCardsFile();

  // количество колод, в которых есть карточка
  int deck_count = data["cards"][card_id]["deck"].size();

  // ищем индекс колоды, чтобы стереть её
  for (auto it = data["cards"][card_id]["deck"].begin(); it != data["cards"][card_id]["deck"].end();) {
    if (*it == deck_id) {
      it = data["cards"][card_id]["deck"].erase(it);
      break;
    }

    it += 1;
  }

  WriteToCardsFile(data);
}

const void DeckManager::RenameDeck(const std::string& deck_id, const std::wstring& w_new_name) {
  json data = ReadFromCardsFile();

  std::string new_name = Converter.to_bytes(w_new_name);

  data["decks"].at(deck_id) = new_name;
  
  WriteToCardsFile(data);
}

const void DeckManager::DeleteDeck(const std::string& deck_id) {
  json data = ReadFromCardsFile();

  auto it = data["decks"].find(deck_id);
  data["decks"].erase(it);

  int cards_cnt = data["cards"].size();

  for (int i = 0; i < cards_cnt; i += 1) {
    RemoveFromDeck(i, deck_id);
  }

  WriteToCardsFile(data);
}