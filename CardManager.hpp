
#include <nlohmann/json.hpp>

#include <unordered_map>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::string, std::string>;
using CardsContainer = std::vector<Flashcard>;

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

  const json ReadFromCardsFile();
  const void WriteToCardsFile(json& data);

  const int RandomNum(const int& max_n);
  const int EncodeName(std::string& deck_name);

  const void CreateDeck(std::string& deck_name);
  const int GetDeckId(std::string& deck_name);
  std::vector<std::string> GetAllDecks();

  CardsContainer GetDeck(const int& deck_id);

  const void AddToDeck(int card_id, int deck_id);
  const void RemoveFromDeck(int card_id, int deck_id);
  const void RenameDeck(std::string previous_name, std::string new_name);
};