#include "deck_manager.hpp"

#include <nlohmann/json.hpp>

#include <codecvt>
#include <random>

using json = nlohmann::ordered_json;
using Flashcard = std::pair<std::wstring, std::wstring>;
using CardsContainer = std::vector<Flashcard>;

namespace {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
}


/*!
* @brief Класс изучения карточек
* 
* Позволяет чето.
*/
class CardManager {
public:
  DeckManager cards;

private:
  std::string deck_id_{ "0" };
  CardsContainer study_deck_{ cards.GetDeck(deck_id_) };
  Flashcard current_card_;

public:
  CardManager(); ///< Конструктор по умолчанию

  /*!
  * @brief Конструктор по идентифицатору колоды
  * 
  * Создаёт экземпляр класса, в котором данная
  * колода является текущей
  * 
  * @param deck_id Идентификатор колоды
  */
  CardManager(std::string& deck_id)
    : cards{}
    , deck_id_{deck_id}
    , study_deck_{ cards.GetDeck(deck_id_) }
    , current_card_{}
  {};

  ~CardManager(); ///< Деструктор по умолчанию
  
  /*!
  * @brief Устанавливает текущую колоду
  * 
  * Устанавливает в качестве текущей колоду,
  * соответствующую данному идентификатору
  * @param deck_id Идентификатор колоды
  */
  void SetCurrentDeck(std::string& deck_id);

  std::wstring GetDeckName();
  std::wstring GetDeckNameFromId(std::string& deck_id);

  /*!
  * @brief Получает идентификатор колоды
  * @return Возвращает идентификатор текущей колоды
  */
  std::string GetDeckId();

  /*!
  * @brief Получает размер колоды
  * @return Возвращает размер текущей колоды
  */
  const int GetDeckSize();

  /*!
  * @brief Получает карточку
  * @return Возвращает пару "вопрос - ответ"
  */
  Flashcard GetCard();

  /*!
  * @brief Получает вопрос
  * @return Возвращает вопрос из карточки
  */
  std::wstring GetQuestion();

  /*!
  * @brief Получает ответ
  * @return Возвращает ответ из карточки
  */
  std::wstring GetAnswer();
  
  /*!
  * @brief Проверяет ответ
  * 
  * Проверяет данный пользователем ответ
  * @param user_ans Ответ пользователя
  * @param card_ans Ожидаемый ответ из карточки
  * @return Возвращает True, если ответ пользователя верный, 
  * в противном случае False
  */
  const bool CheckUserAnswer(std::wstring& user_ans, std::wstring& card_ans);

  /// @private
  void EraseCurrentCard();
};