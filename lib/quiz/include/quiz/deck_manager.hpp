#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using CardsContainer = std::vector<std::pair<std::wstring, std::wstring>>;
using DeckContainer = std::vector<std::pair<std::string, std::wstring>>;

/*! 
* @brief Класс управления карточками
* 
* Позволяет загружать данные из файла по умолчанию 
* и настраивать колоды из карточек
*/
class DeckManager {
private:
  std::string path_to_file_ = "cards.json";

public:
  /*!
  * Конструктор по умолчанию
  */
  DeckManager();

  /*!
  * Деструктор по умолчанию
  */
  ~DeckManager();

  /*!
  * @brief Читает данные из JSON-файла
  * 
  * @return Десериализованный JSON объект
  * 
  * @throw std::ifstream::failure В случае возникновения
  * ошибки открытия/чтения файла
  */
  const json ReadFromCardsFile();

  /*!
  * @brief Записывает данные в JSON-файл
  * 
  * @throw std::ifstream::failure В случае возникновения
  * ошибки открытия/записи в файл
  */
  const void WriteToCardsFile(json& data);

  /// @private
  int RandomNum(int& max_n);

  /// @private
  std::string EncodeName(std::wstring& deck_name); 

  /*! 
  * @brief Создаёт колоду с данным названием
  * @param deck_name Название новой колоды
  */
  const void CreateDeck(std::wstring& deck_name);

  /*!
  * @brief Получает название колоды
  * @param deck_id Идентификатор колоды
  * @return Название колоды, соответствующее данному идентификатору
  */
  const std::wstring GetNameFromId(std::string& deck_id);

  /*!
  * @brief Получает все имеющиеся колоды
  * @return Массив пар из всех колод и их идентификаторов
  */
  const DeckContainer GetAllDecks();

  /*!
  * @brief Получает карточки из колоды
  * @param deck_id Идентификатор колоды
  * @return Массив пар карточек вида "вопрос - ответ" из данной колоды
  */
  const CardsContainer GetDeck(std::string& deck_id);

  /*!
  * @brief Получает название колоды
  * @param deck_id Идентификатор колоды
  * @return Возвращает название колоды, соответствующей
  * данному идентификатору
  */
  const std::wstring GetDeckNameFromId(std::string& deck_id);

  /// @private
  const void AddToDeck(const int& card_id, std::string& deck_id);
  /// @private
  const void RemoveFromDeck(const int& card_id, std::string& deck_id);

  /*!
  * @brief Меняет название колоды
  * @param deck_id Идентификатор колоды
  * @param new_name Новое название колоды
  */
  const void RenameDeck(const std::string& deck_id, std::wstring& new_name);
};