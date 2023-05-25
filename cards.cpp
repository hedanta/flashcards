
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <unordered_map>

using json = nlohmann::ordered_json;
using CardsContainer = std::unordered_map<std::string, std::string>;

// управление колодами
class DeckManager : CardManager{
private:
  std::string deck_name_ = "All";
  CardsContainer deck_cards_;
  CardManager cards;

public:
  DeckManager() = default;
  DeckManager(const DeckManager&) {};
  DeckManager(std::string& deck_name)
    : deck_name_{ deck_name },
    deck_cards_{}
  {};

  DeckManager& operator=(const DeckManager&) = default;

  ~DeckManager() = default;

  CardsContainer& GetCards(std::string& deck_name);
};

// получение карточек из колоды
CardsContainer& DeckManager::GetCards(std::string& deck_name) {
  std::ifstream file;
  file.exceptions(std::ifstream::badbit);

  try {
    file.open(cards.path_to_file_);
    json json_obj = json::parse(file);
    for (auto& el : json_obj["cards"].items()) {
      for (auto& deck_el : el.value()["deck"].items()) {
        if (deck_el.value() == deck_name) {
          deck_cards_.insert({ el.value()["question"], el.value()["answer"] });
        }
      }
    }
  }
  
  catch (std::ifstream::failure& e) {
    std::cerr << "Exception opening/reading/closing file\n";
  }

  file.close();
}

// изучение колоды карточек
class CardLearner {
private:
  DeckManager current_deck_;

public:
  void LoadCards(std::string& deck_name);
};

// загрузка колоды
void CardLearner::LoadCards(std::string& deck_name) {
  current_deck_ = DeckManager(deck_name);
}

// управление карточками
class CardManager {
private:
  std::string path_to_file_ = "cards.json";

public:
  CardManager() {
    path_to_file_ = "cards.json";
  }

  CardManager(const CardManager&) {};

  CardManager(std::string& path)
    : path_to_file_{ path }
  {}

  ~CardManager() = default;

  json ReadFromCardsFile(std::string& path);
  void WriteToCardsFile(std::string& path, json& data);

  void AddToDeck(int card_id, std::string deck_name);
  void RemoveFromDeck(int card_id, std::string deck_name);
};

// чтение из json
json CardManager::ReadFromCardsFile(std::string& path) {
  std::ifstream cards_file(path);
  json data = json::parse(cards_file);
  cards_file.close();
  return data;
}

// запись в json
void CardManager::WriteToCardsFile(std::string& path, json& data) {
  std::ofstream cards_edit(path);
  cards_edit << std::setw(2) << data << std::endl;
  cards_edit.close();
}

// добавление карточки в колоду
void CardManager::AddToDeck(int card_id, std::string deck_name) {
  json data = CardManager::ReadFromCardsFile(path_to_file_);

  data["cards"][card_id]["deck"].push_back(deck_name);

  CardManager::WriteToCardsFile(path_to_file_, data);
}

// удаление карточки из колоды
void CardManager::RemoveFromDeck(int card_id, std::string deck_name) {
  json data = CardManager::ReadFromCardsFile(path_to_file_);

  // количество колод, в которых есть карточка
  int deck_count = data["cards"][card_id]["deck"].size();

  // ищем индекс колоды, чтобы стереть её
  bool deleted = 0;
  for (int deck_idx = 0; deck_idx < deck_count; deck_idx += 1) {
    if (data["cards"][card_id]["deck"][deck_idx] == deck_name) {
      data["cards"][card_id]["deck"].erase(deck_idx);
      deleted = 1;
      break;
    }
  }

  CardManager::WriteToCardsFile(path_to_file_, data);
}

int main() {
  CardManager test;
  test.AddToDeck(1, "maths");
  test.RemoveFromDeck(1, "hehe");
  return 0;
}
