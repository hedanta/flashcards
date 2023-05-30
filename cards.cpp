
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <random>
#include <unordered_map>

using json = nlohmann::ordered_json;
using CardsContainer = std::unordered_map<std::string, std::string>;
using Flashcard = std::pair<std::string, std::string>;

namespace {
  CardsContainer GetDeck(const int deck_id) {
    std::ifstream file;
    file.exceptions(std::ifstream::badbit);

    CardsContainer current_deck{};

    try {
      file.open("cards.json");
      json data = json::parse(file);

      for (auto& el : data["cards"].items()) {
        for (auto& deck_el : el.value()["deck"].items()) {
          if (deck_el.value() == deck_id) {
            current_deck.insert(std::make_pair( el.value()["question"], el.value()["answer"] ));
          }
        }
      }
    }

    catch (std::ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }

    file.close();
    return current_deck;
  }

  int RandomNum(int max_n) {
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<> dis(0, max_n);

    int num = dis(gen);

    return num;
  }

  int Encrypt(std::string& msg) {
    return RandomNum(RandomNum(12345));
  }
}

// управление карточками
class CardManager {
private:
  std::string path_to_file_ = "cards.json";

public:
  CardManager() = default;

  CardManager(const CardManager&) {};

  CardManager(std::string& path)
    : path_to_file_{ path }
  {};

  ~CardManager() = default;

  json ReadFromCardsFile();
  void WriteToCardsFile(json& data);

  void CreateDeck(std::string& deck_name);
  int GetDeckId(std::string& deck_name);

  void AddToDeck(int card_id, int deck_id);
  void RemoveFromDeck(int card_id, int deck_id);
  void RenameDeck(std::string previous_name, std::string new_name);
};

// изучение колоды карточек
class CardLearner {
private:
  CardManager cards;
  std::string deck_name_{ "All" };
  CardsContainer study_deck_{ GetDeck(cards.GetDeckId(deck_name_)) };

  // bool show_result_{ 1 };
  // мб параметр показа результата надо задать не тут

public:
  CardLearner() = default;

  CardLearner(std::string& deck_name)
    : cards{}
    , deck_name_{deck_name}
    , study_deck_{ GetDeck(cards.GetDeckId(deck_name)) }
  {};

  const int GetDeckSize() {  return study_deck_.size();  }

  Flashcard GetCard();

  bool CheckUserAnswer(std::string& user_ans, std::string& card_ans);
};

Flashcard CardLearner::GetCard() {
  int deck_size = CardLearner::GetDeckSize();
  Flashcard card;

  if (deck_size > 0) {
    auto card_it = std::next(study_deck_.begin(), RandomNum(deck_size - 1));
    card = { card_it->first, card_it->second };
    study_deck_.erase(card_it);
  }

  return card;
}

bool CardLearner::CheckUserAnswer(std::string& user_ans, std::string& card_ans) {
  return user_ans == card_ans;
}

// чтение из json
json CardManager::ReadFromCardsFile() {
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
void CardManager::WriteToCardsFile(json& data) {
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

// создание колоды
void CardManager::CreateDeck(std::string& deck_name) {
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
    int deck_enc = Encrypt(deck_name);
    json edits = { std::make_pair(deck_name, deck_enc) };
    data["decks"].insert(edits.begin(), edits.end());
  }

  WriteToCardsFile(data);
}

// it is what it is
int CardManager::GetDeckId(std::string& deck_name) {
  json data = ReadFromCardsFile();

  for (auto& it : data["decks"].items()) {
    if (it.key() == deck_name) {
      return it.value();
    }
  }
}

// добавление карточки в колоду
void CardManager::AddToDeck(int card_id, int deck_id) {
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
void CardManager::RemoveFromDeck(int card_id, int deck_id) {
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

void CardManager::RenameDeck(std::string previous_name, std::string new_name) {
  json data = ReadFromCardsFile();

  const auto deck_it = data.find(previous_name);
  if (deck_it != data.end()) {
    std::swap(data[new_name], *deck_it);
    data.erase(deck_it);
  }
  
  WriteToCardsFile(data);
}

int main() {
  CardManager test;
  
  std::string deck = "Maths";
  int deck_id = test.GetDeckId(deck);
  test.AddToDeck(0, deck_id);
  test.AddToDeck(5, deck_id);

  CardLearner quiz(deck);
  int deck_size = quiz.GetDeckSize();

  for (int i = 0; i < deck_size; i += 1) {
    Flashcard current_card = quiz.GetCard();
    std::cout << "The question is: " << current_card.first << ", the answer is: " << current_card.second << '\n';
  }

  return 0;
}
